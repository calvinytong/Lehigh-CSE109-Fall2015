#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>

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
  int linenum;
  int linepos;
  bool isSpecialChar(char ch);
  bool isIntlit(string s);
  bool isFloatlit(string s);
  bool isStrlit(string s);
  bool isIdent(string s);
  char get(istream& i);
};

#endif
