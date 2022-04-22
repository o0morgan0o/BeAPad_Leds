#ifndef MYCOLORS_H
#define MYCOLORS_H

#include <NeoPixelBus.h>

class MyColors {
    public:
    MyColors() {

        red =new RgbColor(colorSaturation, 0, 0);
        green = new RgbColor(0,colorSaturation,0);
        blue = new RgbColor(0,0,colorSaturation);
        white = new RgbColor(colorSaturation);
        black = new RgbColor(0);
    }


        uint8_t colorSaturation = 128;
        RgbColor* red;
        RgbColor* green;
        RgbColor* blue;
        RgbColor* white;
        RgbColor* black;

        // HslColor* hslRed(red);
        // HslColor* hslGreen(green);
        // HslColor* hslBlue(blue);
        // HslColor* hslWhite(white);
        // HslColor* hslBlack(black);
};

#endif