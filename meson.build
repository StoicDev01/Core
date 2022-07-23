
project(
    'core-lib',
    'c',
    'cpp',
    default_options : ['cpp_std=c++20'],
    version : '0.1.0',
    license : 'MIT' 
)

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')
host_system = host_machine.system()

# Dependencies
glfw_dep            =   dependency('glfw3')
glew_dep            =   dependency('glew')
threads_dep         =   dependency('threads')
fmt_dep             =   dependency('fmt')

if (host_system == 'windows')
    gl_dep = cc.find_library('opengl32')
else
    gl_dep = dependency('opengl')
endif

glm_dep             =   dependency('glm')
glew_dep            =   dependency('glew')
stb_dep             =   dependency('stb-meson')
imgui_dep           =   dependency('imgui')


#micropather_dep     =   dependency('micropather')
#fastnoiselite_dep   =   dependency('fastnoiselite')
#x11_dep             =   dependency('x11')
#json_dep            =   dependency('nlohmann_json')

subdir('src')