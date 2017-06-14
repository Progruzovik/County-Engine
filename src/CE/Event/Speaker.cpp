#include <CE/Event/Speaker.hpp>

namespace ce {

Speaker::Speaker(Listener *listener) : listener(listener) {}

void Speaker::setListener(Listener *value)
{
    listener = value;
}

void Speaker::declareEvent(const sf::String &name)
{
    if (listener) {
        listener->onEvent(this, name);
    }
}

}
