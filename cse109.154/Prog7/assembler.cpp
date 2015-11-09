/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: Implement a simple assembler
 * Program #7
 */

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

//ops array
string ops[] = {"ADD", "SUB", "MULT", "DIV", "REM", "DUP", "AND", "OR", "NOT", "ISEQ", "ISNE", "ISGT", "ISGE", "ISLT", "ISLE", "LOADL", "LOADV", "STOREV", "JUMP", "JUMPF", "PRINT", "PRINTLN", "PRINTS"};

//codes array
string codes[] = {"a0", "a1","a2", "a3", "a4", "a5", "b0", "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8", "c0", "c1", "c2", "d0", "d1", "e0", "e1", "e2"};

//the magic hexcode
string hexcode = "CAFEBE";

//creates the instruction table
Trie *makeInsTable()
{
 Trie *table = new Trie();
 for(int i = 0; i < numops; i++)
 {
  table->put(ops[i], codes[i]);
 }
 return table;
}

//determines if a string is a label
bool isLabel(string s)
{
 return s[s.size() - 1] == ':';
}

//converts a integer to a hex string with a zero prefix
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

//determines if a string is an operator
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

//converts an integer to a string
string toString(int i)
{
 ostringstream oss;
 oss << i;
 return oss.str();
}

//converts a string to an int
int toInt(string s)
{
 stringstream iss(s);
 int i;
 iss >> i;
 return i;
}

//main method, entry point of the program
int main(int argc, char** argv)
{

 Trie *instable = makeInsTable();

 bool lflag = false;
 bool aflag = false;
 bool pflag = false;

 //parse cmdline options
 for(int i = 1; i < argc; i++)
 {
  //init tables
  string program[255];
  program[0] = hexcode;
  Trie *labelmap = new Trie();
  Trie *argmap = new Trie();
  Trie *temptable = new Trie();

  //if -h then print out the usage
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

  //prints the ops table
  if(!strcmp(argv[i], "-i"))
  {
   for(int a = 0; a < numops; a++)
   {
    cout << ops[a] << " " << codes[a] << endl;
   }
   cout << endl;
   continue;
  }

  //turn on the l flag
  if(!strcmp(argv[i], "-l"))
  {
   lflag = true;
   continue;
  }

  //turn on the a flag
  if(!strcmp(argv[i], "-a"))
  {
   aflag = true;
   continue;
  }

  //turn on the p flag
  if(!strcmp(argv[i], "-p"))
  {
   pflag = true;
   continue;
  }
  //pseudo else condition b/c of continues
  //parse out the raw filename without extention
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
  //open the fout stream
  ofstream fout;
  fout.open((rawname += ".s").c_str());

  //opens the fin stream
  fstream fin;
  fin.open(argv[i], ios::in);
  //check if its open return 1 if there is no file
  if(!fin.is_open())
  {
   cout << "no file found" << endl;
   return 1;
  }

  //init lexer
  istream& i = fin;
  Lexer *l = new Lexer(i);

  //start parsing the file
  int line;
  int opcount = 1;
  int argscount = 1;
  Token t = l->nextToken();
  while(t.getType() != Token::ENDOFFILE)
  {
   //prog string represents the byte code for each operation
   string prog = "";
   //set line to the current line
   line = t.getLine();
   //the current token lexeme
   string next = t.getLexeme();

   //check if label
   if(isLabel(next))
   {
    //if label is declared twice then return 1
    if(labelmap->get(next) != "")
    {
      cout << "label declared twice" << endl;
      return 1;
    }
    //if the label is not in the table then put it into the table
    else
    {
     labelmap->put(next, intToHexString(line));
     prog += labelmap->get(next);
     t = l->nextToken();
    }
    //if there are unresolved instances of the label then fill them in
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
   //if not a label then just give 00
   else
   {
    prog += "00";
   }
   //if the next token is an operation and on the same line then process it
   if(isOp(t.getLexeme()) && t.getLine() == line)
   {
    //assign next to lexeme
    string next = t.getLexeme();

    //get the code for the operation
    string code = instable->get(next);

    //concat the code
    prog += code;

    //if the operation has an arg then add it to the args table and concate the index
    if(next == "LOADL" || next == "PRINTS" || next == "LOADV" || next == "STOREV")
    {
     //advace to the arg
     t = l->nextToken();

     //if the arg is in the tree then use that
     if(argmap->get(t.getLexeme()) != "")
     {
      prog += argmap->get(t.getLexeme());
     }
     //if the arg is not already in the table then add it
     else
     {
      argmap->put(t.getLexeme(), intToHexString(argscount));
      prog += argmap->get(t.getLexeme());
      argscount++;
     }

     //return one ahead
     t = l->nextToken();
    }
    //if the instruction has a label arg then process it differently
    else if(next == "JUMPF" || next == "JUMP")
    {
     t = l->nextToken();
     string labelname = t.getLexeme() += ":";
     string index = labelmap->get(labelname);
     if(index == "")
     {
      //this code makes it a one pass assembler, if it encounters a label that
      //has not been added to the table yet then it adds it to the temp table
      //along with the opcount to be resolved later
      //if there are multiple mentions then it creates a comma seperated list
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
    //else there is no op so just 00
    else
    {
     prog += "00";
     t = l->nextToken();
    }
   }
   //if no op then put 0000
   else
   {
    prog += "0000";
   }
   //store the prog string in program and increment the index
   program[opcount] = prog;
   opcount++;
  }
  //end with a 000000
  program[opcount] = "000000";

  //check that we have no references to labels that don't exist
  //write the program table to fout
  for(int iii = 0; iii < opcount + 1; iii++)
  {
   if(program[iii].length != 6)
   {
     cout << "reference to non existant label" << endl;
     return 1;
   }
   fout << program[iii];
  }
  //write the two maps out to fout
  fout << *labelmap;
  fout << *argmap;

  //depending on flags print labelmap and argmap to std out
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
