#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <CE/Core/RectangleNode.hpp>
#include <CE/UI/Text.hpp>

namespace ce {

class Button : public ce::RectangleNode
{
public:
    Button(ce::Listener *listener, const sf::String &string = "",
           const sf::Vector2f &size = sf::Vector2f(165, 40));

    const sf::String &getString() const;
    void setString(const sf::String &value = "");
    void setWidth(float value) override;
    void setHeight(float value) override;
    void setSize(float width, float height) override;

    virtual void resize();

protected:
    void onMouseEntered() override;
    void onMouseLeft() override;
    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;

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
