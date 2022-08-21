#include "transform.h"

#include "fmt/format.h"
#include "core_utils.h"

namespace core{
    Transform::Transform() 
    {
        m_position = core::Vector3f(0,0,0);
        m_scale = core::Vector3f(1,1,1);
        m_rotation = glm::quat(core::Vector3f(0,0,0));
    }

    Matrix4f Transform::get_matrix() const{
        Matrix4f translate_matrix = glm::translate(m_position);
        Matrix4f rotation_matrix = glm::toMat4(m_rotation);
        Matrix4f scale_matrix = glm::scale(m_scale);

        return  translate_matrix * rotation_matrix * scale_matrix;
    }

    void Transform::rotate(float angle, Vector3f axis){
        m_rotation = glm::quat(glm::rotate(m_rotation, angle, axis));
    }

    void Transform::translate(Vector3f direction){
        m_position += direction;
    }

    float Transform::distance_to(Transform& p_transform){
        return glm::distance(m_position, p_transform.m_position);
    }

    
}
