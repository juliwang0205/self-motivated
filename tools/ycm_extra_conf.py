import os
import ycm_core

home_dir = '/home/ubuntu/self-motiveted/'

flags = [
    '-Wall',
    '-Wextra',
    '-Werror',
    '-Wno-long-long',
    '-Wno-variadic-macros',
    '-fexceptions',
    '-DNDEBUG',
    '-std=c++11',
    '-x',
    'c++',
    '-I',
    '/usr/include',
    '-isystem',
    '/usr/lib/gcc/x86_64-linux-gnu/5/include',
    '-isystem',
    '/usr/include/x86_64-linux-gnu',
    '-isystem',
    '/usr/include/c++/5',
    '-isystem',
    '/usr/include/c++/5/bits',
    '-isystem',
    os.path.join(home_dir, 'ics2021/nemu/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/nemu/src/isa/riscv32/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/nemu/src/isa/riscv64/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/nemu/tools/kvm-diff/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/nemu/tools/qemu-diff/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/abstract-machine/am/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/abstract-machine/am/src/platform/nemu/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/abstract-machine/klib/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/am-kernels/benchmarks/coremark/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/am-kernels/benchmarks/microbench/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/am-kernels/tests/am-tests/include'),
    '-isystem',
    os.path.join(home_dir, 'ics2021/am-kernels/tests/cpu-tests/include')
  ]
 
SOURCE_EXTENSIONS = [ '.cpp', '.cxx', '.cc', '.c', ]
 
def FlagsForFile( filename, **kwargs ):
  return {
    'flags': flags,
    'do_cache': True
  }
