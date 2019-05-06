#include "customColorPicker.h"

customColorPicker::customColorPicker(PNG & img, double tolerance, HSLAPixel center)
{
    im = img;
    tol = tolerance;
    ctr = center;

    // all data set to 0
    for(int i = 0; i<11 ; i++){
        for (int j = 0; j<10; j++){
            colorData[i][j] = 0;
        }
    }
    // first row set to 1
    for(int i = 2; i<=6 ; i++){
        if(i!=4){
            colorData[i][2] = 1;
        }
    }
    //second and third row set to 1
    for(int i = 1; i<=7; i++){
        for (int j = 3; j<=4; j++){
            colorData[i][j] = 1;
        }
    }
    // fourth row set to 1
    for(int i = 2; i<=6 ; i++){
        colorData[i][5] = 1;
    }
    // fifth row set to 1
    for(int i = 3; i<=5 ; i++){
        colorData[i][6] = 1;
    }
    colorData[4][7] =1;
}

HSLAPixel customColorPicker::operator()(int x, int y){
    HSLAPixel old = *im.getPixel(x,y);
    HSLAPixel white;
    white.h = 0;
    white.s = 0;
    white.l = 1;
    HSLAPixel pink;
    pink.h = 0;
    pink.s = 1;
    pink.l = 0.9;

    int currX = x%11;
    int currY = y%10;
    if(ctr.dist(*im.getPixel(x,y)) <= tol){
        if(colorData[currX][currY] == 0){
            return white;
        }
        else{
            return pink;
        }
    }
    return old;
}
