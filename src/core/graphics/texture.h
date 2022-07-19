#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "window.h"
#include "image.h"

#include "../gl/gl_wrapper.h"

namespace core::graphics {
    class Texture : public core::gl::GLObjectWithID, core::gl::GLObjectWithBind{
        public:

        Texture();
        ~Texture();

        void bind();
        void unbind();

        void load(Image& image);

        protected:
        bool m_loaded = false;

    };

}