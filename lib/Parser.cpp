#include "rsl-llvm/Lexer.h"
#include "rsl-llvm/Parser.h"

void Parser::parseDefinitions() {
  Token t = lex.peek();
  
  switch(t.type) {
    case Token::FLOAT:
    case Token::STRING:
    case Token::COLOR:
    case Token::POINT:
    case Token::VECTOR:
    case Token::NORMAL:
    case Token::MATRIX:
    case Token::VOID:
      parseFunctionDefinition();
      parseDefinitions();
      break;
    case Token::LIGHT:
    case Token::SURFACE:
    case Token::VOLUME:
    case Token::DISPLACEMENT:
    case Token::IMAGER:
      parseShaderDefinition();
      parseDefinitions();
      break;
    case Token::ENDOFFILE:
      return;
    default:
      assert(0 && "Unexpected token!");
  }
}

void Parser::parseShaderDefinition() {
  // Consume the shader type
  // NOTE: We've already checked in the caller
  // that this is the correct token type, so no need to check
  Token shaderType = lex.consume();
  
  // Consume the shader's name
  Token shaderName = lex.consume(Token::IDENTIFIER);
  
  // Formal arguments
  lex.consume(Token::LPAREN);
  parseFormals();
  lex.consume(Token::RPAREN);
  
  // Shader body
  lex.consume(Token::LBRACE);
  parseStatements();
  lex.consume(Token::RBRACE);
}

void Parser::parseFunctionDefinition() {
  // Consume the shader type
  // NOTE: We've already checked in the caller
  // that this is the correct token type, so no need to check
  Token funcType = lex.consume();
  
  // Consume the shader's name
  Token funcName = lex.consume(Token::IDENTIFIER);
  
  // Formal arguments
  lex.consume(Token::LPAREN);
  parseFormals();
  lex.consume(Token::RPAREN);
  
  // Shader body
  lex.consume(Token::LBRACE);
  parseStatements();
  lex.consume(Token::RBRACE);
}

void Parser::parseStatements() {
  Token t = lex.peek();
  
  while (true) {
    switch (t.type) {
      case Token::IDENTIFIER:
      case Token::SEMI:
      case Token::IF:
        parseStatement();
        break;
      case Token::FOR:
        parseForLoop();
        break;
      case Token::WHILE:
        parseWhileLoop();
        break;
      case Token::BREAK:
        parseBreakStmt();
        break;
      case Token::CONTINUE:
        parseContinueStmt();
        break;
      case Token::RETURN:
        parseReturnStmt();
        break;
      default:
        return;
    }
  }
}

void Parser::parseReturnStmt() {
  lex.consume(Token::RETURN);
  parseExpression();
  lex.consume(Token::SEMI);
}

void Parser::parseContinueStmt() {
  lex.consume(Token::CONTINUE);
  if (lex.peek().type == Token::NUMERIC)
    lex.consume(Token::NUMERIC);
  lex.consume(Token::SEMI);
}

void Parser::parseBreakStmt() {
  lex.consume(Token::BREAK);
  if (lex.peek().type == Token::NUMERIC)
    lex.consume(Token::NUMERIC);
  lex.consume(Token::SEMI);
}

void Parser::parseWhileLoop() {
  lex.consume(Token::WHILE);
  parseRelation();
  lex.consume(Token::LBRACE);
  parseStatements();
  lex.consume(Token::RBRACE);
}

void Parser::parseForLoop() {
  lex.consume(Token::FOR);
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::SEMI);
  parseRelation();
  lex.consume(Token::SEMI);
  parseExpression();
  lex.consume(Token::RPAREN);
  
  Token t = lex.peek();
  if (t.type == Token::LBRACE) {
    lex.consume(Token::LBRACE);
    parseStatements();
    lex.consume(Token::RBRACE);
  } else {
    // FIXME: Parse single statement here.
  }
}