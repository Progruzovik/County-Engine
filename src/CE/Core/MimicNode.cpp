#include <CE/Core/MimicNode.hpp>
#include <CE/constant.hpp>

namespace ce {

MimicNode::MimicNode(bool isSelectable, bool isUpdatable, ce::Listener *listener)
    : AbstractNode(isSelectable, isUpdatable, listener) {}

float MimicNode::getWidth()
{
    float width = 0;
    for (auto *child : getChildren()) {
        float newWidth = child->getX() + child->getWidth() * child->getScale();
        if (newWidth > width) {
            width = newWidth;
        }
    }
    return width;
}

float MimicNode::getHeight()
{
    float height = 0;
    for (auto *child : getChildren()) {
        float newHeight = child->getY() + child->getHeight() * child->getScale();
        if (newHeight > height) {
            height = newHeight;
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
    transformable.setRotation(value * 180 / ce::MATH_PI);
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
    transformable.rotate(angle * 180 / ce::MATH_PI);
    makeTransformed();
}

void MimicNode::move(float moveX, float moveY)
{
    transformable.move(moveX, moveY);
    makeTransformed();
}

const sf::Transformable &MimicNode::getTransformable() const
{
    return transformable;
}

}
