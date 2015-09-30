#include "parser.h"
#include <cstring>

const string Parser::ops[] = {"ADD", "SUB", "AND", "DIV", "REM", "ISEQ", "ISGE", "ISGT", "ISLE",
			      "ISLT", "ISNE", "MULT", "OR", "LOADL", "LOADV", "STOREV", "JUMPF",
			      "JUMP", "INSLABEL", "PRINT", "SEQ", "NULLX", "PRINTLN", "PRINTS"};

Parser::Parser(Lex& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
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
}

void Parser::error(string message) {
  cerr << message << " Found " << token.lexeme() << " at line " << token.line() << " position " << token.pos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.type() != tokenType)
    error(message);
}

Parser::TreeNode* Parser::factor() {
  return NULL;
}

Parser::TreeNode* Parser::term() {
  TreeNode* termNode = factor();
  TreeNode* factorNode;
  int tokenType = token.type();
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
    tokenType = token.type();
  }
  return termNode;
}

Parser::TreeNode* Parser::expression() {
  return NULL;
}

Parser::TreeNode* Parser::relationalExpression() {
  return NULL;
}

Parser::TreeNode* Parser::logicalExpression() {
  return NULL;
}

Parser::TreeNode* Parser::setStatement() {
  return NULL;
}

Parser::TreeNode* Parser::parsePrintExpression() {
  return NULL;
}

Parser::TreeNode* Parser::printStatement() {
  return NULL;
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
  switch (token.type()) {
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
  return NULL;
}

Parser::TreeNode* Parser::program() {
  return NULL;
}
