#ifndef CE_CIRCLENODE_HPP
#define CE_CIRCLENODE_HPP

#include <CE/Core/AbstractVisualNode.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace ce {

class CircleNode : public AbstractVisualNode
{
public:
    CircleNode(float radius, const sf::Color &color = sf::Color::White,
               bool isSelectable = false, bool isUpdatable = false, Listener *listener = nullptr);

    void setAlpha(float value) override;
    float getWidth() override;
    float getHeight() override;
    virtual void setRadius(float value);
    void setScale(float value) override;

    void setRotation(float value) override;
    sf::FloatRect getRect() override;

    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float offsetX, float offsetY) override;

protected:
    sf::CircleShape shape;

    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
    bool checkMouseOnIt(const sf::Vector2i &mousePosition) override;
};

}

#endif
