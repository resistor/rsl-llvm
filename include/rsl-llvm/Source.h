#include <llvm/Support/MemoryBuffer.h>
#include <string>

#ifndef RSL_LEX_SOURCE_H
#define RSL_LEX_SOURCE_H

class Source {
private:
  llvm::MemoryBuffer* Buffer;
  
  size_t* SourceLineCache;
  unsigned NumLines;
public:
  
  Source(const std::string& filename) {
    // FIXME: Should notice and report failures.
    Buffer = llvm::MemoryBuffer::getFileOrSTDIN(filename);
    
    SourceLineCache = 0;
    NumLines = 0;
  }
  
  void computeLineNumbers();
};

#endif