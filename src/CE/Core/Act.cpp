#include <CE/Core/Act.hpp>
#include <CE/UI/Parameters.hpp>

namespace ce {

Act::Act(Stage *stage, ContentMode contentMode, const sf::Color &bgColor)
    : Speaker(stage), bgColor(bgColor), contentMode(contentMode), root(RootNode(stage)) {}

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
    sf::Vector2i currentMousePosition = root.select();
    if (contentMode == ContentMode::MOVABLE_BY_MOUSE && root.checkMouseOnIt(currentMousePosition) && content) {
        sf::Vector2i offset;
        if (isRightMouseButtonPressed) {
            offset.x += currentMousePosition.x - mousePosition.x;
            offset.y += currentMousePosition.y - mousePosition.y;
            if (std::abs(offset.x) + std::abs(offset.y) > 10) {
                isMouseMovedWithRightButton = true;
            }
        }
        mousePosition.x = (unsigned int) currentMousePosition.x;
        mousePosition.y = (unsigned int) currentMousePosition.y;
        const unsigned int activeArea = Parameters::get().getIndent() / 2;
        if (mousePosition.x < activeArea) {
            offset.x += SCROLL_SPEED * Parameters::get().getK();
        } else if (mousePosition.x > root.getWindow().getSize().x - activeArea) {
            offset.x -= SCROLL_SPEED * Parameters::get().getK();
        }
        if (mousePosition.y < activeArea) {
            offset.y += SCROLL_SPEED * Parameters::get().getK();
        } else if (mousePosition.y > root.getWindow().getSize().y - activeArea) {
            offset.y -= SCROLL_SPEED * Parameters::get().getK();
        }
        content->move(offset.x, offset.y);
    } else if (contentMode == ContentMode::CENTERED_ON_NODE) {
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
        root.removeContent(content, true);
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

void Act::removeContent(bool toDelete)
{
    if (content) {
        root.removeContent(content, toDelete);
        content = nullptr;
    }
}

void Act::updateUi(AbstractNode *oldUi, AbstractNode *newUi)
{
    if (oldUi) {
        root.removeChild(oldUi, true);
    }
    if (newUi) {
        root.addChild(newUi);
    }
}

}
