#include <iostream>
#include <string>
#include <fstream>
#include "Trie.h"
#include <string.h>
#include "Lexer.h"
#include "Token.h"
#include <sstream>
#include <bitset>
#include <vector>
#define numops 23

using namespace std;

string ops[] = {"ADD", "SUB", "MULT", "DIV", "REM", "DUP", "AND", "OR", "NOT", "ISEQ", "ISNE", "ISGT", "ISGE", "ISLT", "ISLE", "LOADL", "LOADV", "STOREV", "JUMP", "JUMPF", "PRINT", "PRINTLN", "PRINTS"};

string codes[] = {"a0", "a1","a2", "a3", "a4", "a5", "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "c0", "c1", "c2", "d0", "d1", "e0", "e1", "e2"};

string hexcode = "CAFEBE";

Trie *makeInsTable()
{
 Trie *table = new Trie();
 for(int i = 0; i < numops; i++)
 {
  table->put(ops[i], codes[i]);
 }
 return table;
}

bool isLabel(string s)
{
 return s[s.size() - 1] == ':';
}

string intToHexString(int i)
{
 stringstream stream;
 stream << hex << i;
 string s = stream.str();
 if(s.size() == 1)
 {
  s.insert(0, "0");
 }
 for(unsigned int b = 0; b < s.length(); b++)
 {
  s[b] = tolower(s[b]);
 }
 return s;
}

bool isOp(string s)
{
 for(int ii = 0; ii < numops; ii++)
 {
  if(ops[ii] == s)
  {
   return true;
  }
 }
 return false;
}

string toString(int i)
{
 ostringstream oss;
 oss << i;
 return oss.str();
}

int toInt(string s)
{
 stringstream iss(s);
 int i;
 iss >> i;
 return i;
}
int main(int argc, char** argv)
{
 //init tables
 string program[255];
 program[0] = hexcode;
 Trie *labelmap = new Trie();
 Trie *argmap = new Trie();
 Trie *instable = makeInsTable();
 Trie *temptable = new Trie();

 bool lflag = false;
 bool aflag = false;
 bool pflag = false;
 
 //parse cmdline options
 for(int i = 1; i < argc; i++)
 {
  if(!strcmp(argv[i], "-h"))
  {
   cout << "Assembler Usage:\n";
   cout << "To pipe in a file: cat myfile.sasm | ./assemble\n";
   cout << "Piping in a file requires the output of this program to be piped into the Linker.\n";
   cout << "To assemble 1 or more files: ./assemble file1.sasm file2.sasm ...\n";
   cout << "Passing in file names as command line args saves them as *.s files to pass into the Linker.\n";
   cout << "Command line arguments:\n";
   cout << " -h display this usage information\n";
   cout << " -i prints all the .sasm instructions as well as their bytecode representation.\n";
   cout << " -l prints the label map. The decimal value of the 1 byte hex string on the left and the";
   cout<< " respective label on the right.\n";
   cout << "-a prints the instruction arguments. The decimal value of the 1 byte hex string on the left";
   cout << " and the respective argument on the right.\n";
   cout << "-p prints the bytecode of the .sasm program. It prints every instruction on its own line,";
   cout << " mirroring the .sasm that was input.\n";
   continue;
  }

  if(!strcmp(argv[i], "-i"))
  {
   for(int a = 0; a < numops; a++)
   {
    cout << ops[a] << " " << codes[a] << endl;
   }
   cout << endl;
   continue;
  }

  if(!strcmp(argv[i], "-l"))
  {
   lflag = true; 
   continue;
  }

  if(!strcmp(argv[i], "-a"))
  {
   aflag = true;
   continue;
  }

  if(!strcmp(argv[i], "-p"))
  {
   pflag = true;
   continue;
  }
  //pseudo else condition b/c of continues
  string name = argv[i]; 
  string rawname;
  unsigned int index = name.find_last_of(".");
  if(index != string::npos)
  {
   rawname = name.substr(0, index);
  }
  else
  {
   rawname = name;
  }
  ofstream fout;
  fout.open((rawname += ".s").c_str());
  
  fstream fin;
  fin.open(argv[i], ios::in);
  if(!fin.is_open())
  {
   cout << "no file found" << endl;
   return 1;
  }
  istream& i = fin;
  Lexer *l = new Lexer(i);
  Token t = l->nextToken();
  int line;
  int opcount = 1;
  int argscount = 1;
  while(t.getType() != Token::ENDOFFILE)
  {
   string prog = "";
   line = t.getLine();
   string next = t.getLexeme();
   if(isLabel(next))
   {
    if(labelmap->get(next) != "")
    {
      cout << "label declared twice" << endl;
      return 1;
    } 
    else
    {
     labelmap->put(next, intToHexString(line)); 
     prog += labelmap->get(next);
     t = l->nextToken();
    }
    if(temptable->get(next) != "")
    {
     istringstream ss(temptable->get(next));
     string token;
     while(getline(ss, token, ','))
     {
      int tofix = toInt(token);
      program[tofix] += labelmap->get(next);
     }
    }
   }
   else
   {
    prog += "00";
   }
   if(isOp(t.getLexeme()) && t.getLine() == line)
   {
    string next = t.getLexeme();
    string code = instable->get(next);
    prog += code;
    if(next == "LOADL" || next == "PRINTS" || next == "LOADV" || next == "STOREV")
    {
     t = l->nextToken();
     if(argmap->get(t.getLexeme()) != "")
     {
      prog += argmap->get(t.getLexeme()); 
     }
     else
     {
      argmap->put(t.getLexeme(), intToHexString(argscount));
      prog += argmap->get(t.getLexeme());
      argscount++;
     }
     t = l->nextToken();
    }
    else if(next == "JUMPF" || next == "JUMP")
    {
     t = l->nextToken();
     string labelname = t.getLexeme() += ":";
     string index = labelmap->get(labelname);
     if(index == "")
     {
      if(temptable->get(labelname) == "")
      {
       temptable->put(labelname, toString(opcount));
      }
      else
      {
       string s = temptable->get(labelname);
       string ns = s + "," + toString(opcount);
       temptable->put(labelname, ns);
      }
     }
     prog += labelmap->get(labelname);
     t = l->nextToken();
    }
    else
    {
     prog += "00";
     t = l->nextToken();
    }
   }
   else
   {
    prog += "0000";
   }
   program[opcount] = prog;
   opcount++;
  }
  program[opcount] = "000000";
  for(int iii = 0; iii < opcount + 1; iii++)
  {
   fout << program[iii];
  }
  fout << *labelmap;
  fout << *argmap;

  if(lflag)
  {
   labelmap->printPlainText();  
  }
  if(aflag)
  {
   argmap->printPlainText();
  }
  if(pflag)
  {
   for(int c = 0; c < opcount + 1; c++)
   {
    cout << program[c] << endl;
   }
   cout << endl;
  }

 } 
 return 0;
}
