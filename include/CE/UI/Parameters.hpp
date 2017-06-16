#ifndef CE_PARAMETERS_HPP
#define CE_PARAMETERS_HPP

#include <SFML/System/Vector2.hpp>

namespace ce {

class Parameters
{
public:
    static Parameters &get()
    {
        static Parameters instance;
        return instance;
    }

    unsigned int getK() const;
    unsigned int getIndent() const;
    const sf::Vector2f &getElementSize() const;
    void update(unsigned int width, unsigned int height);

private:
    Parameters() {}
    ~Parameters() {}

    unsigned int k;
    unsigned int indent;
    sf::Vector2f elementSize;
};

}

#endif
