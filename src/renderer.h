#ifndef Renderer_H_
#define Renderer_H_

#include "AGL.h"
#include "AGLM.h"
#include "image.h"
#include <string>

namespace agl {
   enum BlendMode {DEFAULT, ADD, ALPHA};
   struct Quad
   {
       glm::mat4 transform;
       glm::vec4 color;
   };

   class Renderer
   {
   public:
      Renderer();
      virtual ~Renderer();

      void draw();
      virtual void init(const std::string& vertex, const std::string& fragment);
      virtual GLuint loadTexture(const std::string& imageName);
      virtual void perspective(float fovRadians, float aspect, float near, float far); 
      virtual void ortho(float minx, float maxx, float miny, float maxy, float minz, float maxz); 
      virtual void lookTo(const glm::vec3& lookfrom, const glm::vec3& lookat, const glm::vec3& up);

      virtual void begin(GLuint textureId, BlendMode mode);
      virtual void quad(const glm::mat4& transf, const glm::vec4& color);
      virtual void end();

      virtual bool initialized() const { return mInitialized; }
      glm::vec3 viewPosition() const { return mLookFrom; }
      glm::vec3 viewDirection() const { return mLookTo; }
      glm::vec3 viewUp() const { return mUp; }

   protected:

      virtual void blendMode(BlendMode mode);
      GLuint loadShader(const std::string& vertex, const std::string& fragment);
      std::string loadShaderFromFile(const std::string& fileName);

   protected:
       // todo: list of shaders
      GLuint mShaderId;
      GLuint mVboPosId;
      GLuint mVaoId;
      glm::mat4 mProjectionMatrix;
      glm::mat4 mViewMatrix;
      glm::vec3 mLookFrom, mLookTo, mUp;
      bool mInitialized;
      std::vector<Quad> mQuads;
   };
}

#endif
