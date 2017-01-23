//
// Created by kev on 23/01/17.
//

#include <RollPath.hpp>

using namespace glm;
using namespace glimac;
using namespace std;


glm::vec3 RollPath::getPointCurve(float time){
    float t = time - glm::floatBitsToInt(time);
    vec3 p0 = list_point[glm::floatBitsToInt(time) % 5000];
    vec3 p1 = list_point[(glm::floatBitsToInt(time)+1) % 5000];
    vec3 p2 = list_point[(glm::floatBitsToInt(time)+2) % 5000];
    vec3 p3 = list_point[(glm::floatBitsToInt(time)+3) % 5000];
    return p0*(1-t)*(1-t)*(1-t)+3*p1*t*(1-t)*(1-t)+3*p2*t*t*(1-t)+p3*t*t*t;
}

void RollPath::init(const FilePath&){
    for(int i=0;i<2500;i+=5){
        list_point.push_back(vec3(std::log(i),std::log(i),std::log(i)));
    }
    for(int i=2500;i>0;i-=5){
        list_point.push_back(vec3(std::log(i),std::log(i),std::log(i)));
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