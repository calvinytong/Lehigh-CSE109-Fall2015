
#ifndef Trie_H
#define Trie_H

#include <iostream>
#include <string>
#include "Node.h"
#include "Link.h"

using namespace std;

class Node;
class Link;

class Trie
{
 public:
  Node *startnode;

  void put(string key, int value);
  int get(string key);

  Trie();

  ~Trie();
};

#endif
