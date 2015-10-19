/*
 * CSE 109
 * Calvin Tong
 * cyt219
 * Program Description: parses the output of the lexer and builds a tree 
 * I have only implemented some of the methods in this program,
 * the methods I have written have a comment on the top of them
 * Program #6
 */

#include "parser.h"
#include <cstring>
#include <string>

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
			      "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
			      "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
}

Parser::~Parser() {
}

void Parser::genCode() {
  TreeNode* programNode = program();
  generateCode(programNode);
}

void Parser::gen(TreeNode* node) {
  switch (node->op) {
    case SEQ:
    case NULLX:
      break;
    case LOADL:
    case LOADV:
    case STOREV:
    case JUMPF:
    case JUMP:
      emit(node->op, node->val);
      break;
    case PRINTS:
      emit(node->op, "\"" + node->val + "\"");
      break;
    case INSLABEL:
      emit(node->val);
      break;
    default:
      emit(node->op);
  }
}

void Parser::generateCode(TreeNode* node) {
  if (node != NULL) {
    generateCode(node->leftChild);
    generateCode(node->rightChild);
    gen(node);
  }
}

Parser::TreeNode* Parser::optimize(TreeNode* node) {
    return NULL;
}

void Parser::error(string message) {
  cerr << message << " Found " << token.getLexeme() << " at line " << token.getLine() << " position " << token.getPos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.getType() != tokenType)
    error(message);
}

/*
 * parses a factor
 * @return the node containing the factor tree
 */
Parser::TreeNode* Parser::factor() {
  TreeNode* factornode;
  int tokentype = token.getType();
  
  //check token type
  switch(tokentype)
  {
   case Token::INTLIT:
    factornode = new TreeNode(LOADL, token.getLexeme());
    break;
   case Token::FLOATLIT:
    factornode = new TreeNode(LOADL, token.getLexeme());
    break;
   case Token::IDENT:
    factornode = new TreeNode(LOADV, token.getLexeme());
    break;
   case Token::LPAREN:
    factornode = expression();
    check(Token::RPAREN, "expression has no closing paren");
    break;
  }
  token = lexer.nextToken();
  return factornode;
}

//not written by me
Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor();
  TreeNode* factorNode;
  int tokenType = token.getType();
  while (tokenType == Token::TIMES || tokenType == Token::DIVIDE || tokenType == Token::REM) {
    token = lexer.nextToken();
    factorNode = factor();
    switch (tokenType) {
      case Token::TIMES:
        termNode = new TreeNode(MULT, termNode, factorNode);
        break;
      case Token::DIVIDE:
        termNode = new TreeNode(DIV, termNode, factorNode);
        break;
      case Token::REM:
        termNode = new TreeNode(REM, termNode, factorNode);
        break;
    }
    tokenType = token.getType();
  }
  return termNode;
}

/*
 * parses an expression
 * @return a pointer to the node containing the expression tree
 */
Parser::TreeNode* Parser::expression() {
  //get initial term
  TreeNode* expNode = term();
  TreeNode* termNode;
  int tokenType = token.getType();
  
  //if there are more terms iterate through
  while(tokenType == Token::PLUS || tokenType == Token::MINUS)
  {
   token = lexer.nextToken();
   termNode = term();
   switch(tokenType)
   {
    case Token::PLUS:
     expNode = new TreeNode(ADD, expNode, termNode);
     break;
    case Token::MINUS:
     expNode = new TreeNode(SUB, expNode, termNode);
     break;
   }
   tokenType = token.getType();
  }  
  return expNode;
}

Parser::TreeNode* Parser::relationalExpression() {
 TreeNode* expnode = expression();
 TreeNode* cmpnode;
 TreeNode* rootnode;
 int tokenType = token.getType();
 token = lexer.nextToken();
 cmpnode = expression();
 switch(tokenType)
 {
  case Token::EQ:
   rootnode = new TreeNode(ISEQ, expnode, cmpnode);
   break;
  case Token::LT:
   rootnode = new TreeNode(ISLT, expnode, cmpnode);
   break;
  case Token::GT:
   rootnode = new TreeNode(ISLT, expnode, cmpnode);
   break;
  case Token::GE:
   rootnode = new TreeNode(ISGE, expnode, cmpnode);
   break;
  case Token::NE:
   rootnode = new TreeNode(ISNE, expnode, cmpnode);
   break;
 }
 return rootnode;
}

Parser::TreeNode* Parser::logicalExpression() {
  TreeNode* leftnode = relationalExpression();
  TreeNode* rightnode;
  TreeNode* rootnode;
  int tokenType = token.getType();
  if(tokenType == Token::AND)
  {
   token = lexer.nextToken();
   rightnode = relationalExpression();
   rootnode = new TreeNode(AND, leftnode, rightnode);
  }
  else if(tokenType == Token::OR)
  {
   token = lexer.nextToken();
   rightnode = relationalExpression();
   rootnode = new TreeNode(OR, leftnode, rightnode);
  }
  else
  {
   return leftnode;
  }
  tokenType = token.getType();
  while(tokenType == Token::AND || tokenType == Token::OR)
  {
   token = lexer.nextToken();
   rightnode = relationalExpression();
   switch(tokenType)
   {
    case Token::AND:
     rootnode = new TreeNode(AND, rootnode, rightnode);
     break;
    case Token::OR:
     rootnode = new TreeNode(OR, rootnode, rightnode);
     break;
   }
   tokenType = token.getType();
  }
  return rootnode;
}

/*
 * parses a set statment
 * @return a pointer to the node containing the set statment tree
 */
Parser::TreeNode* Parser::setStatement() {
  TreeNode* setnode;
  TreeNode* expnode;
  TreeNode* seqnode;
  
  //check to make sure syntax is correct
  string message = "invalid set syntax";
  check(Token::SET, message);
  token = lexer.nextToken();
  check(Token::IDENT, message);
  
  //create the set node
  setnode = new TreeNode(STOREV, token.getLexeme());
  token = lexer.nextToken();
  check(Token::ASSIGN, message);
  token = lexer.nextToken();

  //parse the expression
  expnode = expression();
  seqnode = new TreeNode(SEQ, expnode, setnode);
  return seqnode;
}

/*
 * parses a print expression
 * @return printnode the node containing the print expression tree
 */
Parser::TreeNode* Parser::parsePrintExpression() {
  TreeNode* stringnode;
  TreeNode* printnode;
  
  //check type of token
  int tokenType = token.getType();
  switch(tokenType)
  {
   //if str lit then just return a node with the string and PRINTS 
   case Token::STRLIT:
    stringnode = new TreeNode(PRINTS, token.getLexeme());
    token = lexer.nextToken();
    return stringnode;
   //if ident then load the variable
   case Token::IDENT:
    stringnode = new TreeNode(LOADV, token.getLexeme());
    token = lexer.nextToken();
    break;
   //else it is an expression so call expression method
   default:
    stringnode = expression();
  }
  printnode = new TreeNode(PRINT, NULL, stringnode);
  return printnode;
}

/*
 * parses a print statement
 * @return the node containing the tree with instructions to execute a print
 */
Parser::TreeNode* Parser::printStatement() {
  TreeNode* printstatenode;
  TreeNode* printnode;
  TreeNode* println = new TreeNode(PRINTLN);
  //get the next Token
  token = lexer.nextToken();
  
  //get initial print statement
  printstatenode = parsePrintExpression();
  
  //loop until commas run out and build the tree out
  int tokenType = token.getType();
  while(tokenType == Token::COMMA)
  {
   token = lexer.nextToken();
   printnode = parsePrintExpression();
   printstatenode = new TreeNode(SEQ, printstatenode, printnode);
   tokenType = token.getType();
  }
  printstatenode = new TreeNode(SEQ, printstatenode, println);
  return printstatenode;
}

Parser::TreeNode* Parser::whileStatement() {
  string lblone = makeLabel();
  string lbltwo = makeLabel();
  
  TreeNode* opnode = new TreeNode(INSLABEL, lblone += ":");
  lblone.erase(lblone.size() - 1);
  TreeNode* seqnode = new TreeNode(SEQ, NULL, opnode);
  
  token = lexer.nextToken();
  
  opnode = logicalExpression();
  seqnode = new TreeNode(SEQ, seqnode, opnode);
  
  check(Token::DO, "improper while syntax");
  
  opnode = new TreeNode(JUMPF, lbltwo);
  seqnode = new TreeNode(SEQ, seqnode, opnode);
  
  token = lexer.nextToken();

  opnode = compoundStatement();
  seqnode = new TreeNode(SEQ, seqnode, opnode);

  opnode = new TreeNode(JUMP, lblone);
  seqnode = new TreeNode(SEQ, seqnode, opnode);

  opnode = new TreeNode(INSLABEL, lbltwo += ":");
  seqnode = new TreeNode(SEQ, seqnode, opnode);
  
  check(Token::END, "end of while not found");
  token = lexer.nextToken();
  return seqnode;
}

Parser::TreeNode* Parser::forStatement() {
  return NULL;
}

Parser::TreeNode* Parser::ifStatement() {
  string lblone = makeLabel();
  string lbltwo = makeLabel();
  token = lexer.nextToken();
  
  TreeNode* opnode = logicalExpression();
  TreeNode* seqnode = new TreeNode(SEQ, NULL, opnode);

  check(Token::THEN, "invalid if syntax");
  token = lexer.nextToken();
  
  opnode = new TreeNode(JUMPF, lblone); 
  seqnode = new TreeNode(SEQ, seqnode, opnode);

  opnode = compoundStatement();
  seqnode = new TreeNode(SEQ, seqnode, opnode);

  opnode = new TreeNode(JUMP, lbltwo);
  seqnode = new TreeNode(SEQ, seqnode, opnode);
  
  opnode = new TreeNode(INSLABEL, lblone += ":");
  seqnode = new TreeNode(SEQ, seqnode, opnode); 

  int tokenType = token.getType();
  
  if(tokenType == Token::ELSE)
  {
   token = lexer.nextToken();
   opnode = compoundStatement();
   seqnode = new TreeNode(SEQ, seqnode, opnode);
  }
  check(Token::ENDIF, "invalid if syntax");
  token = lexer.nextToken();
  opnode = new TreeNode(INSLABEL, lbltwo += ":");
  seqnode = new TreeNode(SEQ, seqnode, opnode);
  
  return seqnode;
}

Parser::TreeNode* Parser::switchStatement() {
  return NULL;  
}

//statement was written by femister
Parser::TreeNode* Parser::statement() {
  TreeNode* statement = NULL;
  switch (token.getType()) {
    case Token::SET:
      statement = setStatement();
      break;
    case Token::PRINT:
      statement = printStatement();
      break;
    case Token::WHILE:
      statement = whileStatement();
      break;
    case Token::IF:
      statement = ifStatement();
      break;
    default:
      error("Unrecognized statement");
      break;
  }
  return statement;
}

/*
 * parses a compound statement
 * @return a pointer to the node containing the compound statement
 */
Parser::TreeNode* Parser::compoundStatement() {
  //get initial statement
  TreeNode* compnode = statement();
  TreeNode* statementnode;
  int tokenType = token.getType();
  while(tokenType == Token::SET || tokenType == Token::WHILE || tokenType == Token::PRINT || tokenType == Token::IF)
  {
   statementnode = statement();
   compnode = new TreeNode(SEQ, compnode, statementnode);
   tokenType = token.getType();
  }

  return compnode;
}

/*
 * entry point to the tree parses the start of the program
 * @return a popinter to the node that is the root of the tree
 */
Parser::TreeNode* Parser::program() {
  TreeNode* compoundnode;
  string message = "invalid program declaration";
  
  //check to see if the program is initialized correct syntax
  check(Token::PROGRAM, message);
  token = lexer.nextToken();
  check(Token::IDENT, message);
  token = lexer.nextToken();

  //build the tree by calling compound statement
  compoundnode = compoundStatement();
  check(Token::END, message);
  token = lexer.nextToken();
  check(Token::PROGRAM, message);
  return compoundnode;
}
