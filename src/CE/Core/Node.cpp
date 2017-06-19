#include <CE/Core/Node.hpp>
#include <CE/Core/TransformableNode.hpp>

namespace ce {

Node::Node(bool isSelectable) : isSelectable(isSelectable) {}

Node::~Node()
{
    for (auto *child : children) {
        delete child;
    }
}

bool Node::checkSelectable() const
{
    return isSelectable;
}

void Node::setSelectable(bool value)
{
    if (isSelectable != value) {
        isSelectable = value;
        onMouseLeft();
    }
}

Node *Node::getParent() const
{
    return parent;
}

const sf::Window &Node::getWindow() const
{
    return parent->getWindow();
}

void Node::update()
{
    for (auto *child : children) {
        child->update();
    }
    onUpdated();
}

void Node::addChild(TransformableNode *child)
{
    child->setParent(this);
    children.push_back(child);
    child->onAdded();
}

void Node::removeChild(TransformableNode *child, bool toDelete)
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        child->dispose(toDelete);
        children.erase(it);
    }
}

void Node::removeChildren(bool toDelete, unsigned long firstIndex, long lastIndex)
{
    const auto begin = children.begin() + firstIndex;
    const auto end = lastIndex == -1 || lastIndex > children.size()
            ? children.end()
            : children.begin() + lastIndex;
    std::for_each(begin, end, [this, toDelete](Node *child) {
       child->dispose(toDelete);
    });
    children.erase(begin, end);
}

Node *Node::select(const sf::Vector2i &mousePosition)
{
    Node *selectedChild = nullptr;
    auto it = std::find_if(children.rbegin(), children.rend(), [mousePosition](Node *child) -> bool {
        return child->checkPointOnIt(mousePosition);
    });
    if (it != children.rend()) {
        selectedChild = (*it)->select(mousePosition);
    }
    if (selectedChild && selectedChild->checkSelectable()) {
        return selectedChild;
    }
    if (checkSelectable()) {
        return this;
    }
    return nullptr;
}

void Node::drawToTarget(sf::RenderTarget &target)
{
    for (auto *child : children) {
        child->drawToTarget(target);
    }
}

void Node::setParent(Node *value)
{
    parent = value;
    makeTransformed();
}

void Node::dispose(bool toDelete)
{
    if (toDelete) {
        delete this;
    } else {
        setParent(nullptr);
    }
}

}
