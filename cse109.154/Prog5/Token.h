#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

//header for the token class
class Token
{
 public:
  //header file declarations for the token types
  static const int  Token::INTLIT = 1;
  static const int  Token:: FLOATLIT = 2;
  static const int  Token::STRLIT = 3;
  static const int  Token::IDENT = 4;
  static const int  Token::PLUS = 5;
  static const int  Token::MINUS = 6;
  static const int  Token::TIMES = 7;
  static const int  Token::DIVIDE = 8;
  static const int  Token::REM = 9;
  static const int  Token::ASSIGN = 10;
  static const int  Token::LPAREN = 11;
  static const int  Token::RPAREN = 12;
  static const int  Token::COMMA = 13;
  static const int  Token::EQ = 14;
  static const int  Token::LT = 15;
  static const int  Token::LE = 16;
  static const int  Token::GT = 17;
  static const int  Token::GE = 18;
  static const int  Token::NE = 19;

  static const int  Token::SET = 20;
  static const int  Token::PRINT = 21;
  static const int  Token::WHILE = 22;
  static const int  Token::DO = 23;
  static const int  Token::END = 24;
  static const int  Token::AND = 25;
  static const int  Token::OR = 26;
  static const int  Token::IF = 27;
  static const int  Token::THEN = 28;
  static const int  Token::ELSE = 29;
  static const int  Token::ENDIF = 30;
  static const int  Token::PROGRAM = 31;
  static const int  Token::ENDOFFILE = 32;
  static const int  Token::ERROR = 33;
  //constructors
  Token(int t, string lex, int l, int p);
  Token();

  //destructors
  ~Token();

  //getters
  int getType() const;
  string getLexeme() const;
  int getLine() const;
  int getPos() const;

  //setters
  void setType(int i);
  void setLexeme(string s);
  void setLinenum(int i);
  void setCharpos(int i);

  //friend operator overload
  friend ostream& operator<<(ostream& in, Token& t);

  private:
    //private member variables
   int tokentype;
   string lexeme;
   int linenum;
   int charpos;
};

#endif
