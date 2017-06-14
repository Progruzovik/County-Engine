#ifndef CORE_ROOTNODE_HPP
#define CORE_ROOTNODE_HPP

#include <CE/Core/MimicNode.hpp>
#include <CE/Core/Stage.hpp>

namespace ce {

class RootNode : public MimicNode
{
public:
    RootNode(sf::RenderWindow *window);

    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;
    void onRightMouseButtonReleased() override;

    const sf::Window &getWindow() const override;
    bool checkMouseOnIt(const sf::Vector2i &mousePosition) override;

    sf::Vector2i select();
    void draw();
    void addContent(AbstractNode *content);
    void removeContent(AbstractNode *content, bool toDelete = false);

private:
    MimicNode *contentLayer = new MimicNode(true, true);
    sf::RenderWindow *window;
};

}

#endif
