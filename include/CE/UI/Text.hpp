#ifndef CE_TEXT_HPP
#define CE_TEXT_HPP

#include <CE/Core/VisualNode.hpp>
#include <SFML/Graphics/Text.hpp>

namespace ce {

class Text : public VisualNode
{
public:
    static void loadFont(const std::string &filename);
    explicit Text(const sf::String &string = "", unsigned int characterSize = CHARACTER_SIZE,
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
    static constexpr unsigned int CHARACTER_SIZE = 18;
    static sf::Font font;

    const unsigned int characterSize;
    sf::Text text;

    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
};

}

#endif
