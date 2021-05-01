// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "myparticlesystem.h"

using namespace std;
using namespace agl;
using namespace glm;

void MyParticleSystem::createParticles(int size) 
{
   for (int i = 0; i < size; i++)
   {
	   vec3 vel = random_unit_sphere() * random_float(.9f, 1.0f);
	   vec3 acc(0, -9.8, 0);
	   vec4 col = vec4(random_vec3(), 1.0f);
	   float mass = random_float(.8f, 1.0f);
	   Particle p = { vec3(0,0,0), vec3(1,1,1), vel * 50.0f, acc, col, 0, mass };
	   mParticles.push_back(p);
   }
}

void MyParticleSystem::update(float dt)
{
	// update particles
	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle& p = mParticles[i];
		p.age += dt;

		if (p.age > 0.5f)
		{
			p.color += glm::vec4(1, 1, 1, -.5f) * dt * .3f;
			p.color = glm::clamp(p.color, 0.0f, 1.0f);
			p.scale += glm::vec3(-1, -1, -1) * dt * .3f;
			p.scale = glm::clamp(p.scale, 0.0f, 1.0f);
			if (near_zero(p.color.w) || near_zero(p.scale))
			{
				mParticles.erase(mParticles.begin() + i);
			}
		}
		else
		{
		}
		p.position += p.velocity * dt;
		p.velocity += p.acceleration * dt;
		p.velocity += -p.velocity * dt * 3.0f * p.mass;

		mat4 pos = glm::translate(glm::mat4(1), p.position);
		mat4 scl = glm::scale(glm::mat4(1), p.scale);
		p.transform = pos * scl;

		if (mParticles.size() == 0)
		{
			this->createParticles(200);
		}
	}
}

