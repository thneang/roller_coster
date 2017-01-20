//
// Created by kev on 19/01/17.
//

#ifndef ROLLER_COSTER_GROUND_HPP
#define ROLLER_COSTER_GROUND_HPP

#include <vector>

#include <glimac/common.hpp>
namespace glimac {
    class Ground {
    public:
        Ground(GLfloat width, GLfloat height) :
                m_nVertexCount(0) {
            build(width,height);
        }
    private:
        void build(GLfloat width, GLfloat height);
        std::vector<ShapeVertex> m_Vertices;
        GLsizei m_nVertexCount; // Nombre de sommets
    };
}

#endif //ROLLER_COSTER_GROUND_HPP
