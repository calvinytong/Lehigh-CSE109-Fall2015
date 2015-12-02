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
  class Graph 
  {
   public:
     Graph(int n, vector<string> wvector, unsigned int len);

     int getSize();
     Node** getWords();
     unsigned int getLength();
     void BFS(string root, string target);
     Trie* getTrie();
     friend ostream& operator<<(ostream &os, Graph &g);

   private:
     int size;
     Node** words;
     Trie *t;
     vector<string> findSimilar(vector<string> wvector, string s);
     unsigned int wordlength;

     void buildGraph(vector<string> wvector);
  };

}
#endif
