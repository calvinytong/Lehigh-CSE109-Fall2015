/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: a simple lexer
 * Program #5
 */

#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>

class Token;

using namespace std;

//lexer class header
class Lexer
{
 public:
  //constructor
  Lexer(istream& i);

  //destructor
  ~Lexer();

  //public member functions
  char nextChar();
  Token nextToken();
  
  //getter methods
  istream& getIn() const;
  char getNext() const;
  
  //setter methods
  void setNext(char c);

 private:
  //private member variables
  istream& in;
  char next;
  int linenum;
  int linepos;

  //private member functions
  bool isSpecialChar(char ch);
  bool isIntlit(string s);
  bool isFloatlit(string s);
  bool isStrlit(string s);
  bool isIdent(string s);
  char get(istream& i);
};

#endif
