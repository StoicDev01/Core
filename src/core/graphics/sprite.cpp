#include "sprite.h"

namespace core::graphics {

    Sprite::Sprite()
    {
        // SHAPE and Texture
        m_shape = core::RectangleData();
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

    void Sprite::set_texture(Texture& p_texture){
        m_texture = &p_texture;
        core::Vector2u texture_size = p_texture.get_size();
        m_scale = core::Vector3f(texture_size.x, texture_size.y, 1);
    }

    void Sprite::draw(){
        // use shader program
        m_shader_program.use();

        core::Matrix4f& view = core::view_matrix;
        core::Matrix4f& projection = core::projection_matrix;

        // pass uniforms
        glActiveTexture(GL_TEXTURE0);
        int texture_id = glGetUniformLocation(m_shader_program.get_id(), "texture_");
        glUniform1i(texture_id, 0);

        unsigned int modelLoc = glGetUniformLocation(m_shader_program.get_id(), "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(get_matrix()));

        unsigned int viewLoc = glGetUniformLocation(m_shader_program.get_id(), "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(m_shader_program.get_id(), "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // bind texture
        if (m_texture)
            m_texture->bind();
        
        // bind shape vao
        m_shape.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        m_shape.unbind();

        if (m_texture)
            m_texture->unbind();
    }
}