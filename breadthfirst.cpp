/* Adam Jussila
   This is a breadth first search algorithm, which is aimed at taking an edge
   map of a given image, then filling in the regions that constitute a single
   objet with the same color. Each object should be a different color.
   12/11/17

   The main inspiritation was taken from:
   https://gist.github.com/sameer-j/7d944595a386fe70aa79, where the algorithm 
   was laid out. I will be modifying it to help us create something that will 
   work for our code.

*/


#include "CImg.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <ctime>

#include <list>
#include <algorithm>

using namespace std;
using namespace cimg_library;

// define a graph with a position, neighbors, color, and explored flag.
class Graph
{
  int x, y;
  Graph *up, *left, *right, *down;
  int color;
  bool explored;
  bool isEdge;

public:
  // 0 arg constructor
  Graph() {
    this->x = 0;
    this->y = 0;
    this->color= 0;
    this->explored = false;
    this->isEdge = false;
  }

  // constructor
  Graph(int x, int y, bool edge);

  // set the color of a pixel.
  void setColor(Graph *curr, int color);

  // get the x and y coords of the pixel.
  int getX(Graph *curr);
  int getY(Graph *curr);

  // set whether or not we've looked at it.
  int setExplored(Graph *curr, int flag);
};

//the constructor. Just sets the values of the graph up.
Graph::Graph(int x, int y, bool edge)
{
  this->x = x;
  this->y = y;
  setExplored(this, false);
  setColor(this, 0);
  this->isEdge = edge;
}

// sets the color of the given graph node.
void Graph::setColor( Graph *curr, int color)
{
  c = *curr;
  c->color = int;
}

// sets the explored flag for a given node.
void Graph::setExplored( Graph *curr, bool flag)
{
  c = *curr;
  c->explored = flag;
}

// returns the x value of the graph.
void Graph::getX( Graph *curr ) 
{
  c = *curr;
  return c->x;
}

// returns the y value of the graph
void Graph::getY( Graph *curr )
{
  c = *curr;
  return c->y;
}


int main(int argc, char * argv[])
{
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

  CImg<double> src(input_file);
  CImg<double> output(src.width(), src.height(),1 ,1);
  Graph ** graph;

  graph = new Graph[512][512];

// Algorithm:
//   create a graph with x, y, isedge from segmented image
//     all explored, color = 0
  for (int x = 0; x < src.width(); x++) {
    for (int y = 0; y < src.height(); y++) {
      graph[x][y] = * new Graph(x, y, (src(x,y) != 0));
    }
  }

//   for every pixel in the graph (for row, for column)
//   if it's an edge:
//     mark it as an edge
//     mark it as explored

//   else if it's not explored
//     then, add to worklist

//     while worklist isnt' empty:
//       for the current pixel:
//         mark it as explored
//         mark it with color n

//       check the neighbors of the pixel
//         make sure the pixels are within the bounds of the image

//       if these pixels aren't edges:
//         add them to the worklist

//       otherwise:
//         mark them as edges
//         mark them as explored 

//     after clearing the worklist:
//       increment color by 1

  
  

  return 0;
}
