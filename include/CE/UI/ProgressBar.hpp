#ifndef UI_PROGRESSBAR_HPP
#define UI_PROGRESSBAR_HPP

#include <CE/Core/RectangleNode.hpp>

namespace ce {

class ProgressBar final : public ce::RectangleNode
{
public:
    ProgressBar(float width, float height, const sf::Color &color = sf::Color::Black,
                int maximum = 100, int minimum = 0);

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
