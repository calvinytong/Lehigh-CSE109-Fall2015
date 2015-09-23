#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
using namespace std;

class Token;

int linenum;
int linepos;

const string specialChars = "+-*/%=(),<>!$";

//regex intlit("[1-9][0-9]*|0|0x[0-9a-f]+");
//regex floatlit("([1-9][0-9]*|0)\\.[0-9]+");
//regex strlit("\".*\"");
//regex ident("[a-zA-Z][a-zA-Z0-9_]*");

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
 c = get(this->getIn());
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

Token Lexer::nextToken()
{
 string lex = "";
 while(true)
 {
  tokpos = linepos; 
  next = nextChar();
  if(isspace(next) && lex == "")
  {
   next = nextChar();
  }
  if(isspace(next) || (isSpecialChar(next) && lex != "" && next != ')'))
  {
    if(lex == "set")
     return Token(Token::SET, lex, linenum, tokpos);
    else if(lex == "print")
     return Token(Token::PRINT, lex, linenum, linepos);
    else if(lex == "while")
     return Token(Token::WHILE, lex, linenum, linepos);
    else if(lex == "do")
     return Token(Token::DO, lex, linenum, linepos);
    else if(lex == "end")
     return Token(Token::END, lex, linenum, linepos);
    else if(lex ==  "and")
     return Token(Token::AND, lex, linenum, linepos);
    else if(lex ==  "or")
     return Token(Token::OR, lex, linenum, linepos);
    else if(lex == "if")
     return Token(Token::IF, lex, linenum, linepos);
    else if (lex == "then")
     return Token(Token::THEN, lex, linenum, linepos);
    else if (lex == "else")
     return Token(Token::ELSE, lex, linenum, linepos);
    else if(lex == "endif")
     return Token(Token::ENDIF, lex, linenum, linepos);
    else if(lex ==  "program")
     return Token(Token::PROGRAM, lex, linenum, linepos);
    else
    {
     return Token(Token::INTLIT, lex, linenum, linepos);
    // if(regexsearch(lex, intlit))
     // return Token(Token::INTLIT, lex, linenum, linepos);
    // else if(regex_match(lex, floatlit))
     // return Token(Token::FLOATLIT, lex, linenum, linepos);
    // else if(regex_match(lex, strlit))
     // return Token(Token::STRLIT, lex, linenum, linepos);
    // else if(regex_match(lex, ident))
     // return Token(Token::IDENT, lex, linenum, linepos);
    // else
     // return Token(Token::ERROR, lex, linenum, linepos);
    }
  }
  else if(isSpecialChar(next))
  {
   switch(next)
   {
    case '+':
     return Token(Token::PLUS, "+", linenum, linepos);
    case '-':
     return Token(Token::MINUS, "-", linenum, linepos);
    case '*':
     return Token(Token::TIMES, "*", linenum, linepos);
    case '/':
     return Token(Token::DIVIDE, "/", linenum, linepos);
    case '%':
     return Token(Token::REM, "%", linenum, linepos);
    case '=':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::EQ, "==", linenum, linepos);
     }
     else
     {
      return Token(Token::ASSIGN, "=", linenum, linepos);
     }
    case '(':
     return Token(Token::LPAREN, "(", linenum, linepos);
    case ')':
     return Token(Token::RPAREN, ")", linenum, linepos); 
    case ',':
     return Token(Token::COMMA, ",", linenum, linepos);
    case '<':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::LE, "<=", linenum, linepos);
     }
     else
     {
      return Token(Token::LT, "<", linenum, linepos);
     }
    case '>':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::GE, ">=", linenum, linepos);
     }
     else
     {
      return Token(Token::LE, ">", linenum, linepos);
     }
    case '!':
     next = nextChar();
     next = nextChar();
     return Token(Token::NE, "!=", linenum, linepos);
    case '$':
     return Token(Token::ENDOFFILE, "$", linenum, linepos);
    default:
     return Token(Token::ERROR, "error", linenum, linepos);
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

char Lexer::get(istream& i)
{
 return i.get();
}
