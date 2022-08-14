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
        core::shapes::Rectangle rectangle;
        core::shapes::Circle circle;
        core::graphics::View2D view_2d;

        ExampleGeometry(core::graphics::Window& window):
            Scene (window, "Example Scene"),
            view_2d(-(1600/2),(1600/2),-(900)/2,900/2, 0.01f, 1000.0f)
        {

        }

        // Executed on start
        void init(){
            rectangle.m_color = core::graphics::Color::red();
            rectangle.m_position = core::Vector3f(0,0,-110);
            rectangle.m_scale = core::Vector3f(50,50,1);

            circle.m_color = core::graphics::Color::blue();
            circle.set_radius(100.0f);
            circle.m_position = core::Vector3f(0, 0, -100);

            view_2d.m_position = core::Vector3f(0,0,0);
            
            core::Vector3f rectangle_position;
            core::Vector3f scale_position;
            glm::quat rectangle_rotation;
            core::Vector3f skew;
            core::Vector4f perspective;

            glm::decompose(rectangle.get_matrix(), scale_position, rectangle_rotation, rectangle_position, skew, perspective);
            fmt::print("RECTANGLE POSITION: ({}, {}, {})", rectangle_position.x, rectangle_position.y, rectangle_position.z);
            endl();

            core::Vector3f view_position;
            core::Vector3f view_scale;
            glm::quat view_rotation;
            core::Vector3f view_skew;
            core::Vector4f view_perspective;

            glm::decompose(view_2d.get_matrix(), view_scale, view_rotation, view_position, view_skew, view_perspective);
            core::Vector3f view_rotation_euler = glm::eulerAngles(view_rotation);

            fmt::print("VIEW POSITION: ({}, {}, {})", view_position.x, view_position.y, view_position.z);
            endl();
            fmt::print("VIEW SCALE: ({}, {}, {})", view_scale.x, view_scale.y, view_scale.z);
            endl();
            fmt::print("VIEW ROTATION: ({}, {}, {})", view_rotation_euler.x, view_rotation_euler.y, view_rotation_euler.z);
            endl();

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
            circle.draw();
            rectangle.draw();
            view_2d.set_active();
        }

    };
}