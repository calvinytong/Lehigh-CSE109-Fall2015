#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include "Node.h"
#include "Trie.h"
#include <ostream>

using namespace std;

class Trie;
namespace prog8lib
{
  //the graph class creates a graph where each word is connected to all words that
  //are one letter away from it
  class Graph 
  {
   public:
     //constructs the graph and hashes the dictionary
     Graph(int n, vector<string> wvector, unsigned int len);

     //gets the size
     int getSize();

     //gets the words
     Node** getWords();

     //gets the length
     unsigned int getLength();

     //preforms a binary search and prints out the path
     void BFS(string root, string target);

     //gets the trie
     Trie* getTrie();

     //overloads the insertion operator for debug
     friend ostream& operator<<(ostream &os, Graph &g);

   private:
     //number of words
     int size;

     //pointer to words
     Node** words;

     //pointer to the dict hash
     Trie *t;

     //private method for finding similar words
     vector<string> findSimilar(vector<string> wvector, string s);
     unsigned int wordlength;
     
     //private method that builds the graph
     void buildGraph(vector<string> wvector);
  };
}
#endif
