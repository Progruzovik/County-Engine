#ifndef UI_TEXT_HPP
#define UI_TEXT_HPP

#include <CE/Core/AbstractVisualNode.hpp>
#include <CE/UI/Parameters.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ce {

class Text : public AbstractVisualNode
{
public:
    static constexpr unsigned int CHRACTER_SIZE = 18;
    static void loadFont(const std::string &filename);

    Text(const sf::String &string = "", unsigned int characterSize = CHRACTER_SIZE,
         const sf::Color &color = sf::Color::Black);

    const sf::String &getString() const;
    void setString(const sf::String &value);

    void setAlpha(float value) override;
    float getWidth() override;
    float getHeight() override;
    void setScale(float value) override;

    void setRotation(float value) override;
    sf::FloatRect getRect() override;

    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float offsetX, float offsetY) override;

    virtual void resize();

private:
    static sf::Font font;

    unsigned int characterSize;
    sf::Text text;

    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
};

}

#endif
