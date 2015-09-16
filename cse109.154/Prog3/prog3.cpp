/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: Implement a simple Trie data structure
 * Program #3 
 */

#include <iostream>
#include "Trie.h"

int main(int argc, char** argv)
{
 //create a new trie
 Trie *t = new Trie();

 //set a bunch of keys
 t->put("lehigh", 100);
 t->put("hello", 500);
 t->put("lemon", 6000);
 t->put("lemmings", 200);
 
 //retreive the values
 cout << t->get("lehigh") << endl;
 cout << t->get("hello") << endl;
 cout << t->get("lemon") << endl;
 cout << t->get("lemmings") << endl;
 return 0;
}
