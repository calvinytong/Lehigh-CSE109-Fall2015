#include <cstdlib>
#include "Token.h"

namespace Tok
{
 int const Token::INTLIT = 1;
 int const Token:: FLOATLIT = 2;
 int const Token::STRLIT = 3;
 int const Token::IDENT = 4;

 int const Token::PLUS = 5;
 int const Token::MINUS = 6;
 int const Token::TIMES = 7;
 int const Token::DIVIDE = 8;
 int const Token::REM = 9;
 int const Token::ASSIGN = 10;
 int const Token::LPAREN = 11;
 int const Token::RPAREN = 12;
 int const Token::COMMA = 13;
 int const Token::EQ = 14;
 int const Token::LT = 15;
 int const Token::LE = 16;
 int const Token::GT = 17;				 
 int const Token::GE = 18;
 int const Token::NE = 19;

 int const Token::SET = 20;
 int const Token::PRINT = 21;
 int const Token::WHILE = 22;
 int const Token::DO = 23;
 int const Token::END = 24;
 int const Token::AND = 25;
 int const Token::OR = 26;
 int const Token::IF = 27;
 int const Token::THEN = 28;
 int const Token::ELSE = 29;
 int const Token::ENDIF = 30;
 int const Token::PROGRAM = 31;
 int const Token::ENDOFFILE = 32;
 int const Token::ERROR = 33;



 Token::Token(int t, string lex, int l, int p):tokentype(t), lexeme(lex), linenum(l), charpos(p)
 { 

 }

 Token::Token(): tokentype(NULL), lexeme(NULL), linenum(NULL), charpos(NULL)
 {

 } 

 int Token::getType() const
 {
  return this->tokentype;
 }

 string Token::getLexeme() const
 {
  return this->lexeme;
 }

 int Token::getLine() const
 {
  return this->linenum;
 }

 int Token::getPos() const
 {
  return this->charpos;
 } 

 void Token::setType(int i)
 {
  tokentype = i; 
 }

 void Token::setLexeme(string s)
 {
  lexeme = s;
 }

 void Token::setLinenum(int i)
 {
  linenum = i;
 }

 void Token::setCharpos(int i)
 {
  charpos = i;
 }
}
