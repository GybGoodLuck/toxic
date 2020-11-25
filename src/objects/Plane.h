#pragma once

#include <memory>

#include "../GLUtils.h"
#include "../vertices/Vertices.h"

class Plane {

public:
    using Ptr = std::shared_ptr<Plane>;
    Plane();

    void bindFrameBuffer();

    void update();
    void draw();
    
private:
    GLint m_program;
    GLint s_program;

    GLint u_model;
    GLint u_view;
    GLint u_projection;

    GLint s_model;
    GLint s_view;
    GLint s_projection;

    VAO m_vao;
    VBO m_vbo;
    int m_indexCount;

    VAO s_vao;
    VBO s_vbo;
    int s_indexCount;

    FBO m_fbo;
    unsigned int m_texColorBuffer;

    GLuint m_textureId;

};