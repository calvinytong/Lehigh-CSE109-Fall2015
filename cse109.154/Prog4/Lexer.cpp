#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <stdio.h>
using namespace std;

class Token;

//string containing special chars
const string specialChars = "+-*/%=(),<>!$";

/*
 * constructor for lexer class sets next to null, linenum to 1, linepos to 1
 * @param istream the address of the istream
 */
Lexer::Lexer(istream& i):in(i), next('\0'), linenum(1), linepos(1)
{

}

/*
 * destructor no dynamically allocated memory so no code needed 
 */
Lexer::~Lexer()
{

}

/*
 * getter for the istream
 * @return the istream object
 */
istream& Lexer::getIn() const
{
 return this->in;
}

/*
 *getter for the next string
 * @return the next char
 */
char Lexer::getNext() const
{
 return this->next;
}

/*
 * setter for the  
 */
void Lexer::setNext(char c)
{
 this->next = c;
}

/*
 * 
 */
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
    c = get(this->getIn());
   linepos = 0;
   linenum++;
   return c;
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

/*
 * 
 */
Token Lexer::nextToken()
{
 string lex = "";
 int tokpos = linepos;
 int tokline = linenum;
 if(next == '\0')
  next = nextChar();
 while(true)
 {
  if(isspace(next) && lex == "")
  {
   while(isspace(next))
   { 
    next = nextChar();
    tokpos = linepos;
    tokline = linenum;
   }
  }
  if(isspace(next) || (isSpecialChar(next) && lex != ""))
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
     if(isIntlit(lex))
      return Token(Token::INTLIT, lex, tokline, tokpos);
     else if(isFloatlit(lex))
      return Token(Token::FLOATLIT, lex, tokline, tokpos);
     else if(isStrlit(lex))
      return Token(Token::STRLIT, lex, tokline, tokpos);
     else if(isIdent(lex))
      return Token(Token::IDENT, lex, tokline, tokpos);
     else
      return Token(Token::ERROR, lex, tokline, tokpos);
    }
  }
  else if(isSpecialChar(next))
  {
   char temp = next;
   next = nextChar();
   switch(temp)
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
     temp = next;
     if(temp == '=')
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
     temp = next;
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
     temp = next;
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
   next = nextChar();
  }
 }
}

/*
 * 
 */
bool Lexer::isSpecialChar(char ch)
{
 return specialChars.find(ch) != string::npos;
}

/*
 * 
 */
bool Lexer::isIntlit(string s)
{
 for(uint i = 0; i < s.size(); i++)
 {
  if(!isdigit(s[i]))
  {
   return false;
  }
 }
 return true;
}

/*
 * 
 */
bool Lexer::isFloatlit(string s)
{
 if(!isdigit(s[0]))
 {
  return false;
 }
 int count = 0;
 for(uint i = 0; i < s.size(); i++)
 {
  if(s[i] == '.')
  {
   count++;
  }
  else if(!isdigit(s[i]))
  {
   return false;
  }
 }
 if(count == 0 || count > 1)
 {
  return false;
 }
 else
 {
  return true;
 }
}

/*
 * 
 */
bool Lexer::isStrlit(string s)
{
 if(s[0] == '\"' && s[s.length()-1] == '\"')
 {
  return true;
 }
 else
 {
  return false;
 }
}

/*
 * 
 */
bool Lexer::isIdent(string s)
{
 for(uint i = 0; i < s.size(); i++)
 {
  if(!isalnum(s[i]))
  {
   if(s[i] == '_' || s[i] == '*')
   {
    continue;
   }
   else
   {
    return false;
   }
  }
 }
 return true;
}

/*
 * 
 */
char Lexer::get(istream& i)
{
 return i.get();
}
