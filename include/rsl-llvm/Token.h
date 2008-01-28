#include "llvm/Support/StringPool.h"
#include <cstddef>

#ifndef RSL_TOKEN_H
#define RSL_TOKEN_H

struct Token {
  enum TokenType {
    // Punctuation
    LPAREN,       // (
    RPAREN,       // )
    AMPAMP,       // &&
    STAR,         // *
    STAREQUAL,    // *=
    PLUS,         // +
    PLUSEQUAL,    // +=
    MINUS,        // -
    MINUSEQUAL,   // -=
    EXCLAIM,      // !
    EXLCAIMEQUAL, // !=
    EQUAL,        // =
    EQUALEQUAL,   // ==
    SLASH,        // /
    SLASHEQUAL,   // /=
    LESS,         // <
    LESSEQUAL,    // <=
    GREATER,      // >
    GREATEREQUAL, // >=
    PIPEPIPE,      // ||
    QUESTION,      // ?
    COLON,         // :
    SEMI,          // ;
    COMMA,         // ,
    LBRACE,        // {
    RBRACE,        // }
    LBRACKET,      // [
    RBRACKET,      // ]
    QUOTE,         // "
    
    // Keywords
    FOR,
    WHILE,
    IF,
    ELSE,
    BREAK,
    CONTINUE,
    RETURN,
    OUTPUT,
    EXTERN,
    VARYING,
    UNIFORM,
    SOLAR,
    ILLUMINATE,
    ILLUMINANCE,
    
    
    // Built-in typenames
    FLOAT,
    STRING,
    COLOR,
    POINT,
    VECTOR,
    NORMAL,
    MATRIX,
    VOID,
    
    // Shader types
    LIGHT,
    SURFACE,
    VOLUME,
    DISPLACEMENT,
    IMAGER,
    
    // Texture types
    TEXTURE,
    ENVIRONMENT, 
    SHADOW,
    
    NUMERIC,
    IDENTIFIER,
    ENDOFFILE,
    
    UNKNOWN
  };
  
  TokenType type;
  size_t index;
  unsigned length;
  
  // Only used for identifiers, unknowns, and numeric constants
  llvm::PooledStringPtr spelling;
  
  Token(TokenType t, size_t i, unsigned l) : type(t), index(i),
                                             spelling(), length(l) { }
  
  Token(TokenType t, size_t i, unsigned l, const llvm::PooledStringPtr& sp) :
        type(t), index(i), spelling(sp), length(l) { }
};

#endif