//
// Created by kev on 23/01/17.
//

#include <RollPath.hpp>

using namespace glm;
using namespace glimac;
using namespace std;


Geometry::Vertex RollPath::getPointCurve(float time){
    float t = time - glm::floatBitsToInt(time);
    vec3 p0 = list_point[glm::floatBitsToInt(time) % 5000].m_Position;
    vec3 p1 = list_point[(glm::floatBitsToInt(time)+1) % 5000].m_Position;
    vec3 p2 = list_point[(glm::floatBitsToInt(time)+2) % 5000].m_Position;
    vec3 p3 = list_point[(glm::floatBitsToInt(time)+3) % 5000].m_Position;
    vec3 pos = p0*(1-t)*(1-t)*(1-t)+3.0f*p1*t*(1-t)*(1-t)+3.0f*p2*t*t*(1-t)+p3*t*t*t;
    Geometry::Vertex v;
    v.m_Position = pos;
    v.m_TexCoords = list_point[0].m_TexCoords;
    v.m_Normal = pos;
    return v;
}

void RollPath::init(const FilePath&){
    for(int i=0;i<2500;i+=5){
        vec3 pos = vec3(std::log(i),std::log(i),std::log(i));
        Geometry::Vertex v;
        v.m_Position= pos;
        v.m_Normal = pos;
        v.m_TexCoords = vec2(i/5000,0.5);
        list_point.push_back(v);
    }
    for(int i=2500;i>0;i-=5){
        vec3 pos = vec3(std::log(i),std::log(i),std::log(i));
        Geometry::Vertex v;
        v.m_Position= pos;
        v.m_Normal = pos;
        v.m_TexCoords = vec2(i/5000,0.5);
        list_point.push_back(v);
    }
}

void RollPath::init_texture(){

}

void RollPath::init_vbo(){

}

void RollPath::init_vao(){

}

void RollPath::init_index(){

}

void RollPath::draw(){

}

void RollPath::duplicate_vertex(){

}

void RollPath::free(){
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}