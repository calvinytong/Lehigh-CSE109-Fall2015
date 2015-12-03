#include "Graph.h"
#include "Trie.h"
#include <vector>
#include <iostream>
#include <list>
#include <stack>
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
  
  Trie* Graph::getTrie()
  {
    return t;
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
    Node *current;
    list<Node*> queue;
    Node *next; 
    for(int c = 0; c < size; c++)
    {
      visited[c] = false;
    }
    words[index]->distance = 0;
    visited[index] = true;
    queue.push_back(words[index]);

    while(!queue.empty())
    {
      current = queue.front(); 
      queue.pop_front();
      if(current->value == target)
      {
        stack<string> s;
	next = current;
	int dist = next->distance;
	for(int i = 0; i <= dist; i++)
	{
	  s.push(next->value);
          next = next->parent;
	}
	for(int i = 0; i <= dist; i++)
	{
          cout << s.top() << " ";
	  s.pop();
	}
	cout << endl;
	return;
      }
      for(vector<Node*>::size_type d = 0; d != current->neighbors.size(); d++)
      {
        int id = t->get(current->neighbors[d]->value);
	if(!visited[id])
	{
          visited[id] = true;
	  current->neighbors[d]->distance = current->distance + 1;
	  current->neighbors[d]->parent = current;
	  queue.push_back(current->neighbors[d]);
	}	
      }
    }
    cout << "INVALID " << root << " " << target << endl;
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
