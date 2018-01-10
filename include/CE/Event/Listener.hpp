#ifndef CE_RECEIVER_HPP
#define CE_RECEIVER_HPP

#include <SFML/System/String.hpp>
#include <memory>

namespace ce {

class Speaker;

class Listener
{
public:
    virtual void onEvent(const std::shared_ptr<Speaker> &speaker, const sf::String &name) = 0;
};

}

#endif
