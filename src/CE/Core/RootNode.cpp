#include <CE/Core/RootNode.hpp>
#include <SFML/Window/Mouse.hpp>

namespace ce {

RootNode::RootNode(sf::RenderWindow *window) : MimicNode(true, true), window(window)
{
    addChild(contentLayer);
}

void RootNode::onMouseLeft()
{
    deselectChild();
}

void RootNode::onLeftMouseButtonPressed()
{
    MimicNode::onLeftMouseButtonPressed();
}

void RootNode::onLeftMouseButtonReleased()
{
    MimicNode::onLeftMouseButtonReleased();
}

void RootNode::onRightMouseButtonReleased()
{
    MimicNode::onRightMouseButtonReleased();
}

const sf::Window &RootNode::getWindow() const
{
    return *window;
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
