#include <Vehicle.hpp>
#include <zconf.h>

using namespace glimac;
using namespace std;
using namespace global;

void Vehicle::init(const FilePath& applicationPath) {
    this->vehicle.loadOBJ(
            applicationPath.dirPath() + "assets/3D_models/Vehicle/vehicle.obj",
            applicationPath.dirPath() + "assets/3D_models/Vehicle/vehicle.mtl",
            true
    );


    program = loadProgram(applicationPath.dirPath() + "shaders/Vehicle.vs.glsl",
                applicationPath.dirPath() + "shaders/Vehicle.fs.glsl");

    program.use();
//    images[0] = loadImage(applicationPath.dirPath() + "assets/3D_models/Vehicle/vehicle.jpg");

    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

//    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();
    init_index();

    scale(vec3(0.5f,0.5f,0.5f));

}

void Vehicle::init_texture() {

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

void Vehicle::duplicate_vertex() {
    // Notre buffer avec tous les vertex qui ont été duppliqué

    /****** on duplique donc nos sommets et en même temps on doit leur donner nos coordonnées de texture *****/
    int nb_index = vehicle.getMeshBuffer()[1].m_nIndexCount;
    size_t offset = vehicle.getMeshBuffer()[1].m_nIndexOffset;
    m_VertexBuffer = vector<Geometry::Vertex>(nb_index);

    for (int i = 0; i < nb_index; ++i) {

        Geometry::Vertex tmp = {
                vehicle.getVertexBuffer()[vehicle.getIndexBuffer()[i + offset]].m_Position,
                vehicle.getVertexBuffer()[vehicle.getIndexBuffer()[i + offset]].m_Normal,
                vehicle.getVertexBuffer()[vehicle.getIndexBuffer()[i + offset]].m_TexCoords
        };



        // On a un tableau d'indice qui sont les indices (dans le tableaux des vertexs) des sommets qui forme la figure
        m_VertexBuffer.push_back(tmp);

    }

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
    // Generate a buffer for the indices
    glGenBuffers(vehicle.getMeshCount(), elements);

    for (int i = 0; i < vehicle.getMeshCount(); ++i) {
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

    /************************ Envoie le buffer de la première mesh au gpu ***********************/
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);
//
//    glBufferData(
//            GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
//            vehicle.getMeshBuffer()[0].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
//            vehicle.getIndexBuffer() + vehicle.getMeshBuffer()[0].m_nIndexOffset,
//            GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /************************ Envoie le buffer de la deuxième mesh au gpu ***********************/

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[1]);
//
//    glBufferData(
//            GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
//            vehicle.getMeshBuffer()[1].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
//            vehicle.getIndexBuffer() + vehicle.getMeshBuffer()[1].m_nIndexOffset,
//            GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Vehicle::draw() {
    glBindVertexArray(vao);

    // donne la texture au shader pour l'appliquer avec draw
//    glBindTexture(GL_TEXTURE_2D, texture[0]);
//    glUniform1i(uTextureId, 0);


    for (int i = 0; i < vehicle.getMeshCount(); ++i) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[i]);

        mat4 ProjMatrixVehicle = ProjMatrix * ProjMatrixMul;
        mat4 NormalMatrixVehicle = NormalMatrix * NormalMatrixMul;
        glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrixVehicle));
        glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrixVehicle));

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

void Vehicle::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}