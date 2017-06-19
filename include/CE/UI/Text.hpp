#ifndef CE_TEXT_HPP
#define CE_TEXT_HPP

#include <CE/Core/VisualNode.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ce {

class Text : public VisualNode
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
    sf::FloatRect getRect() override;
    void setRotation(float value) override;

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
