#include <iostream>
#include <string>
#include "Trie.h"

#define numops 22

string ops[] = {"ADD", "SUB", "MULT", "DIV", "REM", "DUP", "AND", "OR", "NOT", "ISEQ", "ISNE", 
"ISGT", "ISGE", "ISLT", "ISLE", "LOADL", "LOADV", "STOREV", "JUMP", "JUMPF", "PRINT", "PRINTLN"
"PRINTS"};

string codes[] = {"A0", "A1", "A3", "A4", "A5", "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7",
"B8", "C0", "C1", "C2", "D0", "D1", "E0", "E1", "E2"};


Trie *makeInsTable()
{
 Trie *table = new Trie();
 for(int i = 0; i < numops; i++)
 {
  table->put(ops[i], codes[i]);
  cout << table->get(ops[i]) << endl;
 }
 return table;
}

int main(int argc, char** argv)
{
 //char *program[255];
 //Trie *labelmap = new Trie();
 //Trie *argmap = new Trie();
 Trie *instable = makeInsTable();
 cout << instable;
 return 0;
}
