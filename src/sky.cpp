#include <Sky.hpp>

using namespace glimac;
using namespace std;
using namespace global;
using  namespace glm;
// TODO On peut peut-être généraliser pour tout dessiner avec le meme code
void Sky::init(const FilePath& applicationPath) {
    this->sky.loadOBJ(
            applicationPath.dirPath() + "assets/3D_models/Sky/sky.obj",
            applicationPath.dirPath() + "assets/3D_models/Sky/",
            false
    );


    program = loadProgram(applicationPath.dirPath() + "shaders/sky.vs.glsl",
                          applicationPath.dirPath() + "shaders/sky.fs.glsl");


    images[0] = loadImage(applicationPath.dirPath() + "assets/textures/sky.png");

    init_texture();
//    duplicate_vertex();

    init_vbo();
    init_vao();
    init_index();

    sky.freeVertexBuffer();
    sky.freeVertexBuffer();

}

void Sky::init_texture() {

    texture = new GLuint[1];
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


void Sky::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    // version pour utiliser drawElement
//    glBufferData(GL_ARRAY_BUFFER, this->sky.getVertexCount()*sizeof(Geometry::Vertex), this->sky.getVertexBuffer(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sky.getVertexCount() *sizeof(Geometry::Vertex), this->sky.getVertexBuffer(), GL_STATIC_DRAW);


//    glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Sky::init_vao() {
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

void Sky::init_index() {

    elements = new GLuint[sky.getMeshCount()];
    // Generate a buffer for the indices
    glGenBuffers(sky.getMeshCount(), elements);

    /************************ Envoie le buffer de la première mesh au gpu ***********************/
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);

    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
//             nombre de sommet utilisé par la mesh
            sky.getMeshBuffer()[0].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
            sky.getIndexBuffer() + sky.getMeshBuffer()[0].m_nIndexOffset,
            GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Sky::draw() {
    glBindVertexArray(vao);

    program.use();
    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");

    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");


    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(uTextureId, 0);

    mat4 scale = glm::scale(MatrixID, vec3(110.f, 110.f, 110.f));

    for (unsigned int i = 0; i < sky.getMeshCount(); ++i) {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[i]);

        MVMatrixMul = MVMatrix * scale;
        NormalMatrixMul = transpose(MVMatrixMul);

        glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrix * MVMatrixMul));
        glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrixMul));
        glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrixMul));



        // Draw the triangles !
        // afficher bien la forme grace au index mais texture impossible...
        glDrawElements(
                GL_TRIANGLES,      // mode
                sky.getMeshBuffer()[i].m_nIndexCount,    // count
                GL_UNSIGNED_INT,   // type
                (void *) 0      // element array buffer offset
        );

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    }



    glBindVertexArray(0);
}


void Sky::free() {
    if (texture) {
        delete[] texture;
    }
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}