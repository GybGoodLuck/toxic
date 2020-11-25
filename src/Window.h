#pragma once

#include <iostream>
#include <memory>

#include "GLUtils.h"
#include "objects/Plane.h"

class Window {

public:
    using Ptr = std::shared_ptr<Window>;

    static Window::Ptr Create(int width, int height, const std::string& name) {
        return std::make_shared<Window>(width, height, name);
    }

    Window(int width, int height, const std::string& name) 
            : m_width(width), m_height(height), m_name(name) {
        init();
    }

    void renderLoop();

private:
    void init();
    void createWindow();

    void processInput();

private:
    int m_width;
    int m_height;    
    std::string m_name;

    GLFWwindow* m_glWindow;

    Plane::Ptr m_plane;


};