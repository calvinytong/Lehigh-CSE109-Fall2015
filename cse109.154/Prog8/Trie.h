#ifndef Trie_H
#define Trie_H

#include <string>
#include "TrieNode.h"
#include "Link.h"

using namespace std;

class TrieNode;
class Link;
namespace prog8lib
{
  class Trie
  {
   //assignment stated that all members public, this is not best practice
   public:
    
    //the start node of the Trie
    TrieNode *startnode;
    
    //member functions
    void put(string key, int value);
    int get(string key);
    TrieNode *makeLink(char c, TrieNode *current);
  
    //constructor
    Trie(); 
    
    //destructor
    ~Trie();
    
  };
}
#endif
