#ifndef ARENA_H
#define ARENA_H

#pragma once

#include <vector>

#include "./GameValues.h"
#include "./Pipe.h"

class Arena
{
public:
    Arena();
    ~Arena();

    void init();
    void update();
    void render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess);
private:
    Pipe pipes[game_arena_nb_pipes]; 
    Model ground;
    Model ceiling;

};

#endif