#ifndef CORE_ABSTRACTACT_HPP
#define CORE_ABSTRACTACT_HPP

#include <CE/Core/RootNode.hpp>
#include <CE/Event/Speaker.hpp>

namespace ce {

class AbstractAct : public ce::Speaker, public ce::Listener
{
public:
    AbstractAct(Stage *stage, bool isContentMovable = false,
                const sf::Color &bgColor = sf::Color::White);

    void onLeftMouseButtonPressed();
    void onLeftMouseButtonReleased();
    void onRightMouseButtonPressed();
    void onRightMouseButtonReleased();

    const sf::Color &getBgColor() const;

    virtual void setUpNodes();
    void update();

protected:
    sf::Color bgColor;

    void setContent(AbstractNode *value);
    void setLeftUi(AbstractNode *value);
    void setRightUi(AbstractNode *value);
    void setTopUi(AbstractNode *value);
    void setBottomUi(AbstractNode *value);

    void removeContent();
    virtual void resizeUi() = 0;

private:
    static constexpr unsigned int SCROLL_SPEED = 5;

    bool isContentMovable;
    bool isRightMouseButtonPressed = false;
    bool isMouseMovedWithRightButton = false;
    sf::Vector2u mousePosition;

    std::unique_ptr<RootNode> root;
    AbstractNode *content = nullptr;
    AbstractNode *leftUi = nullptr;
    AbstractNode *rightUi = nullptr;
    AbstractNode *topUi = nullptr;
    AbstractNode *bottomUi = nullptr;

    void updateUi(AbstractNode *oldUi, AbstractNode *newUi);
};

}

#endif
