#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <stdio.h>
using namespace std;
int main(int argc, char** argv)
{
 Lexer *l = new Lexer(cin);
 cout << "Type" << '\t' << "Lexeme" << '\t' << "Line #" << '\t' << "Pos" << endl;
 Token t = l->nextToken();
 while(t.getType() != Token::ENDOFFILE)
 {
  cout << t;
  t = l->nextToken();
 }
 return 0; 
}
