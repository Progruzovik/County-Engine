#include <CE/Core/AbstractAct.hpp>
#include <CE/UI/Parameters.hpp>

namespace ce {

AbstractAct::AbstractAct(Stage *stage, bool isScrollable, const sf::Color &bgColor)
    : Speaker(stage), bgColor(bgColor), isContentMovable(isScrollable), root(new RootNode(stage)) {}

void AbstractAct::onLeftMouseButtonPressed()
{
    root->onLeftMouseButtonPressed();
}

void AbstractAct::onLeftMouseButtonReleased()
{
    root->onLeftMouseButtonReleased();
}

void AbstractAct::onRightMouseButtonPressed()
{
    if (isContentMovable) {
        isRightMouseButtonPressed = true;
        isMouseMovedWithRightButton = false;
    }
}

void AbstractAct::onRightMouseButtonReleased()
{
    if (isContentMovable) {
        isRightMouseButtonPressed = false;
        if (!isMouseMovedWithRightButton) {
            root->onRightMouseButtonReleased();
        }
    } else {
        root->onRightMouseButtonReleased();
    }
}

const sf::Color &AbstractAct::getBgColor() const
{
    return bgColor;
}

void AbstractAct::setUpNodes()
{
    const float fullLeftIndent = leftUi ? leftUi->getWidth() : 0;
    const float fullTopIndent = topUi ? topUi->getHeight() : 0;

    float freeWidth = root->getWindow().getSize().x - fullLeftIndent;
    if (leftUi) {
        leftUi->setY(fullTopIndent);
    }
    if (rightUi) {
        rightUi->setPos(root->getWindow().getSize().x - rightUi->getWidth(), fullTopIndent);
        freeWidth -= rightUi->getWidth();
    }

    if (topUi) {
        topUi->setX(fullLeftIndent);
    }
    float freeHeight = root->getWindow().getSize().y - fullTopIndent;
    if (bottomUi) {
        bottomUi->setPos(fullLeftIndent, root->getWindow().getSize().y - bottomUi->getHeight());
        freeHeight -= bottomUi->getHeight();
    }

    if (content) {
        if (isContentMovable) {
            content->setScale(ce::Parameters::get().getK());
        } else {
            content->setScale(std::min(freeWidth / content->getWidth(), freeHeight / content->getHeight()));
            content->setOrigin(content->getCenterX(), content->getCenterY());
            content->setPos(fullLeftIndent + freeWidth / 2, fullTopIndent + freeHeight / 2);
        }
    }
}

void AbstractAct::update()
{
    resizeUi();
    root->update();
    sf::Vector2i currentMousePosition = root->select();
    if (isContentMovable && root->checkMouseOnIt(currentMousePosition) && content) {
        int moveX = 0, moveY = 0;
        if (isRightMouseButtonPressed) {
            moveX += currentMousePosition.x - mousePosition.x;
            moveY += currentMousePosition.y - mousePosition.y;
            if (std::abs(moveX) + std::abs(moveY) > 10) {
                isMouseMovedWithRightButton = true;
            }
        }
        mousePosition.x = (unsigned int) currentMousePosition.x;
        mousePosition.y = (unsigned int) currentMousePosition.y;
        const unsigned int activeArea = ce::Parameters::get().getIndent() / 2;
        if (mousePosition.x < activeArea) {
            moveX += SCROLL_SPEED * ce::Parameters::get().getK();
        } else if (mousePosition.x > root->getWindow().getSize().x - activeArea) {
            moveX -= SCROLL_SPEED * ce::Parameters::get().getK();
        }
        if (mousePosition.y < activeArea) {
            moveY += SCROLL_SPEED * ce::Parameters::get().getK();
        } else if (mousePosition.y > root->getWindow().getSize().y - activeArea) {
            moveY -= SCROLL_SPEED * ce::Parameters::get().getK();
        }
        content->move(moveX, moveY);
    }
    root->draw();
}

void AbstractAct::setContent(AbstractNode *value)
{
    if (content) {
        root->removeContent(content, true);
    }
    content = value;
    root->addContent(content);
    setUpNodes();
}

void AbstractAct::setLeftUi(AbstractNode *value)
{
    updateUi(leftUi, value);
    leftUi = value;
    setUpNodes();
}

void AbstractAct::setRightUi(AbstractNode *value)
{
    updateUi(rightUi, value);
    rightUi = value;
    setUpNodes();
}

void AbstractAct::setTopUi(AbstractNode *value)
{
    updateUi(topUi, value);
    topUi = value;
    setUpNodes();
}

void AbstractAct::setBottomUi(AbstractNode *value)
{
    updateUi(bottomUi, value);
    bottomUi = value;
    setUpNodes();
}

void AbstractAct::removeContent()
{
    if (content) {
        root->removeContent(content);
        content = nullptr;
    }
}

void AbstractAct::updateUi(AbstractNode *oldUi, AbstractNode *newUi)
{
    if (oldUi) {
        root->removeChild(oldUi, true);
    }
    if (newUi) {
        root->addChild(newUi);
    }
}

}
