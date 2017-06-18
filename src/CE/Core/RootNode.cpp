#include <CE/Core/RootNode.hpp>

namespace ce {

RootNode::RootNode(sf::RenderWindow &window) : window(window)
{
    addChild(contentLayer);
}

void RootNode::onMouseMoved(const sf::Vector2i &mousePosition)
{
    AbstractNode *result = select(mousePosition);
    if (selectedNode != result) {
        if (selectedNode) {
            selectedNode->onMouseLeft();
        }
        selectedNode = result;
        if (selectedNode) {
            selectedNode->onMouseEntered();
        }
    }
    if (selectedNode) {
        selectedNode->onMouseMoved(mousePosition);
    }
}

void RootNode::onMouseLeft()
{
    if (selectedNode) {
        selectedNode->onMouseLeft();
        selectedNode = nullptr;
    }
}

void RootNode::onLeftMouseButtonPressed()
{
    if (selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onLeftMouseButtonPressed();
        } else {
            selectedNode = nullptr;
        }
    }
}

void RootNode::onLeftMouseButtonReleased()
{
    if (selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onLeftMouseButtonReleased();
        } else {
            selectedNode = nullptr;
        }
    }
}

void RootNode::onRightMouseButtonReleased()
{
    if (selectedNode) {
        if (selectedNode->checkSelectable()) {
            selectedNode->onRightMouseButtonReleased();
        } else {
            selectedNode = nullptr;
        }
    }
}

const sf::Window &RootNode::getWindow() const
{
    return window;
}

void RootNode::update()
{
    MimicNode::update();
}

void RootNode::draw()
{
    drawToTarget(window);
}

void RootNode::addContent(AbstractNode *content)
{
    contentLayer->addChild(content);
}

void RootNode::removeContent(AbstractNode *content, bool toDelete)
{
    contentLayer->removeChild(content, toDelete);
}

}
