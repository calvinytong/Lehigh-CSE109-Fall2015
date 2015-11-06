#include <iostream>
#include <string>
#include <fstream>
#include "Trie.h"
#include <string.h>
#include "Lexer.h"
#define numops 22

using namespace std;

string ops[] = {"ADD", "SUB", "MULT", "DIV", "REM", "DUP", "AND", "OR", "NOT", "ISEQ", "ISNE", 
"ISGT", "ISGE", "ISLT", "ISLE", "LOADL", "LOADV", "STOREV", "JUMP", "JUMPF", "PRINT", "PRINTLN"
"PRINTS"};

string codes[] = {"A0", "A1", "A3", "A4", "A5", "B0", "B1", "B2", "B3", "B4", "B5", "B6", "B7",
"B8", "C0", "C1", "C2", "D0", "D1", "E0", "E1", "E2"};

string hexcode = "CAFEBE";

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
 ifstream fin;
 istream iin;
 Lexer l;
 //init tables
 string program[255];
 program[0] = hexcode;
 //Trie *labelmap = new Trie();
 //Trie *argmap = new Trie();
 Trie *instable = makeInsTable();
 
 //parse cmdline options
 for(int i = 1; i < argc; i++)
 {
  if(!strcmp(argv[i], "-h"))
  {
   continue;
  }

  if(!strcmp(argv[i], "-i"))
  {
   continue;
  }

  if(!strcmp(argv[i], "-l"))
  {
   continue;
  }

  if(!strcmp(argv[i], "-a"))
  {
   continue;
  }

  if(!strcmp(argv[i], "p"))
  {
   continue;
  }

  //pseudo else condition b/c of continues
  l = new Lexer(iin);
 }
 
 return 0;
}
