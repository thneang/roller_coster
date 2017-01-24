//
// Created by kev on 23/01/17.
//

#include <RollPath.hpp>

using namespace glm;
using namespace glimac;
using namespace std;
using namespace global;


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

void RollPath::init(const FilePath& applicationPath){
    for(int i=0;i<6;i++){
        vec3 pos = vec3(std::log(i)*300,std::log(i)*300,std::log(i)*300);
        Geometry::Vertex v;
        v.m_Position= pos;
        v.m_Normal = pos;
        v.m_TexCoords = vec2(i/12,0.5);
        list_point.push_back(v);
    }
    for(int i=6, j=6;i>0;i--,j++){
        vec3 pos = vec3(std::log(j)*300,std::log(i)*300,std::log(j)*300);
        Geometry::Vertex v;
        v.m_Position= pos;
        v.m_Normal = pos;
        v.m_TexCoords = vec2(j/12,0.5);
        list_point.push_back(v);
    }

    program = loadProgram(applicationPath.dirPath() + "shaders/RollPath.vs.glsl",
                          applicationPath.dirPath() + "shaders/RollPath.fs.glsl");

    program.use();

    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

//    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();
    init_index();

}

void RollPath::init_texture(){
    // créer un buffer pour notre texture
    glGenTextures(1, &texture[0]);


    // on bind la texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // On envoie l'image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, images[0]->getWidth(), images[0]->getHeight(), 0, GL_RGBA, GL_FLOAT, images[0]->getPixels());


    // filtre pour deux cas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void RollPath::init_vbo(){
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    // version pour utiliser drawElement
    glBufferData(GL_ARRAY_BUFFER, this->list_point.size()*sizeof(Geometry::Vertex), &this->list_point[0], GL_STATIC_DRAW);

//    glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RollPath::init_vao(){
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(VERTEX_ATTRIB_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTRIB_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTRIB_TEXTURE_COORD);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTRIB_POSITION, VERTEX_ATTRIB_POSITION_SIZE, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid *) offsetof(Geometry::Vertex, m_Position));
    glVertexAttribPointer(VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_NORMAL_SIZE, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid *) offsetof(Geometry::Vertex, m_Normal));
    glVertexAttribPointer(VERTEX_ATTRIB_TEXTURE_COORD, VERTEX_ATTRIB_TEXTURE_COORD_SIZE, GL_FLOAT, GL_FALSE, sizeof(Geometry::Vertex), (const GLvoid *) offsetof(Geometry::Vertex, m_TexCoords));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
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