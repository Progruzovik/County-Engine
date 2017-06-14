#ifndef EVENT_RECEIVER_HPP
#define EVENT_RECEIVER_HPP

#include <SFML/System/String.hpp>

namespace ce {

class Speaker;

class Listener
{
public:
    virtual ~Listener() {}
    virtual void onEvent(Speaker *speaker, const sf::String &name) = 0;
};

}

#endif
