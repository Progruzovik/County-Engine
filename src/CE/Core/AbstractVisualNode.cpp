#include <CE/Core/AbstractVisualNode.hpp>

namespace ce {

AbstractVisualNode::AbstractVisualNode(bool isSelectable) : AbstractNode(isSelectable) {}

void AbstractVisualNode::drawToTarget(sf::RenderTarget &target)
{
    target.draw(getDrawable(), getParent()->getCombinedTransform());
    AbstractNode::drawToTarget(target);
}

}
