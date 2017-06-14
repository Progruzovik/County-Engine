#include <CE/UI/ProgressBar.hpp>

namespace ce {

ProgressBar::ProgressBar(float width, float height, const sf::Color &color, int maximum, int minimum)
    : RectangleNode(width, height, color), maxWidth(width), minimum(minimum), maximum(maximum) {}

float ProgressBar::getWidth()
{
    return maxWidth;
}

void ProgressBar::setWidth(float width)
{
    maxWidth = width;
    calculateWidth();
}

void ProgressBar::setMinimum(float minimum)
{
    this->minimum = minimum;
}

void ProgressBar::setMaximum(float maximum)
{
    this->maximum = maximum;
}

void ProgressBar::setValue(float value)
{
    if (value < minimum) {
        this->value = minimum;
    } else if (value > maximum) {
        this->value = maximum;
    } else {
        this->value = value;
    }
    calculateWidth();
}

void ProgressBar::calculateWidth()
{
    ce::RectangleNode::setWidth((value - minimum) / (maximum - minimum) * maxWidth);
}

}
