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
    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i] = Pipe(i);
        pipes[i].init();
    }
  
	ground = Model();
	ground.LoadModel("flappy/ground");
	ceiling = Model();
	ceiling.LoadModel("flappy/ground");
}

void Arena::update()
{
    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i].update();
    }
}

void Arena::render(GLuint uniformModel, GLuint uniformSpecularIntensity, GLuint uniformShininess)
{
    glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, game_arena_floor_y + .5f, 0.0f));
	model = glm::scale(model, glm::vec3(1.f, 1.f, 10.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//dirtTexture.UseTexture();
	//shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
	ground.RenderModel();

	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, game_arena_ceiling_y+1.f+0.302665f, 0.0f));
	model = glm::scale(model, glm::vec3(1.f, 1.f, 10.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//dirtTexture.UseTexture();
	//dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
    ceiling.RenderModel();

    for(size_t i = 0; i < game_arena_nb_pipes; i++){
        pipes[i].render(uniformModel, uniformSpecularIntensity, uniformShininess);
    }
}