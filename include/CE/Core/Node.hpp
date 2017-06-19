#ifndef CE_NODE_HPP
#define CE_NODE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Window.hpp>

namespace ce {

class TransformableNode;

class Node
{
public:
    Node(bool isSelectable = false);
    virtual ~Node();

    virtual void onMouseEntered() {}
    virtual void onMouseMoved(const sf::Vector2i &mousePosition) {}
    virtual void onMouseLeft() {}
    virtual void onLeftMouseButtonPressed() {}
    virtual void onLeftMouseButtonReleased() {}
    virtual void onRightMouseButtonReleased() {}

    bool checkSelectable() const;
    void setSelectable(bool value);

    virtual const sf::Transform &getCombinedTransform() = 0;
    Node *getParent() const;
    virtual const sf::Window &getWindow() const;

    void addChild(TransformableNode *child);
    void removeChild(TransformableNode *child, bool toDelete = false);
    void removeChildren(bool toDelete = false, unsigned long firstIndex = 0, long lastIndex = -1);

protected:
    std::vector<TransformableNode *> children;

    virtual void onAdded() {}
    virtual void onUpdated() {}

    Node *select(const sf::Vector2i &mousePosition);
    virtual void update();

    virtual void makeTransformed() {}
    virtual bool checkPointOnIt(const sf::Vector2i &point) = 0;
    virtual void drawToTarget(sf::RenderTarget &target);

private:
    bool isSelectable;
    Node *parent = nullptr;

    void setParent(Node *value);
    void dispose(bool toDelete);
};

}

#endif
