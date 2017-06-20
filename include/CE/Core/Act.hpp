#ifndef CE_ACT_HPP
#define CE_ACT_HPP

#include <CE/Event/Speaker.hpp>
#include <CE/Core/MimicNode.hpp>
#include <CE/Core/Stage.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace ce {

class Act : public Node, public Speaker
{
public:
    enum class Mode { STATIC, MOVABLE_BY_MOUSE, CENTERED_ON_NODE };

    Act(Stage *stage, Mode contentMode, const sf::Color &bgColor = sf::Color::Black);

    void onMouseMoved(const sf::Vector2i &mousePosition) override;
    void onMouseLeft() override;
    void onLeftMouseButtonPressed() override;
    void onLeftMouseButtonReleased() override;
    void onRightMouseButtonPressed();
    void onRightMouseButtonReleased() override;
    virtual void onKeyReleased(sf::Keyboard::Key key) {}

    const sf::Color &getBgColor() const;
    const sf::Transform &getCombinedTransform() override;
    const sf::Window &getWindow() const override;

    void setCenter(TransformableNode *value);
    void setContent(TransformableNode *value);
    void setLeftUi(TransformableNode *value);
    void setRightUi(TransformableNode *value);
    void setTopUi(TransformableNode *value);
    void setBottomUi(TransformableNode *value);

    virtual void setUpNodes();
    void update() override;

protected:
    sf::Color bgColor;

    bool checkPointOnIt(const sf::Vector2i &point) override;

private:
    static constexpr unsigned int SCROLL_SPEED = 5;

    const sf::Transform mockTransform;
    Mode contentMode;
    sf::Vector2i savedMousePosition;
    bool isRightMouseButtonPressed = false;
    bool isMouseMovedWithRightButton = false;
    sf::RenderWindow &window;

    Node *selectedNode = nullptr;
    MimicNode *contentLayer = new MimicNode();

    TransformableNode *center = nullptr;
    TransformableNode *content = nullptr;
    TransformableNode *leftUi = nullptr;
    TransformableNode *rightUi = nullptr;
    TransformableNode *topUi = nullptr;
    TransformableNode *bottomUi = nullptr;

    void updateUi(TransformableNode *oldUi, TransformableNode *newUi);
    virtual void resizeUi() {}
};

}

#endif
