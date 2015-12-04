#include "Graph.h"
#include "Trie.h"
#include <vector>
#include <iostream>
#include <list>
#include <stack>
namespace prog8lib
{
  //initializes the graph
  Graph::Graph(int n, vector<string> wvector, unsigned int len):size(n), wordlength(len)
  {
    //make words a new node* array
    words = new Node*[n];

    //set t to a new trie
    t = new Trie();

    //hash the dictionary into t
    for(vector<string>::size_type i = 0; i != wvector.size(); i++)
    {
      t->put(wvector[i], i);
      words[i] = new Node(wvector[i]);
    }

    //build the graph using the word vector
    buildGraph(wvector);
  }
 
  //getter methods
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
  
  //builds the graph from a given word vector
  void Graph::buildGraph(vector<string> wvector)
  {
    //for each word in wvector
    for(vector<string>::size_type i = 0; i != wvector.size(); i++)
    { 
      //find the similar words
      vector<string> same = findSimilar(wvector, wvector[i]);
      
      //create the vertex using the trie to retreive the word
      for(vector<string>::size_type ii = 0; ii != same.size(); ii++)
      {
        words[i]->createVertex(words[t->get(same[ii])]);
      }
    }
  } 
  
  //finds similar
  vector<string> Graph::findSimilar(vector<string> wvector, string s)
  {
    //the same vector will hold the words
    vector<string> same;
    
    //iterate thru the word vector
    for(vector<string>::size_type iii = 0; iii != wvector.size(); iii++)
    {
      //set the score variable to 0
      unsigned int score = 0;
      string w = wvector[iii];
      
      //for each letter in the words
      for(unsigned int windex = 0; windex < w.length(); windex++)
      {
        //if the letters are the same increment score
        if(w[windex] == s[windex])
	{
          score++;
	}
      }

      //if the score is equal to the length - 1 then the word is valid so push it into the vector
      if(score == s.length() - 1)
      {
        same.push_back(w);
      }
    }
    return same;
  }
  
  //preforms a BFS search thru the graph to find the shortest path between the two words
  void Graph::BFS(string root, string target)
  {
    //get the root index from the hash
    int index = t->get(root);

    //create a new boolean array to track which nodes we have visited
    bool *visited = new bool[size];
    
    //pointer to the current node
    Node *current;

    //queue for bfs
    list<Node*> queue;
    
    //pointer to next node
    Node *next; 

    //set the array to false
    for(int c = 0; c < size; c++)
    {
      visited[c] = false;
    }

    //set the root distance to 0
    words[index]->distance = 0;
    
    //mark as visited
    visited[index] = true;

    //push the word into the queue
    queue.push_back(words[index]);

    while(!queue.empty())
    {
      //pop the first item off the queue
      current = queue.front(); 
      queue.pop_front();

      //if we have foudn the value then stop the search
      if(current->value == target)
      {
        //stack to print words in the correct order
        stack<string> s;
	next = current;
	
	//get the distance from the root
	int dist = next->distance;
	
	//trace the links back to the root
	for(int i = 0; i <= dist; i++)
	{
	  //push each node onto the stack
	  s.push(next->value);
          next = next->parent;
	}

	//write out the stack and then return
	for(int i = 0; i <= dist; i++)
	{
          cout << s.top() << " ";
	  s.pop();
	}
	cout << endl;
	return;
      }
      //if we ahve not found the value then explore the neighbors of current
      for(vector<Node*>::size_type d = 0; d != current->neighbors.size(); d++)
      {
        int id = t->get(current->neighbors[d]->value);
	if(!visited[id])
	{
	  //if the node has not been visited then set visited to true
          visited[id] = true;

	  //set the distance tot he current distance + 1
	  current->neighbors[d]->distance = current->distance + 1;
	  
	  //set the parent to the current
	  current->neighbors[d]->parent = current;

	  //push the node onto the stack
	  queue.push_back(current->neighbors[d]);
	}	
      }
    }
    //if we finish the search with no hits then it is invalid
    cout << "INVALID " << root << " " << target << endl;
  }
  

  //ostream overwrite for debug
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
