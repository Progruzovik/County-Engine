#include <CE/Event/Speaker.hpp>

namespace ce {

Speaker::Speaker(const std::shared_ptr<Listener> &listener) : listener(listener) {}

void Speaker::setListener(const std::shared_ptr<Listener> &value)
{
    listener = value;
}

void Speaker::declareEvent(const sf::String &name)
{
    if (!listener.expired()) {
        listener.lock()->onEvent(sharedFromThis(), name);
    }
}

}
