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

conf = Configure(env)
# Checks for libraries, header files, etc. go here!
env = conf.Finish()

env['CXXFLAGS'] += ["-O0","-g"]

def isCPPFile(f):
  return f.endswith('.cpp')

lexfiles = filter(isCPPFile, ["lib/LexRSL/" + i for i in os.listdir('lib/LexRSL')])
parsefiles = filter(isCPPFile, ["lib/ParseRSL/" + i for i in os.listdir('lib/ParseRSL')])
semafiles = filter(isCPPFile, ["lib/SemaRSL/" + i for i in os.listdir('lib/SemaRSL')])
codegenfiles = filter(isCPPFile, ["lib/CodegenRSL/" + i for i in os.listdir('lib/CodegenRSL')])

env.StaticLibrary('lib/LexRSL', lexfiles)
#env.StaticLibrary('lib/ParseRSL', parsefiles)
#env.StaticLibrary('lib/SemaRSL', semafiles)
#env.StaticLibrary('lib/CodegenRSL', codegenfiles)


corelinkcall = subprocess.Popen('llvm-config --libs core', shell=True, stdout=subprocess.PIPE)
corelinkflags = corelinkcall.communicate()[0].rstrip('\n').split(' ')
#corelinkflags = [i[2:] for i in corelinkflags]
#print corelinkflags

rslcfiles = filter(isCPPFile, ["tools/rslc/" + i for i in os.listdir('tools/rslc')])

env["LINKFLAGS"].extend(corelinkflags)
env.Program('rslc', rslcfiles, LIBS=['LexRSL'], LIBPATH='lib', )