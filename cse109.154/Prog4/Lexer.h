#ifndef LEXER_H
#define LEXER_H

#include <iostream>

class Token;

using namespace std;

class Lexer
{
 public:
  Lexer(istream& i);

  ~Lexer();

  char nextChar();
  Token nextToken();

  istream& getIn() const;
  char getNext() const;

  void setNext(char c);

 private:
  istream& in;
  char next;
  bool isSpecialChar(char ch);
};

#endif
