#pragma once
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtc/quaternion.hpp"
#include "vector"
#include "cstdint"

namespace core{
    template <size_t size_x, size_t size_y, typename T>
    class Matrix : public glm::mat<size_x, size_y, T, glm::defaultp>{

    };

    typedef glm::vec<3, uint32_t, glm::defaultp>    Vector3u;
    typedef glm::vec<3, int, glm::defaultp>         Vector3i;
    typedef glm::vec<3, float, glm::defaultp>       Vector3f;

    typedef glm::vec<2, uint32_t, glm::defaultp>    Vector2u;
    typedef glm::vec<2, int, glm::defaultp>         Vector2i;
    typedef glm::vec<2, float, glm::defaultp>       Vector2f;

    typedef glm::vec<4, uint32_t, glm::defaultp>    Vector4u;
    typedef glm::vec<4, int, glm::defaultp>         Vector4i;
    typedef glm::vec<4, float, glm::defaultp>       Vector4f;

    typedef glm::mat4 Matrix4f;


    template <typename T>
    class VectorMatrix : public std::vector<std::vector<T>>{
        public:

        VectorMatrix(){}

        VectorMatrix(size_t size_x, size_t size_y){
            create(size_x, size_y);
        }

        void create(size_t size_x, size_t size_y, T default_value){
            this->swap(std::vector<std::vector<T>>(size_x, std::vector<T>(size_y, default_value)));
        }

    };


    class Transform{
        public:
        Transform();

        float distance_to(Transform& p_transform);

        void rotate(float angle, Vector3f axis);
        void translate(Vector3f direction);

        core::Matrix4f get_matrix() const;

        Vector3f m_position;
        Vector3f m_scale;
        glm::quat m_rotation;

        Vector3f m_world_up;
        Vector3f m_up;
        Vector3f m_front;
        Vector3f m_right;

        
    };
}
