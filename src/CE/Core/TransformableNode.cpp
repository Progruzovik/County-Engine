#include <CE/Core/TransformableNode.hpp>
#include <CE/constant.hpp>

namespace ce {

TransformableNode::TransformableNode(bool isSelectable) : Node(isSelectable) {}

float TransformableNode::getHalfX()
{
    return getWidth() / 2;
}

float TransformableNode::getHalfY()
{
    return getHeight() / 2;
}

float TransformableNode::getScale() const
{
    return getTransformable().getScale().x;
}

float TransformableNode::getRotation() const
{
    float rotation = getTransformable().getRotation() * MATH_PI / 180;
    if (rotation > MATH_PI) {
        rotation -= MATH_PI * 2;
    }
    return rotation;
}

float TransformableNode::getOriginX() const
{
    return getTransformable().getOrigin().x;
}

void TransformableNode::setOriginX(float x)
{
    setOrigin(x, getOriginY());
}

float TransformableNode::getOriginY() const
{
    return getTransformable().getOrigin().y;
}

void TransformableNode::setOriginY(float y)
{
    setOrigin(getOriginX(), y);
}

float TransformableNode::getX() const
{
    return getTransformable().getPosition().x;
}

void TransformableNode::setX(float value)
{
    setPos(value, getY());
}

float TransformableNode::getY() const
{
    return getTransformable().getPosition().y;
}

void TransformableNode::setY(float value)
{
    setPos(getX(), value);
}

const sf::Vector2f& TransformableNode::getPos() const
{
    return getTransformable().getPosition();
}

const sf::Transform &TransformableNode::getCombinedTransform()
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

void TransformableNode::moveX(float offset)
{
    move(offset, 0);
}

void TransformableNode::moveY(float offset)
{
    move(0, offset);
}

void TransformableNode::removeFromParent()
{
    getParent()->removeChild(castSharedFromThis<TransformableNode>());
}

bool TransformableNode::checkPointOnIt(const sf::Vector2i &point)
{
    sf::Vector2f localPoint = translatePointToLocalCoordinates(point);
    return localPoint.x > 0 && localPoint.x < getWidth() && localPoint.y > 0 && localPoint.y < getHeight();
}

sf::Vector2f TransformableNode::translatePointToLocalCoordinates(const sf::Vector2i &point)
{
    const sf::FloatRect combinedRect = getParent()->getCombinedTransform().transformRect(getRect());
    const float combinedScale = combinedRect.width / getWidth();
    return { (point.x - combinedRect.left) / combinedScale, (point.y - combinedRect.top) / combinedScale };
}

void TransformableNode::makeTransformed()
{
    isTransformed = true;
    for (auto &child : children) {
        child->makeTransformed();
    }
}

}
