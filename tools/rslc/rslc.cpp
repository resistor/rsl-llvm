#include "rsl-llvm/Lexer.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/MemoryBuffer.h"

#include <iostream>
#include <string>

using namespace llvm;

cl::opt<std::string> OutputFilename("o",
                                    cl::desc("Specify output filename"),
                                    cl::value_desc("filename"));

cl::opt<std::string> InputFilename(llvm::cl::Positional,
                                   cl::desc("<input file>"),
                                   cl::init("-"),
                                   cl::Required);

int main(int argc, char** argv) {
  cl::ParseCommandLineOptions(argc, argv);
  
  std::string errstr;
  MemoryBuffer* srcBuff = MemoryBuffer::getFileOrSTDIN(InputFilename, &errstr);
  
  if (!srcBuff) {
    std::cerr << errstr << "\n";
    return -1;
  }

  Lexer lex(srcBuff);
  
  return 0;
}