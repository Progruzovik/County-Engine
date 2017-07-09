#ifndef CE_ACT_HPP
#define CE_ACT_HPP

#include <CE/Core/MimicNode.hpp>
#include <CE/Core/Stage.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace ce {

class Act : public Node
{
public:
    enum class Mode { STATIC, MOVABLE_BY_MOUSE, CENTERED_ON_NODE };

    Act(Mode contentMode, Stage &stage, const sf::Color &bgColor = sf::Color::Black);

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

    void setCenter(const std::shared_ptr<TransformableNode> &value);
    void setContent(const std::shared_ptr<TransformableNode> &value);
    void setLeftUi(const std::shared_ptr<TransformableNode> &value);
    void setRightUi(const std::shared_ptr<TransformableNode> &value);
    void setTopUi(const std::shared_ptr<TransformableNode> &value);
    void setBottomUi(const std::shared_ptr<TransformableNode> &value);
    void setOverlayUi(const std::shared_ptr<TransformableNode> &value);

    virtual void setUpNodes();
    void update() override;

protected:
    sf::Color bgColor;

    bool checkPointOnIt(const sf::Vector2i &point) override;
    void declareEvent(const sf::String &name);

private:
    static constexpr unsigned int SCROLL_SPEED = 5;

    const sf::Transform mockTransform;
    Mode contentMode;
    sf::Vector2i savedMousePosition;
    bool isRightMouseButtonPressed = false;
    bool isMouseMovedWithRightButton = false;
    Stage &stage;

    std::shared_ptr<Node> selectedNode;
    std::shared_ptr<MimicNode> contentLayer = std::make_shared<MimicNode>();

    std::shared_ptr<TransformableNode> center;
    std::shared_ptr<TransformableNode> content;
    std::shared_ptr<TransformableNode> leftUi;
    std::shared_ptr<TransformableNode> rightUi;
    std::shared_ptr<TransformableNode> topUi;
    std::shared_ptr<TransformableNode> bottomUi;
    std::shared_ptr<TransformableNode> overlayUi;

    void updateUi(const std::shared_ptr<TransformableNode> &oldUi, const std::shared_ptr<TransformableNode> &newUi);
    virtual void resizeUi() {}
};

}

#endif
