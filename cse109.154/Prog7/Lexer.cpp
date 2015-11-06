#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <stdio.h>
#include <fstream>
using namespace std;

class Token;

//string containing special chars
const string specialChars = "+-*/%=(),<>!$\"";

/*
 * constructor for lexer class sets next to null, linenum to 1, linepos to 1
 * @param istream the address of the istream
 */
Lexer::Lexer(istream& i):in(i), next('\0'), linenum(1), linepos(1)
{

}

Lexer::Lexer(ifstream& i):in(i), next('\0'), linenum(1), linepos(1)
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
 * setter for the next variable
 * @param c the value next will become  
 */
void Lexer::setNext(char c)
{
 this->next = c;
}

/*
 * gets the next char from the input stream
 * @return c the next char in input stream
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
 * gets the next token from std in and returns is as a token object
 * @return the token object
 */
Token Lexer::nextToken()
{
 //string to hold the current token
 string lex = "";

 //save linepos and line num at start
 int tokpos = linepos;
 int tokline = linenum;
 
 //if gets the ball rolling on the first call of nextToken 
 if(next == '\0')
  next = nextChar();
 
 while(true)
 {
  //if there is a space next and the token is empty continue iteration until you reach the next char
  if(isspace(next) && lex == "")
  {
   while(isspace(next))
   { 
    next = nextChar();
    //update tokpos and tokline
    tokpos = linepos;
    tokline = linenum;
   }
  }

  //if there is a space or special character next and lex is not empty we have a token
  if(isspace(next) || (isSpecialChar(next) && lex != ""))
  {  
    //giant ugly if statment could have been done using arrays for good practice but I wanted to practice my vim skills
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
    //if its not a keyword then it must be one of the other types
    else
    {
     if(isIntlit(lex))
      return Token(Token::INTLIT, lex, tokline, tokpos);
     else if(isFloatlit(lex))
      return Token(Token::FLOATLIT, lex, tokline, tokpos);
     else if(isIdent(lex))
      return Token(Token::IDENT, lex, tokline, tokpos);
     else
      return Token(Token::ERROR, lex, tokline, tokpos);
    }
  }
  //if its a special character and lex is empty then parse the characters
  else if(isSpecialChar(next))
  {
   //make sure the program is one step ahead of the parser
   char temp = next;
   next = nextChar();
   //giant switch again bad practice but vim skills are important
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
     //check for ==
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
     //check for <=
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
     //check for >=
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
    case '\"':
     lex += next;
     next = nextChar();
     while(next != '\"')
     {
      lex += next;
      next = nextChar();
     }
     next = nextChar();
     return Token(Token::STRLIT, lex, tokline, tokpos);
    default:
     return Token(Token::ERROR, "error", tokline, tokpos);
   }
  }
  //else we just have a char and append it to lex then go to the next char
  else
  {
   lex += next;
   next = nextChar();
  }
 }
}

/*
 * uses the special chars string to figure out if a char is special
 * @param ch the character that is being tested 
 * @return true if it is false if it is not
 */
bool Lexer::isSpecialChar(char ch)
{
 return specialChars.find(ch) != string::npos;
}

/*
 * determines if a string is type intlit
 * @param s the string that is being tested
 */
bool Lexer::isIntlit(string s)
{
 for(uint i = 0; i < s.size(); i++)
 {
  //if anything is not a digit then it fails
  if(!isdigit(s[i]))
  {
   return false;
  }
 }
 return true;
}

/*
 * determines if a string is type float
 * @param s the string that is being tested
 * @return true if true false if false 
 */
bool Lexer::isFloatlit(string s)
{
 //if the first char is not a number fail
 if(!isdigit(s[0]))
 {
  return false;
 }
 int count = 0;
 for(uint i = 0; i < s.size(); i++)
 {
  //count the periods
  if(s[i] == '.')
  {
   count++;
  }
  //if anything is not a digit except the period then fail
  else if(!isdigit(s[i]))
  {
   return false;
  }
 }
 //if the count is not 1 then fail
 if(count != 1)
 {
  return false;
 }
 //otherwise return true
 else
 {
  return true;
 }
}

/*
 * checks if an inputed string is a string literal
 * @param s the string that is being tested
 * @return true if true false if false 
 */
bool Lexer::isStrlit(string s)
{
  //only condition is that it has to have quotes on both sides
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
 * checks if string is of type ident
 * @param s the string that is being tested
 * @return true if true false if false 
 */
bool Lexer::isIdent(string s)
{
 for(uint i = 0; i < s.size(); i++)
 {
  //if its not a number then check if its one of the two allowed chars
  if(!isalnum(s[i]))
  {
   //if allowed continue
   if(s[i] == '_' || s[i] == '*')
   {
    continue;
   }
   //else not a string
   else
   {
    return false;
   }
  }
 }
 return true;
}

/*
 * gets the next char from the istream using get method
 * @param i the address of the istream
 * @return the next char
 */
char Lexer::get(istream& i)
{
 return i.get();
}
