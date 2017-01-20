//
// Created by kev on 19/01/17.
//

#include "Ground.hpp"
namespace glimac {
    void Ground::build(GLfloat width, GLfloat height) {
        std::vector<ShapeVertex> data;
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                ShapeVertex vertex;
                vertex.position.x = i;
                vertex.position.z = j;
                vertex.position.y = 0;

                vertex.normal = vertex.position;

                data.push_back(vertex);
            }
        }
        m_nVertexCount = width*height+width*height/2;

        for(int i=0;i<width;i++) {
            for (int j = 0; j < height; j++) {
                m_Vertices.push_back(data[i+j]);
                m_Vertices.push_back(data[i+j+width]);
                m_Vertices.push_back(data[i+j+width+1]);
                m_Vertices.push_back(data[i+j]);
                m_Vertices.push_back(data[i+j+width+1]);
                m_Vertices.push_back(data[i+j+1]);
            }
        }

    }
}
