#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "ParticleSystem.h"
#include "ParticleHandler.h"
#include "FPSManager.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Random.h"
#include "globals.h"
#include "Emitter.h"

unsigned int Window::width(1280);
unsigned int Window::height(720);
float Window::aspectRatio(((float)Window::width) / Window::height);
//int width = 1280, height = 720;
//float aspectRatio = ((float)width) / height;
Camera camera(-Window::aspectRatio, Window::aspectRatio, -1.0f, 1.0f);
float xpos, ypos;


// Test error function
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) 
{
    std::cout << "[OpenGL Error](" << type << ") " << message << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int Width, int Height)
{
    Window::width = Width;
    Window::height = Height;

    Window::aspectRatio = ((float)Window::width) / Window::height;
    float xSpan = 1; // Feel free to change this to any xSpan you need.
    float ySpan = 1; // Feel free to change this to any ySpan you need.

    if (Window::aspectRatio > 1) {
        // Width > Height, so scale xSpan accordinly.
        xSpan *= Window::aspectRatio;
    }
    else {
        // Height >= Width, so scale ySpan accordingly.
        ySpan = xSpan / Window::aspectRatio;
    }

    camera.SetProjMatrix(glm::ortho(-1 * xSpan, xSpan, -1 * ySpan, ySpan, -1.0f, 1.0f));

    // Use the entire window for rendering.
    glViewport(0, 0, Window::width, Window::height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double x, y; 
        glfwGetCursorPos(window, &x, &y);
        xpos = ((x / Window::width) * 2 - 1) * Window::aspectRatio;
        ypos = (y / Window::height) * -2 + 1;
        float rX = ((xpos/ Window::aspectRatio + 1.0f) / 2.0f) * Window::width;
        float rY = ((ypos - 1.0f) / -2.0f) * Window::height;
        std::cout << "Left mouse button pressed: (" << x << ", " << y << ")" << std::endl;
        std::cout << "Computed screen space: (" << rX << ", " << rY << ")" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) 
    {
       
    }

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) 
    {
        switch (key) 
        {
        }
    }

}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);



    /* Create a windowed mode window and its OpenGL context */
 
    window = glfwCreateWindow(Window::width, Window::height, "Particle System", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    glfwSwapInterval(0);
    unsigned int activeCount = 0;
    FPSManager FPSManagerObject(window, 60, 1.0, "Particle System", &activeCount);

  
    // Adjust viewport on resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Mouse button callback
    glfwSetMouseButtonCallback(window, mouse_button_callback); //register mouse click handling func 

    // Key Pressed callback
    glfwSetKeyCallback(window, key_callback); //register key button input
    

    if (glewInit() != GLEW_OK)
        std::cout << "Error: glewInit() failed!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    // Enable debug output
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(MessageCallback, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    Renderer renderer(0.1f, 0.1f, 0.1f, 1.0f);

    Random rng;
    rng.Init();

    std::string circleTexPath = "res/textures/CircleTex.png";
    std::string snowTexPath = "res/textures/snowflakeTex.png";
    
    Texture circleTex(circleTexPath);
    Texture snowTex(snowTexPath);

      
    ParticleSystem ps1(5000, circleTex); //fire
    ParticleSystem ps2(1000, circleTex); //rain
    ParticleSystem ps3(1000, circleTex); //steam
    ParticleSystem ps4(3000, snowTex); //snow
    //ParticleSystem ps3(30000, circleTex); //steam
   // ParticleSystem ps4(10000, snowTex); //snow
    ParticleHandler ph(15.0f, Window::width, Window::height);
   // ParticleSystem ps5(20000, t1); //fire2
   
    Emitter e1(ps1);
    Emitter e4(ps4);
    //Emitter e3(ps3);


    std::vector<ParticleSystem*> systems;
    systems.push_back(&ps1);
    systems.push_back(&ps2);
    systems.push_back(&ps3);
    systems.push_back(&ps4);
    //systems.push_back(&ps3);
    /*systems.push_back(&ps3);
    systems.push_back(&ps4);*/
    
    /*for (int i = 0; i < ps1.GetParticleCount(); i++)
    {
        glm::vec2 Position = glm::vec2(rng.Float(-Window::aspectRatio, Window::aspectRatio), rng.Float(-1.0f, 1.0f));
        glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(-0.05f, 0.05f));
        glm::vec3 Color = glm::vec3(1.0f, 0.0f, 0.0f);
        float Size = 0.01f;
        ps1.Emit({ Position, Velocity, Color, Size, 1000});
    }
    for (int i = 0; i < ps2.GetParticleCount(); i++)
    {
        glm::vec2 Position = glm::vec2(rng.Float(-Window::aspectRatio, Window::aspectRatio), rng.Float(-1.0f, 1.0f));
        glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(-0.05f, 0.05f));
        glm::vec3 Color = glm::vec3(1.0f, 1.0f, 0.0f);
        float Size = 0.01f;
        ps2.Emit({ Position, Velocity, Color, Size, 1000 });
    }*/
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        float timeStep = (float)FPSManagerObject.enforceFPS(false);
        /* Render here */
        renderer.Clear();



        //ph.NaiveCollision(ps1, ps2);
        //ph.BuildGrid(systems);
        ph.NDUGCollision2(systems);
        e1.SimulateFire({ 0.0f, -0.8f }, 400.0f, timeStep);
        e4.SimulateSnow({ -Window::aspectRatio, Window::aspectRatio }, 50.0f, timeStep);
        ps2.Update(timeStep);
        ps3.Update(timeStep);
        
    
        activeCount = 0;
        activeCount += ps1.numActive;
        activeCount += ps2.numActive; 
        activeCount += ps3.numActive;
        activeCount += ps4.numActive;

        ps1.OnRender(camera);
        ps2.OnRender(camera);
        ps3.OnRender(camera);
        ps4.OnRender(camera);
        //ps3.OnRender(camera);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    

    glfwTerminate();

    return 0;
}