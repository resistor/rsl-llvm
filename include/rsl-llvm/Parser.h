#ifndef RSL_PARSER_H
#define RSL_PARSER_H

class Lexer;

class Parser {
private:
  Lexer& lex;
  
public:
  Parser(Lexer& l) : lex(l) { }
  
  void parseDefinitions();
private:
  void parseFunctionDefinition();
  void parseShaderDefinition();
  void parseFormals();
  void parseFormalType();
  
  void parseStatements();
  void parseStatement();
  
  void parseVariableDecl();
  void parseCallStmt();
  void parseAssignmentStmt();
  void parseReturnStmt();
  void parseBreakStmt();
  void parseContinueStmt();
  void parseIfStmt();
  
  void parseWhileLoop();
  void parseForLoop();
  void parseLoopBody();
  void parseIlluminateLoop();
  void parseIlluminanceLoop();
  void parseSolarLoop();
  
  void parseBlockBody();
  
  void parseExpression();
  void parseExpressionList();
  void parseDefExpressions();
  
  void parseCallExpr();
  void parseAssignmentExpr();
  void parseUnaryExpr();
  void parseArrayExpr();
  void parseCastExpr();
  void parseDotExpr();
  void parseMulExpr();
  void parsePowExpr();
  void parseAddExpr();
  void parseCmpExpr();
  void parseEqualityExpr();
  void parseAndExpr();
  void parseOrExpr();
  void parseConditionalExpr();
  
  void parsePrimary();
  void parseTexture();
  void parseTextureType();
  void parseTextureArguments();
  void parseTuple();
  void parseTypecast();
};

#endif
