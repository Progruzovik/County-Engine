#ifndef CE_STAGE_HPP
#define CE_STAGE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <CE/Event/Listener.hpp>

namespace ce {

class Act;

class Stage : public sf::RenderWindow
{
public:
    Stage(const sf::VideoMode &mode, const sf::String &title, sf::Uint32 style = sf::Style::Default);

    virtual void onEvent(const std::shared_ptr<Act> &act, const sf::String &name) {}
    void setAct(const std::shared_ptr<Act> &value);
    const std::shared_ptr<Act> &getAct() const;
    void start();

private:
    sf::View view;
    std::shared_ptr<Act> act;

    virtual void onUpdated() {}
    void update();
};

}

#endif
