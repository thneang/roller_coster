//
// Created by kev on 23/01/17.
//

#include <RollPath.hpp>

using namespace glm;
using namespace glimac;
using namespace std;
using namespace global;


void RollPath::initCurve(){
    for(unsigned int i=0;i < list_point_base.size()-3;i+=3){
        vec3 p0 = list_point_base[i].m_Position;
        vec3 p1 = list_point_base[i+1].m_Position;
        vec3 p2 = list_point_base[i+2].m_Position;
        vec3 p3 = list_point_base[i+3].m_Position;
        for(float t=0.0f ; t < 1.0f ; t+=1/100.0f) {
            vec3 pos = p0 * (1 - t) * (1 - t) * (1 - t) + 3.0f * p1 * t * (1 - t) * (1 - t) + 3.0f * p2 * t * t * (1 - t) +
                       p3 * t * t * t;
            Geometry::Vertex v;
            v.m_Position = pos;
            m_VertexBuffer.push_back(v);
        }
    }
    for(unsigned int i=0;i<m_VertexBuffer.size();i+=3){
        vec3 n = glm::cross(glm::normalize(m_VertexBuffer[i+1].m_Position - m_VertexBuffer[i].m_Position),
                            glm::normalize(m_VertexBuffer[i+2].m_Position - m_VertexBuffer[i].m_Position));
        m_VertexBuffer[i].m_Normal = n;
        m_VertexBuffer[i+1].m_Normal = n;
        m_VertexBuffer[i+2].m_Normal = n;
    }
    for(unsigned int i = 0 ; i < m_VertexBuffer.size() ; i++) {
        m_VertexBuffer[i].m_TexCoords = vec2(i/m_VertexBuffer.size(),0.5);
    }
}

void RollPath::init(const FilePath& applicationPath){
    list_point_base.push_back(Geometry::Vertex());
    list_point_base[list_point_base.size()-4].m_Position = vec3(0,0,0);
    //monté
    add_point_controle(vec3(200,0,0),
                       vec3(200,500,0),
                       vec3(200,500,0));
    //ralentissement
    add_point_controle(vec3(50,0,0),
                       vec3(50,0,0),
                       vec3(50,0,0));
    //descente
    add_point_controle(vec3(200,-400,0),
                       vec3(200,-400,0),
                       vec3(200,0,0));
    //monté loop
    add_point_controle(vec3(200,400,50),
                       vec3(-100,400,50),
                       vec3(-100,200,50));
    //pointe loop
    add_point_controle(vec3(-25,25,0),
                       vec3(-25,0,0),
                       vec3(-25,-25,0));
    //descente loop
    add_point_controle(vec3(-100,-200,50),
                       vec3(-100,-400,50),
                       vec3(200,-300,0));
    //virage après loop
    add_point_controle(vec3(200,-100,0),
                       vec3(200,0,200),
                       vec3(-200,0,200));
    //monté après virage
    add_point_controle(vec3(-200,0,50),
                       vec3(-200,500,0),
                       vec3(-200,500,0));
    //ralentissement
    add_point_controle(vec3(-50,0,0),
                       vec3(-50,0,0),
                       vec3(-50,0,0));
    //descente
    add_point_controle(vec3(-100,-400,0),
                       vec3(-100,-300,0),
                       vec3(-100,-100,0));
    //monté petite loop
    add_point_controle(vec3(-100,50,-100),
                       vec3(-50,50,50),
                       vec3(-50,50,50));
    //ralentissement
    add_point_controle(vec3(-10,10,10),
                       vec3(-10,0,10),
                       vec3(-10,-10,10));
    //descente petite loop
    add_point_controle(vec3(-50,-50,50),
                       vec3(-50,-50,50),
                       vec3(-100,-50,-100));
    //virage après loop
    add_point_controle(vec3(-200,0,-50),
                       vec3(-200,0,-200),
                       vec3(200,0,-200));

    //fin à ameliorer ( une fois quon sera sur de notre trajectoire on fera une descente moins raid en fin.)
    vec3 v1 = -list_point_base[list_point_base.size()-1].m_Position/3.0f;
    vec3 v2 = -list_point_base[list_point_base.size()-1].m_Position/3.0f;
    vec3 v3 = -list_point_base[list_point_base.size()-1].m_Position/3.0f;
    add_point_controle(v1,
                       v2,
                       v3);


    program = loadProgram(applicationPath.dirPath() + "shaders/RollPath.vs.glsl",
                          applicationPath.dirPath() + "shaders/RollPath.fs.glsl");

    initCurve();
//    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();

}

void RollPath::add_point_controle(vec3 v1, vec3 v2, vec3 v3){
    for(int i=0;i<3;i++){
        list_point_base.push_back(Geometry::Vertex());
    }
    list_point_base[list_point_base.size()-3].m_Position = list_point_base[list_point_base.size()-4].m_Position + v1;
    list_point_base[list_point_base.size()-2].m_Position = list_point_base[list_point_base.size()-3].m_Position + v2;
    list_point_base[list_point_base.size()-1].m_Position = list_point_base[list_point_base.size()-2].m_Position + v3;
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
    glBufferData(GL_ARRAY_BUFFER, this->m_VertexBuffer.size()*sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);

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

    glBindVertexArray(vao);

    program.use();

    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    mat4 rotate = glm::rotate(MatrixID, 90.0f, vec3(0.0f, -1.0f, 0.0f));

    MVMatrixMul = MVMatrix * rotate;
    NormalMatrixMul = transpose(MVMatrixMul);

    glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrixMul));
    glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrixMul));
    glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrixMul));

//    glDrawArrays(GL_QUADRATIC_CURVE_TO_NV, 0, m_VertexBuffer.size());
    glDrawArrays(GL_LINES, 0, m_VertexBuffer.size());

    glBindVertexArray(0);

}

void RollPath::duplicate_vertex(){
}

void RollPath::free(){
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}