subdir('system')
subdir('gl')
subdir('graphics')


dependencies = [
    fmt_dep, 
    threads_dep, 
    gl_dep,
    glm_dep,
    glfw_dep,
    glew_dep,
    imgui_dep
]

lib_inc = include_directories('.','gl','graphics','system')
dep_inc = include_directories('.')

sources = glwrapper_sources + graphics_sources + system_sources

core_lib = library(
    'core-framework', 
    dependencies :dependencies,
    include_directories: lib_inc,
    sources : sources
)

core_dep = declare_dependency(
    link_with: core_lib, 
    include_directories: dep_inc,
    dependencies: dependencies
)