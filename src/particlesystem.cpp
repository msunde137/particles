#include "particlesystem.h"
#include "AGLM.h"

using namespace glm;
using namespace std;
using namespace agl;

ParticleSystem::ParticleSystem()
{
    mBlendMode = ADD;
    mTexture = -1;
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::init(std::shared_ptr<Renderer> renderer, int size)
{
    mRenderer = renderer;
    mTexture = mRenderer->loadTexture("../textures/particle.png");
    createParticles(size);
}

void ParticleSystem::draw()
{
    //calculate camera frame
    vec4 fa = vec4(glm::cross(mRenderer->viewDirection(), mRenderer->viewUp()), 0);
    vec4 fb = vec4(mRenderer->viewUp(), 0);
    vec4 fc = vec4(-mRenderer->viewDirection(), 0);
    mat4 frame(fa, fb, fc, vec4(0, 0, 0, 1));
    mRenderer->begin(mTexture, mBlendMode);
    for (int i = 0; i < mParticles.size(); i++)
    {
        Particle particle = mParticles[i];
        mRenderer->quad(particle.transform * frame, particle.color);
    }
    mRenderer->end();
}
