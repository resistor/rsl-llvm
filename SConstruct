import os

env = Environment(CPPPATH = [ 'include' ])

def isCPPFile(f):
  return f.rpartition('.')[2] == 'cpp'

lexfiles = filter(isCPPFile, ["build/lib/LexRSL/" + i for i in os.listdir('lib/LexRSL')])
parsefiles = filter(isCPPFile, ["build/lib/ParseRSL/" + i for i in os.listdir('lib/ParseRSL')])
semafiles = filter(isCPPFile, ["build/lib/SemaRSL/" + i for i in os.listdir('lib/SemaRSL')])
codegenfiles = filter(isCPPFile, ["build/lib/CodegenRSL/" + i for i in os.listdir('lib/CodegenRSL')])

env.BuildDir('build/lib', 'lib', duplicate=0)

env.StaticLibrary('build/lib/LexRSL', lexfiles)
#env.StaticLibrary('build/lib/ParseRSL', parsefiles)
#env.StaticLibrary('build/lib/SemaRSL', semafiles)
#env.StaticLibrary('build/lib/CodegenRSL', codegenfiles)


