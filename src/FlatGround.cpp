#include <FlatGround.hpp>

using namespace glimac;
using namespace std;
using namespace global;
using namespace glm;

void FlatGround::init(const FilePath& applicationPath) {
    program = loadProgram(applicationPath.dirPath() + "shaders/FlatGround.vs.glsl",
                          applicationPath.dirPath() + "shaders/FlatGround.fs.glsl");

    program.use();

    images[0] = loadImage(applicationPath.dirPath() + "assets/3D_models/Landscape/environnement.jpg");

    uTextureId = glGetUniformLocation(program.getGLId(), "uTexture");
    uMVPMatrixId = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    uMVMatrixId = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    uNormalMatrixId = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    cout << images[0]->getWidth() << endl;
    cout << images[0]->getHeight() << endl;

    float points[] = {
            -0.5,  0.5,
            -0.5, -0.5,
            0.5, -0.5,
            -0.5,  0.5,
            0.5, -0.5,
            0.5,  0.5
    };


    // Init vertex buffer, au final on construit juste un carré avec une texture qu'on va draw plusieurs fois
    // Premiers point à l'origine, les normales sont donc perpendiculaire au plan, c'est juste l'axe y
    Geometry::Vertex vertex1{
            vec3(0.f, 0.0f, -images[0]->getHeight()),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(0.0f, 1.0f)
    };

    Geometry::Vertex vertex2{
            vec3(0.0f, 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(0.0f, 0.0f)
    };

    Geometry::Vertex vertex3{
            vec3(images[0]->getWidth(), 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(1.0f, 0.0f)
    };


    Geometry::Vertex vertex4{
            vec3(0.0f, 0.0f, -images[0]->getHeight()),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(0.0f, 1.0f)
    };

    Geometry::Vertex vertex5{
            vec3(images[0]->getWidth(), 0.0f, 0.0f),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(1.0f, 0.0f)
    };

    Geometry::Vertex vertex6{
            vec3(images[0]->getWidth(), 0.0f, -images[0]->getHeight()),
            vec3(0.0f, 1.0f, 0.0f),
            vec2(1.0f, 1.0f)
    };



    m_VertexBuffer.push_back(vertex1);
    m_VertexBuffer.push_back(vertex2);
    m_VertexBuffer.push_back(vertex3);
    m_VertexBuffer.push_back(vertex1);
    m_VertexBuffer.push_back(vertex3);
    m_VertexBuffer.push_back(vertex4);


    auto n = glm::cross(glm::normalize(m_VertexBuffer[1].m_Position - m_VertexBuffer[0].m_Position),
                        glm::normalize(m_VertexBuffer[2].m_Position - m_VertexBuffer[0].m_Position));

    m_VertexBuffer[0].m_Normal = n;
    m_VertexBuffer[1].m_Normal = n;
    m_VertexBuffer[2].m_Normal = n;
    m_VertexBuffer[4].m_Normal = n;
    m_VertexBuffer[5].m_Normal = n;
    m_VertexBuffer[6].m_Normal = n;

    cout << m_VertexBuffer.size() << endl;

    init_texture();

    init_vbo();
    init_vao();

}

void FlatGround::init_texture() {

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

void FlatGround::init_vbo() {
    // création du buffer
    glGenBuffers(1, &vbo);

    // bind le buffer créer pour mettre nos données
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Envoie les donnés
    // version pour utiliser drawElement
    glBufferData(GL_ARRAY_BUFFER, m_VertexBuffer.size() * sizeof(Geometry::Vertex), m_VertexBuffer.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void FlatGround::init_vao() {
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

void FlatGround::draw() {
    glBindVertexArray(vao);

    // donne la texture au shader pour l'appliquer avec draw
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glUniform1i(uTextureId, 0);


    mat4 ProjMatrixFlatGround = ProjMatrix * MVMatrix * ProjMatrixMul;
    mat4 NormalMatrixFlatGround = NormalMatrix * NormalMatrixMul;

    glUniformMatrix4fv(uMVPMatrixId, 1, GL_FALSE, value_ptr(ProjMatrixFlatGround));
    glUniformMatrix4fv(uMVMatrixId, 1, GL_FALSE, value_ptr(MVMatrix));
    glUniformMatrix4fv(uNormalMatrixId, 1, GL_FALSE, value_ptr(NormalMatrixFlatGround));

    glDrawArrays(GL_TRIANGLES, 0, m_VertexBuffer.size());


    glBindVertexArray(0);
}

void FlatGround::free() {
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}