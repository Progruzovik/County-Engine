#ifndef CE_BUTTON_HPP
#define CE_BUTTON_HPP

#include <CE/Core/RectangleNode.hpp>
#include <CE/Event/Speaker.hpp>
#include <CE/UI/Text.hpp>

namespace ce {

class Button : public RectangleNode, public Speaker
{
public:
    Button(Listener *listener, const sf::String &string = "", const sf::Vector2f &size = sf::Vector2f(165, 40));

    void onMouseEntered() override;
    void onMouseLeft() override;
    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;

    const sf::String &getString() const;
    void setString(const sf::String &value = "");
    void setWidth(float value) override;
    void setHeight(float value) override;
    void setSize(float width, float height) override;

    virtual void resize();

private:
    enum class State { DEFAULT, MOUSE_OVER, MOUSE_PRESSED, DISABLED };
    void updateSize();

    Text *text;
    sf::Vector2f size;
    State state = State::DEFAULT;

    void setState(State state);
};

}

#endif
