#include "rsl-llvm/Source.h"
#include <vector>
#include <algorithm>

void Source::computeLineNumbers() {
  std::vector<size_t> LineOffsets;
  
  const unsigned char* Buf = (const unsigned char *)Buffer->getBufferStart();
  const unsigned char* End = (const unsigned char *)Buffer->getBufferEnd();
  unsigned Offs = 0;
  
  while (1) {
    const unsigned char* NextBuf = (const unsigned char*)Buf;
    while (*NextBuf != '\n' && *NextBuf != '\r' && *NextBuf != '\0')
      ++NextBuf;
    
    Offs += NextBuf-Buf;
    
    if (Buf[0] == '\n' || Buf[0] == '\r') {
      if ((Buf[1] == '\n' || Buf[1] == '\r') && Buf[0] != Buf[1])
        ++Offs, ++Buf;
      
      ++Offs, ++Buf;
      LineOffsets.push_back(Offs);
    } else {
      if (Buf == End) break;
      
      ++Offs, Buf;
    }
  }
  
  NumLines = LineOffsets.size();
  SourceLineCache = new size_t[LineOffsets.size()];
  std::copy(LineOffsets.begin(), LineOffsets.end(), SourceLineCache);
}