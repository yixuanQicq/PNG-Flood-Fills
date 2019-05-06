/**
 * @file customColorPicker.h
 * Definition of a custom color picker.
 *
 */
#ifndef CUSTOMCOLORPICKER_H
#define CUSTOMCOLORPICKER_H

#include "colorPicker.h"

class customColorPicker : public colorPicker
{
    public:
    customColorPicker(PNG & img, double tolerance, HSLAPixel center);

    virtual HSLAPixel operator()(int x, int y);

    private:
        PNG im;
        double tol;
        HSLAPixel ctr;
        int colorData[11][10];

};

#endif
