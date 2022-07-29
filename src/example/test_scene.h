#include "core/core.h"

namespace scenes{
    class TestScene : public core::Scene{
        public:
        core::Shape shape;
        core::graphics::View2D view2d;


        TestScene(core::graphics::Window& window) :
            Scene(window, "TestScene"),
            view2d(-(4.0f / 2.0f), (4.0f / 2.0f), (3.0f / 2.0f), -(3.0f / 2.0f), -1000.0f, 1000.0f)
        {

            shape.create_from(core::SquareData());
        }

        void init(){
            view2d.set_active();

            shape.m_position = core::Vector3f(10,0,0);
            view2d.m_position = core::Vector3f(0,0,-10);
        }

        void handle_event(core::Event){
            
        }

        void update(float delta){
            view2d.set_active();
        }

        void draw(core::graphics::Window& window){
            window.clear();
            shape.draw();
        }

    };
}