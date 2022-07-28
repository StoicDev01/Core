#pragma once

#include "GLFW/glfw3.h"
#include "gleq.h"

namespace core{

    typedef GLEQevent Event;

    inline void free_event(Event& event){
        gleqFreeEvent(&event);
    }
}