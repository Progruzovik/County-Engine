#include <CE/Core/Stage.hpp>
#include <CE/Core/Act.hpp>
#include <CE/UI/Parameters.hpp>
#include <SFML/Window/Event.hpp>

namespace ce {

Stage::Stage(const sf::VideoMode &mode, const sf::String &title)
    : sf::RenderWindow(mode, title), view(sf::FloatRect(0, 0, mode.width, mode.height))
{
    setVerticalSyncEnabled(true);
    setView(view);
}

void Stage::setAct(const std::shared_ptr<Act> &value)
{
    act = value;
}

const std::shared_ptr<Act> &Stage::getAct() const
{
    return act;
}

void Stage::start()
{
    while (isOpen()) {
        update();
    }
}

void Stage::update()
{
    onUpdated();

    sf::Event event;
    while (pollEvent(event)) {
        if (event.type == sf::Event::Resized) {
            Parameters::get().update(event.size.width, event.size.height);
            view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
            setView(view);
            act->setUpNodes();
        } else if (event.type == sf::Event::MouseMoved) {
            act->onMouseMoved(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
        } else if (event.type == sf::Event::MouseLeft) {
            act->onMouseLeft();
        } else if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                act->onLeftMouseButtonPressed();
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                act->onRightMouseButtonPressed();
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                act->onLeftMouseButtonReleased();
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                act->onRightMouseButtonReleased();
            }
        } else if (event.type == sf::Event::KeyReleased) {
            act->onKeyReleased(event.key.code);
        } else if (event.type == sf::Event::Closed) {
            close();
        }
    }

    clear(act->getBgColor());
    act->update();
    display();
}

}
