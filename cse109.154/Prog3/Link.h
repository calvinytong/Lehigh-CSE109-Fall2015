#ifndef Link_H
#define Link_H

#include <iostream>
#include "Node.h"

using namespace std;

class Node;

class Link
{
 public:
  char letter;
  Node *next;

  Link(char l, Node *n);

  ~Link();
};

#endif
