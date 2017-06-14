#ifndef CORE_MIMICNODE_HPP
#define CORE_MIMICNODE_HPP

#include <CE/Core/AbstractNode.hpp>
#include <CE/Event/Listener.hpp>

namespace ce {

class MimicNode : public AbstractNode
{
public:
    MimicNode(bool isSelectable = false, bool isUpdatable = false,
              ce::Listener *listener = nullptr);

    float getWidth() override;
    float getHeight() override;
    void setScale(float value) override;

    void setRotation(float value) override;
    sf::FloatRect getRect() override;

    void setOrigin(float x, float y) override;
    void setPos(float x, float y) override;
    void rotate(float angle) override;
    void move(float moveX, float moveY) override;

protected:
    const sf::Transformable &getTransformable() const override;

private:
    sf::Transformable transformable;
};

}

#endif
