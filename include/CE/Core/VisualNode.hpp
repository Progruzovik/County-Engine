#ifndef CE_VISUALNODE_HPP
#define CE_VISUALNODE_HPP

#include <CE/Core/TransformableNode.hpp>

namespace ce {

class VisualNode : public TransformableNode
{
public:
    VisualNode(bool isSelectable = false);

    virtual void setAlpha(float value) = 0;
    void drawToTarget(sf::RenderTarget &target) override;

private:
    virtual const sf::Drawable &getDrawable() const = 0;
};

}

#endif
