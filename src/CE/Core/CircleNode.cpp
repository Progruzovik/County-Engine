#include <CE/Core/CircleNode.hpp>
#include <cmath>

namespace ce {

CircleNode::CircleNode(float radius, const sf::Color &color, bool isSelectable)
    : AbstractVisualNode(isSelectable), shape(sf::CircleShape(radius))
{
    shape.setOrigin(radius, radius);
    shape.setFillColor(color);
}

void CircleNode::setAlpha(float value)
{
    shape.setFillColor(sf::Color(shape.getFillColor().r, shape.getFillColor().g,
                                 shape.getFillColor().b, (sf::Uint8) (value * 255)));
}

float CircleNode::getWidth()
{
    return shape.getRadius() * 2;
}

float CircleNode::getHeight()
{
    return getWidth();
}

void CircleNode::setRadius(float value)
{
    shape.setRadius(value);
}

void CircleNode::setScale(float value)
{
    shape.setScale(value, value);
    makeTransformed();
}

void CircleNode::setRotation(float value)
{
    shape.setRotation(value);
    makeTransformed();
}

sf::FloatRect CircleNode::getRect()
{
    return shape.getGlobalBounds();
}

void CircleNode::setOrigin(float x, float y)
{
    shape.setOrigin(x, y);
    makeTransformed();
}

void CircleNode::setPos(float x, float y)
{
    shape.setPosition(x, y);
    makeTransformed();
}

void CircleNode::rotate(float angle)
{
    shape.rotate(angle);
    makeTransformed();
}

void CircleNode::move(float offsetX, float offsetY)
{
    shape.move(offsetX, offsetY);
    makeTransformed();
}

const sf::Transformable &CircleNode::getTransformable() const
{
    return shape;
}

const sf::Drawable &CircleNode::getDrawable() const
{
    return shape;
}

bool CircleNode::checkMouseOnIt(const sf::Vector2i &mousePosition)
{
    sf::Vector2f mouseLocalPosition = calculateMouseLocalPosition(mousePosition);
    mouseLocalPosition.x -= shape.getRadius();
    mouseLocalPosition.y -= shape.getRadius();
    return std::sqrt(mouseLocalPosition.x * mouseLocalPosition.x + mouseLocalPosition.y * mouseLocalPosition.y)
           <= shape.getRadius();
}

}
