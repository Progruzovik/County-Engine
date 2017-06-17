#include <CE/Core/AbstractVisualNode.hpp>

namespace ce {

AbstractVisualNode::AbstractVisualNode(bool isSelectable, bool isUpdatable, Listener *listener)
    : AbstractNode(isSelectable, isUpdatable, listener) {}

void AbstractVisualNode::drawToTarget(sf::RenderTarget &target)
{
    target.draw(getDrawable(), getParent()->getCombinedTransform());
    AbstractNode::drawToTarget(target);
}

}
