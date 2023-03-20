#ifndef BIRD_H
#define BIRD_H

#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>

#include "../Engine/Modeling/Model.h"

class Bird
{
public:
    Bird();
    ~Bird();

    void init();
    void update();
    void render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess);

    void setbUp(bool val){bUp = val;}

private:
    Model* model_bird;
    //Physics
    glm::vec2 pos = glm::vec2(-3.5,0);
    GLfloat speed = 0.f;
    GLfloat mass = 2.f;
    GLfloat maxspeed = 10.f;// ms-1

    bool bUp = false;
};

#endif