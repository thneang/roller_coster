#include <Environnement.hpp>
#include <glimac/Geometry.hpp>
#include <GL_global.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

// TODO On peut peut-être généraliser pour tout dessiner avec le meme code
void Environnement::init(const FilePath& applicationPath) {
    this->environnement.loadOBJ(
            applicationPath.dirPath() + "assets/3D_models/SnowTerrain/SnowTerrain.obj",
            applicationPath.dirPath() + "assets/3D_models/SnowTerrain/SnowTerrain.mtl",
            true
    );

    program = loadProgram(applicationPath.dirPath() + "shaders/Environnement.vs.glsl",
                applicationPath.dirPath() + "shaders/Environnement.fs.glsl");

    program.use();

    images[0] = loadImage(applicationPath.dirPath() + "assets/3D_models/SnowTerrain/686.jpg");


//    init_texture();
    init_vbo();
    init_vao();
    init_index();

}

// TODO
void Environnement::init_texture() {

    // créer un buffer pour notre texture
    // TODO corriger erreur de seg ici
    glGenTextures(1, texture);


    // on bind la texture
    glBindTexture(GL_TEXTURE_2D, texture[0]);

    // On envoie l'image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, images[0]->getWidth(), images[0]->getHeight(), 0, GL_RGBA, GL_FLOAT, images[0]->getPixels());



    // filtre pour deux cas
    /* Afin de pouvoir utiliser une texture, il faut spécifier à OpenGL des filtres que ce dernier appliquera lorsque
    1) plusieurs pixels à l'écran sont couvert par un pixel de texture et
    2) un pixel à l'écran couvre plusieurs pixels de texture. Rajoutez les lignes suivantes:
    */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Environnement::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    glBufferData(GL_ARRAY_BUFFER, this->environnement.getVertexCount()*sizeof(Geometry::Vertex), this->environnement.getVertexBuffer(), GL_STATIC_DRAW);

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
            environnement.getMeshBuffer()[1].m_nIndexCount * sizeof(unsigned int),
//             position du buffer qui contient les données
            environnement.getIndexBuffer() + environnement.getMeshBuffer()[1].m_nIndexOffset,
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

// TODO ajouter les matrices
void Environnement::draw() {
    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elements[0]);

    // Draw the triangles !
    glDrawElements(
            GL_TRIANGLES,      // mode
            environnement.getMeshBuffer()[1].m_nIndexCount,    // count
            GL_UNSIGNED_INT,   // type
            (void*)0       // element array buffer offset
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Environnement::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}