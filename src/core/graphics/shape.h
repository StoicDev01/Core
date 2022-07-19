#pragma once

#include <memory.h>
#include "../gl/gl_wrapper.h"

namespace core::graphics {
    class Shape{
        public:

        void bind();
        void unbind();

        protected:
        std::shared_ptr<core::gl::VertexArray > m_vertex_array;
        std::shared_ptr<core::gl::VertexBuffer> m_vertex_buffer;
        std::shared_ptr<core::gl::VertexBuffer> m_element_buffer;

        void create_objects();
    };

    class Rectangle : public Shape{
        public:
        Rectangle();
    };
}