#include<iostream>
#include<cmath>
#include "CImg.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <ctime>
 
using namespace std;
using namespace cv;
 
 
// Computes the x component of the gradient vector
// at a given point in a image.
// returns gradient in the x direction
int xGradient(CImg<double> image, int x, int y)
{
  return image(y-1, x-1) +
    2*image(y, x-1) +
    image(y+1, x-1) -
    image(y-1, x+1) -
    2*image(y, x+1) -
    image(y+1, x+1);
}
 
// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction
 
int yGradient(CImg<double> image, int x, int y)
{
  return image(y-1, x-1) +
    2*image(y-1, x) +
    image(y-1, x+1) -
    image(y+1, x-1) -
    2*image(y+1, x) -
    image(y+1, x+1);
}
 
int main()
{
 
  CImg<double> src, dst;
  int gx, gy, sum;
 
  // Load an image
  src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
  dst = src.clone();
  if( !src.data )
    { return -1; }
 
 
  for(int y = 0; y < src.rows; y++)
    for(int x = 0; x < src.cols; x++)
      dst(y,x) = 0.0;
 
  for(int y = 1; y < src.rows - 1; y++){
    for(int x = 1; x < src.cols - 1; x++){
      gx = xGradient(src, x, y);
      gy = yGradient(src, x, y);
      sum = abs(gx) + abs(gy);
      sum = sum > 255 ? 255:sum;
      sum = sum < 0 ? 0 : sum;
      dst(y,x) = sum;
    }
  }
 
  namedWindow("final");
  imshow("final", dst);
 
  namedWindow("initial");
  imshow("initial", src);
 
  waitKey();
 
 
  return 0;
}
