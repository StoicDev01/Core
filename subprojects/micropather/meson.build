project(
    'micropather', 
    'cpp',
    version : '1.0.0',
    default_options : ['cpp_std=c++11']
)

micropather_inc = include_directories('.')
lib = library('micropather', 'micropather.cpp', include_directories: micropather_inc)
micropather_dep = declare_dependency(include_directories: micropather_inc, link_with: lib)
meson.override_dependency('micropather', micropather_dep)