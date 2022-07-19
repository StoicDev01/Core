#pragma once
#include <vector>
#include <string>
#include <iostream>

#include "../graphics/graphics.h"

namespace core{
    // Main Object Class
    class Object{
        public:
        std::string m_name;

        // Components m_component

        virtual void update(float delta);
        virtual void handle_event(float delta);
        virtual void draw(graphics::Window& window);
    };
}
