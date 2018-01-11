#include <CE/Core/Act.hpp>
#include <CE/constant.hpp>
#include <SFML/Window/Mouse.hpp>

namespace ce {

Act::Act(Mode contentMode, Stage &stage, const sf::Color &bgColor)
    : bgColor(bgColor), contentMode(contentMode), savedMousePosition(sf::Mouse::getPosition(stage)), stage(stage) {}

void Act::onMouseMoved(const sf::Vector2i &mousePosition)
{
    std::shared_ptr<Node> newSelectedNode = select(mousePosition);
    if (selectedNode != newSelectedNode) {
        if (selectedNode) {
            selectedNode->onMouseLeft();
        }
        selectedNode = newSelectedNode;
        if (selectedNode) {
            selectedNode->onMouseEntered();
        }
    }
    if (selectedNode) {
        selectedNode->onMouseMoved(mousePosition);
    }

    if (contentMode == Mode::MOVABLE_BY_MOUSE) {
        if (isRightMouseButtonPressed) {
            sf::Vector2i offset(mousePosition.x - savedMousePosition.x, mousePosition.y - savedMousePosition.y);
            if (std::abs(offset.x) + std::abs(offset.y) > 10) {
                isMouseMovedWithRightButton = true;
            }
            content->move(offset.x, offset.y);
        }
        savedMousePosition = mousePosition;
    }
}

void Act::onMouseLeft()
{
    if (selectedNode) {
        selectedNode->onMouseLeft();
        selectedNode.reset();
    }
}

void Act::onLeftMouseButtonPressed()
{
    if (selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onLeftMouseButtonPressed();
        } else {
            selectedNode.reset();
        }
    }
}

void Act::onLeftMouseButtonReleased()
{
    if (selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onLeftMouseButtonReleased();
        } else {
            selectedNode.reset();
        }
    }
}

void Act::onRightMouseButtonPressed()
{
    if (contentMode == Mode::MOVABLE_BY_MOUSE) {
        isRightMouseButtonPressed = true;
        isMouseMovedWithRightButton = false;
    }
}

void Act::onRightMouseButtonReleased()
{
    if (contentMode == Mode::MOVABLE_BY_MOUSE) {
        isRightMouseButtonPressed = false;
    }

    if (!isMouseMovedWithRightButton && selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onRightMouseButtonReleased();
        } else {
            selectedNode.reset();
        }
    }
}

const sf::Color &Act::getBgColor() const
{
    return bgColor;
}

const sf::Transform &Act::getCombinedTransform()
{
    return mockTransform;
}

const sf::Window &Act::getWindow() const
{
    return stage;
}

void Act::setCenter(const std::shared_ptr<TransformableNode> &value)
{
    center = value;
}

void Act::setContent(const std::shared_ptr<TransformableNode> &value)
{
    if (!contentLayer->getParent()) {
        addChild(contentLayer);
    }
    if (content) {
        contentLayer->removeChild(content);
    }
    content = value;
    contentLayer->addChild(content);
    setUpNodes();
}

void Act::setLeftUi(const std::shared_ptr<TransformableNode> &value)
{
    updateUi(leftUi, value);
    leftUi = value;
}

void Act::setRightUi(const std::shared_ptr<TransformableNode> &value)
{
    updateUi(rightUi, value);
    rightUi = value;
}

void Act::setTopUi(const std::shared_ptr<TransformableNode> &value)
{
    updateUi(topUi, value);
    topUi = value;
}

void Act::setBottomUi(const std::shared_ptr<TransformableNode> &value)
{
    updateUi(bottomUi, value);
    bottomUi = value;
}

void Act::setOverlayUi(const std::shared_ptr<TransformableNode> &value)
{
    updateUi(overlayUi, value);
    overlayUi = value;
}

void Act::setUpNodes()
{
    resizeUi();
    const float fullLeftIndent = leftUi ? leftUi->getWidth() : 0;
    const float fullTopIndent = topUi ? topUi->getHeight() : 0;

    if (leftUi) {
        leftUi->setY(fullTopIndent);
    }
    float freeWidth = stage.getSize().x - fullLeftIndent;
    if (rightUi) {
        rightUi->setPos(stage.getSize().x - rightUi->getWidth(), fullTopIndent);
        freeWidth -= rightUi->getWidth();
    }

    if (topUi) {
        topUi->setX(fullLeftIndent);
    }
    float freeHeight = stage.getSize().y - fullTopIndent;
    if (bottomUi) {
        bottomUi->setPos(fullLeftIndent, stage.getSize().y - bottomUi->getHeight());
        freeHeight -= bottomUi->getHeight();
    }

    if (contentMode == Mode::STATIC) {
        contentLayer->setScale(std::min(freeWidth / contentLayer->getWidth(), freeHeight / contentLayer->getHeight()));
        contentLayer->setOrigin(contentLayer->getHalfX(), contentLayer->getHalfY());
        contentLayer->setPos(fullLeftIndent + freeWidth / 2, fullTopIndent + freeHeight / 2);
    }
}

void Act::update()
{
    Node::update();

    if (contentMode == Mode::MOVABLE_BY_MOUSE) {
        sf::Vector2i offset;
        const unsigned int activeArea = INDENT / 2;
        if (savedMousePosition.x < activeArea) {
            offset.x += SCROLL_SPEED;
        } else if (savedMousePosition.x > stage.getSize().x - activeArea) {
            offset.x -= SCROLL_SPEED;
        }
        if (savedMousePosition.y < activeArea) {
            offset.y += SCROLL_SPEED;
        } else if (savedMousePosition.y > stage.getSize().y - activeArea) {
            offset.y -= SCROLL_SPEED;
        }
        contentLayer->move(offset.x, offset.y);
    } else if (contentMode == Mode::CENTERED_ON_NODE) {
        sf::Vector2f offset = center->getCombinedTransform().transformPoint(0, 0);
        contentLayer->move(stage.getSize().x / 2 - offset.x, stage.getSize().y / 2 - offset.y);
    }

    drawToTarget(stage);
}

bool Act::checkPointOnIt(const sf::Vector2i &point)
{
    return point.x > 0 && point.x < stage.getSize().x && point.y > 0 && point.y < stage.getSize().y;
}

void Act::declareEvent(const sf::String &name)
{
    stage.onEvent(castSharedFromThis<Act>(), name);
}

void Act::updateUi(const std::shared_ptr<TransformableNode> &oldUi, const std::shared_ptr<TransformableNode> &newUi)
{
    if (!contentLayer->getParent()) {
        addChild(contentLayer);
    }
    if (oldUi) {
        removeChild(oldUi);
    }
    if (newUi) {
        addChild(newUi);
    }
}

}
