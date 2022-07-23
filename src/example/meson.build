cpp_args = []

if (host_system == 'widnows')
    cpp_args = ['-static-libgcc', '-static-libstdc++']
endif

executable(
    'Example',
    dependencies: core_dep,
    include_directories : '.',
    sources: files('./main.cpp', 'gameObject.cpp'),
    cpp_args : cpp_args
)
