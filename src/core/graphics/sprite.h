#pragma once

#include "shape.h"
#include "texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../system/transform.h"
#include "../system/data.h"

namespace core::graphics{

    class Sprite : public core::shapes::Rectangle{
        public:

        Sprite();

        Texture* get_texture();
        void set_texture(Texture& p_texture);
        void draw();
    };
}