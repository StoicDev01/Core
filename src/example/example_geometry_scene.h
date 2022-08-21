#include "../core/system/scene.h"
#include "../core/system/transform.h"
#include "../core/system/events.h"

#include "../core/graphics/sprite.h"
#include "../core/graphics/view.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include "../core/system/data.h"

namespace scenes{
    class ExampleGeometry : public core::Scene{
        public:
        core::shapes::Rectangle up_rectangle;
        core::shapes::Rectangle down_rectangle;
        core::shapes::Rectangle right_rectangle;
        core::shapes::Rectangle left_rectangle;

        core::shapes::Circle circle;
        core::graphics::View2D view_2d;

        ExampleGeometry(core::graphics::Window& window):
            Scene (window, "Example Scene"),
            view_2d(-(1600/2),(1600/2),-(900)/2,900/2, 0.01f, 1000.0f)
        {

        }

        // Executed on start
        void init(){
            up_rectangle.m_color = core::graphics::Color::red();
            up_rectangle.m_position = core::Vector3f(0,25, 1);
            up_rectangle.m_scale = core::Vector3f(50,50,1);

            down_rectangle.m_color = core::graphics::Color::blue();
            down_rectangle.m_position = core::Vector3f(0,-25, 1);
            down_rectangle.m_scale = core::Vector3f(50,50,1);

            right_rectangle.m_color = core::graphics::Color::black();
            right_rectangle.m_position = core::Vector3f(50,0, 1);
            right_rectangle.m_scale = core::Vector3f(50,50,1);

            left_rectangle.m_color = core::graphics::Color::green();
            left_rectangle.m_position = core::Vector3f(-50,0, 1);
            left_rectangle.m_scale = core::Vector3f(50,50,1);

            circle.m_position = core::Vector3f(0,0,1);
            circle.m_color = core::graphics::Color::black();
            circle.m_thickness = 0.2;
            circle.set_radius(200.0f);

            view_2d.m_position = core::Vector3f(0,0,0);
            // Invert z scale so the view points towards positive Z axis
            view_2d.m_scale = core::Vector3f(1,1,-1);

            // Enable blending
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        // Executed on client handle event
        void handle_event(core::Event event){
        }

        // Executed on logic update
        void update(float delta){
            //view_2d.translate(core::Vector3f(0,0,1 * delta));
        }

        // Executed on client update draw
        void draw(core::graphics::Window& window){
            window.clear(core::graphics::Color(255,255,255,255));
            up_rectangle.draw();
            down_rectangle.draw();
            right_rectangle.draw();
            left_rectangle.draw();
            circle.draw();
            view_2d.set_active();
        }
    };
}