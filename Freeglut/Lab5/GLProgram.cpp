#include "GLProgram.hpp"
#include "texture_loader.hpp"
#include "obj_loader.hpp"
#include "shader_stuff.h"

void GLProgram::createProgram() {
    program = glCreateProgram();
}

void GLProgram::loadBMP(const char *path) {
    int tex_width;
    int tex_height;
    unsigned char *tex_data;

    loadBMP_custom(path, tex_width, tex_height, &tex_data);

    glGenTextures(1, &TextureID);
    glBindTexture(GL_TEXTURE_2D, TextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_BGR, GL_UNSIGNED_BYTE, tex_data);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

void GLProgram::loadObject(const char * path) {
    if (!loadOBJ(path, OBJ_vertices, OBJ_uvs, OBJ_normals))
    {
        printf("Not loaded!\n");
        exit(1);
    }
}

void GLProgram::loadShaders(const char * vert,  const char * frag) {
    glAttachShader( program, LoadShader(GL_VERTEX_SHADER, "shaders/ld_vertex4.glsl"));
    glAttachShader( program, LoadShader(GL_FRAGMENT_SHADER, "shaders/ld_fragment4.glsl"));
    LinkAndValidateProgram( program );
}

void GLProgram::prepareVBO() {
    glGenVertexArrays( 1, &vArray );
    glBindVertexArray( vArray );

    // Wspolrzedne wierzchokow
    glGenBuffers( 1, &vBuffer_coord );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_coord );
    glBufferData( GL_ARRAY_BUFFER, OBJ_vertices.size() * sizeof(glm::vec3), &OBJ_vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 0 );

    // Wektory normalne
    glGenBuffers( 1, &vBuffer_normal );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_normal );
    glBufferData( GL_ARRAY_BUFFER, OBJ_normals.size() * sizeof(glm::vec3), &OBJ_normals[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 1 );

    glGenBuffers( 1, &vBuffer_uv );
    glBindBuffer( GL_ARRAY_BUFFER, vBuffer_uv );
    glBufferData( GL_ARRAY_BUFFER, OBJ_uvs.size() * sizeof(glm::vec2), &OBJ_vertices[0], GL_STATIC_DRAW );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( 2 );
}

void GLProgram::draw(glm::mat4x4 Matrix_proj_mv) {
    glBindVertexArray( vArray );
    glUseProgram( program );

    // ------------------------------------------------------
    glUniform3fv( glGetUniformLocation( program, "Light_Ambient" ), 1, &Light_Ambient[0] );
    glUniform3fv( glGetUniformLocation( program, "Light_Diffuse" ), 1, &Light_Diffuse[0] );
    glUniform3fv( glGetUniformLocation( program, "Light_Position" ), 1, &Light_Position[0] );

    glUniformMatrix4fv( glGetUniformLocation( program, "Matrix_proj_mv" ), 1, GL_FALSE, glm::value_ptr(Matrix_proj_mv));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glBindVertexArray(vArray);
    glDrawArrays( GL_TRIANGLES, 0, OBJ_vertices.size() );
}
