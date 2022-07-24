#pragma once

#include "sstream"
#include "stdlib.h"
#include "GL/glew.h"
#include "string"
#include "filesystem"
#include "fstream"
#include "fmt/format.h"
#include "vector"

#include "../system/core_utils.h"

namespace core::gl{

    class GLObjectWithID{
        public:

        uint32_t get_id();

        protected:
        uint32_t m_id;
    };

    class GLObjectWithBind{
        public:

        virtual void bind();
        virtual void unbind();
    };

    class VertexArray : public GLObjectWithID, public GLObjectWithBind{
        public:

        VertexArray();
        ~VertexArray();

        void bind();
        void unbind();
    };

    class VertexBuffer : public GLObjectWithID, public GLObjectWithBind{
        public:

        VertexBuffer(GLenum buffer_type = GL_ARRAY_BUFFER);
        ~VertexBuffer();

        void set_data(float* vertex_buffer_data, size_t size, GLenum usage = GL_STATIC_DRAW);
        void set_data(uint32_t* vertex_buffer_data, size_t size, GLenum usage = GL_STATIC_DRAW);

        void bind();
        void unbind();

        protected:
        GLenum m_buffer_type;
    };

    class Shader : public GLObjectWithID{
        public:

        Shader();
        Shader(std::string shader_code, GLenum shader_type);
        Shader(std::filesystem::path shader_code_path, GLenum shader_type);
        ~Shader();

        void create(std::string shader_code, GLenum shader_type);
        void create(std::filesystem::path shader_code_path, GLenum shader_type);

        bool compile();


        private:
        void verify_initialized();

        bool m_initialized = false;
        int m_shader_type = GL_FRAGMENT_SHADER;
        std::string m_shader_code;
    };

    class ShaderProgram : public GLObjectWithID{
        public:
        ShaderProgram();
        ~ShaderProgram();

        void attach(Shader& shader);
        void detach_id(uint32_t shader_id);
        void detach(Shader& shader);
        void detach_all();

        bool link();
        void use();

        private:
        std::vector<uint32_t> m_attached_shaders;
    };
}