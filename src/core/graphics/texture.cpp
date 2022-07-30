#include "texture.h"        

namespace core::graphics{
    Texture::Texture(){
        glGenTextures(1, &m_id);
    }

    Texture::~Texture(){
        glDeleteTextures(1, &m_id);
    }

    void Texture::bind(){
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void Texture::unbind(){
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::load(Image& image){
        bind();

        if (image.m_color_channels == 4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.m_size.x, image.m_size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.get_data());
        }
        else if (image.m_color_channels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.m_size.x, image.m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image.get_data());
        }
        else if (image.m_color_channels == 2){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, image.m_size.x, image.m_size.y, 0, GL_RG, GL_UNSIGNED_BYTE, image.get_data());
        }
        else if (image.m_color_channels == 1){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R, image.m_size.x, image.m_size.y, 0, GL_R, GL_UNSIGNED_BYTE, image.get_data());
        }

        glGenerateMipmap(GL_TEXTURE_2D);
        m_loaded = true;
        m_size = image.m_size;
        unbind();
    }

    core::Vector2u Texture::get_size(){
        return m_size;
    }
}