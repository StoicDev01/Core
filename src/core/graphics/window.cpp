#include "window.h"
#include "data.h"

namespace core::graphics{

    Window::Window(int width, int height, const char* name){
        glfwSetErrorCallback(glfw_error_callback);
        glfwInit(); // init glfw
        gleqInit(); // init gleq

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_glfw_window = glfwCreateWindow(width, height, name, NULL, NULL);
        gleqTrackWindow(m_glfw_window);

        glfwSetInputMode(m_glfw_window, GLFW_STICKY_KEYS, GL_TRUE);
        m_open = true;
    }

    Window::~Window(){
        shutdown_backends();
        destroy_context();
    }

    void Window::create_opengl_context(){
        glfwMakeContextCurrent(m_glfw_window);
        glfwSwapInterval(1); // Enable vsync
        glEnable(GL_DEPTH_TEST);
    }

    void Window::init_glew(){
        glewExperimental = true;
        if (glewInit() != 0){
            fmt::print("[ WINDOW GLEW INIT ] ERROR INITIALIZING GLEW.");
            endl();
        }

        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(opengl_message_callback, 0);
    }

    void Window::create_imgui_context(){
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        auto imgui_io = ImGui::GetIO();
        imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        imgui_io.IniFilename = nullptr;
        ImGui::StyleColorsDark();
        m_has_imgui_context = true;
    }

    void Window::init_backends(){
        ImGui_ImplGlfw_InitForOpenGL(m_glfw_window, true);
        ImGui_ImplOpenGL3_Init(m_glsl_version);
        m_initialized_backends = true;
    }
    
    void Window::create_context(){
        create_opengl_context();
        init_glew();

        create_imgui_context();
        init_backends();
    }


    void Window::shutdown_backends(){
        if (!m_initialized_backends)
            return;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        m_initialized_backends = false;
    }

    void Window::destroy_imgui_context(){
        ImGui::DestroyContext();
    }

    void Window::destroy_context(){
        if (m_has_imgui_context)
            destroy_imgui_context();
        
        glfwDestroyWindow(m_glfw_window);
        glfwTerminate();
    }

    // Called before draw
    void Window::new_frame(){
        if (m_initialized_backends){
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
        }

        ImGui::NewFrame();
    }

    // called after draw
    void Window::render(){
        auto io = ImGui::GetIO();
        int display_w, display_h;

        ImGui::Render();
        glfwGetFramebufferSize(m_glfw_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(m_glfw_window);
    }

    void Window::clear(Color color ){
        glClearColor(color.r, color.g ,color.b, color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }

    bool Window::is_open(){
        return !glfwWindowShouldClose(m_glfw_window);
    }

    void Window::close(){
        glfwSetWindowShouldClose(m_glfw_window, GLFW_TRUE);
    }

    void Window::resize(int width, int height){
        glfwSetWindowSize(m_glfw_window, width, height);
    }

    GLFWwindow* Window::get_glfw_window(){
        return m_glfw_window;
    }

    Vector2u Window::get_size(){
        int width, height;
        glfwGetFramebufferSize(m_glfw_window, &width, &height);
        Vector2u size((uint32_t)width, (uint32_t)height);
        return size;
    }

    // get mouse position relative to window top left corner
    core::Vector2f Window::get_mouse_pos(){
        double x, y;
        glfwGetCursorPos(m_glfw_window, &x, &y);
        return core::Vector2f((float)x, (float)y);
    };

    // get world position relative to position of the screen relative to top left corner
    core::Vector2f Window::screen_to_world_pos(core::Vector2f screen_pos, bool top_left){ 
        core::Vector2u window_size = get_size();
        core::Matrix4f& active_view = core::view_matrix;
        core::Matrix4f& active_projection = core::projection_matrix;

        int window_size_x; int window_size_y;
        int window_pos_x; int window_pos_y;

        glfwGetWindowPos(m_glfw_window, &window_pos_x, &window_pos_y);
        glfwGetWindowSize(m_glfw_window, &window_size_x, &window_size_y);

        core::Vector3f world_pos;

        if (top_left){
            world_pos = glm::unProject(
                core::Vector3f(screen_pos.x, -screen_pos.y + window_size_y, 0.0),
                active_view, active_projection, 
                core::Vector4f(0, 0, (float)window_size_x, (float)window_size_y)
            );
        }
        else{
            world_pos = glm::unProject(
                core::Vector3f(screen_pos.x, screen_pos.y, 0.0),
                active_view, active_projection,
                core::Vector4f(0,0, (float)window_size_x, (float)window_size_y)
            );
        }

        return core::Vector2f(world_pos.x, world_pos.y);
    };

    void Window::glfw_error_callback(int error, const char* description){
        fmt::print("[ GLFW ERROR {} ] {}", error, description);
        endl();
    }

    void GLAPIENTRY Window::opengl_message_callback( 
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const void* userParam 
    ){

        if (type == GL_DEBUG_TYPE_ERROR){
            fmt::print(
                stderr, "[ OPENGL ERROR ] type: {}, severity:  {}, message: {}",
                type, severity, message
            );
        }
        else{
            fmt::print(
                stderr, "[ OPENGL ] type: {}, severity:  {}, message: {}",
                type, severity, message
            );
        }

        endl();
    }

    bool Window::imgui_want_capture(core::Event event){
        ImGuiIO& io = ImGui::GetIO();
        if (event.type == GLEQ_BUTTON_PRESSED or event.type == GLEQ_BUTTON_RELEASED){
            if (io.WantCaptureMouse){
                return true;
            }
        }

        if (event.type == GLEQ_KEY_PRESSED or event.type == GLEQ_KEY_RELEASED){
            if (io.WantCaptureKeyboard){
                return true;
            }
        }
        return false;
    }
}