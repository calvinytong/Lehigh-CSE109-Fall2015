#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
using namespace std;

class Token;



const string specialChars = "+-*/%=(),<>!$";

//regex intlit("[1-9][0-9]*|0|0x[0-9a-f]+");
//regex floatlit("([1-9][0-9]*|0)\\.[0-9]+");
//regex strlit("\".*\"");
//regex ident("[a-zA-Z][a-zA-Z0-9_]*");

Lexer::Lexer(istream& i):in(i), next('\0'), linenum(1), linepos(1)
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
   linepos = 1;
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
   linepos = 1;
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
 int tokpos = linepos;
 int tokline = linenum;
 while(true)
 {
  next = nextChar();
  if(isspace(next) && lex == "")
  {
   next = nextChar();
  }
  if(isspace(next) || (isSpecialChar(next) && lex != "" && next != ')'))
  {
    if(lex == "set")
     return Token(Token::SET, lex, tokline, tokpos);
    else if(lex == "print")
     return Token(Token::PRINT, lex, tokline, tokpos);
    else if(lex == "while")
     return Token(Token::WHILE, lex, tokline, tokpos);
    else if(lex == "do")
     return Token(Token::DO, lex, tokline, tokpos);
    else if(lex == "end")
     return Token(Token::END, lex, tokline, tokpos);
    else if(lex ==  "and")
     return Token(Token::AND, lex, tokline, tokpos);
    else if(lex ==  "or")
     return Token(Token::OR, lex, tokline, tokpos);
    else if(lex == "if")
     return Token(Token::IF, lex, tokline, tokpos);
    else if (lex == "then")
     return Token(Token::THEN, lex, tokline, tokpos);
    else if (lex == "else")
     return Token(Token::ELSE, lex, tokline, tokpos);
    else if(lex == "endif")
     return Token(Token::ENDIF, lex, tokline, tokpos);
    else if(lex ==  "program")
     return Token(Token::PROGRAM, lex, tokline, tokpos);
    else
    {
     return Token(Token::INTLIT, lex, tokline, tokpos);
    // if(regexsearch(lex, intlit))
     // return Token(Token::INTLIT, lex, tokline, tokpos);
    // else if(regex_match(lex, floatlit))
     // return Token(Token::FLOATLIT, lex, tokline, tokpos);
    // else if(regex_match(lex, strlit))
     // return Token(Token::STRLIT, lex, tokline, tokpos);
    // else if(regex_match(lex, ident))
     // return Token(Token::IDENT, lex, tokline, tokpos);
    // else
     // return Token(Token::ERROR, lex, tokline, tokpos);
    }
  }
  else if(isSpecialChar(next))
  {
   switch(next)
   {
    case '+':
     return Token(Token::PLUS, "+", tokline, tokpos);
    case '-':
     return Token(Token::MINUS, "-", tokline, tokpos);
    case '*':
     return Token(Token::TIMES, "*", tokline, tokpos);
    case '/':
     return Token(Token::DIVIDE, "/", tokline, tokpos);
    case '%':
     return Token(Token::REM, "%", tokline, tokpos);
    case '=':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::EQ, "==", tokline, tokpos);
     }
     else
     {
      return Token(Token::ASSIGN, "=", tokline, tokpos);
     }
    case '(':
     return Token(Token::LPAREN, "(", tokline, tokpos);
    case ')':
     return Token(Token::RPAREN, ")", tokline, tokpos); 
    case ',':
     return Token(Token::COMMA, ",", tokline, tokpos);
    case '<':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::LE, "<=", tokline, tokpos);
     }
     else
     {
      return Token(Token::LT, "<", tokline, tokpos);
     }
    case '>':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::GE, ">=", tokline, tokpos);
     }
     else
     {
      return Token(Token::LE, ">", tokline, tokpos);
     }
    case '!':
     next = nextChar();
     next = nextChar();
     return Token(Token::NE, "!=", tokline, tokpos);
    case '$':
     return Token(Token::ENDOFFILE, "$", tokline, tokpos);
    default:
     return Token(Token::ERROR, "error", tokline, tokpos);
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
