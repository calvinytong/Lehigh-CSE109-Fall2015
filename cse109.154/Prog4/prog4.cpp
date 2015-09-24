#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "Lexer.h"
#include "Token.h"

using namespace std;

int main(int argc, char** argv)
{
 //lexer object
 Lexer *l = new Lexer(cin);

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
