#include "rsl-llvm/Token.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/Support/MemoryBuffer.h"
#include <deque>
#include <string>

#ifndef RSL_LEXER_H
#define RSL_LEXER_H

class Lexer {
private:
  const llvm::MemoryBuffer* Buffer;
  
  size_t* SourceLineCache;
  unsigned NumLines;
  
  std::deque<Token> token_queue;
  size_t NextCharacter;
  
  typedef llvm::StringMap<Token::TokenType> HashTableTy;
  HashTableTy KeywordHashTable;
public:
  
  Lexer(const llvm::MemoryBuffer* buf) : Buffer(buf), NextCharacter(0),
                                         SourceLineCache(0), NumLines(0) {
    const char* kw_for = "for";
    KeywordHashTable.GetOrCreateValue(kw_for, kw_for+3).setValue(Token::FOR);
    
    const char* kw_while = "while";
    KeywordHashTable.GetOrCreateValue(kw_while, kw_while+5).setValue(Token::WHILE);
    
    const char* kw_if = "if";
    KeywordHashTable.GetOrCreateValue(kw_if, kw_if+2).setValue(Token::IF);
    
    const char* kw_else = "else";
    KeywordHashTable.GetOrCreateValue(kw_else, kw_else+4).setValue(Token::ELSE);
    
    const char* kw_break = "break";
    KeywordHashTable.GetOrCreateValue(kw_break, kw_break+5).setValue(Token::BREAK);
    
    const char* kw_continue = "continue";
    KeywordHashTable.GetOrCreateValue(kw_continue, kw_continue+8).setValue(Token::CONTINUE);
    
    const char* kw_return = "return";
    KeywordHashTable.GetOrCreateValue(kw_return, kw_return+6).setValue(Token::RETURN);
    
    const char* kw_output = "output";
    KeywordHashTable.GetOrCreateValue(kw_output, kw_output+6).setValue(Token::OUTPUT);
    
    const char* kw_extern = "extern";
    KeywordHashTable.GetOrCreateValue(kw_extern, kw_extern+6).setValue(Token::EXTERN);
    
    const char* kw_varying = "varying";
    KeywordHashTable.GetOrCreateValue(kw_varying, kw_varying+7).setValue(Token::VARYING);
    
    const char* kw_uniform = "uniform";
    KeywordHashTable.GetOrCreateValue(kw_uniform, kw_uniform+7).setValue(Token::UNIFORM);
    
    const char* kw_solar = "solar";
    KeywordHashTable.GetOrCreateValue(kw_solar, kw_solar+5).setValue(Token::SOLAR);
    
    const char* kw_illuminate = "illuminate";
    KeywordHashTable.GetOrCreateValue(kw_illuminate, kw_illuminate+10).setValue(Token::ILLUMINATE);
    
    const char* kw_illuminance = "illuminance";
    KeywordHashTable.GetOrCreateValue(kw_illuminance, kw_illuminance+11).setValue(Token::ILLUMINANCE);
    
    const char* kw_float = "float";
    KeywordHashTable.GetOrCreateValue(kw_float, kw_float+5).setValue(Token::FLOAT);
    
    const char* kw_string = "string";
    KeywordHashTable.GetOrCreateValue(kw_string, kw_string+6).setValue(Token::STRING);
    
    const char* kw_color = "color";
    KeywordHashTable.GetOrCreateValue(kw_color, kw_color+5).setValue(Token::COLOR);
    
    const char* kw_point = "point";
    KeywordHashTable.GetOrCreateValue(kw_point, kw_point+5).setValue(Token::POINT);
    
    const char* kw_vector = "vector";
    KeywordHashTable.GetOrCreateValue(kw_vector, kw_vector+6).setValue(Token::VECTOR);
    
    const char* kw_normal = "normal";
    KeywordHashTable.GetOrCreateValue(kw_normal, kw_normal+6).setValue(Token::NORMAL);
    
    const char* kw_matrix = "matrix";
    KeywordHashTable.GetOrCreateValue(kw_matrix, kw_matrix+6).setValue(Token::MATRIX);
    
    const char* kw_void = "void";
    KeywordHashTable.GetOrCreateValue(kw_void, kw_void+4).setValue(Token::VOID);
    
    const char* kw_light = "light";
    KeywordHashTable.GetOrCreateValue(kw_light, kw_light+5).setValue(Token::LIGHT);
    
    const char* kw_surface = "surface";
    KeywordHashTable.GetOrCreateValue(kw_surface, kw_surface+7).setValue(Token::SURFACE);
    
    const char* kw_volume = "volume";
    KeywordHashTable.GetOrCreateValue(kw_volume, kw_volume+6).setValue(Token::VOLUME);
    
    const char* kw_displacement = "displacement";
    KeywordHashTable.GetOrCreateValue(kw_displacement, kw_displacement+12).setValue(Token::DISPLACEMENT);
    
    const char* kw_imager = "imager";
    KeywordHashTable.GetOrCreateValue(kw_imager, kw_imager+6).setValue(Token::IMAGER);
    
    const char* kw_texture = "texture";
    KeywordHashTable.GetOrCreateValue(kw_texture, kw_texture+7).setValue(Token::TEXTURE);
    
    const char* kw_environment = "environment";
    KeywordHashTable.GetOrCreateValue(kw_environment, kw_environment+11).setValue(Token::ENVIRONMENT);
    
    const char* kw_shadow = "shadow";
    KeywordHashTable.GetOrCreateValue(kw_shadow, kw_shadow+6).setValue(Token::SHADOW);
  }
  
  void computeLineNumbers();
  
  unsigned getLineNumber(size_t pos) {
    return std::lower_bound(SourceLineCache,
                            SourceLineCache+NumLines, pos) - SourceLineCache;
  }
  
  Token peek(unsigned LookAhead = 1);

private:
  Token LexNextToken();
  Token LexKeywordOrIdentifier();
  Token LexNumeric();
};

#endif