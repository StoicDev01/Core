#include "../core/system/scene.h"
#include "../core/system/transform.h"
#include "../core/system/events.h"

#include "../core/graphics/sprite.h"
#include "../core/graphics/view.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "../core/system/data.h"

namespace scenes{
    class ExampleGeometry : public core::Scene{
        public:
        core::shapes::Rectangle rectangle;
        core::shapes::Circle circle;
        core::graphics::View2D view_2d;

        ExampleGeometry(core::graphics::Window& window):
            Scene (window, "Example Scene"),
            view_2d(-(1600/2),(1600/2),-(900)/2,900/2)
        {

        }

        // Executed on start
        void init(){
            rectangle.m_color = core::graphics::Color::red();
            rectangle.m_position = core::Vector3f(1,1,1);
            rectangle.m_scale = core::Vector3f(50,50,1);

            circle.m_color = core::graphics::Color::blue();
            circle.m_position = core::Vector3f(5,0,1);
            circle.set_radius(5.0f);

            view_2d.m_position = core::Vector3f(0,0,-2);

            // Enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        // Executed on client handle event
        void handle_event(core::Event event){
        }

        // Executed on logic update
        void update(float delta){
        }

        // Executed on client update draw
        void draw(core::graphics::Window& window){
            window.clear(core::graphics::Color(255,255,255,255));
            rectangle.draw();
            //circle.draw();
            view_2d.set_active();
        }

    };
}