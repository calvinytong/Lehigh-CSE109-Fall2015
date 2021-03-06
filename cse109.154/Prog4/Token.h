#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

//header for the token class
class Token
{
 public:
  //header file declarations for the token types
  static const int INTLIT;
  static const int FLOATLIT;
  static const int STRLIT;
  static const int IDENT;

  static const int PLUS;
  static const int MINUS;
  static const int TIMES;
  static const int DIVIDE;
  static const int REM;
  static const int ASSIGN;
  static const int LPAREN;
  static const int RPAREN;
  static const int COMMA;
  static const int EQ;
  static const int LT;
  static const int LE;
  static const int GT;
  static const int GE;
  static const int NE;

  static const int SET;
  static const int PRINT;
  static const int WHILE;
  static const int DO;
  static const int END;
  static const int AND;
  static const int OR;
  static const int IF;
  static const int THEN;
  static const int ELSE;
  static const int ENDIF;
  static const int PROGRAM;

  static const int ENDOFFILE;
  static const int ERROR;
  
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
