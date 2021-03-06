#include <CE/UI/Text.hpp>
#include <CE/constant.hpp>
#include <cmath>

namespace ce {

sf::Font Text::font;

void Text::loadFont(const std::string &filename)
{
    font.loadFromFile(filename);
}

Text::Text(const sf::String &string, unsigned int characterSize, const sf::Color &color)
    : characterSize(characterSize), text(sf::Text(string, font, characterSize))
{
    text.setFillColor(color);
}

const sf::String &Text::getString() const
{
    return text.getString();
}

void Text::setString(const sf::String &value)
{
    text.setString(value);
}

void Text::setAlpha(float value)
{
    text.setFillColor(sf::Color(text.getFillColor().r, text.getFillColor().g,
                                text.getFillColor().b, (sf::Uint8) (value * 255)));
}

float Text::getWidth()
{
    return text.getLocalBounds().width;
}

float Text::getHeight()
{
    return text.getLocalBounds().top + text.getLocalBounds().height;
}

void Text::setScale(float value)
{
    text.setScale(value, value);
    makeTransformed();
}

sf::FloatRect Text::getRect()
{
    return text.getGlobalBounds();
}

void Text::setRotation(float value)
{
    text.setRotation(value * 180 / MATH_PI);
    makeTransformed();
}

void Text::setOrigin(float x, float y)
{
    text.setOrigin(std::round(x), std::round(y));
    makeTransformed();
}

void Text::setPos(float x, float y)
{
    text.setPosition(std::round(x), std::round(y));
    makeTransformed();
}

void Text::rotate(float angle)
{
    text.rotate(angle * 180 / MATH_PI);
    makeTransformed();
}

void Text::move(float offsetX, float offsetY)
{
    text.move(std::round(offsetX), std::round(offsetY));
    makeTransformed();
}

void Text::resize()
{
    text.setCharacterSize(characterSize);
}

const sf::Transformable &Text::getTransformable() const
{
    return text;
}

const sf::Drawable &Text::getDrawable() const
{
    return text;
}

}
