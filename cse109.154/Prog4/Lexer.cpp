#include <cstdlib>
#include <iostream>
#include <regex>
#include "Lexer.h"
#include "Token.h"

using namespace std;
using namespace Tok;
class Token;

int linenum;
int linepos;

const string specialChars = "+-*/%=(),<>!$";

regex intlit("[1-9][0-9]*|0|0x[0-9a-f]+");
regex floatlit("([1-9][0-9]*|0)\\.[0-9]+");
regex strlit("\".*\"");
regex ident("[a-zA-Z][a-zA-Z0-9_]*");

Lexer::Lexer(istream& i):in(i), next('\0')
{

}

Lexer::~Lexer()
{

}

istream& Lexer::getIn() const
{
 return this->in;
}

char Lexer::getNext() const
{
 return this->next;
}

void Lexer::setNext(char c)
{
 this->next = c;
}

char Lexer::nextChar()
{
 char c;
 this->getIn() >> c;
 if(c == EOF)
 {
  return '$';
 }
 else if(c == '#')
 {
  while(c != '\n' && c != EOF)
  {
   this->getIn() >> c;
  }
  if(c == '\n')
  {
   this->getIn() >> c;
   linepos = 0;
   linenum++;
   return c;
  }
  else
  {
   return '$';
  }
 }
 else
 {
  if(c == '\n')
  {
   linepos = 0;
   linenum++;
  }
  else
  {
   linepos++;
  }
  return c;
 }
}

Tok::Token Lexer::nextToken()
{
 string lex = "";
 while(true)
 {
  next = nextChar();
  
  if(isspace(next) || isSpecialChar(next))
  {
    if(lex == "set")
     return Token(SET, lex, linenum, linepos);
    else if(lex == "print")
     return Token(PRINT, lex, linenum, linepos);
    else if(lex == "while")
     return Token(WHILE, lex, linenum, linepose);
    else if(lex == "do")
     return Token(DO, lex, linenum, linepose);
    else if(lex == "end")
     return Token(END, lex, linenum, linepose);
    else if(lex ==  "and")
     return Token(AND, lex, linenum, linepose);
    else if(lex ==  "or")
     return Token(OR, lex, linenum, linepose);
    else if(lex == "if")
     return Token(IF, lex, linenum, linepose);
    else if (lex == "then")
     return Token(THEN, lex, linenum, linepose);
    else if (lex == "else")
     return Token(ELSE, lex, linenum, linepose);
    else if(lex == "endif")
     return Token(ENDIF, lex, linenum, linepose);
    else if(lex ==  "program")
     return Token(PROGRAM, lex, linenum, linepose);
    else
    {
     if(regex_match(lex, intlit))
      return Token(INTLIT, lex, linenum, linepos);
     else if(regex_match(lex, floatlit))
      return Token(FLOATLIT, lex, linenum, linepos);
     else if(regex_match(lex, strlit))
      return Token(STRLIT, lex, linenum, linepos);
     else if(regex_match(lex, ident)) 
      return Token(IDENT, lex, linenum, linepos);
     else
      return Token(ERROR, lex, linenum, linepos);
    }
  }
  else if(isSpecialChar(next))
  {
   switch(next)
   {
    case '+':
     return Token(PLUS, "+", linenum, linepos);
    case '-':
     return Token(MINUS, "-", linenum, linepos);
    case '*':
     return Token(TIMES, "*", linenum, linepos);
    case '/':
     return Token(DIVIDE, "/", linenum, linepos);
    case '%':
     return Token(REM, "%", linenum, linepos);
    case '=':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(EQ, "==", linenum, linepos);
     }
     else
     {
      return Token(ASSIGN, "=", linenum, linepos);
     }
    case '(':
     return Token(LPAREN, "(", linenum, linepos);
    case ')':
     return Token(RPAREN, ")", linenum, linepos);
    case ',':
     return Token(COMMA, ",", linenum, linepos);
    case '<':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(LE, "<=", linenum, linepos);
     }
     else
     {
      return Token(LT, "<", linenum, linepos);
     }
    case '>':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(GE, ">=", linenum, linepos);
     }
     else
     {
      return Token(LE, ">", linenum, linepos);
     }
    case '!':
     next = nextChar();
     next = nextChar();
     return Token(NE, "!", linenum, linepos);
    case '$':
     return Token(ENDOFFILE, EOF, linenum, linepos);
    default:
     return Token(ERROR, next, linenum, linepos);
   }
  }
  else
  {
   lex += next;
  } 
 }
}

bool Lexer::isSpecialChar(char ch)
{
 return specialChars.find(ch) != string::npos;
}

