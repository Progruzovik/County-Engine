#include <CE/Core/Act.hpp>
#include <CE/UI/Parameters.hpp>
#include <SFML/Window/Mouse.hpp>

namespace ce {

Act::Act(Stage *stage, ContentMode contentMode, const sf::Color &bgColor)
    : Speaker(stage), bgColor(bgColor), root(RootNode(stage)), contentMode(contentMode),
      savedMousePosition(sf::Mouse::getPosition(root.getWindow())),
      isMouseOnIt(root.checkMouseOnIt(savedMousePosition)) {}

void Act::onMouseEntered()
{
    isMouseOnIt = true;
}

void Act::onMouseLeft()
{
    isMouseOnIt = false;
    root.onMouseLeft();
}

void Act::onLeftMouseButtonPressed()
{
    root.onLeftMouseButtonPressed();
}

void Act::onLeftMouseButtonReleased()
{
    root.onLeftMouseButtonReleased();
}

void Act::onRightMouseButtonPressed()
{
    if (contentMode == ContentMode::MOVABLE_BY_MOUSE) {
        isRightMouseButtonPressed = true;
        isMouseMovedWithRightButton = false;
    }
}

void Act::onRightMouseButtonReleased()
{
    if (contentMode == ContentMode::MOVABLE_BY_MOUSE) {
        isRightMouseButtonPressed = false;
        if (!isMouseMovedWithRightButton) {
            root.onRightMouseButtonReleased();
        }
    } else {
        root.onRightMouseButtonReleased();
    }
}

const sf::Color &Act::getBgColor() const
{
    return bgColor;
}

void Act::setUpNodes()
{
    const float fullLeftIndent = leftUi ? leftUi->getWidth() : 0;
    const float fullTopIndent = topUi ? topUi->getHeight() : 0;

    float freeWidth = root.getWindow().getSize().x - fullLeftIndent;
    if (leftUi) {
        leftUi->setY(fullTopIndent);
    }
    if (rightUi) {
        rightUi->setPos(root.getWindow().getSize().x - rightUi->getWidth(), fullTopIndent);
        freeWidth -= rightUi->getWidth();
    }

    if (topUi) {
        topUi->setX(fullLeftIndent);
    }
    float freeHeight = root.getWindow().getSize().y - fullTopIndent;
    if (bottomUi) {
        bottomUi->setPos(fullLeftIndent, root.getWindow().getSize().y - bottomUi->getHeight());
        freeHeight -= bottomUi->getHeight();
    }

    if (content) {
        if (contentMode == ContentMode::STATIC) {
            content->setScale(std::min(freeWidth / content->getWidth(), freeHeight / content->getHeight()));
            content->setOrigin(content->getHalfX(), content->getHalfY());
            content->setPos(fullLeftIndent + freeWidth / 2, fullTopIndent + freeHeight / 2);
        } else {
            content->setScale(Parameters::get().getK());
        }
    }
}

void Act::update()
{
    resizeUi();
    root.update();

    if (isMouseOnIt && root.getWindow().hasFocus()) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(root.getWindow());
        root.select(mousePosition);

        if (contentMode == ContentMode::MOVABLE_BY_MOUSE) {
            sf::Vector2i offset;
            if (isRightMouseButtonPressed) {
                offset.x += mousePosition.x - savedMousePosition.x;
                offset.y += mousePosition.y - savedMousePosition.y;
                if (std::abs(offset.x) + std::abs(offset.y) > 10) {
                    isMouseMovedWithRightButton = true;
                }
            }
            savedMousePosition.x = mousePosition.x;
            savedMousePosition.y = mousePosition.y;
            const unsigned int activeArea = Parameters::get().getIndent() / 2;
            if (savedMousePosition.x < activeArea) {
                offset.x += SCROLL_SPEED * Parameters::get().getK();
            } else if (savedMousePosition.x > root.getWindow().getSize().x - activeArea) {
                offset.x -= SCROLL_SPEED * Parameters::get().getK();
            }
            if (savedMousePosition.y < activeArea) {
                offset.y += SCROLL_SPEED * Parameters::get().getK();
            } else if (savedMousePosition.y > root.getWindow().getSize().y - activeArea) {
                offset.y -= SCROLL_SPEED * Parameters::get().getK();
            }
            content->move(offset.x, offset.y);
        }
    }
    if (contentMode == ContentMode::CENTERED_ON_NODE) {
        sf::Vector2u windowSize = root.getWindow().getSize();
        sf::Vector2f offset((center->getHalfX() - content->getOriginX()) * content->getScale(),
                            (center->getHalfY() - content->getOriginY()) * content->getScale());
        AbstractNode *currentNode = center;
        while (currentNode != content) {
            offset.x += (currentNode->getX() - currentNode->getOriginX()) * content->getScale();
            offset.y += (currentNode->getY() - currentNode->getOriginY()) * content->getScale();
            currentNode = currentNode->getParent();
        }
        content->setPos(windowSize.x / 2 - offset.x, windowSize.y / 2 - offset.y);
    }

    root.draw();
}

void Act::setCenter(AbstractNode *value)
{
    center = value;
}

void Act::setContent(AbstractNode *value)
{
    if (content) {
        root.removeContent(content);
    }
    content = value;
    root.addContent(content);
    setUpNodes();
}

void Act::setLeftUi(AbstractNode *value)
{
    updateUi(leftUi, value);
    leftUi = value;
    setUpNodes();
}

void Act::setRightUi(AbstractNode *value)
{
    updateUi(rightUi, value);
    rightUi = value;
    setUpNodes();
}

void Act::setTopUi(AbstractNode *value)
{
    updateUi(topUi, value);
    topUi = value;
    setUpNodes();
}

void Act::setBottomUi(AbstractNode *value)
{
    updateUi(bottomUi, value);
    bottomUi = value;
    setUpNodes();
}

void Act::updateUi(AbstractNode *oldUi, AbstractNode *newUi)
{
    if (oldUi) {
        root.removeChild(oldUi);
    }
    if (newUi) {
        root.addChild(newUi);
    }
}

}
