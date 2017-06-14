#include <CE/Core/RectangleNode.hpp>
#include <CE/constant.hpp>

namespace ce {

RectangleNode::RectangleNode(float width, float height, const sf::Color &color,
                             bool isSelectable, bool isUpdatable, ce::Listener *listener)
    : AbstractVisualNode(isSelectable, isUpdatable, listener),
      shape(sf::RectangleShape(sf::Vector2f(width, height)))
{
    shape.setFillColor(color);
}

void RectangleNode::setAlpha(float value)
{
    shape.setFillColor(sf::Color(shape.getFillColor().r, shape.getFillColor().g,
                                 shape.getFillColor().b, (sf::Uint8) (value * 255)));
}

float RectangleNode::getWidth()
{
    return shape.getSize().x;
}

void RectangleNode::setWidth(float value)
{
    setSize(value, getHeight());
}

float RectangleNode::getHeight()
{
    return shape.getSize().y;
}

void RectangleNode::setHeight(float value)
{
    setSize(getWidth(), value);
}

void RectangleNode::setScale(float scale)
{
    shape.setScale(scale, scale);
    makeTransformed();
}

void RectangleNode::setRotation(float value)
{
    shape.setRotation(value * 180 / ce::MATH_PI);
    makeTransformed();
}

sf::FloatRect RectangleNode::getRect()
{
    return shape.getGlobalBounds();
}

void RectangleNode::setSize(float width, float height)
{
    shape.setSize(sf::Vector2f(width, height));
}

void RectangleNode::setOrigin(float x, float y)
{
    shape.setOrigin(x, y);
    makeTransformed();
}

void RectangleNode::setPos(float x, float y)
{
    shape.setPosition(x, y);
    makeTransformed();
}

void RectangleNode::rotate(float angle)
{
    shape.rotate(angle * 180 / ce::MATH_PI);
    makeTransformed();
}

void RectangleNode::move(float moveX, float moveY)
{
    shape.move(moveX, moveY);
    makeTransformed();
}

const sf::Transformable &RectangleNode::getTransformable() const
{
    return shape;
}

const sf::Drawable &RectangleNode::getDrawable() const
{
    return shape;
}

}
