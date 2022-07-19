#pragma once

#include <memory.h>
#include <stdexcept>

namespace core{

    class Singleton {
        public:

        static void init_instance();
        static Singleton& get();


        protected:
        static Singleton* m_instance;

        Singleton();
        ~Singleton();
    };
}