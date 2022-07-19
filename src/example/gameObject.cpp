#include "gameObject.h"

GameObject& GameObject::Get(){
    static GameObject test;
    return test;
}

GameObject::GameObject() {

}

void GameObject::set_current_scene(core::Scene* scene){
    scene->init();
    m_current_scene = scene;
}

core::Scene* GameObject::getCurrentScene(){
    return this->m_current_scene;
}
