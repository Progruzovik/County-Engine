#include <CE/Core/AbstractVisualNode.hpp>

namespace ce {

AbstractVisualNode::AbstractVisualNode(bool isSelectable, bool isUpdatable, ce::Listener *listener)
    : AbstractNode(isSelectable, isUpdatable, listener) {}

void AbstractVisualNode::drawToTarget(sf::RenderTarget *target)
{
    if (getParent()) {
        target->draw(getDrawable(), getParent()->getCombinedTransform());
    } else {
        target->draw(getDrawable());
    }
    AbstractNode::drawToTarget(target);
}

}
