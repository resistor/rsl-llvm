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