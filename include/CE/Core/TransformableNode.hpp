#ifndef CE_TRANSFORMABLENODE_HPP
#define CE_TRANSFORMABLENODE_HPP

#include <CE/Core/Node.hpp>

namespace ce {

class TransformableNode : public Node
{
public:
    TransformableNode(bool isSelectable = false);

    virtual float getWidth() = 0;
    virtual float getHeight() = 0;
    float getHalfX();
    float getHalfY();
    float getScale() const;
    virtual void setScale(float value) = 0;
    virtual sf::FloatRect getRect() = 0;

    float getRotation() const;
    virtual void setRotation(float value) = 0;
    float getOriginX() const;
    void setOriginX(float x);
    float getOriginY() const;
    void setOriginY(float y);
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    const sf::Vector2f &getPos() const;

    virtual const sf::Transform &getCombinedTransform() override;

    virtual void setOrigin(float x, float y) = 0;
    virtual void setPos(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    void moveX(float offset);
    void moveY(float offset);
    virtual void move(float offsetX, float offsetY) = 0;

    void removeFromParent();

protected:
    bool checkPointOnIt(const sf::Vector2i &point) override;
    sf::Vector2f translatePointToLocalCoordinates(const sf::Vector2i &point);
    void makeTransformed() override;

private:
    bool isTransformed = true;
    sf::Transform combinedTransform;

    virtual const sf::Transformable &getTransformable() const = 0;
};

}

#endif
