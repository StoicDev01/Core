#include "view.h"

namespace core::graphics{

    void View::set_active(){
        core::projection_matrix = m_projection_matrix;
        core::view_matrix = View::get_matrix();
    }

    Matrix4f View::get_matrix(){
        return glm::inverse(Transform::get_matrix());
    }

    View2D::View2D(){

    }

    View2D::View2D(float left, float right, float bottom, float top, float near, float far ){
        create(left, right, bottom, top, near, far );
    }

    void View2D::create(float left, float right, float bottom, float top, float near, float far ){
        m_projection_matrix = glm::ortho(left, right, bottom, top, near, far);
    }

    View3D::View3D(){

    }

    View3D::View3D(float fov_radians, float aspect_ratio, float near, float far){
        create(fov_radians, aspect_ratio, near, far);
    }

    void View3D::create(float fov_radians, float aspect_ratio, float near, float far){
        m_projection_matrix = glm::perspective(fov_radians, aspect_ratio, near, far);
    }
}