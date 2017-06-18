#include <CE/Core/AbstractNode.hpp>
#include <CE/constant.hpp>

namespace ce {

AbstractNode::AbstractNode(bool isSelectable, Listener *listener)
    : Speaker(listener), isSelectable(isSelectable) {}

AbstractNode::~AbstractNode()
{
    for (auto *child : children) {
        delete child;
    }
}

void AbstractNode::onMouseEntered()
{
    isSelected = true;
}

void AbstractNode::onMouseLeft()
{
    isSelected = false;
}

bool AbstractNode::checkSelectable() const
{
    return isSelectable;
}

void AbstractNode::setSelectable(bool value)
{
    if (isSelectable != value) {
        isSelectable = value;
        onMouseLeft();
    }
}

const sf::Transform &AbstractNode::getCombinedTransform()
{
    if (isTransformed) {
        isTransformed = false;
        if (getParent()) {
            combinedTransform = getParent()->getCombinedTransform() * getTransformable().getTransform();
        } else {
            combinedTransform = getTransformable().getTransform();
        }
    }
    return combinedTransform;
}

AbstractNode *AbstractNode::getParent() const
{
    return parent;
}

const sf::Window &AbstractNode::getWindow() const
{
    return parent->getWindow();
}

float AbstractNode::getHalfX()
{
    return getWidth() / 2;
}

float AbstractNode::getHalfY()
{
    return getHeight() / 2;
}

float AbstractNode::getScale() const
{
    return getTransformable().getScale().x;
}

float AbstractNode::getRotation() const
{
    float rotation = getTransformable().getRotation() * MATH_PI / 180;
    if (rotation > MATH_PI) {
        rotation -= MATH_PI * 2;
    }
    return rotation;
}

float AbstractNode::getOriginX() const
{
    return getTransformable().getOrigin().x;
}

void AbstractNode::setOriginX(float x)
{
    setOrigin(x, getOriginY());
}

float AbstractNode::getOriginY() const
{
    return getTransformable().getOrigin().y;
}

void AbstractNode::setOriginY(float y)
{
    setOrigin(getOriginX(), y);
}

float AbstractNode::getX() const
{
    return getTransformable().getPosition().x;
}

void AbstractNode::setX(float value)
{
    setPos(value, getY());
}

float AbstractNode::getY() const
{
    return getTransformable().getPosition().y;
}

void AbstractNode::setY(float value)
{
    setPos(getX(), value);
}

void AbstractNode::moveX(float offset)
{
    move(offset, 0);
}

void AbstractNode::moveY(float offset)
{
    move(0, offset);
}

void AbstractNode::update()
{
    for (auto *child : children) {
        child->update();
    }
    onUpdated();
}

void AbstractNode::removeFromParent(bool toDelete)
{
    parent->removeChild(this, toDelete);
}

void AbstractNode::addChild(AbstractNode *child)
{
    child->setParent(this);
    children.push_back(child);
    child->onAdded();
}

void AbstractNode::removeChild(AbstractNode *child, bool toDelete)
{
    auto it = std::find(children.begin(), children.end(), child);
    if (it != children.end()) {
        child->dispose(toDelete);
        children.erase(it);
    }
}

void AbstractNode::removeChildren(bool toDelete, unsigned long firstIndex, long lastIndex)
{
    const auto begin = children.begin() + firstIndex;
    const auto end = lastIndex == -1 || lastIndex > children.size()
            ? children.end()
            : children.begin() + lastIndex;
    std::for_each(begin, end, [this, toDelete](AbstractNode *child) {
       child->dispose(toDelete);
    });
    children.erase(begin, end);
}

void AbstractNode::onUpdated()
{
    declareEvent(UPDATE);
}

const std::vector<AbstractNode *> &AbstractNode::getChildren() const
{
    return children;
}

AbstractNode *AbstractNode::select(const sf::Vector2i &mousePosition)
{
    AbstractNode *selectedChild = nullptr;
    auto it = std::find_if(children.rbegin(), children.rend(), [mousePosition](AbstractNode *child) -> bool {
        return child->checkMouseOnIt(mousePosition);
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

void AbstractNode::makeTransformed()
{
    isTransformed = true;
    for (auto *child : children) {
        child->makeTransformed();
    }
}

bool AbstractNode::checkMouseOnIt(const sf::Vector2i &mousePosition)
{
    sf::Vector2f mouseLocalPosition = calculateMouseLocalPosition(mousePosition);
    return mouseLocalPosition.x > 0 && mouseLocalPosition.x < getWidth()
           && mouseLocalPosition.y > 0 && mouseLocalPosition.y < getHeight();
}

sf::Vector2f AbstractNode::calculateMouseLocalPosition(const sf::Vector2i &mousePosition)
{
    const sf::FloatRect combinedRect = parent->getCombinedTransform().transformRect(getRect());
    const float combinedScale = combinedRect.width / getWidth();
    return sf::Vector2f((mousePosition.x - combinedRect.left) / combinedScale,
                        (mousePosition.y - combinedRect.top) / combinedScale);
}

void AbstractNode::drawToTarget(sf::RenderTarget &target)
{
    for (auto *child : children) {
        child->drawToTarget(target);
    }
}

void AbstractNode::setParent(AbstractNode *value)
{
    parent = value;
    makeTransformed();
}

void AbstractNode::dispose(bool toDelete)
{
    if (toDelete) {
        delete this;
    } else {
        setParent(nullptr);
    }
}

}
