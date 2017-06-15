#include <CE/Core/SpriteNode.hpp>
#include <CE/constant.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace ce {

SpriteNode::SpriteNode(const sf::Texture &texture, bool isSelectable, bool isUpdatable, Listener *listener)
    : AbstractVisualNode(isSelectable, isUpdatable, listener)
{
    sprite.setTexture(texture);
}

void SpriteNode::setAlpha(float value)
{
    sprite.setColor(sf::Color(sprite.getColor().r, sprite.getColor().g,
                              sprite.getColor().b, (sf::Uint8) (value * 255)));
}

float SpriteNode::getWidth()
{
    return sprite.getTexture()->getSize().x;
}

float SpriteNode::getHeight()
{
    return sprite.getTexture()->getSize().y;
}

void SpriteNode::setScale(float value)
{
    sprite.setScale(value, value);
    makeTransformed();
}

void SpriteNode::setRotation(float value)
{
    sprite.setRotation(value * 180 / MATH_PI);
    makeTransformed();
}

sf::FloatRect SpriteNode::getRect()
{
    return sprite.getGlobalBounds();
}

void SpriteNode::setOrigin(float x, float y)
{
    sprite.setOrigin(x, y);
    makeTransformed();
}

void SpriteNode::setPos(float x, float y)
{
    sprite.setPosition(x, y);
    makeTransformed();
}

void SpriteNode::rotate(float angle)
{
    sprite.rotate(angle * 180 / MATH_PI);
    makeTransformed();
}

void SpriteNode::move(float offsetX, float offsetY)
{
    sprite.move(offsetX, offsetY);
    makeTransformed();
}

const sf::Transformable &SpriteNode::getTransformable() const
{
    return sprite;
}

const sf::Drawable &SpriteNode::getDrawable() const
{
    return sprite;
}

}
