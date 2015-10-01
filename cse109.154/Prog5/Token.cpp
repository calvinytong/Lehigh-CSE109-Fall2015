#include <cstdlib>
#include <iostream>
#include "Token.h"


//declarations of static constants
// int const Token::INTLIT = 1;
// int const Token:: FLOATLIT = 2;
// int const Token::STRLIT = 3;
// int const Token::IDENT = 4;
// int const Token::PLUS = 5;
// int const Token::MINUS = 6;
// int const Token::TIMES = 7;
// int const Token::DIVIDE = 8;
// int const Token::REM = 9;
// int const Token::ASSIGN = 10;
// int const Token::LPAREN = 11;
// int const Token::RPAREN = 12;
// int const Token::COMMA = 13;
// int const Token::EQ = 14;
// int const Token::LT = 15;
// int const Token::LE = 16;
// int const Token::GT = 17;
// int const Token::GE = 18;
// int const Token::NE = 19;

// int const Token::SET = 20;
// int const Token::PRINT = 21;
// int const Token::WHILE = 22;
// int const Token::DO = 23;
// int const Token::END = 24;
// int const Token::AND = 25;
// int const Token::OR = 26;
// int const Token::IF = 27;
// int const Token::THEN = 28;
// int const Token::ELSE = 29;
// int const Token::ENDIF = 30;
// int const Token::PROGRAM = 31;
// int const Token::ENDOFFILE = 32;
// int const Token::ERROR = 33;


/*
 * constructor
 * @param t type of the lexeme
 * @param lex the actual lexeme
 * @param l the line number of the lexeme
 * @param p the position of the char on the line
 */
Token::Token(int t, string lex, int l, int p):tokentype(t), lexeme(lex), linenum(l), charpos(p)
{

}
/*
 * default constructor for testing sets all to null
 */
Token::Token(): tokentype(NULL), lexeme(NULL), linenum(NULL), charpos(NULL)
{

}

/*
 * destructor method not needed in this class
 */
Token::~Token()
{

}

/*
 * getter method for token type
 * @return the tokentype as an int
 */
int Token::getType() const
{
 return this->tokentype;
}

/*
 * getter method for lexeme
 * @return the lexeme
 */
string Token::getLexeme() const
{
  return this->lexeme;
}

/*
 * getter method for line num
 * @return the line number
 */
int Token::getLine() const
{
  return this->linenum;
}

/*
 * getter method for line pos
 * @return the position on the line
 */
int Token::getPos() const
{
  return this->charpos;
}

//note setters are for testing

/*
 * setter method for token type
 * @param i the new token type
 */
void Token::setType(int i)
{
  tokentype = i;
}

/*
 * setter method for Lexeme 
 * @param i the new lexeme 
 */
void Token::setLexeme(string s)
{
  lexeme = s;
}

/*
 * setter method for line num
 * @param i the new line num
 */
void Token::setLinenum(int i)
{
  linenum = i;
}

/*
 * setter method for char pos
 * @param i the new char position
 */
void Token::setCharpos(int i)
{
  charpos = i;
}

/*
 * friend overload for the << operator writes out the token with tab separation
 * @param out the address of the output stream
 * @param t the address of the token object
 */
ostream& operator<<(ostream& out, Token& t)
{
 out << t.getType() << '\t' << t.getLexeme() << '\t' << t.getLine() << '\t' << t.getPos() << endl;
 return out;
}
