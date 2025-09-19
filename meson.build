#*
#* Created by v1tr10l7 on 02.09.2025.
#* Copyright (c) 2025-2025, Szymon Zemke <v1tr10l7@proton.me>
#*
#* SPDX-License-Identifier: GPL-3
#*/
project('Cryptix-Utils', ['c', 'cpp'],
  version: 'v0.0.1', license: 'GPL-3.0',
  default_options: [
    'optimization=3',
    'warning_level=2',
    'werror=true',
    'c_std=c17',
    'cpp_std=c++23',
  ],
)

if not meson.get_compiler('cpp').has_argument('-std=gnu++23')
  error('C++23 support is needed. Please install clang 17 or higher.')
endif

c = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
ld = cxx.get_linker_id()
arch = host_machine.cpu_family()

cxx_args = [
  '-fno-rtti',
  '-unwindlib=none',
  '-fno-exceptions',
  '-DFMT_HEADER_ONLY',
  '-DFMT_STATIC_THOUSANDS_SEPARATOR=1',
  '-DFMT_USE_LONG_DOUBLE=0',
  '-DFMT_USE_DOUBLE=0',
  '-DFMT_USE_FLOAT=0',
  '-DFMT_USE_FLOAT128=0',
  '-DFMT_USE_EXCEPTIONS=0',
  '-DPRISM_DISABLE_FMT=1',
]
add_global_arguments(cxx_args, language: 'cpp')

incs = include_directories(
  'Source',
)

extraincs = get_option('extra_incs')
build_tests = get_option('build_tests')

if extraincs != ''
  cxx_args += '-I' + extraincs
  message('\n\n\n\nextra incs: ', extraincs)
else 
  message('no extra incs\n\n\n\n')
endif

deps = [
  dependency('prism'),
  dependency('neon'),
]

utilities = [
  'fb_test',
  'isatty_test',
  'ncurses_test',
  'pipe_test',
  'reboot',
  'shutdown',
  'su',
  'pthread_test',
  'test_tty',
  'udev',
  # 'vi',
]

foreach utility : utilities
  srcs = files(
    'Source' / utility + '.cpp'
  )

  executable(
    utility, srcs,
    include_directories: incs,
    link_args: ['-lsupc++', '-lgcc_s', '-lncurses', '-ltinfo'], 
    dependencies: deps, install: true
  )
endforeach

subdir('Tests')
