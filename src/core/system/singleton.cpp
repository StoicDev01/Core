#include "singleton.h"

namespace core{

    Singleton* Singleton::m_instance = 0;

    void Singleton::init_instance(){
        new Singleton;
    }

    Singleton& Singleton::get(){            
        if (!m_instance)
            init_instance();
        
        return *m_instance;
    }


    Singleton::Singleton() {
        if (m_instance) 
            throw std::logic_error("Instance already exists");
        
        m_instance = this;
    };
    
}