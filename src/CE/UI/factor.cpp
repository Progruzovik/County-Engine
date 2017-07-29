namespace ce {

static unsigned int factor = 0;

unsigned int getFactor()
{
    return factor;
}

void updateFactor(unsigned int width, unsigned int height)
{
    if (width == 2560 && height == 1440) {
        factor = 2;
    } else {
        factor = 1;
    }
}

}
