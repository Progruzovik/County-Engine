#ifndef CE_NODE_HPP
#define CE_NODE_HPP

#include <CE/Utility/EnableSharedFromThis.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Window.hpp>

namespace ce {

class TransformableNode;

class Node : public EnableSharedFromThis<Node>
{
public:
    Node(bool isSelectable = false);

    virtual void onMouseEntered() {}
    virtual void onMouseMoved(const sf::Vector2i &mousePosition) {}
    virtual void onMouseLeft() {}
    virtual void onLeftMouseButtonPressed() {}
    virtual void onLeftMouseButtonReleased() {}
    virtual void onRightMouseButtonReleased() {}

    bool checkSelectable() const;
    void setSelectable(bool value);

    virtual const sf::Transform &getCombinedTransform() = 0;
    std::shared_ptr<Node> getParent() const;
    virtual const sf::Window &getWindow() const;

    void addChild(const std::shared_ptr<TransformableNode> &child);
    void removeChild(const std::shared_ptr<TransformableNode> &child);
    void removeChildren(bool toDelete = false, unsigned long firstIndex = 0, long lastIndex = -1);

protected:
    std::vector<std::shared_ptr<TransformableNode> > children;

    std::shared_ptr<Node> select(const sf::Vector2i &mousePosition);
    virtual void update();
    virtual bool checkPointOnIt(const sf::Vector2i &point) = 0;
    virtual void makeTransformed() {}
    virtual void drawToTarget(sf::RenderTarget &target);

private:
    bool isSelectable;
    std::weak_ptr<Node> parent;

    virtual void onAdded() {}
    virtual void onUpdated() {}

    void setParent(const std::shared_ptr<Node> &value);
};

}

#endif
