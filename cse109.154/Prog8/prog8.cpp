/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: generate word pairs
 * Program #8
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include "Graph.h"
#include <algorithm>

using namespace std;


int main(int argc, char** argv)
{
  vector<prog8lib::Graph*> graphs;
  vector<unsigned int> builtgraphs;
  fstream cstream;
  fstream wstream;
  cstream.open("classwords.txt", ios::in);
  wstream.open("words", ios::in);
  if(!cstream.is_open())
  {
    cout << "classwords not found" << endl;
    return 1;
  }
  else if(!wstream.is_open())
  {
    cout << "words file not found" << endl;
    return 1;
  }
 
  string line;
  while(getline(cstream, line))
  {
    stringstream ss(line);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    vector<string> wvector;
    int glength = 0;
     
    if(vstrings.size() == 3)
    {
      unsigned int wordlength = vstrings[1].length(); 
      string w;
      if(!(find(builtgraphs.begin(), builtgraphs.end(), wordlength) != builtgraphs.end()))
      {
        while(getline(wstream, w))
        {
          if(w.length() == wordlength)
	  {
            wvector.push_back(w);
	    glength++;
	  }
	}
        graphs.push_back(new prog8lib::Graph(glength, wvector, wordlength));
	builtgraphs.push_back(wordlength);
      }
      for(vector<prog8lib::Graph*>::size_type e = 0; e != graphs.size(); e++)
      {
        if(graphs[e]->getLength() == wordlength)
	{
	  prog8lib::Trie *t = graphs[e]->getTrie();
          if(t->get(vstrings[1]) != -1 && t->get(vstrings[2]) != -1)
	  {
	    graphs[e]->BFS(vstrings[1], vstrings[2]);
	  }
	  else
	  {
            cout << "INVALID " << vstrings[1] << " " << vstrings[2] << endl; 
	  }
	}
      }
      wstream.clear();
      wstream.seekg(0, ios::beg);
    } 
    else
    {
      continue;
    }
  }
  return 0;
 }


