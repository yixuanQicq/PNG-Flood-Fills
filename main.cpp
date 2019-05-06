#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "filler.h"
#include "stripeColorPicker.h"
#include "rainbowColorPicker.h"
#include "borderColorPicker.h"

using namespace std;
using namespace cs221util;

#define FUNCTORTESTHEIGHT 60
#define FUNCTORTESTWIDTH 60
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45
#define FUNCTORTESTGRIDSPACING 8

// use the following for border tests
#define SOLIDX 80
#define SOLIDY 80
#define SOLIDTOLERANCE 0.01
#define SOLIDTESTIMAGE "originals/Canada.png"
#define SOLIDFRAMEFREQ 100

// use the following for stripe tests
#define GRIDX 120
#define GRIDY 75
#define GRIDTOLERANCE 0.008
#define GRIDTESTIMAGE "originals/mooncake.png"
#define GRIDFRAMEFREQ 50
#define GRIDGRIDSPACING 5

// use for rainbow
#define RAINFREQ 1.0/1000.0
#define RAINTOLERANCE 0.05
#define RAINX 75
#define RAINY 75
#define RAINTESTIMAGE "originals/cloud.png"
#define RAINFRAMEFREQ 500

int main(int argc, char* argv[]){
    // Check the number of parameters
    if (argc != 5) {
        // Tell the user how to run the program
        printf("%d\n", argc);
        printf("%s\n", "Note image must be in <images> directory, you should omit the .png suffix in file name");
        printf("filler should be one of the following: Strip, Rainbow, Heart");
        printf("last two input value should be x and y starting points, respectively")
        std::cerr << "Usage: <orig_image_file_name> <compression factor>" << std::endl;
        return 1;
    }
    // read in an image
	PNG origImg;
	string prefix = "images/";
	string orig_image_file_name = argv[1];
	string suffix = ".png";
	string orig_image_location = prefix.append(orig_image_file_name);
	orig_image_location = orig_image_location.append(suffix);
	origImg.readFromFile(orig_image_location);

    animation anim;
    if (strcmp(argv[2], "Strip") == 0) {
        HSLAPixel px(200., 1.0, 0.5);
        anim = filler::fillStripeBFS(origImg, argv[3], argv[4], px, GRIDGRIDSPACING,
                                     GRIDTOLERANCE, GRIDFRAMEFREQ);
    }

    if (strcmp(argv[2], "Rainbow") == 0) {
        anim = filler::fillRainDFS(origImg, argv[3], argv[4], RAINFREQ,
                                         RAINTOLERANCE,
                                         RAINFRAMEFREQ);
    }

    animation anim;
    if (strcmp(argv[2], "Heart") == 0) {
        anim = filler::fillCustomBFS(origImg, argv[3], argv[4], RAINTOLERANCE,1000);
    }

    PNG result = anim.write("images/output.gif");
    result.writeToFile("images/output.png");

}