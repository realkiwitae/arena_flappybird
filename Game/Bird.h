#ifndef BIRD_H
#define BIRD_H

#pragma once

#include "glm/glm.hpp"
#include <GL/glew.h>

#include "../Engine/Modeling/Model.h"

#include "./GameValues.h"

#include "../kiwinn/DNA.hpp"
#include "../kiwinn/NeuralNetwork.hpp"

class Bird
{
public:
    Bird();
    ~Bird();

    void init();
    void update();
    void render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess);
    void setbUp(bool val){bUp = val;}
    void kill(GLfloat y);
    glm::vec2 getPos(){return pos;}
    GLfloat getCollisionW(){return collision_w;}
    GLfloat getCollisionH(){return collision_h;}

    void possess(DNA* dna);

private:
    Model* model_bird;
    //Physics
    glm::vec2 pos = glm::vec2(game_bird_x,0);
    GLfloat speed = 0.f;
    GLfloat mass = 2.f;
    GLfloat maxspeed = 10.f;// ms-1
    GLfloat collision_w = 1.f;
    GLfloat collision_h = .5f;
    bool bUp = false;
    GLfloat fitness = 0.f;
    GLfloat birth = 0.f;

    bool bIsAI = false;
    DNA* flappy_dna;
    NeuralNetwork* flappy_nn = nullptr;
};

#endif