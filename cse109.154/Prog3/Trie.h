#ifndef Trie_H
#define Trie_H

#include <string>
#include "Node.h"
#include "Link.h"

using namespace std;

class Node;
class Link;

class Trie
{
 //assignment stated that all members public, this is not best practice
 public:
  
  //the start node of the Trie
  Node *startnode;
  
  //member functions
  void put(string key, int value);
  int get(string key);
  Node *makeLink(char c, Node *current);

  //constructor
  Trie(); 
  
  //destructor
  ~Trie();
  
};

#endif
