project('fastnoiselite', version: '1.0.3')
noise_inc = include_directories('.')

fastnoiselite_dep = declare_dependency(include_directories: noise_inc)
meson.override_dependency('fastnoiselite', fastnoiselite_dep)