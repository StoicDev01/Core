#include "window.h"

namespace core::graphics{

    Window::Window(){
        glfwSetErrorCallback(glfw_error_callback);
        glfwInit();

        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_glfw_window = glfwCreateWindow(1600, 900, "Rpg", NULL, NULL);
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

    GLFWwindow* Window::get_glfw_window(){
        return m_glfw_window;
    }

    int Window::get_key(int glfw_key){
        return glfwGetKey(m_glfw_window, glfw_key);
    }

    int Window::get_mouse_button(int glfw_mouse_button){
        return glfwGetMouseButton(m_glfw_window, glfw_mouse_button);
    }

    bool Window::is_key_pressed(int glfw_key){
        return (get_key(glfw_key) == GLFW_PRESS);
    }

    bool Window::is_key_released(int glfw_key){
        return (get_key(glfw_key) == GLFW_RELEASE);
    }

    bool Window::is_mouse_button_pressed(int glfw_mouse_button){
        return (get_mouse_button(glfw_mouse_button) == GLFW_PRESS);
    }

    bool Window::is_mouse_button_released(int glfw_mouse_button){
        return (get_mouse_button(glfw_mouse_button) == GLFW_RELEASE);
    }

    Vector2u Window::get_size(){
        int width, height;
        glfwGetWindowSize(m_glfw_window, &width, &height);
        Vector2u size((uint)width, (uint)height);
        return size;
    }

    core::Vector2f Window::get_mouse_pos(){
        double x, y;
        glfwGetCursorPos(m_glfw_window, &x, &y);
        return core::Vector2f((float)x, (float)y);
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
        endl();
    }
}