#include "shape.h"

#include "shape.h"

namespace core::graphics{

    // SHAPE
    void Shape::bind(){
        if (m_vertex_array){
            m_vertex_array->bind();
        }
    }

    void Shape::unbind(){
        if (m_vertex_array){
            m_vertex_array->unbind();
        }
    }

    void Shape::create_objects(){
        m_vertex_array    = std::make_shared<core::gl::VertexArray>();
        m_vertex_buffer   = std::make_shared<core::gl::VertexBuffer>(GL_ARRAY_BUFFER);
        m_element_buffer  = std::make_shared<core::gl::VertexBuffer>(GL_ELEMENT_ARRAY_BUFFER);
    }

    // RECTANGLE
    Rectangle::Rectangle()
    {
        create_objects();


        float vertex_buffer_data[] {
            // Vertices           // texture coords
                0.5f,  0.5f,  0.0f,  1.0f, 1.0f,    // top right
                0.5f, -0.5f,  0.0f,  1.0f, 0.0f,    // bot right
            -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,    // bot left
            -0.5f,  0.5f,  0.0f,  0.0f, 1.0f     // top left
        };

        uint32_t element_buffer_data[] {
            0, 1, 3,
            1, 2, 3
        };

        m_vertex_array->bind();
        m_vertex_buffer->set_data(vertex_buffer_data, sizeof(vertex_buffer_data), GL_STATIC_DRAW);
        m_element_buffer->set_data(element_buffer_data, sizeof(element_buffer_data), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        m_vertex_array->unbind();
    }
}
