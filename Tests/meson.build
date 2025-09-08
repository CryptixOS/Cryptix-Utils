#*
#* Created by v1tr10l7 on 02.09.2025.
#* Copyright (c) 2025-2025, Szymon Zemke <v1tr10l7@proton.me>
#*
#* SPDX-License-Identifier: GPL-3
#*/

tests = [
  'Example',
]
cpp_args = [
  '-Wno-unused-parameter',
  '-Wno-self-assign-overloaded',
  '-lgcc_s',
  '-fmodules-ts',
]
link_args = [
  '-lstdc++exp',
]

extraincs = get_option('extra_incs')
if extraincs != ''
  cpp_args += '-I' + extraincs
endif

foreach name : tests
  test = executable(
    name, [files(name / 'main.cpp')],
    cpp_args: cpp_args, link_args: link_args,
    include_directories: incs, dependencies: deps
  )
  test(name, test)
endforeach
