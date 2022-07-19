#pragma once

#include <filesystem>
#include "../core/system/scene.h"
#include "../core/system/singleton.h"

// Example of a singleton

// Definition of the object
class GameObject{
private:
    GameObject(); // Disallow instantiation outside of the class.

    core::Scene               *m_current_scene;
public:
    GameObject(const GameObject&) = delete;
    GameObject& operator=(const GameObject &) = delete;
    GameObject(GameObject &&) = delete;
    GameObject & operator=(GameObject &&) = delete;

    void set_current_scene        (core::Scene* scene);
    core::Scene*                  getCurrentScene();
    

    static GameObject& Get();
};

// see gameObject.cpp