#ifndef CORE_STAGE_HPP
#define CORE_STAGE_HPP

#include <CE/Event/Listener.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ce {

class AbstractAct;

class Stage : public sf::RenderWindow, public Listener
{
public:
    Stage(const sf::VideoMode &mode, const sf::String &title, AbstractAct *currentAct);
    ~Stage();

    sf::View &getMutableView();

    void onEvent(Speaker *, const sf::String &) override {}
    void start();

protected:
    AbstractAct *currentAct;

    virtual void update();

private:
    sf::View view;

    void updateView();
};

}

#endif
