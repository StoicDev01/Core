#pragma once

#include <memory.h>
#include "../gl/gl_wrapper.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../system/transform.h"
#include "../system/data.h"

namespace core {
    class ShapeData{
        public:

        void bind();
        void unbind();

        inline size_t get_element_count(){
            return m_element_count;
        }
        
        inline size_t get_vertex_count(){
            return m_vertex_count;
        }

        protected:
        std::shared_ptr<core::gl::VertexArray > m_vertex_array;
        std::shared_ptr<core::gl::VertexBuffer> m_vertex_buffer;
        std::shared_ptr<core::gl::VertexBuffer> m_element_buffer;

        size_t m_element_count;
        size_t m_vertex_count;

        void create_objects();
    };

    class RectangleData : public ShapeData{
        public:
        RectangleData();
    };

    class SquareData : public ShapeData{
        public:
        SquareData();
    };
}

namespace core {

    // Main shape class
    class Shape : public core::Transform{
        public:

        Shape();
        Shape(ShapeData shape_data);

        void create_from(ShapeData shape_data, bool has_shader = true);
        void draw();

        protected:
        ShapeData m_shape_data;
        graphics::Texture* m_texture;

        core::gl::ShaderProgram m_shader_program;
        core::gl::Shader m_vertex_shader;
        core::gl::Shader m_fragment_shader;
    };
}