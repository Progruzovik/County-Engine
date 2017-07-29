#ifndef CE_SPEAKER_HPP
#define CE_SPEAKER_HPP

#include <CE/Event/Listener.hpp>
#include <CE/Utility/EnableSharedFromThis.hpp>

namespace ce {

class Speaker : public EnableSharedFromThis<Speaker>
{
public:
    explicit Speaker(const std::shared_ptr<Listener> &listener = nullptr);

    void setListener(const std::shared_ptr<Listener> &value);

protected:
    void declareEvent(const sf::String &name);

private:
    std::weak_ptr<Listener> listener;
};

}

#endif
