#include <CE/Core/RootNode.hpp>
#include <SFML/Window/Mouse.hpp>

namespace ce {

RootNode::RootNode(sf::RenderWindow *window) : MimicNode(true, true), window(window)
{
    addChild(contentLayer);
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

bool RootNode::checkMouseOnIt(const sf::Vector2i &mousePosition)
{
    return MimicNode::checkMouseOnIt(mousePosition);
}

sf::Vector2i RootNode::select()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(getWindow());
    MimicNode::select(mousePosition);
    return mousePosition;
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
