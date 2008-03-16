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

void Parser::parseFormals() {
  // FIXME: Implement parameters!
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
  while (true) {
    Token t = lex.peek();
    
    switch (t.type) {
      case Token::FLOAT:
      case Token::STRING:
      case Token::COLOR:
      case Token::POINT:
      case Token::VECTOR:
      case Token::NORMAL:
      case Token::MATRIX:
        parseVariableDecl();
        break;
      case Token::IDENTIFIER:
        if (lex.peek(2).type == Token::LPAREN)
          parseCallStmt();
        else
          parseAssignmentStmt();
        break;
      case Token::SEMI:
        lex.consume(Token::SEMI);
        break;
      case Token::IF:
        parseIfStmt();
        break;
      case Token::FOR:
        parseForLoop();
        break;
      case Token::WHILE:
        parseWhileLoop();
        break;
      case Token::SOLAR:
        parseSolarLoop();
        break;
      case Token::ILLUMINATE:
        parseIlluminateLoop();
        break;
      case Token::ILLUMINANCE:
        parseIlluminanceLoop();
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

void Parser::parseVariableDecl() {
  unsigned stage = 0;
  
  while (stage < 3) {
    Token t = lex.consume();
    
    if (t.type == Token::EXTERN && stage == 0) {
      stage = 1;
    } else if ((t.type == Token::VARYING ||
                t.type == Token::UNIFORM)
               && stage < 2) {
      stage = 2;
    } else if (t.type == Token::FLOAT ||
               t.type == Token::STRING ||
               t.type == Token::COLOR ||
               t.type == Token::POINT ||
               t.type == Token::VECTOR ||
               t.type == Token::NORMAL ||
               t.type == Token::MATRIX) {
      stage = 3;
    }
  }
  
  parseDefExpressions();
  lex.consume(Token::SEMI);
}

void Parser::parseAssignmentStmt() {
  parseAssignmentExpr();
  lex.consume(Token::SEMI);
}

void Parser::parseCallStmt() {
  parseCallExpr();
  lex.consume(Token::SEMI);
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
  lex.consume(Token::LPAREN);
  parseRelation();
  lex.consume(Token::RPAREN);
  parseBlockBody();
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
  parseBlockBody();
}

void Parser::parseIlluminateLoop() {
  lex.consume(Token::ILLUMINATE);
  lex.consume(Token::LPAREN);
  parseExpressionList();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseIlluminanceLoop() {
  lex.consume(Token::ILLUMINANCE);
  lex.consume(Token::LPAREN);
  parseExpressionList();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseSolarLoop() {
  lex.consume(Token::SOLAR);
  lex.consume(Token::LPAREN);
  parseExpressionList();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseIfStmt() {
  lex.consume(Token::IF);
  lex.consume(Token::LPAREN);
  parseRelation();
  lex.consume(Token::RPAREN);
  parseBlockBody();
  
  Token t = lex.peek();
  if (t.type == Token::ELSE)
    parseBlockBody();
}

void Parser::parseBlockBody() {
  Token t = lex.peek();
  if (t.type == Token::LBRACE) {
    lex.consume(Token::LBRACE);
    parseStatements();
    lex.consume(Token::RBRACE);
  } else {
    switch (t.type) {
      case Token::IDENTIFIER:
        parseAssignmentStmt();
        break;
      case Token::SEMI:
        lex.consume(Token::SEMI);
        break;
      case Token::IF:
        parseIfStmt();
        break;
      case Token::FOR:
        parseForLoop();
        break;
      case Token::WHILE:
        parseWhileLoop();
        break;
      case Token::SOLAR:
        parseSolarLoop();
        break;
      case Token::ILLUMINATE:
        parseIlluminateLoop();
        break;
      case Token::ILLUMINANCE:
        parseIlluminanceLoop();
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
        assert(0 && "Expected a statement!");
    }
  }
}

void Parser::parseDefExpressions() {
  while (lex.peek().type == Token::IDENTIFIER) {
    lex.consume(Token::IDENTIFIER);
    
    if (lex.peek().type == Token::EQUAL) {
      lex.consume(Token::EQUAL);
      parseExpression();
    }
    
    if (lex.peek().type == Token::COMMA)
      lex.consume(Token::COMMA);
    else
      break;
  }
}

void Parser::parseCallExpr() {
  lex.consume(Token::IDENTIFIER);
  lex.consume(Token::LPAREN);
  
  while (lex.peek().type != Token::RPAREN) {
    parseExpression();
    if (lex.peek().type != Token::RPAREN)
      lex.consume(Token::COMMA);
  }
  
  lex.consume(Token::RPAREN);
}

void Parser::parseAssignmentExpr() {
  lex.consume(Token::IDENTIFIER);
  
  if (lex.peek().type == Token::LBRACKET) {
    lex.consume(Token::LBRACKET);
    parseExpression();
    lex.consume(Token::RBRACKET);
  }
  
  Token t = lex.peek();
  switch (t.type) {
    case Token::EQUAL:
    case Token::PLUSEQUAL:
    case Token::MINUSEQUAL:
    case Token::STAREQUAL:
    case Token::SLASHEQUAL:
      lex.consume();
      break;
    default:
      assert(0 && "Expected assignment operator!");
  }
  
  parseExpression();
}

void Parser::parseRelation() {
  // FIXME: Implement relations!
}

void Parser::parseExpression() {
  // FIXME: Implement expressions!
}

void Parser::parseExpressionList() {
  // FIXME: Implement expression lists!
}