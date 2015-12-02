#include "Graph.h"
#include "Trie.h"
#include <vector>
#include <iostream>
#include <list>
namespace prog8lib
{
  Graph::Graph(int n, vector<string> wvector, unsigned int len):size(n), wordlength(len)
  {
    words = new Node*[n];
    t = new Trie();
    for(vector<string>::size_type i = 0; i != wvector.size(); i++)
    {
      t->put(wvector[i], i);
      words[i] = new Node(wvector[i]);
    }
    buildGraph(wvector);
  }

  int Graph::getSize()
  {
    return size;
  }

  Node** Graph::getWords()
  {
    return words;
  }
  
  unsigned int Graph::getLength()
  {
    return wordlength;
  }

  void Graph::buildGraph(vector<string> wvector)
  {
    for(vector<string>::size_type i = 0; i != wvector.size(); i++)
    {
      vector<string> same = findSimilar(wvector, wvector[i]);
      for(vector<string>::size_type ii = 0; ii != same.size(); ii++)
      {
        words[i]->createVertex(words[t->get(same[ii])]);
      }
    }
  } 

  vector<string> Graph::findSimilar(vector<string> wvector, string s)
  {
    vector<string> same;
    for(vector<string>::size_type iii = 0; iii != wvector.size(); iii++)
    {
      unsigned int score = 0;
      string w = wvector[iii];
      for(unsigned int windex = 0; windex < w.length(); windex++)
      {
        if(w[windex] == s[windex])
	{
          score++;
	}
      }
      if(score == s.length() - 1)
      {
        same.push_back(w);
      }
    }
    return same;
  }
  
  void Graph::BFS(string root, string target)
  {
    int index = t->get(root);
    bool *visited = new bool[size];
    Node *n;
    for(int c = 0; c < size; c++)
    {
      visited[c] = false;
    }
    list<Node*> queue;
    visited[index] = true;
    queue.push_back(words[index]);

    while(!queue.empty())
    {
      n = queue.front(); 
      cout << *n << " ";
      if(n->value == target)
      {
        cout << endl;
        break;
      }
      queue.pop_front();

      for(vector<Node*>::size_type d = 0; d != n->neighbors.size(); d++)
      {
        int id = t->get(n->neighbors[d]->value);
	if(!visited[id])
	{
          visited[id] = true;
	  queue.push_back(n->neighbors[d]);
	}
	
      }
    }

  }

  ostream& operator<<(ostream &os, Graph &g)
  {
    for(int b = 0; b < g.size; b++)
    {
      os << *g.words[b] << " ";
    }
    os << endl;
    return os;
  }
}
