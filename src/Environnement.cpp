#include <Environnement.hpp>

using namespace glimac;
using namespace std;
using namespace global;
using  namespace glm;
// TODO On peut peut-être généraliser pour tout dessiner avec le meme code
void Environnement::init(const FilePath& applicationPath) {
    this->environnement.loadOBJ(
            applicationPath.dirPath() + "assets/3D_models/Landscape/environnement.obj",
            applicationPath.dirPath() + "assets/3D_models/Landscape/",
            false
    );

    program = loadProgram(applicationPath.dirPath() + "shaders/Environnement.vs.glsl",
                applicationPath.dirPath() + "shaders/Environnement.fs.glsl");


    images[0] = loadImage(applicationPath.dirPath() + "assets/3D_models/Landscape/environnement.jpg");




    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();
    init_index();

}

void Environnement::init_texture() {

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

void Environnement::duplicate_vertex() {
    // Notre buffer avec tous les vertex qui ont été duppliqué

    /****** on dupplique donc nos sommets et en même temps on doit leur donner nos coordonnées de texture *****/
    int nb_index = environnement.getMeshBuffer()[0].m_nIndexCount;
    size_t offset = environnement.getMeshBuffer()[0].m_nIndexOffset;
    m_VertexBuffer = vector<Geometry::Vertex>(nb_index);

    for (int i = 0; i < nb_index; ++i) {

        Geometry::Vertex tmp = {
                environnement.getVertexBuffer()[environnement.getIndexBuffer()[i + offset]].m_Position,
                environnement.getVertexBuffer()[environnement.getIndexBuffer()[i + offset]].m_Normal,
                environnement.getVertexBuffer()[environnement.getIndexBuffer()[i + offset]].m_TexCoords
        };



        // On a un tableau d'indice qui sont les indices (dans le tableaux des vertexs) des sommets qui forme la figure
        m_VertexBuffer.push_back(tmp);

    }

}

void Environnement::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    // version pour utiliser drawElement
//    glBufferData(GL_ARRAY_BUFFER, this->environnement.getVertexCount()*sizeof(Geometry::Vertex), this->environnement.getVertexBuffer(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, 4*sizeof(Geometry::Vertex), this->environnement.getVertexBuffer(), GL_STATIC_DRAW);


//    glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Environnement::init_vao() {
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

void Environnement::init_index() {
    // Generate a buffer for the indices
    glGenBuffers(1, &elements[0]);

    /************************ Envoie le buffer de la première mesh au gpu ***********************/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);

    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
            environnement.getMeshBuffer()[0].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
            environnement.getIndexBuffer() + environnement.getMeshBuffer()[0].m_nIndexOffset,
            GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /************************ Envoie le buffer de la deuxième mesh au gpu ***********************/

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[1]);
//
//    glBufferData(
//            GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
//            environnement.getMeshBuffer()[1].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
//            environnement.getIndexBuffer() + environnement.getMeshBuffer()[1].m_nIndexOffset,
//            GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Environnement::draw() {
    glBindVertexArray(vao);
    program.use();
    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);


    // donne la texture au shader pour l'appliquer avec draw
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(uTextureId, 0);

//    mat4 translate = glm::translate(MVMatrix, vec3(0.0f,-15.0f,0.0f));


    glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrix));

    // Draw the triangles !
    // afficher bien la forme grace au index mais texture impossible...
    glDrawElements(
            GL_TRIANGLES,      // mode
            environnement.getIndexCount(),    // count
            GL_UNSIGNED_INT,   // type
            (void*)0       // element array buffer offset
    );

    // On a un rectangle texturé pour le moment
    // pour faire le sol on translate ce rectangle et on draw, autant de fois qu'on a besoin pour faire le sol
    vec3 distance = environnement.getVertexBuffer()[1].m_Position - environnement.getVertexBuffer()[0].m_Position;
    mat4 translateV = glm::translate(MatrixID, distance);
    for (int i = 0; i < 8; ++i) {
        mat4 translateH = glm::translate(translateV, distance * vec3((float) i, 0.0f, 0.0f));
        glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrix * translateH));
        glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrix * translateH));
//
//        // Draw the triangles !
//        // afficher bien la forme grace au index mais texture impossible...
        glDrawElements(
                GL_TRIANGLES,      // mode
                environnement.getIndexCount(),    // count
                GL_UNSIGNED_INT,   // type
                (void*)0       // element array buffer offset
        );
    }

//    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.size());


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}


void Environnement::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}