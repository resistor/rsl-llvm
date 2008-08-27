#include "rsl-llvm/Lexer.h"
#include <vector>
#include <algorithm>

static llvm::StringPool SpellingPool;

void Lexer::computeLineNumbers() {
  // Find the file offsets of all of the *physical* source lines.  This does
  // not look at trigraphs, escaped newlines, or anything else tricky.
  std::vector<unsigned> LineOffsets;
  
  // Line #1 starts at char 0.
  LineOffsets.push_back(0);
  
  const char *Buf = Buffer->getBufferStart();
  const char *End = Buffer->getBufferEnd();
  unsigned Offs = 0;
  while (1) {
    // Skip over the contents of the line.
    const char *NextBuf = Buf;
    while (*NextBuf != '\n' && *NextBuf != '\r' && *NextBuf != '\0')
      ++NextBuf;
    Offs += NextBuf-Buf;
    Buf = NextBuf;
    
    if (Buf[0] == '\n' || Buf[0] == '\r') {
      // If this is \n\r or \r\n, skip both characters.
      if ((Buf[1] == '\n' || Buf[1] == '\r') && Buf[0] != Buf[1])
        ++Offs, ++Buf;
      ++Offs, ++Buf;
      LineOffsets.push_back(Offs);
    } else {
      // Otherwise, this is a null.  If end of file, exit.
      if (Buf == End) break;
      // Otherwise, skip the null.
      ++Offs, ++Buf;
    }
  }
  
  // Copy the offsets into the FileInfo structure.
  NumLines = LineOffsets.size();
  SourceLineCache = new size_t[LineOffsets.size()];
  std::copy(LineOffsets.begin(), LineOffsets.end(), SourceLineCache);
}

Token Lexer::peek(unsigned LookAhead) {
  assert(LookAhead > 0 && "Can't have non-positive lookahead!");
  
  // If we've already lex'ed that far ahead, just return the token
  // from the queue
  if (LookAhead <= token_queue.size()) {
    return token_queue[LookAhead-1];
  
  // Otherwise, we need to lex more tokens!
  } else {
    while (token_queue.size() < LookAhead)
      token_queue.push_back(LexNextToken());
    
    return token_queue.back();
  }
}

Token Lexer::consume() {
  if (token_queue.size()) {
    Token tok = token_queue.front();
    token_queue.pop_front();
    return tok;
  } else {
    Token tok = LexNextToken();
    return tok;
  }
}

Token Lexer::consume(Token::TokenType t) {
  if (token_queue.size()) {
    Token tok = token_queue.front();
    
    if (tok.type != t)
      tok.dump();
    
    assert(tok.type == t && "Unexpected token encountered!");
    token_queue.pop_front();
    return tok;
  } else {
    Token tok = LexNextToken();
    assert(tok.type == t && "Unexpected token encountered!");
    return tok;
  }
}

Token Lexer::LexNextToken() {
  while (*(Buffer->getBufferStart() + NextCharacter) == ' ' ||
         *(Buffer->getBufferStart() + NextCharacter) == '\n' ||
         *(Buffer->getBufferStart() + NextCharacter) == '\t' ||
         *(Buffer->getBufferStart() + NextCharacter) == '\r')
    NextCharacter++;
  
  unsigned start = 0;
  
  switch (*(Buffer->getBufferStart() + NextCharacter)) {
  case '{':
    return Token(Token::LBRACE, NextCharacter++, 1);
  case '}':
    return Token(Token::RBRACE, NextCharacter++, 1);
  case '[':
    return Token(Token::LBRACKET, NextCharacter++, 1);
  case ']':
    return Token(Token::RBRACKET, NextCharacter++, 1);
  case '(':
    return Token(Token::LPAREN, NextCharacter++, 1);
  case ')':
    return Token(Token::RPAREN, NextCharacter++, 1);
  case '?':
    return Token(Token::QUESTION, NextCharacter++, 1);
  case ':':
    return Token(Token::COLON, NextCharacter++, 1);
  case ';':
    return Token(Token::SEMI, NextCharacter++, 1);
  case ',':
    return Token(Token::COMMA, NextCharacter++, 1);
  case '\0':
    return Token(Token::ENDOFFILE, NextCharacter, 1);
  case '.':
    if (*(Buffer->getBufferStart() + NextCharacter + 1) >= '0' &&
       (*(Buffer->getBufferStart() + NextCharacter + 1) <= '9')) {
      return LexNumeric();
    } else
      return Token(Token::DOT, NextCharacter++, 1);
  case '^':
    return Token(Token::CARET, NextCharacter++, 1);
  case '|':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '|')
      return Token(Token::PIPEPIPE, (NextCharacter++)-1, 2);
    else {
      const char* Location = Buffer->getBufferStart() + NextCharacter;
      return Token(Token::UNKNOWN, (NextCharacter++)-1, 2,
                   SpellingPool.intern(Location, Location+2));
    }
  case '&':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '&')
      return Token(Token::AMPAMP, (NextCharacter++)-1, 2);
    else {
      const char* Location = Buffer->getBufferStart() + NextCharacter;
      return Token(Token::UNKNOWN, (NextCharacter++)-1, 2,
                   SpellingPool.intern(Location, Location+2));
    }
  case '*':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::STAREQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::STAR, (NextCharacter)-1, 1);
  case '+':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::PLUSEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::PLUS, (NextCharacter)-1, 1);
  case '-':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::MINUSEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::MINUS, (NextCharacter)-1, 1);
  case '/':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::SLASHEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::SLASH, (NextCharacter)-1, 1);
  case '!':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::EXCLAIMEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::EXCLAIM, (NextCharacter)-1, 1);
  case '<':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::LESSEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::LESS, (NextCharacter)-1, 1);
  case '>':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::GREATEREQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::GREATER, (NextCharacter)-1, 1);
  case '=':
    NextCharacter++;
    if (*(Buffer->getBufferStart() + NextCharacter) == '=')
      return Token(Token::EQUALEQUAL, (NextCharacter++)-1, 2);
    else
      return Token(Token::EQUAL, (NextCharacter)-1, 1);
  case '"':
    start = NextCharacter++;
    while (*(Buffer->getBufferStart() + NextCharacter) != '"')
      NextCharacter++;
    
    return Token(Token::STRINGCONSTANT, start, ++NextCharacter - start);    
  default:
    unsigned char letter = *(Buffer->getBufferStart() + NextCharacter);
    if ((letter >= 'a' && letter <= 'z') ||
        (letter >= 'A' && letter <= 'Z') ||
        letter == '_')
      return LexKeywordOrIdentifier();
    else if (letter >= '0' && letter <= '9')
      return LexNumeric();
    else {
      const char* Location = Buffer->getBufferStart() + NextCharacter;
      return Token(Token::UNKNOWN, NextCharacter++, 1,
                   SpellingPool.intern(Location, Location+1));
    }
  }
}

Token Lexer::LexKeywordOrIdentifier() {
  const char* Start = Buffer->getBufferStart() + NextCharacter;
  const char* End = Start+1;
  
  while ((*End >= 'a' && *End <= 'z') ||
         (*End >= 'A' && *End <= 'Z') ||
         (*End >= '0' && *End <= '9') ||
         *End == '_')
    End++;
  
  Token::TokenType type = Token::IDENTIFIER;
  
  HashTableTy::iterator I = KeywordHashTable.find(Start, End);
  if (I != KeywordHashTable.end())
    type = I->getValue();
  
  unsigned size = End - Start;
  size_t index = NextCharacter;
  NextCharacter += size;
  
  return Token(type, index, size, SpellingPool.intern(Start, End));
}

Token Lexer::LexNumeric() {
  const char* Start = Buffer->getBufferStart() + NextCharacter;
  const char* End = Start+1;
  
  Token::TokenType type = Token::NUMERIC;
  
  bool sawPeriod = false;
  while ((*End >= '0' && *End <= '9') ||
         *End == '.') {
    if (*End == '.')
      if (sawPeriod) {
        type = Token::UNKNOWN;
      } else {
        sawPeriod = true;
      }
    
    End++;
  }
  
  // 1e+12
  if ((*End == 'E' || *End == 'e') && (*(End+1) == '+' || *(End+1) == '-')) {
    End += 2;
    
    sawPeriod = false;
    while ((*End >= '0' && *End <= '9') ||
           *End == '.') {
      if (*End == '.')
        if (sawPeriod) {
          type = Token::UNKNOWN;
        } else {
          sawPeriod = true;
        }
      
      End++;
    }
  }
  
  unsigned size = End - Start;
  size_t index = NextCharacter;
  NextCharacter += size;
  
  return Token(Token::NUMERIC, index, size, SpellingPool.intern(Start, End));
}

unsigned Lexer::getLineNumber(size_t pos) {
  return std::lower_bound(SourceLineCache,
                          SourceLineCache+NumLines, pos) - SourceLineCache;
}