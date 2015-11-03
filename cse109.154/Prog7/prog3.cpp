/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: Implement a simple Trie data structure
 * Program #3 
 */

#include <iostream>
#include "Trie.h"
#include <string>
int main(int argc, char** argv)
{
 //create a new trie
 Trie *t = new Trie();
 string s = "test test"; 
 //put a bunch of stuff
 cout << "testing put function" << endl;
 
 cout << "putting key lehigh to value 100" << endl;
 t->put("lehigh", s);

 cout << "putting key hello to value 500" << endl;
 t->put("hello", s);

 cout << "putting key lemon to value 6000" << endl;
 t->put("lemon", s);

 cout << "putting key lemmings to value 200" << endl << endl;
 t->put("lemmings", s);
 
 //retreive the stuff
 cout << "testing get function" << endl;

 cout << "key lehigh returned " << t->get("lehigh") << endl;
 cout << "key hello returned " << t->get("hello") << endl;
 cout << "key lemon returned " << t->get("lemon") << endl;
 cout << "key lemmings returned " << t->get("lemmings") << endl;
 return 0;
}
