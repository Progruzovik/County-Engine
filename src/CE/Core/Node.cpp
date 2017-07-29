#include <CE/Core/Node.hpp>
#include <CE/Core/TransformableNode.hpp>

namespace ce {

Node::Node(bool isSelectable) : isSelectable(isSelectable) {}

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

std::shared_ptr<Node> Node::getParent() const
{
    return parent.lock();
}

const sf::Window &Node::getWindow() const
{
    return parent.lock()->getWindow();
}

void Node::update()
{
    for (auto &child : children) {
        child->update();
    }
    onUpdated();
}

void Node::addChild(const std::shared_ptr<TransformableNode> &child)
{
    if (child->getParent()) {
        child->removeFromParent();
    }
    child->setParent(sharedFromThis());
    children.push_back(child);
    child->onAdded();
}

void Node::removeChild(const std::shared_ptr<TransformableNode> &child)
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        child->setParent(nullptr);
        children.erase(it);
    }
}

void Node::removeChildren(unsigned long firstIndex, long lastIndex)
{
    const auto begin = children.begin() + firstIndex;
    const auto end = lastIndex == -1 || lastIndex > children.size()
            ? children.end()
            : children.begin() + lastIndex;
    std::for_each(begin, end, [this](const std::shared_ptr<Node> &child) {
        child->setParent(nullptr);
    });
    children.erase(begin, end);
}

std::shared_ptr<Node> Node::select(const sf::Vector2i &mousePosition)
{
    std::shared_ptr<Node> selectedChild;
    auto it = std::find_if(children.rbegin(), children.rend(), [mousePosition](const std::shared_ptr<Node> &child)
        -> bool { return child->checkPointOnIt(mousePosition); });
    if (it != children.rend()) {
        selectedChild = (*it)->select(mousePosition);
    }
    if (selectedChild && selectedChild->checkSelectable()) {
        return selectedChild;
    }
    if (checkSelectable()) {
        return sharedFromThis();
    }
    return nullptr;
}

void Node::drawToTarget(sf::RenderTarget &target)
{
    for (auto &child : children) {
        child->drawToTarget(target);
    }
}

void Node::setParent(const std::shared_ptr<Node> &value)
{
    parent = value;
    makeTransformed();
}

}
