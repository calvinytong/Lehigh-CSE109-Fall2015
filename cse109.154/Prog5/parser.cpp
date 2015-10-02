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

Parser::TreeNode* Parser::factor() {
  TreeNode* factornode;
  int tokentype = token.getType();
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
    break;
  }
  token = lexer.nextToken();
  return factornode;
}

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

Parser::TreeNode* Parser::expression() {
  TreeNode* expNode = term();
  TreeNode* termNode;
  int tokenType = token.getType();
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
  return NULL;
}

Parser::TreeNode* Parser::logicalExpression() {
  return NULL;
}

Parser::TreeNode* Parser::setStatement() {
  TreeNode* setnode;
  TreeNode* expnode;
  TreeNode* seqnode;
  string message = "invalid set syntax";
  check(Token::SET, message);
  token = lexer.nextToken();
  check(Token::IDENT, message);
  setnode = new TreeNode(STOREV, token.getLexeme());
  token = lexer.nextToken();
  check(Token::ASSIGN, message);
  token = lexer.nextToken();
  expnode = expression();
  seqnode = new TreeNode(SEQ, expnode, setnode);
  return seqnode;
}

Parser::TreeNode* Parser::parsePrintExpression() {
  TreeNode* stringnode;
  TreeNode* printnode;
  int tokenType = token.getType();
  switch(tokenType)
  {
   case Token::STRLIT:
    stringnode = new TreeNode(PRINTS, token.getLexeme());
    token = lexer.nextToken();
    return stringnode;
   case Token::IDENT:
    stringnode = new TreeNode(LOADV, token.getLexeme());
    token = lexer.nextToken();
    break;
   default:
    stringnode = expression();
  }
  printnode = new TreeNode(PRINT, NULL, stringnode);
  return printnode;
}

Parser::TreeNode* Parser::printStatement() {
  TreeNode* printstatenode;
  TreeNode* printnode;
  string message = "invalid print syntax";
  check(Token::PRINT, message);
  token = lexer.nextToken();
  printstatenode = parsePrintExpression();
  int tokenType = token.getType();
  while(tokenType == Token::COMMA)
  {
   token = lexer.nextToken();
   printnode = parsePrintExpression();
   printstatenode = new TreeNode(SEQ, printstatenode, printnode);
   tokenType = token.getType();
  }
  return printstatenode;
}

Parser::TreeNode* Parser::whileStatement() {
  return NULL;
}

Parser::TreeNode* Parser::forStatement() {
  return NULL;
}

Parser::TreeNode* Parser::ifStatement() {
  return NULL;
}

Parser::TreeNode* Parser::switchStatement() {
  return NULL;  
}

Parser::TreeNode* Parser::statement() {
  TreeNode* statement = NULL;
  switch (token.getType()) {
    case Token::SET:
      statement = setStatement();
      break;
    case Token::PRINT:
      statement = printStatement();
      break;
    default:
      error("Unrecognized statement");
      break;
  }
  return statement;
}

Parser::TreeNode* Parser::compoundStatement() {
  TreeNode* compnode = statement();
  TreeNode* statementnode;
  while(token.getLexeme() != "end")
  {
   statementnode = statement();
   compnode = new TreeNode(SEQ, compnode, statementnode);
  }
  token = lexer.nextToken();
  check(Token::PROGRAM, "invalide ending");
  return compnode;
}

Parser::TreeNode* Parser::program() {
  TreeNode* compoundnode;
  string message = "invalid program declaration";
  check(Token::PROGRAM, message);
  token = lexer.nextToken();
  check(Token::IDENT, message);
  token = lexer.nextToken();
  compoundnode = compoundStatement();
  return compoundnode;
}
