//
// Created by kev on 19/01/17.
//

#ifndef ROLLER_COSTER_GROUND_HPP
#define ROLLER_COSTER_GROUND_HPP

#include <vector>

#include <glimac/common.hpp>

class Ground {
    Ground(GLfloat width, GLfloat heigth, GLsizei discLat, GLsizei discLong):
    m_nVertexCount(0) {
    }
private:
    std::vector<ShapeVertex> m_Vertices;
    GLsizei m_nVertexCount; // Nombre de sommets
};


#endif //ROLLER_COSTER_GROUND_HPP
