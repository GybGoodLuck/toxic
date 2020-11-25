#include "Window.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Window::init() {
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    createWindow();
}

void Window::createWindow() {
    m_glWindow = glfwCreateWindow(m_width, m_height, m_name.c_str(), NULL, NULL);
    if (m_glWindow == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_glWindow);
    glfwSetFramebufferSizeCallback(m_glWindow, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    m_plane = std::make_shared<Plane>();
}

void Window::renderLoop() {

    while (!glfwWindowShouldClose(m_glWindow))
    {
        processInput();
        m_plane->update();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        m_plane->draw();
        glfwSwapBuffers(m_glWindow);
        glfwPollEvents();
    }
    glfwTerminate();   
}

void Window::processInput() {
    if(glfwGetKey(m_glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_glWindow, true);
}