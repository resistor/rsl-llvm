import os, subprocess, SCons.Util

cppflagscall = subprocess.Popen('llvm-config --cppflags', shell=True, stdout=subprocess.PIPE)
llvmcppflags = cppflagscall.communicate()[0].rstrip('\n').split(' ')

ldflagscall = subprocess.Popen('llvm-config --ldflags', shell=True, stdout=subprocess.PIPE)
llvmldflags = ldflagscall.communicate()[0].rstrip('\n').split(' ')

env = Environment(CPPPATH = [ 'include' ],
                  CXXFLAGS = llvmcppflags,
                  LINKFLAGS = llvmldflags)

if os.environ.has_key('CC'):
  env['CC'] = os.environ['CC']
if os.environ.has_key('CFLAGS'):
  env['CCFLAGS'] += SCons.Util.CLVar(os.environ['CFLAGS'])
if os.environ.has_key('CXX'):
	env['CXX'] = os.environ['CXX']
if os.environ.has_key('CXXFLAGS'):
	env['CXXFLAGS'] += SCons.Util.CLVar(os.environ['CXXFLAGS'])
if os.environ.has_key('LDFLAGS'):
	env['LINKFLAGS'] += SCons.Util.CLVar(os.environ['LDFLAGS'])

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


