#include "Plane.h"
#include "../shader/Shader.h"
#include "Config.h"

Plane::Plane() {
    m_program = createProgram(verticesSource, fragmentSource);    
    s_program = createProgram(screenVerticesSource, screenFragmentSource);
    
    u_model = glGetUniformLocation(m_program, "model");
    u_view = glGetUniformLocation(m_program, "view");
    u_projection = glGetUniformLocation(m_program, "projection");

    s_model = glGetUniformLocation(s_program, "model");
    s_view = glGetUniformLocation(s_program, "view");
    s_projection = glGetUniformLocation(s_program, "projection");

    m_vao = Vertices::getInstance()->getVerticesBuffer(SQUARE).vao;
    m_vbo = Vertices::getInstance()->getVerticesBuffer(SQUARE).vbo;
    m_indexCount = Vertices::getInstance()->getVerticesBuffer(SQUARE).indexCount;

    s_vao = Vertices::getInstance()->getVerticesBuffer(SQUARE).vao;
    s_vbo = Vertices::getInstance()->getVerticesBuffer(SQUARE).vbo;
    s_indexCount = Vertices::getInstance()->getVerticesBuffer(SQUARE).indexCount;

    bindFrameBuffer();

    std::string path = RES_PATH + "image/dog.jpg";
    m_textureId = loadTexture(path.c_str());
}

void Plane::bindFrameBuffer() {
    glGenFramebuffers(1, &m_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    
    glGenTextures(1, &m_texColorBuffer);
    glBindTexture(GL_TEXTURE_2D, m_texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 800, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texColorBuffer, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Plane::update() {
    auto model = glm::mat4(1.0f);
    glm::vec3 pos = {0, 0, -1};
    glm::quat quat = {0, 0, 0, 1};
    model = glm::translate(model, pos);
    model = model * glm::mat4_cast(quat);

    auto projection = glm::perspective(glm::radians(120.f), 1.0f,
        0.1f, 5000.f);
    glm::vec3 cameraPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 cameraDir = {0.0f, 0.0f, -1.0f};
    glm::vec3 cameraUp = {0.0f, 1.0f, 0.0f};
    auto view = glm::lookAt(cameraPos, cameraPos + cameraDir, cameraUp);

    glUseProgram(m_program);
    glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view));


    auto model2 = glm::mat4(1.0f);
    glm::vec3 pos2 = {0, 0, -1};
    glm::quat quat2 = {0, 0, 0, 1};
    model2 = glm::translate(model2, pos2);
    quat2 *= glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 0.0, 1.0));
    model2 = model2 * glm::mat4_cast(quat2);
    glUseProgram(s_program);
    glUniformMatrix4fv(s_model, 1, GL_FALSE, glm::value_ptr(model2));
    glUniformMatrix4fv(s_projection, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(s_view, 1, GL_FALSE, glm::value_ptr(view));
}

void Plane::draw() {
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(m_program);
    glBindTexture(GL_TEXTURE_2D, m_textureId);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_indexCount);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(s_program);
    glBindTexture(GL_TEXTURE_2D, m_texColorBuffer);
    glBindVertexArray(s_vao);
    glDrawArrays(GL_TRIANGLES, 0, s_indexCount);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}