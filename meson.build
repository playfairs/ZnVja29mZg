project('t8forge', 'c')

cc = meson.get_compiler('c')
sdl_dep = dependency('sdl3')

add_project_arguments([
  '-D_POSIX_C_SOURCE=200809L',
  '-Wundef',
  '-Wno-unused-parameter',
  '-Wno-missing-braces',
  '-Wno-cpp',
  cc.get_supported_arguments([
    '-Wno-builtin-declaration-mismatch',      # gcc
    '-Wno-incompatible-library-redeclaration' # clang
  ])
], language: 'c')


find_sources = run_command(
  'python3', '-c',
  'import glob; print("\\n".join(glob.glob("src/**/*.c", recursive=True)))',
  check: true
)
sources = find_sources.stdout().strip().split('\n')
include = include_directories('include')

executable('t8forge', sources,
  c_args: [],
  link_args: [],
  dependencies: [sdl_dep],
  include_directories: include,
  install: true
)
