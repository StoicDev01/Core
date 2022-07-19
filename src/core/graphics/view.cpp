#include "view.h"

namespace core::graphics{

    void View::set_active(){
        core::projection_matrix = m_projection_matrix;
        core::view_matrix = get_matrix();
    }

    View2D::View2D(float left, float right, float bottom, float top, float near, float far ){
        m_projection_matrix = glm::ortho(left, right, bottom, top, near, far);
    }

    View3D::View3D(float fov_radians, float aspect_ratio, float near, float far){
        m_projection_matrix = glm::perspective(fov_radians, aspect_ratio, near, far);
    }

}