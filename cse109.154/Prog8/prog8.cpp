/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: generate word ladders
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

/*
 * Entry Point to the program
 * @param argc the number of argmuments
 * @param argv the array of args
 */
int main(int argc, char** argv)
{
  //vector holding pointers to the graphs
  vector<prog8lib::Graph*> graphs;

  //vector holding the number of letters in each built graph
  vector<unsigned int> builtgraphs;

  //the class word stream
  fstream cstream;

  //the words file stream
  fstream wstream;

  //open files
  cstream.open("classwords.txt", ios::in);
  wstream.open("words", ios::in);
  
  //make sure that the files are actually open
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
  
  //process the classwords
 
  //string holding the current line
  string line;
  while(getline(cstream, line))
  {
    //split the line with space delimeter and store it in wvector
    stringstream ss(line);
    istream_iterator<string> begin(ss);
    istream_iterator<string> end;
    vector<string> vstrings(begin, end);
    vector<string> wvector;
    
    //the length of the vector as an int 
    int glength = 0;
     
    //check to make sure the strings are correctly formated
    if(vstrings.size() == 3)
    {
      //get the length of the first word
      unsigned int wordlength = vstrings[1].length(); 
      
      //if the graph for that length of word has not been built yet then create the graph by
      //iteratin through the dictionary
      string w;
      if(!(find(builtgraphs.begin(), builtgraphs.end(), wordlength) != builtgraphs.end()))
      {
        //iterate through the dictionary pulling out words as needed
        while(getline(wstream, w))
        {
          if(w.length() == wordlength)
	  {
            wvector.push_back(w);
	    glength++;
	  }
	}
	//put the new graph and the length of the graph into the build graphs and graphs
	//vectors
        graphs.push_back(new prog8lib::Graph(glength, wvector, wordlength));
	builtgraphs.push_back(wordlength);
      }

      //find the correct graph in the graph vector
      for(vector<prog8lib::Graph*>::size_type e = 0; e != graphs.size(); e++)
      {
        if(graphs[e]->getLength() == wordlength)
	{
	  //check that the words are in the dict using the Trie
	  prog8lib::Trie *t = graphs[e]->getTrie();
          if(t->get(vstrings[1]) != -1 && t->get(vstrings[2]) != -1)
	  {
	    //preform a BFS on the graph to find the shortest path (prints happen insdie
	    //funciton
	    graphs[e]->BFS(vstrings[1], vstrings[2]);
	  }
	  //if they are not in the dict then it is invalid
	  else
	  {
            cout << "INVALID " << vstrings[1] << " " << vstrings[2] << endl; 
	  }
	}
      }
      //reset the dictionary iterators
      wstream.clear();
      wstream.seekg(0, ios::beg);
    }
    //if not correctly formatted then continue
    else
    {
      continue;
    }
  }
  //if success exit with code 0
  return 0;
 }


