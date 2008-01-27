#include <llvm/Support/MemoryBuffer.h>
#include <string>

#ifndef RSL_LEX_LEXER_H
#define RSL_LEX_LEXER_H

class Lexer {
private:
  const llvm::MemoryBuffer* Buffer;
  
  size_t* SourceLineCache;
  unsigned NumLines;
public:
  
  Lexer(const llvm::MemoryBuffer* buf) : Buffer(buf) {
    SourceLineCache = 0;
    NumLines = 0;
  }
  
  void computeLineNumbers();
  
  unsigned getLineNumber(size_t pos) {
    return std::lower_bound(SourceLineCache, SourceLineCache+NumLines, pos) - SourceLineCache;
  }
};

#endif