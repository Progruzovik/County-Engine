#ifndef CE_ACT_HPP
#define CE_ACT_HPP

#include <CE/Core/RootNode.hpp>
#include <CE/Core/Stage.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace ce {

class Act : public Speaker
{
public:
    enum class Mode { STATIC, MOVABLE_BY_MOUSE, CENTERED_ON_NODE };

    Act(Stage *stage, Mode contentMode, const sf::Color &bgColor = sf::Color::Black);

    void onMouseMoved(const sf::Vector2i &mousePosition);
    void onMouseLeft();
    void onLeftMouseButtonPressed();
    void onLeftMouseButtonReleased();
    void onRightMouseButtonPressed();
    void onRightMouseButtonReleased();
    virtual void onKeyReleased(sf::Keyboard::Key key) {}

    const sf::Color &getBgColor() const;
    void setCenter(AbstractNode *value);
    void setContent(AbstractNode *value);
    void setLeftUi(AbstractNode *value);
    void setRightUi(AbstractNode *value);
    void setTopUi(AbstractNode *value);
    void setBottomUi(AbstractNode *value);

    virtual void setUpNodes();
    void update();

protected:
    sf::Color bgColor;
    RootNode root;

    virtual void resizeUi() {}

private:
    static constexpr unsigned int SCROLL_SPEED = 5;

    Mode contentMode;
    sf::Vector2i savedMousePosition;
    bool isRightMouseButtonPressed = false;
    bool isMouseMovedWithRightButton = false;

    AbstractNode *center = nullptr;
    AbstractNode *content = nullptr;
    AbstractNode *leftUi = nullptr;
    AbstractNode *rightUi = nullptr;
    AbstractNode *topUi = nullptr;
    AbstractNode *bottomUi = nullptr;

    void updateUi(AbstractNode *oldUi, AbstractNode *newUi);
};

}

#endif
