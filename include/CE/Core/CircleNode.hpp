#ifndef CE_CIRCLENODE_HPP
#define CE_CIRCLENODE_HPP

#include <CE/Core/VisualNode.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace ce {

class CircleNode : public VisualNode
{
public:
    explicit CircleNode(float radius, const sf::Color &color = sf::Color::White, bool isSelectable = false);

    void setAlpha(float value) override;
    float getWidth() override;
    float getHeight() override;
    virtual void setRadius(float value);
    void setScale(float value) override;
    sf::FloatRect getRect() override;
    void setRotation(float value) override;


    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float offsetX, float offsetY) override;

protected:
    sf::CircleShape shape;

    bool checkPointOnIt(const sf::Vector2i &point) override;

private:
    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
};

}

#endif
