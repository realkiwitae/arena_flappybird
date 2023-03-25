#include "Arena.h"
#include "GameValues.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Arena::Arena()
{

}

Arena::~Arena()
{

}

void Arena::init()
{   
    if(!brickTexture){
        brickTexture = new Texture("Textures/brick.png");
        brickTexture->LoadTextureA();
    }

    if(!pipe){
        pipe = new Model();
        pipe->LoadModel("flappy/pipe");
    }
    if(!incpipe){
        incpipe = new Model();
        incpipe->LoadModel("flappy/incpipe");
    }

    incoming_pipe_id = 0;
    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i] = Pipe(i);
        pipes[i].init(pipe,incpipe);
    }

    if(!ground){
        ground = new Model();
        ground->LoadModel("flappy/ground");
    }
    if(!ceiling){
        ceiling = new Model();
        ceiling->LoadModel("flappy/ground");
    }
}

bool Arena::update()
{
    bool b = false;
    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i].update(incoming_pipe_id);
        if(i == incoming_pipe_id
            &&pipes[i].getPos().x < game_bird_x - game_bird_collison_w/2.f)
        {
            incoming_pipe_id = (incoming_pipe_id+1)%game_arena_nb_pipes;
            b = true;
        }
    }
    return b;
}

void Arena::render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess)
{
    glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, game_arena_floor_y + .8f, 0.0f));
	model = glm::scale(model, glm::vec3(1.f, 1.f, 10.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//dirtTexture.UseTexture();
	//shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	ground->RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, game_arena_ceiling_y+1.f, 0.0f));
	model = glm::scale(model, glm::vec3(1.f, 1.f, 10.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//dirtTexture.UseTexture();
	//dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    ceiling->RenderModel();

    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i].render(uniformModel, uniformSpecularIntensity, uniformShininess);
    }
}

void Arena::checkCollision(Bird* b){
    if(b->isDead())return;
    glm::vec2 bird_pos = b->getPos();
    // if(fabs(bird_pos.y-game_arena_floor_y) < b->getCollisionH()/2.f){
    //     b->kill(0.f);
    //     return;
    // }
    // if(fabs(bird_pos.y-game_arena_ceiling_y) < b->getCollisionH()/2.f){
    //     b->kill(0.f);
    //     return;
    // }
    for(Pipe& p : pipes){
        p.checkCollision(b);
    }
}