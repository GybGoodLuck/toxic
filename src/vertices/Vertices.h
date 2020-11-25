#pragma once

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>
#include <map>

#include "VerticesInfo.h"
#include "../GLUtils.h"

enum ObjectType {
    TRIANGLE = 0,
    FONT,
    PLANE,
    CUBE,
    SPHERE,
    SQUARE,
};

struct VerticesBuffer {
    VAO vao = 0;
    VBO vbo = 0;
    EBO ebo = 0;

    int indexCount = 0;

    bool isVaild() {
        return (vao != 0) && (vbo != 0) && (indexCount != 0);
    }
};

class Vertices {

public:
    static std::shared_ptr<Vertices> getInstance();
    VerticesBuffer getVerticesBuffer(ObjectType type);


private:
    std::map<ObjectType, VerticesBuffer> m_vaoMap;

    VerticesBuffer bindPlane();
    VerticesBuffer bindFont();
    VerticesBuffer bindCube();
    VerticesBuffer bindSphere();
    VerticesBuffer bindSquare();

    VerticesBuffer findVAO(ObjectType type);

    const unsigned int X_SEGMENTS = 200;
    const unsigned int Y_SEGMENTS = 200;
};