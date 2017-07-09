#include <CE/UI/Button.hpp>
#include <CE/UI/Parameters.hpp>
#include <CE/constant.hpp>

namespace ce {

Button::Button(const std::shared_ptr<Listener> &listener, const sf::String &string, const sf::Vector2f &size)
    : RectangleNode(size.x * Parameters::get().getK(), size.y * Parameters::get().getK(), sf::Color(0x333333FF), true),
      Speaker(listener), size(size)
{
    setString(string);
}

void Button::onCreated()
{
    addChild(text);
}

void Button::onMouseEntered()
{
    setState(State::MOUSE_OVER);
    RectangleNode::onMouseEntered();
}

void Button::onMouseLeft()
{
    if (checkSelectable()) {
        setState(State::DEFAULT);
    } else {
        setState(State::DISABLED);
    }
    RectangleNode::onMouseLeft();
}

void Button::onLeftMouseButtonPressed()
{
    setState(State::MOUSE_PRESSED);
}

void Button::onLeftMouseButtonReleased()
{
    setState(State::MOUSE_OVER);
    declareEvent(CLICK);
}

const sf::String &Button::getString() const
{
    return text->getString();
}

void Button::setString(const sf::String &value)
{
    text->setString(value);
    text->setOrigin(text->getHalfX(), text->getHalfY());
    text->setPos(getHalfX(), getHalfY());
}

void Button::setWidth(float value)
{
    setSize(value, size.y);
}

void Button::setHeight(float value)
{
    setSize(size.x, value);
}

void Button::setSize(float width, float height)
{
    size.x = width;
    size.y = height;
    updateSize();
}

void Button::resize()
{
    updateSize();
    text->resize();
    text->setOrigin(text->getHalfX(), text->getHalfY());
}

void Button::setState(State state)
{
    this->state = state;
    if (state == State::DEFAULT) {
        shape.setFillColor(sf::Color(0x333333FF));
    } else if (state == State::MOUSE_OVER || state == State::DISABLED) {
        shape.setFillColor(sf::Color(0x666666FF));
    } else if (state == State::MOUSE_PRESSED) {
        shape.setFillColor(sf::Color::Black);
    }
}

void Button::updateSize()
{
    RectangleNode::setSize(size.x * Parameters::get().getK(), size.y * Parameters::get().getK());
    text->setPos(getHalfX(), getHalfY());
}

}
