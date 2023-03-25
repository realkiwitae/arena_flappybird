#ifndef ARENA_H
#define ARENA_H

#pragma once

#include <vector>

#include "./Bird.h"
#include "./GameValues.h"
#include "./Pipe.h"

class Arena
{
public:
    Arena();
    ~Arena();

    void init();
    bool update();
    void render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess);
    void checkCollision(Bird* b);
    int getIncId(){return incoming_pipe_id;}
    glm::vec2 getIncGap(){return pipes[incoming_pipe_id].getGap();}
private:
    Pipe pipes[game_arena_nb_pipes]; 
    Model* ground;
    Model* ceiling;
    Model* pipe;
    Model* incpipe;
    Texture* brickTexture;
    int incoming_pipe_id;
};

#endif