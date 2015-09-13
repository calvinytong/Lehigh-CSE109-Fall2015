#ifndef NODE_H
#define NODE_H

#include <iostream>
#include "Link.h"
using namespace std;

class Link;

class Node
{
 public:
  int value;
  Link *links[10];
  int numlinks;

  Node();
  Node(int v);

  ~Node();
};

#endif
