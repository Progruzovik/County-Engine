#ifndef CE_MIMICNODE_HPP
#define CE_MIMICNODE_HPP

#include <CE/Core/TransformableNode.hpp>
#include <CE/Event/Listener.hpp>

namespace ce {

class MimicNode : public TransformableNode
{
public:
    explicit MimicNode(bool isSelectable = false);

    float getWidth() override;
    float getHeight() override;
    void setScale(float value) override;
    sf::FloatRect getRect() override;
    void setRotation(float value) override;

    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float offsetX, float offsetY) override;

private:
    sf::Transformable transformable;

    const sf::Transformable &getTransformable() const override;
};

}

#endif
