#ifndef CE_ABSTRACTVISUALNODE_HPP
#define CE_ABSTRACTVISUALNODE_HPP

#include <CE/Core/AbstractNode.hpp>

namespace ce {

class AbstractVisualNode : public AbstractNode
{
public:
    AbstractVisualNode(bool isSelectable = false);

    virtual void setAlpha(float value) = 0;
    void drawToTarget(sf::RenderTarget &target) override;

protected:
    virtual const sf::Drawable &getDrawable() const = 0;
};

}

#endif
