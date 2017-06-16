#ifndef CORE_ABSTRACTACT_HPP
#define CORE_ABSTRACTACT_HPP

#include <CE/Core/RootNode.hpp>
#include <CE/Event/Speaker.hpp>

namespace ce {

enum class ContentMode { STATIC, MOVABLE_BY_MOUSE, CENTERED_ON_NODE };

class AbstractAct : public Speaker, public Listener
{
public:
    AbstractAct(Stage *stage, ContentMode contentMode,
                const sf::Color &bgColor = sf::Color::Black);

    void onLeftMouseButtonPressed();
    void onLeftMouseButtonReleased();
    void onRightMouseButtonPressed();
    void onRightMouseButtonReleased();

    const sf::Color &getBgColor() const;

    virtual void setUpNodes();
    void update();

protected:
    sf::Color bgColor;

    void setCenter(AbstractNode *value);
    void setContent(AbstractNode *value);
    void setLeftUi(AbstractNode *value);
    void setRightUi(AbstractNode *value);
    void setTopUi(AbstractNode *value);
    void setBottomUi(AbstractNode *value);

    void removeContent();
    virtual void resizeUi() = 0;

private:
    static constexpr unsigned int SCROLL_SPEED = 5;

    ContentMode contentMode;
    bool isRightMouseButtonPressed = false;
    bool isMouseMovedWithRightButton = false;
    sf::Vector2u mousePosition;
    RootNode root;

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
