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

void Bird::init()
{
    birth = now;
    pos.x = game_bird_x;
    model_bird = new Model();
	model_bird->LoadModel("flappy/bird");
}

void Bird::update(){
    GLfloat gravityForce = game_gravity * mass;
    speed = glm::clamp(!bUp*(fabs(pos.y-game_arena_ceiling_y)>0.001)*speed + bUp*glm::max(speed,0.f) + (1-2*bUp)*gravityForce*deltaTime, -maxspeed, maxspeed);
    pos.y += speed*deltaTime;

    pos.y = glm::clamp(pos.y,game_arena_floor_y,game_arena_ceiling_y);
  //  std::cout << pos.y << std::endl;
}

void Bird::render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess)
{
    glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0,pos.y,pos.x));
	model = glm::scale(model, glm::vec3(.1f, .1f, .1f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	model_bird->RenderModel();
}

void Bird::kill(GLfloat y){
    pos = glm::vec2(game_bird_x,y);

    if(fitness < now - birth){
        fitness = now - birth;
        std::cout << "Bird " << fitness << std::endl;
    }
    birth = now;
}