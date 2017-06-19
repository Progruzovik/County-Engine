#include <CE/Core/VisualNode.hpp>

namespace ce {

VisualNode::VisualNode(bool isSelectable) : TransformableNode(isSelectable) {}

void VisualNode::drawToTarget(sf::RenderTarget &target)
{
    target.draw(getDrawable(), getParent()->getCombinedTransform());
    Node::drawToTarget(target);
}

}
