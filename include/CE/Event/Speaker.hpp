#ifndef CE_SPEAKER_HPP
#define CE_SPEAKER_HPP

#include <CE/Event/Listener.hpp>

namespace ce {

class Speaker
{
public:
    Speaker(Listener *listener = nullptr);
    virtual ~Speaker() {}

    void setListener(Listener *value);

protected:
    void declareEvent(const sf::String &name);

private:
    Listener *listener;
};

}

#endif
