
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
glfw_dep            =   subproject('glfw3').get_variable('glfw_dep')
gleq_dep            =   subproject('gleq').get_variable('gleq_dep')
glew_dep            =   subproject('glew').get_variable('glew_dep')
threads_dep         =   dependency('threads',   static : true)
fmt_dep             =   subproject('fmt').get_variable('fmt_dep')

if (host_system == 'windows')
    gl_dep = cc.find_library('opengl32')
else
    gl_dep = dependency('opengl')
endif

glm_dep             =   subproject('glm').get_variable('glm_dep')
glew_dep            =   subproject('glew').get_variable('glew_dep')
stb_dep             =   subproject('stb').get_variable('stb_dep')
imgui_dep           =   subproject('imgui').get_variable('imgui_dep')


#micropather_dep     =   dependency('micropather')
#fastnoiselite_dep   =   dependency('fastnoiselite')
#x11_dep             =   dependency('x11')
#json_dep            =   dependency('nlohmann_json')

subdir('src')