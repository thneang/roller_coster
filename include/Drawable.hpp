#ifndef ROLLER_COSTER_DRAWABLE_HPP
#define ROLLER_COSTER_DRAWABLE_HPP

#include <glimac/Image.hpp>
#include <glimac/Program.hpp>
#include <GL_global.hpp>
#include <iostream>
#include <glimac/Geometry.hpp>

class Drawable {
protected :

    // ensemble des "ID" de texture
    GLuint texture[1];
    // "ID" du buffer de vertex
    GLuint vbo;
    //"ID" du buffer attribut
    GLuint vao;

    // Contient les "ID" de nos meshes
    GLuint elements[4];

    // Le buffer qui contient nos vertex, une duplication de sommets importé est nécessaire pour appliquer des textures
    // on fait cela car un meme vertex ne peut pas avoir plusieurs coordonnée de texture;
    std::vector<glimac::Geometry::Vertex> m_VertexBuffer;


    // Nos images utilisé par les textures
    // TODO passer en pointeur pour plusieurs textures
    std::unique_ptr<glimac::Image> images[1];

    // Program pour utiliser les shaders
    glimac::Program program;

    GLint uTextureId;

    /************************* Id des matrices pour les shaders *******************************************************/
    GLint uMVPMatrixId;

    GLint uMVMatrixId;

    GLint uNormalMatrixId;

    glm::mat4 ProjMatrixMul;

    glm::mat4 MVMatrixMul;

    glm::mat4 NormalMatrixMul;

    /******************************************************************************************************************/

public :
    // Init l'objet (allocation), envoie les données au gpu et demarre un programme pour les shaders
    virtual void init(const glimac::FilePath& filepath = nullptr) = 0;

    // envoie l'image au gpu
    virtual void init_texture() {};

    // envoie les sommets au gpu
    virtual void init_vbo() {};

    // decrit les données pour le gpu
    virtual void init_vao() {};

    // permet d'utiliser l'indexation des sommets pour draw
    // cela permet de d'éviter de duppliquer des sommets
    // lorsqu'on dessine nos triangles pour les objets
    // permet de dessiner facilement avec glDrawElement mais ne permet pas les textures...
    // A utiliser que pour tester des imports
    virtual void init_index() {}

    // Demande de dessin a openGL
    virtual void draw() = 0;

    // Cette fonction permet de dupliqué les sommets importé d'un modele 3D pour permettre de mettre des textures
    virtual void duplicate_vertex() {};

    // libere l'espace allouée, doit être appelé à la fin du programme
    virtual void free() = 0;

    virtual void rotate(float angle,glm::vec3 v){
        MVMatrixMul = glm::rotate(global::MVMatrix,angle,v);
        ProjMatrixMul *= MVMatrixMul;
        NormalMatrixMul *= MVMatrixMul;
    }

    virtual void translate(glm::vec3 v){
        glm::mat4 translate = glm::translate(global::MVMatrix,v);
        ProjMatrixMul *= translate;
        NormalMatrixMul *= translate;
    }

    virtual void scale(glm::vec3 v){
        glm::mat4 scale = glm::scale(global::MVMatrix,v);
        ProjMatrixMul *= scale;
        NormalMatrixMul *= scale;
    }
};


#endif //ROLLER_COSTER_DRAWABLE_HPP
