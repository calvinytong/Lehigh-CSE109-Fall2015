#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <Token.h>
class Token;

using namespace std;
class Lexer
{
 public:
  Lexer(istream& i);
  
  ~Lexer();

  char nextChar();
  Tok::Token nextToken();

  istream& getIn() const;
  char getNext() const;
 
  void setNext(char c);

 private:
  istream& in;
  char next;
  bool isSpecialChar(char ch);
};

#endif
