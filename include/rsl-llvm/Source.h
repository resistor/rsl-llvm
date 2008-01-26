#include <llvm/Support/MemoryBuffer.h>

#ifndef RSL_LEX_SOURCE_H
#define RSL_LEX_SOURCE_H

class Source {
private:
  llvm::MemoryBuffer* Buffer;
  
  unsigned* SourceLineCache;
public:
  
  Source() {
    Buffer = 0;
    SourceLineCache = 0;
  }
};

#endif