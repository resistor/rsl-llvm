#ifndef RSL_PARSER_H
#define RSL_PARSER_H

class Lexer;

class Parser {
private:
  Lexer& lex;
  
public:
  Parser(Lexer& l) : lex(l) { }
  
private:
  void parseDefinitions();
  void parseFunctionDefinition();
  void parseShaderDefinition();
  void parseFormals();
  
  void parseStatements();
  void parseStatement();
  
  void parseReturnStmt();
  void parseBreakStmt();
  void parseContinueStmt();
  
  void parseWhileLoop();
  void parseForLoop();
  
  void parseExpression();
  void parseRelation();
};

#endif