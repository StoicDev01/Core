#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "fmt/format.h"

#include "image.h"
#include "../system/core_utils.h"
#include "../system/transform.h"
#include "../system/data.h"
#include "cstdint"

namespace core::graphics{
    class Window{
        public:
        Window(int width, int height, const char* name);
        ~Window();

        void create_opengl_context();
        void init_glew();
        void create_imgui_context();
        void init_backends();
        void create_context();

        void shutdown_backends();
        void destroy_imgui_context();
        void destroy_context();

        // Called before draw
        void new_frame();
        // called after draw
        void render();

        void clear(Color color = Color::white());
        void close();

        bool is_open();
        void resize(int width, int height);

        GLFWwindow* get_glfw_window();

        int get_key(int glfw_key);
        int get_mouse_button(int glfw_mouse_button);

        bool is_key_pressed(int glfw_key);
        bool is_key_released(int glfw_key);

        bool is_mouse_button_pressed(int glfw_mouse_button);
        bool is_mouse_button_released(int glfw_mouse_button);

        Vector2u get_size();
        core::Vector2f get_mouse_pos();

        private:
        
        static void glfw_error_callback(int error, const char* description);
        static void GLAPIENTRY opengl_message_callback( 
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam 
        );
        
        bool m_open = false;
        bool m_has_imgui_context = false;
        bool m_initialized_backends = false;

        GLFWwindow* m_glfw_window;

        const char* m_glsl_version = "#version 330";
    };
}
