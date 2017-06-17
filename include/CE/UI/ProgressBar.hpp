#ifndef CE_PROGRESSBAR_HPP
#define CE_PROGRESSBAR_HPP

#include <CE/Core/RectangleNode.hpp>

namespace ce {

class ProgressBar final : public RectangleNode
{
public:
    ProgressBar(float width, float height, const sf::Color &color = sf::Color::Black,
                float maximum = 100, float minimum = 0);

    float getWidth() override;
    void setWidth(float width) override;

    void setMinimum(float minimum);
    void setMaximum(float maximum);
    void setValue(float value);

private:
    float maxWidth;
    float minimum;
    float maximum;
    float value;

    void calculateWidth();
};

}

#endif
