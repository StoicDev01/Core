#pragma once

#include "shape.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../system/transform.h"
#include "../system/data.h"

namespace core::graphics{

    class Sprite : public Transform{
        public:

        Sprite();

        void set_texture(Texture& p_texture);
        void draw();
        
        protected:
        core::ShapeData m_shape;
        Texture* m_texture;

        core::gl::ShaderProgram m_shader_program;
        core::gl::Shader m_vertex_shader;
        core::gl::Shader m_fragment_shader;
    };
}