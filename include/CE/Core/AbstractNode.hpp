#ifndef CE_ABSTRACTNODE_HPP
#define CE_ABSTRACTNODE_HPP

#include <CE/Event/Speaker.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Window.hpp>

namespace ce {

class AbstractNode : public Speaker
{
public:
    AbstractNode(bool isSelectable = false, bool isUpdatable = false,
                 Listener *listener = nullptr);
    virtual ~AbstractNode();

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

    void update();
    void select(const sf::Vector2i &mousePosition);

    void removeFromParent(bool toDelete = false);
    void addChild(AbstractNode *child);
    void removeChild(AbstractNode *child, bool toDelete = false);
    void removeChildren(bool toDelete = false, unsigned long firstIndex = 0, long lastIndex = -1);

protected:
    virtual void onAdded() {};
    virtual void onUpdated();
    virtual void onMouseEntered() {}
    virtual void onMouseLeft();
    virtual void onLeftMouseButtonPressed();
    virtual void onLeftMouseButtonReleased();
    virtual void onRightMouseButtonReleased();

    virtual const sf::Transformable &getTransformable() const = 0;
    const std::vector<AbstractNode *> &getChildren() const;

    void makeTransformed();
    virtual bool checkMouseOnIt(const sf::Vector2i &mousePosition);
    bool checkChildSelected(const AbstractNode *child) const;

    virtual void drawToTarget(sf::RenderTarget *target);
    sf::Vector2f calculateMouseLocalPosition();

private:
    bool isSelectable;
    bool isUpdatable;
    bool isTransformed = true;
    sf::Transform combinedTransform;

    std::vector<AbstractNode *> children;
    AbstractNode *parent = nullptr;
    AbstractNode *selectedChild = nullptr;

    void setParent(AbstractNode *value);
    AbstractNode *getSelectedChild(const sf::Vector2i &mousePosition);
    void deselectChild();
};

}

#endif
