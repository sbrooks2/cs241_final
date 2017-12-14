/* Adam Jussila, Sawyer Brooks, Rebecca Posner, and Patrick Smith
   This is a breadth first search algorithm, which is aimed at taking an edge
   map of a given image, then filling in the regions that constitute a single
   objet with the same color. Each object should be a different color.
   12/11/17
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
// #include <queue>
#include <math.h>

using namespace std;
using namespace cimg_library;

// define a graph with a position, neighbors, color, and explored flag.
class Graph
{
  int x, y;
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
  void setColor(int color);

  int getColor();

  // get the x and y coords of the pixel.
  int getX();
  int getY();

  // set whether or not we've looked at it.
  void setExplored(bool flag);

  // get info on isEdge
  bool edge();

  bool isExplored();

  void setedge(bool flag);
};

//the constructor. Just sets the values of the graph up.
Graph::Graph(int x, int y, bool edge)
{
  this->x = x;
  this->y = y;
  this->explored = false;
  this->color = 0;
  this->isEdge = edge;
}

// sets the color of the given graph node.
void Graph::setColor(int in_color)
{
  // Graph c = * curr;
  this->color = in_color;
}

// gets the color of the given graph node.
int Graph::getColor()
{
  // Graph c = * curr;
  return this->color;
}

// sets the explored flag for a given node.
void Graph::setExplored(bool flag)
{
  // Graph c = *curr;
  this->explored = flag;
}

// returns the x value of the graph.
int Graph::getX() 
{
  // Graph c = * curr;
  return this->x;
}

// returns the y value of the graph
int Graph::getY()
{
  // Graph c = * curr;
  return this->y;
}

// get info on isEdge
bool Graph::edge() {
  return this->isEdge;
}

// get info on explored
bool Graph::isExplored() {
  return this->explored;
}

void Graph::setedge(bool flag) {
  this->isEdge = flag;
}

// Design:
  /*
    front and back are a sentinel nodes
    bidirectional
  */
class Queue {
private:
  struct node {
    Graph * item;
    node * next;
    node * prev;
  };
  node * front;
  node * back;
  bool isempty;
public:
  Queue();
  ~Queue();
  bool isEmpty();
  Graph * pop();
  void push(Graph * graph);

  // do this at some point lol
  // void free_queue();
};

Queue::Queue() {
  this->front = new(node);
  this->back = new(node);
  this->back->next = front;
  this->front->prev = back;

  this->isempty = true;
}

Queue::~Queue() {
  delete[] front;
  delete[] back;
}

bool Queue::isEmpty() {
  return this->isempty;
}

void Queue::push(Graph * graph) {
  node * tmp = new(node);
  tmp->item = graph;

  tmp->prev = this->back;
  tmp->next = this->back->next;
  this->back->next->prev = tmp;
  this->back->next = tmp;
  this->isempty = false;
}

Graph * Queue::pop() {
  node * tmp = this->front->prev;
  Graph * toreturn = tmp->item;

  // adjust
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;

  if (this->back->next == this->front) {
    this->isempty = true;
  }
  // cout << toreturn->getColor() << " ";
  // delete(tmp);
  return toreturn;
}


int main(int argc, char * argv[])
{
  char * input_file;
  char * output_file = (char *) "segment.png";

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
  CImg<double> output(src.width(), src.height(), 1 , 3, 0);

  // graph queue = gq
  Queue gq;

  // color
  int curColor = 1;

  // we have to allocate to memory
  // because otherwise, the two-dimensional graph is too big
  // and we get a STACK OVERLFLOW
  // (I am happy to say I looked on stack overflow to debug this)
  Graph ** graph = new Graph * [src.width()];
  for (int i = 0; i < src.width(); ++i) {
    graph[i] = new Graph[src.height()];
  }

  // this breaks with large images
  // Graph graph = new Graph[src.width()][src.height()];

// Algorithm:
//   create a graph with x, y, isEdge from segmented image
//     all explored, color = 0
  for (int x = 0; x < src.width(); x++) {
    for (int y = 0; y < src.height(); y++) {
      // graph[x][y] = * new Graph(x, y, (src(x,y) != 0));
      graph[x][y] = * new Graph(x, y, (src(x,y) >= 130));
      
      if (x == 0 || y == 0) {
        graph[x][y].setedge(true);
      }

      //   if it's an edge:
      if ( (graph[x][y].edge()) ) {
  //     mark it as explored
        graph[x][y].setExplored(true);
      }
    }
  }

  
//   for every pixel in the graph (for row, for column)
  for (int x = 0; x < src.width(); x++) {
    for (int y = 0; y < src.height(); y++) {
//   if it's not explored
      if (! graph[x][y].isExplored()) {
//     then, add to queue
        gq.push(&graph[x][y]);

//     while queue isnt' empty:
        while (! gq.isEmpty()) {
//       for the current pixel:
          Graph tmp = * gq.pop();

//         mark it as explored
          tmp.setExplored(true);

//         mark it with color n
          // tmp.setColor(curColor);

//       check the neighbors of the pixel
//         make sure they're:
            // In the bounds of the image
            // Not already visited

          int tmpx = tmp.getX();
          int tmpy = tmp.getY();

          // cout << "Working with item " << tmpx << ", " << tmpy << "with color" << tmp.getColor() << endl;

          // left
          if ( (tmpx - 1 >= 0) && (! graph[tmpx - 1][tmpy].isExplored()) ) {
            // add to queue
            graph[tmpx - 1][tmpy].setExplored(true);
            graph[tmpx - 1][tmpy].setColor(curColor);
            gq.push(&graph[tmpx - 1][tmpy]);
          }

          // right
          if ( (tmpx + 1 < src.width()) && (! graph[tmpx + 1][tmpy].isExplored()) ) {
            // add to queue
            graph[tmpx + 1][tmpy].setExplored(true);
            graph[tmpx + 1][tmpy].setColor(curColor);
            gq.push(&graph[tmpx + 1][tmpy]);
          }

          // top
          if ( (tmpy + 1 < src.height()) && (! graph[tmpx][tmpy + 1].isExplored()) ) {
            // add to queue
            graph[tmpx][tmpy + 1].setExplored(true);
            graph[tmpx][tmpy + 1].setColor(curColor);
            gq.push(&graph[tmpx][tmpy + 1]);
          }

          // bottom
          if ( (tmpy -1 >= 0) && (! graph[tmpx][tmpy -1].isExplored()) ) {
            // add to queue
            graph[tmpx][tmpy - 1].setExplored(true);
            graph[tmpx][tmpy - 1].setColor(curColor);
            gq.push(&graph[tmpx][tmpy - 1]);
          }
        }
        ++curColor;
      }
    }
  }

  // delete(&gq);

  // exporting to file

  for(int x = 0; x < src.width(); x++){
      for(int y = 0; y < src.height(); y++){
        if (graph[x][y].edge()) {
          output(x,y,0) = 255;
          output(x,y,1) = 255;
          output(x,y,2) = 255;
        } else {

          output(x,y,0) = fmod((double) (
                      (double) (0 + (float) graph[x][y].getColor() * 255.0/(curColor-1))), 255
          );

          output(x,y,1) = fmod((double) (
                      (double) (85 + (float)  graph[x][y].getColor() * 255.0/(curColor-1))), 255
          );

          output(x,y,2) = fmod((double) (
                      (double) (170 + (float) graph[x][y].getColor() * 255.0/(curColor-1))), 255
          );
        }
        // delete(&graph[x][y]);
      }
  }

  output.save(output_file);
  // delete(&output);
  // delete(&src);
  return 0;
}
