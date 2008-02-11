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
};

#endif