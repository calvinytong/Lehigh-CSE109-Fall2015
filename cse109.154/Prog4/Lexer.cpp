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

int getLine() const;
{
 return this->linenum
}

int getPos() const;
{
  return this->linepos
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
  int tokpos = linepos; 
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
     return Token(Token::PRINT, lex, linenum, tokpos);
    else if(lex == "while")
     return Token(Token::WHILE, lex, linenum, tokpos);
    else if(lex == "do")
     return Token(Token::DO, lex, linenum, tokpos);
    else if(lex == "end")
     return Token(Token::END, lex, linenum, tokpos);
    else if(lex ==  "and")
     return Token(Token::AND, lex, linenum, tokpos);
    else if(lex ==  "or")
     return Token(Token::OR, lex, linenum, tokpos);
    else if(lex == "if")
     return Token(Token::IF, lex, linenum, tokpos);
    else if (lex == "then")
     return Token(Token::THEN, lex, linenum, tokpos);
    else if (lex == "else")
     return Token(Token::ELSE, lex, linenum, tokpos);
    else if(lex == "endif")
     return Token(Token::ENDIF, lex, linenum, tokpos);
    else if(lex ==  "program")
     return Token(Token::PROGRAM, lex, linenum, tokpos);
    else
    {
     return Token(Token::INTLIT, lex, linenum, tokpos);
    // if(regexsearch(lex, intlit))
     // return Token(Token::INTLIT, lex, linenum, tokpos);
    // else if(regex_match(lex, floatlit))
     // return Token(Token::FLOATLIT, lex, linenum, tokpos);
    // else if(regex_match(lex, strlit))
     // return Token(Token::STRLIT, lex, linenum, tokpos);
    // else if(regex_match(lex, ident))
     // return Token(Token::IDENT, lex, linenum, tokpos);
    // else
     // return Token(Token::ERROR, lex, linenum, tokpos);
    }
  }
  else if(isSpecialChar(next))
  {
   switch(next)
   {
    case '+':
     return Token(Token::PLUS, "+", linenum, tokpos);
    case '-':
     return Token(Token::MINUS, "-", linenum, tokpos);
    case '*':
     return Token(Token::TIMES, "*", linenum, tokpos);
    case '/':
     return Token(Token::DIVIDE, "/", linenum, tokpos);
    case '%':
     return Token(Token::REM, "%", linenum, tokpos);
    case '=':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::EQ, "==", linenum, tokpos);
     }
     else
     {
      return Token(Token::ASSIGN, "=", linenum, tokpos);
     }
    case '(':
     return Token(Token::LPAREN, "(", linenum, tokpos);
    case ')':
     return Token(Token::RPAREN, ")", linenum, tokpos); 
    case ',':
     return Token(Token::COMMA, ",", linenum, tokpos);
    case '<':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::LE, "<=", linenum, tokpos);
     }
     else
     {
      return Token(Token::LT, "<", linenum, tokpos);
     }
    case '>':
     next = nextChar();
     if(next == '=')
     {
      next = nextChar();
      return Token(Token::GE, ">=", linenum, tokpos);
     }
     else
     {
      return Token(Token::LE, ">", linenum, tokpos);
     }
    case '!':
     next = nextChar();
     next = nextChar();
     return Token(Token::NE, "!=", linenum, tokpos);
    case '$':
     return Token(Token::ENDOFFILE, "$", linenum, tokpos);
    default:
     return Token(Token::ERROR, "error", linenum, tokpos);
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
