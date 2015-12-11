#ifndef TRIENODE_H
#define TRIENODE_H

#include "Link.h"

using namespace std;

namespace prog8lib
{
  class TrieNode
  {
   //the instructions specified all public member functions and variables,
   //but this is not best practice
   public:
    //the int value of stored inside the node
    int value;
    
    //the pointer to the dynamically allocated array of link pointers
    Link **links;
  
    //the number of links the node has formed
    int numlinks;
  
    //constructors
    TrieNode();
    TrieNode(int v);
    
    //public member functions
    TrieNode *findChar(char c);
    
    //destructor
    ~TrieNode();
  };
}
#endif
