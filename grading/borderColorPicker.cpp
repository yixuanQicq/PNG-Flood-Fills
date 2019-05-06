 #include "borderColorPicker.h"

borderColorPicker::borderColorPicker(HSLAPixel fillColor, PNG & img, double tolerance,HSLAPixel center)
{
/* Your code here! */
    color = fillColor;
    im = img;
    tol = tolerance;
    ctr = center;
}

HSLAPixel borderColorPicker::operator()(int x, int y)
{
/* Your code here! */
    HSLAPixel *old = im.getPixel(x,y);
    int height = (int)im.height();
    int width = (int)im.width();
    if((x+3) > width-1 || ctr.dist(*im.getPixel(x+3,y)) > tol){
        return color;
    }
    if((x-3) < 0 || ctr.dist(*im.getPixel(x-3,y)) > tol){
        return color;
    }
    if((y+3) > height-1 || ctr.dist(*im.getPixel(x,y+3)) > tol){
        return color;
    }
    if((y-3) < 0 || ctr.dist(*im.getPixel(x,y-3)) > tol){
        return color;
    }
    // for (int i = -2; i< 3 ; i++){
    //     for (int j = -2; j<3; j++){
    //         int currX = x+i;
    //         int currY = y+i;
    //             if(currX<0 || (currX > width-1) || currY <0 || (currY> height-1) ||(im.getPixel(i,j)->dist(ctr) > tol)){
    //                 return color;
    //             }
    //     }
    // }
    for(int i = x-2; i < x+3; i++){
        for(int j = y-2; j < y+3; j++){
            if(i<0 || (i > width-1) || j<0 || (j> height-1) ||(im.getPixel(i,j)->dist(ctr) > tol)){
                    return color;
                }
        }
    }

    return *old;
}
