#include "scene.h"

namespace core{
    Scene::Scene(core::graphics::Window& p_window, std::string p_name) :
        m_window(p_window)
    {
        m_name = p_name;
    }

    Scene::~Scene(){
        
    }
    
    void Scene::init(){
    }

    void Scene::handle_event(core::Event event){
        // do something
    }

    void Scene::update(float delta){
        // do something
    }

    void Scene::draw(core::graphics::Window& window){
        // do something
    }

}