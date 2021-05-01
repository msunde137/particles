// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include "confetti.h"

using namespace std;
using namespace agl;
using namespace glm;

void Confetti::createParticles(int size) 
{
	for (int i = 0; i < size; i++)
	{
		vec3 vel = random_unit_sphere() * .5f;
		vec3 pos = random_unit_cube();
		vec3 acc = vec3(0,-.5,0);
		//if (vel.x < 0) __debugbreak();
		float lifetime = random_float(5, 10);
		vec4 col = vec4(random_vec3(), 1.0f);
		Particle p = { pos, vec3(0.25f), vel, acc, col, lifetime };
		mParticles.push_back(p);
	}
}

void Confetti::update(float dt)
{
	// update particles
	for (int i = 0; i < mParticles.size(); i++)
	{
		Particle& p = mParticles[i];

		// death condition
		p.age += dt;
		if (p.age > p.lifetime && p.lifetime > 0)
		{
			p.color += glm::vec4(1, 1, 1, -1) * dt;
			p.color = glm::clamp(p.color, 0.0f, 1.0f);
			p.scale += glm::vec3(-1, -1, -1) * dt;
			p.scale = glm::clamp(p.scale, 0.0f, 1.0f);
			if (near_zero(p.color.w) && near_zero(p.scale))
			{
				mParticles.erase(mParticles.begin() + i);
				createParticles(1);
			}
		}

		// bounding box
		float box = 1;
		vec3 newpos = p.position + glm::normalize(p.velocity) * dt * .1f;
		newpos = vec3(0);
		if (p.position.x + newpos.x > box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(-1, 0, 0));
		}
		else if (p.position.x + newpos.x < -box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(1, 0, 0));
		}
		if (p.position.y + newpos.y > box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(0, -1, 0));
		}
		else if (p.position.y + newpos.y < -box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(0, 1, 0));
		}
		if (p.position.z + newpos.z > box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(0, 0, -1));
		}
		else if (p.position.z + newpos.z < -box)
		{
			p.velocity = glm::reflect(p.velocity, vec3(0, 0, 1));
		}
		
		// movement
		p.position += p.velocity * dt;
		p.velocity += p.acceleration * dt;
		mat4 pos = glm::translate(glm::mat4(1), p.position);
		mat4 scl = glm::scale(glm::mat4(1), p.scale);
		p.transform = pos * scl;
	}
	if (mParticles.size() == 0)
	{
		createParticles(50);
	}
}

