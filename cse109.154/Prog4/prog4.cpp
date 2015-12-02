/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: a simple lexer
 * Program #4
 */


#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "Lexer.h"
#include "Token.h"

using namespace std;

int main(int argc, char** argv)
{
 Lexer *l;
 if(argc == 2)
 {
  ifstream in;
  in.open(argv[1], ios::in);
  if(in)
   l = new Lexer(in);
  else
   return 1;
 }
 else
 {
  l = new Lexer(cin);
 }


 //write header
 cout << "Type" << '\t' << "Lexeme" << '\t' << "Line #" << '\t' << "Pos" << endl;

 //start the loop off
 Token t = l->nextToken();

 //iterate until EOF
 while(t.getType() != Token::ENDOFFILE)
 {
  //write out token
  cout << t;
  t = l->nextToken();
 }
 return 0;
}
