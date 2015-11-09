#include <cstdlib>
#include <iostream>
#include "Lexer.h"
#include "Token.h"
#include <string>
#include <stdio.h>
using namespace std;

class Token;

//string containing special chars
const string specialChars = "$\"";

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
 if(c == '$')
 {
  return '$';
 }
 else if(c == '#')
 {
   while(c != '\n' && c != EOF)
    c = get(this->getIn());
   linepos = 0;
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
  if(isspace(next))
  {  
      return Token(Token::IDENT, lex, tokline, tokpos);
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
    case '$':
     return Token(Token::ENDOFFILE, "$", tokline, tokpos);
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
 * gets the next char from the istream using get method
 * @param i the address of the istream
 * @return the next char
 */
char Lexer::get(istream& i)
{
 
 char c;
 if(i.get(c))
  return c;
 else
  return '$';
}
