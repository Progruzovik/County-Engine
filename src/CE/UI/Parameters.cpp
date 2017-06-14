#include <CE/UI/Parameters.hpp>

namespace ce {

unsigned int Parameters::getK() const
{
    return k;
}

unsigned int Parameters::getIndent() const
{
    return indent;
}

const sf::Vector2f &Parameters::getElementSize() const
{
    return elementSize;
}

void Parameters::update(unsigned int width, unsigned int height)
{
    if (width == 2560 && height == 1440) {
        k = 2;
    } else {
        k = 1;
    }
    indent = k * 20;
    elementSize.x = k * 165;
    elementSize.y = k * 40;
}

}
