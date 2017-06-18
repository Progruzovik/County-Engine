#ifndef CE_ROOTNODE_HPP
#define CE_ROOTNODE_HPP

#include <CE/Core/MimicNode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ce {

class RootNode final : public MimicNode
{
public:
    RootNode(sf::RenderWindow &window);

    void onMouseMoved(const sf::Vector2i &mousePosition) override;
    void onMouseLeft() override;
    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;
    void onRightMouseButtonReleased() override;

    const sf::Window &getWindow() const override;

    void update() override;
    void draw();
    void addContent(AbstractNode *content);
    void removeContent(AbstractNode *content, bool toDelete = false);

private:
    sf::RenderWindow &window;
    AbstractNode *selectedNode = nullptr;
    MimicNode *contentLayer = new MimicNode();
};

}

#endif
