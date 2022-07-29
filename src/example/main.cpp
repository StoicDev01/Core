#include "thread"
#include "time.h"

#include "core/core.h"

#include "example_scene.h"
#include "test_scene.h"
#include "gameObject.h"

// Get GameObject Singleton
GameObject& gameObject = GameObject::Get();
#define DEBUG 0


// logic thread
void logic(core::graphics::Window& window){
    std::clock_t end = 0;

    while (window.is_open()){
        std::clock_t start = std::clock();
        double delta = double(start - end) / CLOCKS_PER_SEC;
        end = std::clock();

        core::Scene* current_scene = gameObject.getCurrentScene();

        if (current_scene){
            current_scene->update(delta);
        }        
    }
}

// Main thread
void client(core::graphics::Window& window){
    // Main loop
    std::clock_t end = 0;

    while (window.is_open()){
        std::clock_t start = std::clock();
        double delta = double(start - end) / CLOCKS_PER_SEC;
        end = std::clock();

        core::Scene* current_scene = gameObject.getCurrentScene();
        core::Event event;

        glfwPollEvents();

        // handle event
        while (window.poll_event(event)){
            current_scene->handle_event(event); 
            
            core::free_event(event);
        }

        // Render
        window.new_frame();
        current_scene->draw(window);
        window.render();
    }
}


int main() {
    // Create window
    core::graphics::Window window(1600, 900, "Example window");
    // Create opengl and imgui context, and init glew
    window.create_context(); 

    // Create a new Scene
    scenes::ExampleScene test_scene(window);
    gameObject.set_current_scene(&test_scene);

    // execute logic and client
    std::thread logic_thread(logic, std::ref(window));
    client(window);

    logic_thread.join();
    return 0;
}