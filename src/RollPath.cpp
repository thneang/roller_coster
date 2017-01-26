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
    for(int i=0;i<13;i++){
        list_point_base.push_back(Geometry::Vertex());
    }

    list_point_base[0].m_Position = vec3(0,0,0);
    list_point_base[1].m_Position = vec3(400,500,600);
    list_point_base[2].m_Position = vec3(900,600,900);
    list_point_base[3].m_Position = vec3(1000,700,1000);

    list_point_base[4].m_Position = list_point_base[3].m_Position;
    list_point_base[5].m_Position = vec3(1500,300,1500);
    list_point_base[6].m_Position = vec3(1600,300,1800);

    list_point_base[7].m_Position = list_point_base[6].m_Position;
    list_point_base[8].m_Position = vec3(1800,200,1700);
    list_point_base[9].m_Position = vec3(2100,100,1800);

    list_point_base[10].m_Position = list_point_base[9].m_Position;
    list_point_base[11].m_Position = vec3(2300,200,2100);
    list_point_base[12].m_Position = vec3(2500,150,2100);

    program = loadProgram(applicationPath.dirPath() + "shaders/RollPath.vs.glsl",
                          applicationPath.dirPath() + "shaders/RollPath.fs.glsl");

    initCurve();
//    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();

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