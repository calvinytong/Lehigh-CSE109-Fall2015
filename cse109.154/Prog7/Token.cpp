#include <cstdlib>
#include <iostream>
#include "Token.h"


//declarations of static constants
int const Token::INTLIT = 1;
int const Token:: FLOATLIT = 2;
int const Token::STRLIT = 3;
int const Token::IDENT = 4;

int const Token::ENDOFFILE = 32;
int const Token::ERROR = 33;


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
