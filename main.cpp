#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include "ObjModel.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "MoveToComponent.h"
#include "RotateComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Timerf.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
ObjModel* model;
char modelPath[] = "models/world/world.obj";
double lastFrameTime = 0;
void init();
void update();
void draw();
void enableLight(bool state);

std::shared_ptr<GameObject> camera;

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);

    tigl::init();

    init();

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();


    return 0;
}

bool turning = false;

void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    camera = std::make_shared<GameObject>();
    camera->position = glm::vec3(-5.0f, 60.0f, -20.0f);
    camera->addComponent(std::make_shared<CameraComponent>(window));
    auto iets = glm::vec3(188, 20, -20);
    camera->addComponent(std::make_shared<MoveToComponent>(iets, 180));
    //camera->addComponent(std::make_shared<RotateComponent>());

    enableLight(true);

    model = new ObjModel(modelPath);

    Timerf *t = new Timerf(2000, &turning);
    t->startTimer();
}

void update()
{
    double frameTime = glfwGetTime();
    float deltaTime = frameTime - lastFrameTime;
    lastFrameTime = frameTime;
    
    
    if (turning) 
    {
        auto iets = glm::vec3(-170, 110, 150);
        camera->addComponent(std::make_shared<MoveToComponent>(iets, 270));
        turning = false;
    }
    
    camera->update(deltaTime);
}

void draw()
{
    glClearColor(186.f / 255, 174.f / 255, 145.f / 255, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 500.0f);

    auto cameraComponent = camera->getComponent<CameraComponent>();

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(cameraComponent->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(true);

    glEnable(GL_DEPTH_TEST);


    glPointSize(10.0f);
    model->draw();
}

void enableLight(bool state)
{
    if (state) {
        tigl::shader->enableLighting(true);
        tigl::shader->setLightCount(1);
        tigl::shader->setLightDirectional(0, false);
        tigl::shader->setLightPosition(0, glm::vec3(0, 25, 0));
        tigl::shader->setLightAmbient(0, glm::vec3(123.f / 255, 137.f / 255, 147.f / 255));
        tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
        tigl::shader->setLightSpecular(1, glm::vec3(225.f / 255, 159.f / 255, 0));
        tigl::shader->setShinyness(5.f);
    }
    else {
        tigl::shader->enableLighting(false);
    }
}