#include <CE/Core/AbstractVisualNode.hpp>

namespace ce {

AbstractVisualNode::AbstractVisualNode(bool isSelectable, Listener *listener)
    : AbstractNode(isSelectable, listener) {}

void AbstractVisualNode::drawToTarget(sf::RenderTarget &target)
{
    target.draw(getDrawable(), getParent()->getCombinedTransform());
    AbstractNode::drawToTarget(target);
}

}
