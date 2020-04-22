#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef LAB5_GLPROGRAM_HPP
#define LAB5_GLPROGRAM_HPP


class GLProgram {
private:
    GLuint program;
    GLuint TextureID;
    GLuint vBuffer_coord;
    GLuint vBuffer_normal;
    GLuint vBuffer_uv;
    GLuint vArray;
    std::vector<glm::vec3> OBJ_vertices;
    std::vector<glm::vec2> OBJ_uvs;
    std::vector<glm::vec3> OBJ_normals;

    glm::vec3 Light_Ambient = glm::vec3(0.2, 0.2, 0.2);
    glm::vec3 Light_Diffuse = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 Light_Position = glm::vec3(0.0, 1.0, -3.0);

public:
    void draw(glm::mat4x4 Matrix_proj_mv);
    void createProgram();
    void loadObject(const char * path);
    void loadShaders(const char * vert, const char * frag);
    void loadBMP(const char * path);
    void prepareVBO();
};


#endif //LAB5_GLPROGRAM_HPP
