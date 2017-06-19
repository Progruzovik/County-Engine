#ifndef CE_RECTANGLENODE_HPP
#define CE_RECTANGLENODE_HPP

#include <CE/Core/VisualNode.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ce {

class RectangleNode : public VisualNode
{
public:
    RectangleNode(float width, float height, const sf::Color &color = sf::Color::White, bool isSelectable = false);

    void setAlpha(float value) override;
    float getWidth() override;
    virtual void setWidth(float value);
    float getHeight() override;
    virtual void setHeight(float value);
    void setScale(float scale) override;
    sf::FloatRect getRect() override;
    void setRotation(float value) override;

    virtual void setSize(float width, float height);
    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float offsetX, float offsetY) override;

protected:
    sf::RectangleShape shape;

    const sf::Transformable &getTransformable() const override;
    const sf::Drawable &getDrawable() const override;
};

}

#endif
