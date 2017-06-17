#ifndef CE_ROOTNODE_HPP
#define CE_ROOTNODE_HPP

#include <CE/Core/MimicNode.hpp>
#include <CE/Core/Stage.hpp>

namespace ce {

class RootNode : public MimicNode
{
public:
    RootNode(sf::RenderWindow *window);

    void onMouseLeft() override;
    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;
    void onRightMouseButtonReleased() override;

    const sf::Window &getWindow() const override;

    void draw();
    void addContent(AbstractNode *content);
    void removeContent(AbstractNode *content, bool toDelete = false);

private:
    MimicNode *contentLayer = new MimicNode(true, true);
    sf::RenderWindow *window;
};

}

#endif
