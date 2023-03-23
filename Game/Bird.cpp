#include "Bird.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Engine/Utils/CommonValues.h"

#include "./GameValues.h"

#include <iostream>

extern GLfloat deltaTime,now;

Bird::Bird()
{

}

Bird::~Bird()
{

}

void Bird::init(Model* model)
{
    birth = now;
    pos.x = game_bird_x;
    model_bird = model;

    bIsAlive = true;
}

void Bird::update(glm::vec2 inc_gap){
    if(!bIsAlive){
        return;
    }
    GLfloat gravityForce = game_gravity * mass;
    double inputs[3] = {
        fabs(game_arena_ceiling_y - pos.y + collision_h/2.f),
        fabs(pos.y - collision_h/2.f - game_arena_floor_y),
        glm::distance(inc_gap , pos)
        };

    flappy_nn->calc(inputs);

    double* out = flappy_nn->getOutput();
    bUp = out[0] > .05f;

    speed = glm::clamp(!bUp*(fabs(pos.y-game_arena_ceiling_y)>0.001)*speed + bUp*glm::max(speed,0.f) + (1-2*bUp)*gravityForce*deltaTime, -maxspeed, maxspeed);
    pos.y += speed*deltaTime;

    pos.y = glm::clamp(pos.y,game_arena_floor_y,game_arena_ceiling_y);
  //  std::cout << pos.y << std::endl;
}

void Bird::render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess)
{
    if(!bIsAlive){
        return;
    }
    glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0,pos.y,pos.x));
	model = glm::scale(model, glm::vec3(.1f, .1f, .1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	model_bird->RenderModel();
}

void Bird::kill(GLfloat y){

    pos = glm::vec2(game_bird_x,y);

    if(flappy_dna->fitness < now - birth){
        flappy_dna->fitness = now - birth;
        //std::cout << "Bird " << fitness << std::endl;
    }
    birth = now;
    bIsAlive = false;

}

void Bird::possess(DNA* dna){
    bIsAI = true;
    flappy_dna = dna;
    int stage_l[game_flappynn_nb_layers] = {3, 4, 4, 1};
    if(!flappy_nn)flappy_nn = new NeuralNetwork(stage_l, game_flappynn_nb_layers);
    flappy_nn->loadCoeffs(dna->data);
}