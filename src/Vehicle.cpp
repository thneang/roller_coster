#include <Vehicle.hpp>
#include <zconf.h>

using namespace glimac;
using namespace std;
using namespace global;
using namespace glm;

void Vehicle::init(const FilePath& applicationPath) {
    // ATTENTION bien vérifier le PATH pour material si c'est pas chargé.
    // Faire la vérif pour la ligne mtllib dans le fichier OBJ ET dans le code
    // avec mtllib du fichier OBJ mettre /nom_du_mtl
    // dans l'appel loadOBJ mettre repertoire mtl mais pas le fichier mtl
    this->vehicle.loadOBJ(
            applicationPath.dirPath() + "assets/3D_models/Vehicle/wagon.obj",
            applicationPath.dirPath() + "assets/3D_models/Vehicle/",
            true
    );


    program = loadProgram(applicationPath.dirPath() + "shaders/Vehicle.vs.glsl",
                applicationPath.dirPath() + "shaders/Vehicle.fs.glsl");

    images[0] = loadImage(applicationPath.dirPath() + "assets/textures/metal.jpg");

    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();
    init_index();

    mat4 rotate = glm::rotate(MatrixID, 90.0f, vec3(0.0f, -1.0f, 0.0f));
    RollMatrix *= rotate;
    vehicle.freeIndexBuffer();

}

void Vehicle::init_texture() {

    texture = new GLuint[1];
    // créer un buffer pour notre texture
    glGenTextures(1, texture);

    // on bind la texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // On envoie l'image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, images[0]->getWidth(), images[0]->getHeight(), 0, GL_RGBA, GL_FLOAT, images[0]->getPixels());


    // filtre pour deux cas
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);


//    texture_ka_buffer = new GLuint[vehicle.getMeshCount()];
//    texture_kd_buffer = new GLuint[vehicle.getMeshCount()];
//    texture_ks_buffer = new GLuint[vehicle.getMeshCount()];
//    texture_Normal_buffer = new GLuint[vehicle.getMeshCount()];
//
//
//    // créer un buffer pour notre texture
//    glGenTextures(vehicle.getMaterialCount(), texture);
//
//    // Cette boucle reserve un id pour les buffer de texture et envoie les données pour chaque type (ka kd ks...)
//    for (unsigned int i = 0; i < vehicle.getMaterialCount(); ++i) {
//
//        // Pour texture ka
//        if (vehicle.getMaterialBuffer()[i].m_pKaMap) {
//            // on bind la texture
//            glBindTexture(GL_TEXTURE_2D, texture_ka_buffer[i]);
//
//            // On envoie l'image
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//                         vehicle.getMaterialBuffer()[i].m_pKaMap->getWidth(),
//                         vehicle.getMaterialBuffer()[i].m_pKaMap->getHeight(), 0, GL_RGBA, GL_FLOAT,
//                         vehicle.getMaterialBuffer()[i].m_pKaMap->getPixels());
//
//
//            // filtre pour deux cas
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//
//        // pour texture kd
//        if (vehicle.getMaterialBuffer()[i].m_pKdMap) {
//            // on bind la texture
//            glBindTexture(GL_TEXTURE_2D, texture_kd_buffer[i]);
//
//            // On envoie l'image
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//                         vehicle.getMaterialBuffer()[i].m_pKdMap->getWidth(),
//                         vehicle.getMaterialBuffer()[i].m_pKdMap->getHeight(), 0, GL_RGBA, GL_FLOAT,
//                         vehicle.getMaterialBuffer()[i].m_pKdMap->getPixels());
//
//
//            // filtre pour deux cas
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//
//        // pour texture ks
//        if (vehicle.getMaterialBuffer()[i].m_pKsMap) {
//            // on bind la texture
//            glBindTexture(GL_TEXTURE_2D, texture_ks_buffer[i]);
//
//            // On envoie l'image
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//                         vehicle.getMaterialBuffer()[i].m_pKsMap->getWidth(),
//                         vehicle.getMaterialBuffer()[i].m_pKsMap->getHeight(), 0, GL_RGBA, GL_FLOAT,
//                         vehicle.getMaterialBuffer()[i].m_pKsMap->getPixels());
//
//
//            // filtre pour deux cas
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//
//        // pour texture Normal
//        if (vehicle.getMaterialBuffer()[i].m_pNormalMap) {
//            // on bind la texture
//            glBindTexture(GL_TEXTURE_2D, texture_Normal_buffer[i]);
//
//            // On envoie l'image
//            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
//                         vehicle.getMaterialBuffer()[i].m_pNormalMap->getWidth(),
//                         vehicle.getMaterialBuffer()[i].m_pNormalMap->getHeight(), 0, GL_RGBA, GL_FLOAT,
//                         vehicle.getMaterialBuffer()[i].m_pNormalMap->getPixels());
//
//
//            // filtre pour deux cas
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//            glBindTexture(GL_TEXTURE_2D, 0);
//        }
//    }

}

void Vehicle::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    // version pour utiliser drawElement
    glBufferData(GL_ARRAY_BUFFER, this->vehicle.getVertexCount()*sizeof(Geometry::Vertex), this->vehicle.getVertexBuffer(), GL_STATIC_DRAW);

//    glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Vehicle::init_vao() {
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

void Vehicle::init_index() {
    elements = new GLuint[vehicle.getMeshCount()];
    // Generate a buffer for the indices
    glGenBuffers(vehicle.getMeshCount(), elements);

    for (unsigned int i = 0; i < vehicle.getMeshCount(); ++i) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[i]);

        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
                vehicle.getMeshBuffer()[i].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
                vehicle.getIndexBuffer() + vehicle.getMeshBuffer()[i].m_nIndexOffset,
                GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}

void Vehicle::draw() {
    glBindVertexArray(vao);

    program.use();
    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    utexture_ka_ID = glGetUniformLocation(program.getGLId(), "uTextureKa");
    utexture_ks_ID = glGetUniformLocation(program.getGLId(), "uTextureKs");
    utexture_kd_ID = glGetUniformLocation(program.getGLId(), "uTextureKd");
    utexture_Normal_ID = glGetUniformLocation(program.getGLId(), "uTextureNormal");

    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    mat4 scale = glm::scale(MatrixID, vec3(2.f, 2.f, 2.f));

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(uTextureId, 0);

    for (unsigned int i = 0; i < vehicle.getMeshCount(); ++i) {

        // donne la texture au shader pour l'appliquer avec draw
//        if (vehicle.getMaterialBuffer()[i].m_pKdMap) {
//            glBindTexture(GL_TEXTURE_2D, texture_kd_buffer[i]);
//            glUniform1i(utexture_kd_ID, 0);
//        }

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[i]);

        mat4 rotate = glm::rotate(MatrixID, 90.0f, vec3(0.0f, -1.0f, 0.0f));
        mat4 translate = glm::translate(MatrixID,vec3(600,1000,0));

        MVMatrixMul = MVMatrix * RollMatrix;
        NormalMatrixMul = transpose(MVMatrixMul);

        glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrixMul));
        glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrixMul));
        glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrixMul));

        // Draw the triangles !
        // afficher bien la forme grace au index mais texture impossible...
        glDrawElements(
                GL_TRIANGLES,      // mode
                vehicle.getMeshBuffer()[i].m_nIndexCount,    // count
                GL_UNSIGNED_INT,   // type
                (void *) 0      // element array buffer offset
        );
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }

//    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.size());



    glBindVertexArray(0);
}

void Vehicle::roll(glm::vec3 v){

    //angleY = cos-1(adj/hyp) = cos-1(V(x²+z²)/norme(v-vCenter))
//    std::cout <<(v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z)<< " " << (v-vCenter).length() << std::endl;
//    std::cout <<acos(glm::sqrt((v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z))/(v-vCenter).length()) << std::endl;
    if(v != vCenter){
        std::cout << m_VertexBuffer.size() << std::endl;
        std::cout << "v "<< v << " center "<< vCenter << "trans "<< v-vCenter << std::endl;
//        rotate(acos(glm::sqrt((v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z))/(v-vCenter).length()),vec3(0,1,0));
        //angleX = cos-1(adj/hyp) = cos-1(z/V(x²+z²))
//        rotate(acos((v.z-vCenter.z)/glm::sqrt((v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z))),vec3(1,0,0));
//        float angle1 = acos(glm::sqrt((v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z))/(v-vCenter).length());
//        mat4 rotate = glm::rotate(MatrixID,angle1,vec3(0,1,0));
//        float angle2 = acos((v.z-vCenter.z)/glm::sqrt((v.x-vCenter.x)*(v.x-vCenter.x)+(v.z-vCenter.z)*(v.z-vCenter.z)));
//        rotate *= glm::rotate(MatrixID,angle2,vec3(1,0,0));
        //translate :
        mat4 translate = glm::translate(MatrixID,v-vCenter);
        RollMatrix *= translate;
//        translate(v-vCenter);
    }
    vCenter = v;
}

void Vehicle::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    vehicle.freeVertexBuffer();
}