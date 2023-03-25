#include "Pipe.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

#include "../Engine/Utils/CommonValues.h"

#include "./GameValues.h"

extern GLfloat deltaTime;

Pipe::Pipe()
{

}

Pipe::~Pipe()
{

}

void Pipe::init(Model* _pipe,Model* _incpipe)
{
    pipe = _pipe;
    incpipe = _incpipe;

    pos.x += game_arena_left + game_arena_width*0/2.f + id*game_arena_pipe_distance;
    teleport();
}

void Pipe::teleport(){

    gap = glm::linearRand(game_arena_floor_y+1.f,game_arena_ceiling_y-1.f);

    size_pipe_bottom = gap - game_arena_floor_y - game_arena_pipe_gap/2.f;
    size_pipe_top = game_arena_ceiling_y - gap - game_arena_pipe_gap/2.f; 
}

void Pipe::update(int _incid){
    pos.x += game_arena_pipe_speed*deltaTime;
    if(pos.x < game_arena_left - 2.f){
        pos.x += game_arena_nb_pipes*game_arena_pipe_distance;
        teleport();
    }
    incid = _incid;
}

void Pipe::render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess)
{
    //bot pipe
    glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0,game_arena_floor_y+size_pipe_bottom/2.f,pos.x));
	model = glm::scale(model, glm::vec3(.2f, size_pipe_bottom, .2f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	if(incid==id){
        incpipe->RenderModel();
    }else{
        pipe->RenderModel();
    }

    //top pipe
    model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0,game_arena_ceiling_y-size_pipe_top/2.f,pos.x));
	model = glm::scale(model, glm::vec3(.2f, size_pipe_top, .2f));
    model = glm::rotate(model,glm::radians(180.f),glm::vec3(0,0,1));


	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//	shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	if(incid==id){
        incpipe->RenderModel();
    }else{
        pipe->RenderModel();
    }

}

void Pipe::checkCollision(Bird* b){
    glm::vec2 bird_pos = b->getPos();

    if(fabs(bird_pos.x - pos.x) < collision_w/2.f && fabs(bird_pos.y - gap) > game_arena_pipe_gap/2.f - b->getCollisionH()/2.f){
        b->kill(gap);
    }
}