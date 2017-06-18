#include <CE/Core/MimicNode.hpp>
#include <CE/constant.hpp>

namespace ce {

MimicNode::MimicNode(bool isSelectable, Listener *listener) : AbstractNode(isSelectable, listener) {}

float MimicNode::getWidth()
{
    float width = 0;
    for (auto *child : getChildren()) {
        float nextWidth = child->getX() - child->getOriginX() + child->getWidth() * child->getScale();
        if (nextWidth > width) {
            width = nextWidth;
        }
    }
    return width;
}

float MimicNode::getHeight()
{
    float height = 0;
    for (auto *child : getChildren()) {
        float nextHeight = child->getY() - child->getOriginY() + child->getHeight() * child->getScale();
        if (nextHeight > height) {
            height = nextHeight;
        }
    }
    return height;
}

void MimicNode::setScale(float value)
{
    transformable.setScale(value, value);
    makeTransformed();
}

void MimicNode::setRotation(float value)
{
    transformable.setRotation(value * 180 / MATH_PI);
    makeTransformed();
}

sf::FloatRect MimicNode::getRect()
{
    return transformable.getTransform().transformRect(sf::FloatRect(0, 0, getWidth(), getHeight()));
}

void MimicNode::setOrigin(float x, float y)
{
    transformable.setOrigin(x, y);
    makeTransformed();
}

void MimicNode::setPos(float x, float y)
{
    transformable.setPosition(x, y);
    makeTransformed();
}

void MimicNode::rotate(float angle)
{
    transformable.rotate(angle * 180 / MATH_PI);
    makeTransformed();
}

void MimicNode::move(float offsetX, float offsetY)
{
    transformable.move(offsetX, offsetY);
    makeTransformed();
}

const sf::Transformable &MimicNode::getTransformable() const
{
    return transformable;
}

}
