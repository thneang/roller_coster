//
// Created by kev on 19/01/17.
//

#include "Ground.hpp"
namespace glimac {
    void Ground::build(GLfloat width, GLfloat height) {

        std::vector<ShapeVertex> data;
        for(int i=0;i<6;i++){
            ShapeVertex vertex;
            vertex.texCoords.x = i * rcpLat;
            vertex.texCoords.y = 1.f - j * rcpLong;

            vertex.normal.x = sin(i * dPhi) * cosTheta;
            vertex.normal.y = sinTheta;
            vertex.normal.z = cos(i * dPhi) * cosTheta;

            vertex.position = r * vertex.normal;
            data.push_back(vertex);
        }
    }
}
