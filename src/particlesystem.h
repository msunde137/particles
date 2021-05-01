#ifndef ParticleSystem_H_
#define ParticleSystem_H_

#include "AGL.h"
#include "image.h"
#include "renderer.h"
#include <vector>

namespace agl {

    struct Particle {
        // initial values
        glm::mat4 itransform;
        glm::vec3 ivelocity;
        glm::vec3 iacceleration;
        glm::vec4 icolor;
        float lifetime;
        // current values
        glm::mat4 transform;
        glm::vec3 velocity;
        glm::vec3 acceleration;
        glm::vec4 color;
        glm::vec3 scale, position;

        float mass;
        float age;
        Particle(glm::vec3 pos = glm::vec3(0), glm::vec3 scl = glm::vec3(1),
            glm::vec3 vel = glm::vec3(0), glm::vec3 acc = glm::vec3(0),
            glm::vec4 col = glm::vec4(1), float life = 0, float mass = 1)
            : position{ pos }, scale{ scl }, ivelocity{ vel }, 
            iacceleration{ acc }, icolor{ col }, lifetime{ life }, mass{ mass }
        {
            itransform = glm::translate(glm::mat4(1), pos) * glm::scale(glm::mat4(1), scale);
            transform = itransform;
            velocity = vel;
            acceleration = acc;
            color = col;
            age = 0.0f;
        }

    };

   class ParticleSystem {
   public:
      ParticleSystem();
      virtual ~ParticleSystem();

      void init(std::shared_ptr<Renderer> renderer, int size);
      virtual void update(float dt) = 0;
      virtual void draw();
      
   protected:
      virtual void createParticles(int size) = 0;

   protected:

      std::vector<Particle> mParticles;
      GLuint mTexture;
      BlendMode mBlendMode;
      std::shared_ptr<Renderer> mRenderer;
   };
}
#endif