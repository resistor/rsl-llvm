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
  Token t = lex.peek();
  
  if (t.type != Token::RPAREN)
    while (1) {
      parseFormalType();
      parseExpression();
    
      t = lex.peek();
      
      if (t.type == Token::SEMI) {
        lex.consume(Token::SEMI);
        t = lex.peek();
      } else
        break;
      
      if (t.type == Token::RPAREN)
        break;
    }
}

void Parser::parseFormalType() {
  Token t = lex.peek();
  
  if (t.type == Token::OUTPUT) {
    lex.consume(Token::OUTPUT);
    t = lex.peek();
  }
  
  if (t.type == Token::VARYING || t.type == Token::UNIFORM) {
    lex.consume();
    t = lex.peek();
  }
  
  switch (t.type) {
    case Token::FLOAT:
    case Token::STRING:
    case Token::COLOR:
    case Token::POINT:
    case Token::VECTOR:
    case Token::NORMAL:
    case Token::MATRIX:
    case Token::VOID:
      lex.consume();
      break;
    default:
      assert(0 && "Invalid type!");
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
      case Token::UNIFORM:
      case Token::VARYING:
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
  
  parseExpression();
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
  parseExpression();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseForLoop() {
  lex.consume(Token::FOR);
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::SEMI);
  parseExpression();
  lex.consume(Token::SEMI);
  parseExpression();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseIlluminateLoop() {
  lex.consume(Token::ILLUMINATE);
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseIlluminanceLoop() {
  lex.consume(Token::ILLUMINANCE);
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseSolarLoop() {
  lex.consume(Token::SOLAR);
  lex.consume(Token::LPAREN);
  
  if (lex.peek().type != Token::RPAREN)
    parseExpression();
    
  lex.consume(Token::RPAREN);
  parseBlockBody();
}

void Parser::parseIfStmt() {
  lex.consume(Token::IF);
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::RPAREN);
  parseBlockBody();
  
  Token t = lex.peek();
  if (t.type == Token::ELSE) {
    lex.consume(Token::ELSE);
    parseBlockBody();
  }
}

void Parser::parseBlockBody() {
  Token t = lex.peek();
  if (t.type == Token::LBRACE) {
    lex.consume(Token::LBRACE);
    parseStatements();
    lex.consume(Token::RBRACE);
  } else {
    switch (t.type) {
      case Token::FLOAT:
      case Token::STRING:
      case Token::COLOR:
      case Token::POINT:
      case Token::VECTOR:
      case Token::NORMAL:
      case Token::MATRIX:
      case Token::UNIFORM:
      case Token::VARYING:
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
        assert(0 && "Expected a statement!");
    }
  }
}

namespace Precedence {
  enum Level {
    Unknown        = 0,    // Not binary operator.
    Comma          = 1,    // ,
    Assignment     = 2,    // =, *=, /=, +=, -=
    Conditional    = 3,    // ? (: is handled specially)
    LogicalOr      = 4,    // ||
    LogicalAnd     = 5,    // &&
    Equality       = 6,    // ==, !=
    Relational     = 7,   //  >=, <=, >, <
    Cross          = 8,    // ^
    Additive       = 9,   // -, +
    Multiplicative = 10,   // *, /
    Dot            = 11
  };
}

static Precedence::Level getOperatorPrecedence(Token t) {
  switch (t.type) {
    default:                   return Precedence::Unknown;
    case Token::COMMA:         return Precedence::Comma;
    case Token::EQUAL:
    case Token::STAREQUAL:
    case Token::SLASHEQUAL:
    case Token::PLUSEQUAL:
    case Token::MINUSEQUAL:    return Precedence::Assignment;
    case Token::QUESTION:      return Precedence::Conditional;
    case Token::PIPEPIPE:      return Precedence::LogicalOr;
    case Token::AMPAMP:        return Precedence::LogicalAnd;
    case Token::EQUALEQUAL:
    case Token::EXCLAIMEQUAL:  return Precedence::Equality;
    case Token::GREATEREQUAL:
    case Token::LESSEQUAL:
    case Token::GREATER:
    case Token::LESS:          return Precedence::Relational;
    case Token::CARET:         return Precedence::Cross;
    case Token::PLUS:
    case Token::MINUS:         return Precedence::Additive;
    case Token::STAR:
    case Token::SLASH:         return Precedence::Multiplicative;
    case Token::DOT:           return Precedence::Dot;
  }
}

void Parser::parseExpression() {
  /* LHS = */parseUnaryExpr();
  parseRHS(/* LHS, */ Precedence::Comma);
}

void Parser::parseAssignmentExpr() {
  /* LHS = */parseUnaryExpr();
  parseRHS(/* LHS, */ Precedence::Assignment);
}

void Parser::parseRHS(/* ASTNode* LHS, */ unsigned MinPrec) {
  unsigned NextTokPrec = getOperatorPrecedence(lex.peek());
  
  while (1) {
    // If this token has a lower precedence than we are allowed to parse (e.g.
    // because we are called recursively, or because the token is not a binop),
    // then we are done!
    if (NextTokPrec < MinPrec)
      return /* LHS */;
    
    // Consume the operator, saving the operator token for error reporting.
    Token OpToken = lex.peek();
    lex.consume();
    
    // Special case handling for the ternary operator
    /* ASTNode* TernaryMiddle = 0 */
    if (NextTokPrec == Precedence::Conditional) {
      if (lex.peek().type != Token::COLON)
        /* TernaryMiddle = */ parseExpression();
      
      // Eat the colon
      lex.consume(Token::COLON);
    }
    
    // Parse another leaf here for the RHS of the operator.
    /* ASTNode* RHS = */ parseUnaryExpr();
    
    // Remember the precedence of this operator and get the precedence of the
    // operator immediately to the right of the RHS.
    unsigned ThisPrec = NextTokPrec;
    NextTokPrec = getOperatorPrecedence(lex.peek());
    
    // Assignment and conditional expressions are right-associative.
    bool isRightAssoc = ThisPrec == Precedence::Conditional ||
                        ThisPrec == Precedence::Assignment;
    
    // Get the precedence of the operator to the right of the RHS.  If it binds
    // more tightly with RHS than we do, evaluate it completely first.
    if (ThisPrec < NextTokPrec ||
        (ThisPrec == NextTokPrec && isRightAssoc)) {
      // If this is left-associative, only parse things on the RHS that bind
      // more tightly than the current operator.  If it is left-associative, it
      // is okay, to bind exactly as tightly.  For example, compile A=B=C=D as
      // A=(B=(C=D)), where each paren is a level of recursion here.
      /* RHS =*/ parseRHS(/* RHS, */ ThisPrec + !isRightAssoc);

      NextTokPrec = getOperatorPrecedence(lex.peek());
    }
    assert(NextTokPrec <= ThisPrec && "Recursion didn't work!");
    
    /*
    if (TernaryMiddle)
      LHS = new TernaryASTNode(LHS, TernaryMiddle, RHS);
    else
      LHS = new ASTNode(OpToken, LHS, RHS);
    */
  }
}

void Parser::parseCallExpr() {
  lex.consume(Token::IDENTIFIER);
  lex.consume(Token::LPAREN);
  if (lex.peek().type != Token::RPAREN)
    parseExpression();
  lex.consume(Token::RPAREN);
}

void Parser::parseUnaryExpr() {
  Token t = lex.peek();
  if (t.type == Token::EXCLAIM || t.type == Token::MINUS) {
    lex.consume();
    parseUnaryExpr();
  } else
    parseCastExpr();
}

void Parser::parseCastExpr() {
  Token t = lex.peek();
  switch(t.type) {
    case Token::FLOAT:
    case Token::STRING:
    case Token::COLOR:
    case Token::POINT:
    case Token::VECTOR:
    case Token::NORMAL:
    case Token::MATRIX:
      parseTypecast();
    default:
      break;
  }
  
  parsePrimary();
}


void Parser::parsePrimary() {
  Token t = lex.peek();
  Token t2 = lex.peek(2);
  
  switch (t.type) {
    case Token::NUMERIC:
      lex.consume(Token::NUMERIC);
      break;
    case Token::STRINGCONSTANT:
      lex.consume(Token::STRINGCONSTANT);
      break;
    case Token::TEXTURE:
    case Token::ENVIRONMENT:
    case Token::SHADOW:
      parseTexture();
      break;
    case Token::LPAREN:
      lex.consume();
      parseExpression();
      lex.consume(Token::RPAREN);
      break;
    case Token::LBRACE:
      lex.consume();
      parseExpression();
      lex.consume(Token::RBRACE);
      break;
    case Token::IDENTIFIER:
      t2 = lex.peek(2);
      if (t2.type == Token::LPAREN)
        parseCallExpr();
      else if (t2.type == Token::LBRACKET)
        parseArrayExpr();
      else
        lex.consume(Token::IDENTIFIER);
      break;
    default:
      assert(0 && "Parse error, expected primary!");
  }
}

void Parser::parseArrayExpr() {
  lex.consume(Token::IDENTIFIER);
  lex.consume(Token::LBRACKET);
  if (lex.peek().type != Token::RBRACKET)
    parseExpression();
  lex.consume(Token::RBRACKET);
}

void Parser::parseTexture() {
  parseTextureType();
  lex.consume(Token::LPAREN);
  parseExpression();
  lex.consume(Token::RPAREN);
}

void Parser::parseTextureType() {
  Token t = lex.peek();
  
  if (t.type == Token::TEXTURE)
    lex.consume(Token::TEXTURE);
  else if (t.type == Token::ENVIRONMENT)
    lex.consume(Token::ENVIRONMENT);
  else if (t.type == Token::SHADOW)
    lex.consume(Token::SHADOW);
  else
    assert(0 && "Invalid texture type!");
}

void Parser::parseTypecast() {
  Token t = lex.peek();
  
  switch (t.type) {
    case Token::FLOAT:
    case Token::STRING:
      lex.consume();
      break;
    case Token::COLOR:
    case Token::POINT:
    case Token::VECTOR:
    case Token::NORMAL:
    case Token::MATRIX:
      lex.consume();
      if (lex.peek().type == Token::STRINGCONSTANT)
        lex.consume(Token::STRINGCONSTANT);
      break;
    default:
      assert(0 && "Invalid typecast!");
  }
}
