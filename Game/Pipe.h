#ifndef PIPE_H
#define PIPE_H

#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>

#include "../Engine/Modeling/Model.h"
#include "./Bird.h"

class Pipe
{
public:
    Pipe();
    Pipe(int _id):id(_id){}
    ~Pipe();
    void init();
    void update();
    void teleport();
    void render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess);
    void checkCollision(Bird* b);
private:
    glm::vec2 pos = glm::vec2(5,0);
    GLfloat size_pipe_top;
    GLfloat size_pipe_bottom;   
    Model* model_pipe_top;
    Model* model_pipe_bottom;
    GLfloat gap; 
    int id = 0;
    GLfloat speed = 0.f;
    GLfloat collision_w = .2f;
};

#endif