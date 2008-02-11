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