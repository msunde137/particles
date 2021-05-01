// Bryn Mawr College, alinen, 2020
//

#include "AGL.h"
#include "AGLM.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include "confetti.h"
#include "renderer.h"

using namespace std;
using namespace glm;
using namespace agl;

static std::shared_ptr<Renderer> theRenderer;

// camera controls
vec2 mousepos;
vec2 dmousepos;
float rotSpd = .1;
float zoomSpd = .1;
float panSpd = .1;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_0:
            theRenderer->lookTo(vec3(0, 0, -1), vec3(0, 0, 1), vec3(0, 1, 0)); return;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE); return;
        }
    }
    else
    {
        switch (key)
        {
        }
    }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
   // Prevent a divide by zero
   if (height == 0) height = 1;

   // Set Viewport to window dimensions
   glViewport(0, 0, width, height);
   theRenderer->perspective(radians(60.0f), (float)width / (float)height, 0.1f, 100.0f);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    vec3 eye = theRenderer->viewPosition();
    vec3 forward = theRenderer->viewDirection();
    vec3 up = theRenderer->viewUp();
    float dir = yoffset;
    vec3 dirvec = glm::normalize(eye) * dir * zoomSpd;
    if (length(dirvec) < length(eye) || dir > 0) eye = eye + dirvec;
    theRenderer->lookTo(eye, forward, up);
    std::cout << glm::length(eye) << ", " << glm::length(dirvec) << std::endl;
} 

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    vec3 eye = theRenderer->viewPosition();
    vec3 forward = theRenderer->viewDirection();
    vec3 up = theRenderer->viewUp();
    if (state == GLFW_PRESS)
    {
        dmousepos = glm::normalize(mousepos - vec2(xpos, ypos));
        mousepos = vec2(xpos, ypos);
        int keyPress = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);
        if (keyPress == GLFW_PRESS)
        {
            //vec3 mv = (up * -dmousepos.y + glm::cross(glm::normalize(eye), up) * -dmousepos.x) * panSpd;
            //eye = eye + mv;
            //theRenderer->lookTo(eye, forward, up);
        }
        else
        {
            // horizontal rotation
            float hozdir = dmousepos.x > 0 ? 1 : dmousepos.x < 0 ? -1 : 0;
            float hozang = rotSpd * hozdir;
            mat4 hozrot = glm::rotate(mat4(1), hozang, vec3(0, 1, 0));
            eye = vec3(hozrot * vec4(eye, 0.0f));
            up = vec3(hozrot * vec4(up, 0.0f));
            forward = vec3(hozrot * vec4(forward, 0.0f));

            // vertical rotation
            vec3 axis = glm::normalize(glm::cross(up,forward));
            float vertdir = dmousepos.y > 0 ? -1 : dmousepos.y < 0 ? 1 : 0;
            float vertang = rotSpd * vertdir;
            eye = vec3(glm::rotate(mat4(1), vertang, axis) * vec4(eye, 0.0f));
            up = glm::cross(axis, glm::normalize(eye));
            forward = glm::cross(axis, up);
        }
        theRenderer->lookTo(eye, forward, up);
    }
    else if (state == GLFW_RELEASE)
    {
    }
    dmousepos = vec2(0);
}

int main(int argc, char** argv)
{
   GLFWwindow* window;

   if (!glfwInit())
   {
      return -1;
   }

   // Explicitly ask for a 4.0 context 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   /* Create a windowed mode window and its OpenGL context */
   float width = 500;
   float height = 500;
   window = glfwCreateWindow(width, height, "Billboard Viewer", NULL, NULL);
   if (!window)
   {
      glfwTerminate();
      return -1;
   }

   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, key_callback);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
   glfwSetMouseButtonCallback(window, mouse_button_callback);
   glfwSetScrollCallback(window, scroll_callback);
   glfwSetCursorPosCallback(window, cursor_position_callback);

#ifndef APPLE
   if (glewInit() != GLEW_OK)
   {
      cout << "Cannot initialize GLEW\n";
      return -1;
   }
#endif

   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glClearColor(.5, .5, .6, 1);
   glClearColor(0,0,0, 1);
   theRenderer = std::make_shared<Renderer>();
   theRenderer->init("../shaders/billboard.vs", "../shaders/billboard.fs");
   GLuint imageId = theRenderer->loadTexture("../textures/particle.png");
   theRenderer->perspective(radians(30.0f), 1.0f, 0.1f, 200.0f);
   theRenderer->lookTo(vec3(0, 0, -10), vec3(0, 0, 1), vec3(0, 1, 0));

   Confetti theSystem;
   theSystem.init(theRenderer, 100);
   float lastTime = glfwGetTime();
   while (!glfwWindowShouldClose(window))
   {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers

      float dt = glfwGetTime() - lastTime;
      lastTime = glfwGetTime();

      theSystem.update(dt);
      theSystem.draw();

      // Swap front and back buffers
      glfwSwapBuffers(window);

      // Poll for and process events
      glfwPollEvents();
   }

   glfwTerminate();
   return 0;
}
