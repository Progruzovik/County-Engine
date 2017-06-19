#ifndef CE_ABSTRACTNODE_HPP
#define CE_ABSTRACTNODE_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Window.hpp>

namespace ce {

class AbstractNode
{
public:
    AbstractNode(bool isSelectable = false);
    virtual ~AbstractNode();

    virtual void onMouseEntered() {}
    virtual void onMouseMoved(const sf::Vector2i &mousePosition) {}
    virtual void onMouseLeft() {}
    virtual void onLeftMouseButtonPressed() {}
    virtual void onLeftMouseButtonReleased() {}
    virtual void onRightMouseButtonReleased() {}

    bool checkSelectable() const;
    void setSelectable(bool value);
    const sf::Transform &getCombinedTransform();

    AbstractNode *getParent() const;
    virtual const sf::Window &getWindow() const;

    virtual float getWidth() = 0;
    float getHalfX();
    virtual float getHeight() = 0;
    float getHalfY();

    float getScale() const;
    virtual void setScale(float value) = 0;
    float getRotation() const;
    virtual void setRotation(float value) = 0;
    float getOriginX() const;
    void setOriginX(float x);
    float getOriginY() const;
    void setOriginY(float y);
    float getX() const;
    void setX(float value);
    float getY() const;
    void setY(float value);
    virtual sf::FloatRect getRect() = 0;

    virtual void setOrigin(float x, float y) = 0;
    virtual void setPos(float x, float y) = 0;
    virtual void rotate(float angle) = 0;
    void moveX(float offset);
    void moveY(float offset);
    virtual void move(float offsetX, float offsetY) = 0;

    void removeFromParent(bool toDelete = false);
    void addChild(AbstractNode *child);
    void removeChild(AbstractNode *child, bool toDelete = false);
    void removeChildren(bool toDelete = false, unsigned long firstIndex = 0, long lastIndex = -1);

protected:
    virtual void onAdded() {}
    virtual void onUpdated() {}

    virtual const sf::Transformable &getTransformable() const = 0;
    const std::vector<AbstractNode *> &getChildren() const;

    AbstractNode *select(const sf::Vector2i &mousePosition);
    virtual void update();

    void makeTransformed();
    virtual bool checkMouseOnIt(const sf::Vector2i &mousePosition);
    sf::Vector2f calculateMouseLocalPosition(const sf::Vector2i &mousePosition);
    virtual void drawToTarget(sf::RenderTarget &target);

private:
    bool isSelectable;
    bool isTransformed = true;
    sf::Transform combinedTransform;

    std::vector<AbstractNode *> children;
    AbstractNode *parent = nullptr;

    void setParent(AbstractNode *value);
    void dispose(bool toDelete);
};

}

#endif
