#ifndef CE_SPRITENODE_HPP
#define CE_SPRITENODE_HPP

#include <CE/Core/AbstractVisualNode.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace ce {

class SpriteNode : public AbstractVisualNode
{
public:
    SpriteNode(const sf::Texture &texture, bool isSelectable = false, Listener *listener = nullptr);

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

private:
    sf::Sprite sprite;

    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
};

}

#endif
