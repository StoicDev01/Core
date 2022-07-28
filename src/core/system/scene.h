#pragma once
#include "core_utils.h"
#include "../graphics/window.h"
#include "events.h"

namespace core{
    class Scene{
        public:

        Scene(core::graphics::Window& p_window, std::string p_name = "undefined");
        ~Scene();
        
        virtual void init();
        virtual void handle_event(core::Event event);
        virtual void update(float delta);
        virtual void draw(core::graphics::Window& window);
        
        protected:
        core::graphics::Window& m_window;
        std::string m_name;
    };

}

