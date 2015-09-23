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
  int getLine() const;
  int getPos() const;

  void setNext(char c);

 private:
  istream& in;
  char next;
  int linenum;
  int linepos;
  bool isSpecialChar(char ch);
  char get(istream& i);
};

#endif
