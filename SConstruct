import os, subprocess, SCons.Util

def filterAndStripPrefix(list, prefix):
  return [i[len(prefix):] for i in filter(lambda s: s.startswith(prefix), list)]

def filterNotPrefix(list, prefix):
  return filter(lambda s: not s.startswith(prefix), list)


cppflagscall = subprocess.Popen('llvm-config --cppflags', shell=True, stdout=subprocess.PIPE)
llvmcppflags = cppflagscall.communicate()[0].rstrip('\n').split(' ')

ldflagscall = subprocess.Popen('llvm-config --ldflags', shell=True, stdout=subprocess.PIPE)
llvmldflags = ldflagscall.communicate()[0].rstrip('\n').split(' ')

env = Environment(CPPPATH = [ 'include' ] + filterAndStripPrefix(llvmcppflags, '-I'),
                  CXXFLAGS = filterNotPrefix(llvmcppflags, '-I'),
                  LIBPATHS = filterAndStripPrefix(llvmldflags, '-L'),
                  LIBS = filterAndStripPrefix(llvmldflags, '-l'))

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

libfiles = filter(isCPPFile, ["lib/" + i for i in os.listdir('lib/')])
env.StaticLibrary('lib/RslLLVM', libfiles)


corelinkcall = subprocess.Popen('llvm-config --libs core', shell=True, stdout=subprocess.PIPE)
corelinkflags = corelinkcall.communicate()[0].rstrip('\n').split(' ')

rslcfiles = filter(isCPPFile, ["tools/rslc/" + i for i in os.listdir('tools/rslc')])

env.Program('rslc', rslcfiles,
            LIBS=env['LIBS'] + ['RslLLVM'] + filterAndStripPrefix(corelinkflags, '-l'),
            LIBPATH=env['LIBPATHS'] + ['lib'])
