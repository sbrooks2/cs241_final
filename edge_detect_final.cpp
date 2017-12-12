#include "CImg.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <ctime>

#include<math.h>

using namespace std;
using namespace cimg_library;

// Computes the x component of the gradient vector
// at a given point in a image.
// returns gradient in the x direction
int xGradsobel(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return img (y-1, x-1) +
    2*img(y, x-1) +
    img(y+1, x-1) -
    img(y-1, x+1) -
    2*img(y, x+1) -
    img(y+1, x+1);
}

// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction
 
int yGradsobel(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return img(y-1, x-1) +
    2*img(y-1, x) +
    img(y-1, x+1) -
    img(y+1, x-1) -
    2*img(y+1, x) -
    img(y+1, x+1);
}

int xGradprew(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return -1*img(y-1, x-1) -
    img(y+1, x-1) +
    img(y-1, x+1) +
    img(y+1, x+1) -
    img(y, x-1) +
    img(y, x+1);
}

int yGradprew(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return -1*img(y-1, x-1) +
    img(y+1, x-1) -
    img(y-1, x+1) +
    img(y+1, x+1) +
    img(y+1, x) -
    img(y-1, x);
}

//This is an attempt to use the roberts cross algorithm of edge detection
int xGradrob(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return img(y-1, x) -
    img(y, x+1);
}

int yGradrob(CImg<double> * image, int x, int y) {
  CImg<double> img = * image;
  return -1*img(y-1, x) +
    img(y, x+1);
}

int main(int argc, char*argv[]) {

  char * input_file;
  char * output_file = (char *) "sobel.png";

  // take the arguments and store the filename and output name.
  if (argc < 3) {
    cout << "Give arguments in the form ./sobel <input_file> <output_file>";
  } 
  else if (argc == 2) {
    input_file = argv[1]; 
  } 
  else {
    input_file = argv[1];
    output_file = argv[2];
  }

 
  // load in the image.
  CImg<double> src(input_file);
  int gx, gy, sum;

  // check greyscale
  if (!(src.spectrum() == 1)) {
    for (int x = 0; x < src.width(); x++) {
      for (int y = 0; y < src.height(); y++) {
        src(x,y,0,0) = (src(x,y,0,0) * 0.3 +
         src(x,y,0,1) * 0.6 +
         src(x,y,0,2) * 0.1);
      }
    }
  }

  CImg<double> output(src.width(), src.height(),1 ,1);
 
  for(int y = 1; y < src.width() - 1; y++){
    for(int x = 1; x < src.height() - 1; x++){
      gx = xGradsobel(&src, x, y);
      gy = yGradsobel(&src, x, y);
      // sum = sqrt(pow(gx, 2) + pow(gy, 2));
      sum = abs(gx) + abs(gy);
      sum = sum > 255 ? 255:sum;
      sum = sum < 0 ? 0 : sum;
      output(y,x) = sum;
    }
  }

  output.save(output_file);
 
  return 0;
}
