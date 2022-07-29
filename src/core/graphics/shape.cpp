#include "shape.h"

#include "shape.h"

namespace core{

    // SHAPE
    void ShapeData::bind(){
        if (m_vertex_array){
            m_vertex_array->bind();
        }
    }

    void ShapeData::unbind(){
        if (m_vertex_array){
            m_vertex_array->unbind();
        }
    }

    void ShapeData::create_objects(){
        m_vertex_array    = std::make_shared<core::gl::VertexArray>();
        m_vertex_buffer   = std::make_shared<core::gl::VertexBuffer>(GL_ARRAY_BUFFER);
        m_element_buffer  = std::make_shared<core::gl::VertexBuffer>(GL_ELEMENT_ARRAY_BUFFER);
    }

    // RECTANGLE
    RectangleData::RectangleData()
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

        m_vertex_count = sizeof(vertex_buffer_data) / sizeof(float);
        m_element_count = sizeof(element_buffer_data) / sizeof(uint32_t);

        m_vertex_array->bind();
        m_vertex_buffer->set_data(vertex_buffer_data, sizeof(vertex_buffer_data), GL_STATIC_DRAW);
        m_element_buffer->set_data(element_buffer_data, sizeof(element_buffer_data), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        m_vertex_array->unbind();
    }

    // SQUARE
    SquareData::SquareData()
    {
        create_objects();


        float vertex_buffer_data[] {
            // Vertices           // texture coords
            1.0f, 1.0f,  0.0f,  1.0f, 1.0f,    // top right
            1.0f, 0.0f,  0.0f,  1.0f, 0.0f,    // bot right
            0.0f, 0.0f,  0.0f,  0.0f, 0.0f,    // bot left
            0.0f, 1.0f,  0.0f,  0.0f, 1.0f     // top left
        };

        uint32_t element_buffer_data[] {
            0, 1, 3,
            1, 2, 3
        };

        m_vertex_count = sizeof(vertex_buffer_data) / sizeof(float);
        m_element_count = sizeof(element_buffer_data) / sizeof(uint32_t);

        m_vertex_array->bind();
        m_vertex_buffer->set_data(vertex_buffer_data, sizeof(vertex_buffer_data), GL_STATIC_DRAW);
        m_element_buffer->set_data(element_buffer_data, sizeof(element_buffer_data), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        m_vertex_array->unbind();
    }

    Shape::Shape(){
    }

    Shape::Shape(ShapeData shape_data){
        create_from(shape_data);
    }

    void Shape::create_from(ShapeData shape_data, bool has_shader){
        m_shape_data = shape_data;
        m_texture = nullptr;

        // SHADER
        m_vertex_shader.create(std::filesystem::path("./data/shaders/sprite.vert"), GL_VERTEX_SHADER);
        m_fragment_shader.create(std::filesystem::path("./data/shaders/sprite.frag"), GL_FRAGMENT_SHADER);

        m_vertex_shader.compile();
        m_fragment_shader.compile();
        
        m_shader_program.attach(m_vertex_shader);
        m_shader_program.attach(m_fragment_shader);

        m_shader_program.link();
    }

    void Shape::draw(){
        // use shader program
        m_shader_program.use();

        core::Matrix4f& view_matrix = core::view_matrix;
        core::Matrix4f& projection_matrix = core::projection_matrix;

        // pass uniforms
        glActiveTexture(GL_TEXTURE0);
        int texture_id = glGetUniformLocation(m_shader_program.get_id(), "texture_");
        glUniform1i(texture_id, 0);

        unsigned int modelLoc = glGetUniformLocation(m_shader_program.get_id(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(get_matrix()));

        unsigned int viewLoc = glGetUniformLocation(m_shader_program.get_id(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

        unsigned int projectionLoc = glGetUniformLocation(m_shader_program.get_id(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        if (m_texture)
            m_texture->bind();

        m_shape_data.bind();

        glDrawElements(GL_TRIANGLES, m_shape_data.get_element_count(), GL_UNSIGNED_INT, 0);
        m_shape_data.unbind();

        if (m_texture)
            m_texture->unbind();
    }
}
