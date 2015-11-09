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
 
  string keys[256];
  int numkeys;

  //member functions
  void put(string key, string value);
  string get(string key);
  Node *makeLink(char c, Node *current);
  void printPlainText();
  //constructor
  Trie(); 
  
  //destructor
  ~Trie();

  friend ostream& operator<<(ostream& in, Trie& t);
  
};

#endif
