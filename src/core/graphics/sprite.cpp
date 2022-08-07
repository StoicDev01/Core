#include "sprite.h"

namespace core::graphics {

    Sprite::Sprite()
    {
        // SHAPE and Texture
        set_shapedata(core::shapedata::Rectangle());
        m_texture = nullptr;
    }

    void Sprite::set_texture(Texture& p_texture){
        core::Vector2u texture_size = p_texture.get_size();

        m_texture = &p_texture;
        m_scale = core::Vector3f(
            texture_size.x, texture_size.y, 1.0
        );
        
    }

    Texture* Sprite::get_texture(){
        return m_texture;
    }

    void Sprite::draw(){
        Shape::draw();
    }
}