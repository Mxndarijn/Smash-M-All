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
#include "RayCastComponent.h"

#include <irrKlang.h>
#pragma comment(lib, "irrKlang.lib")

#include "Camera.h"
#include "ModelComponent.h"
#include "HUDComponent.h"
#include "Timerf.h"
#include <random>

#include "GUIManager.h"
#include "Spawnpoint.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "PlayerComponent.h"
#include "Webcam.h"
#include "GameManager.h"
#include "stb_image.h"


#define CAMERA_SPAWN glm::vec3(-5.0f, 60.0f, -20.0f);
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
GUIManager* guiManager;
GameManager* gameManager;
Webcam* webcam;
std::vector<ObjModel*> models;

double lastFrameTime = 0;
bool drawGui = true;
bool drawEndScreen = false;
bool turning = false;
int volume = 100;
int spawnPointIndex = 0;
bool cameraMoving = false;

void init();
void update();
void draw();
void enableLight(bool state);
void enableFog(bool state);
void renderEndGUI();
void renderGUI();
void setColorGui();
void setWindowIcon(GLFWwindow* window, const char* filename);

std::list<std::shared_ptr<GameObject>> objects;
std::shared_ptr<GameObject> camera;
irrklang::ISoundEngine* soundEngine;
glm::mat4 projection;

// Callback for screen resizer
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    // Voer eventuele andere logica uit op basis van de nieuwe venstergrootte
}

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Smash \'m all", NULL, NULL);
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
        glfwPollEvents();
        update();
        draw();

        if (drawGui)
        {
           guiManager->renderGUI(camera);
        }
        if (drawEndScreen)
        {
            guiManager->renderEndGUI(window, camera, gameManager->score, lives);
        }   

        glfwSwapBuffers(window);

        gameManager->despawnEnemies();
    }

    glfwTerminate();
    return 0;
}


void init()
{
    // Set the icon of the window
    setWindowIcon(window, "resources/icon/icon.png");

    // Initialising of soundEngine
    soundEngine = irrklang::createIrrKlangDevice();
    soundEngine->setSoundVolume(static_cast<float>(volume) / 100);
    irrklang::ISoundSource* soundSource = soundEngine->addSoundSourceFromFile("sounds/mariotheme.mp3");

    srand(time(nullptr));

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    models.push_back(new ObjModel("models/world/world.obj"));
    models.push_back(new ObjModel("models/up/mario_1up.obj"));
    models.push_back(new ObjModel("models/goomba/Goomba_Mario.obj"));
    models.push_back(new ObjModel("models/boo/Boo_Mario.obj"));
    models.push_back(new ObjModel("models/bulletbill/Bullet_Bill_Mario.obj"));

    gameManager = new GameManager(objects, models, camera);
    gameManager->init();

    guiManager = new GUIManager(drawGui, drawEndScreen, soundEngine, volume, &gameManager->enableEnemySpawn);

    guiManager->init(window);

    camera = std::make_shared<GameObject>();
    camera->position = CAMERA_SPAWN
    camera->addComponent(std::make_shared<CameraComponent>(window));
    camera->addComponent(std::make_shared<RotateComponent>());

    webcam = new Webcam(window);
    auto hudComponent = std::make_shared<HUDComponent>(window, webcam, "resources/textures/");
    camera->addComponent(hudComponent);

    auto rayCastComponent = std::make_shared<RayCastComponent>(
        webcam->getResolution(),
        &projection,
        webcam->getPoints()
    );
    camera->addComponent(rayCastComponent);

    enableLight(true);
    enableFog(true);
    irrklang::ISound* sound = soundEngine->play2D(soundSource, false, false, true);
}

void update()
{
    double frameTime = glfwGetTime();
    float deltaTime = frameTime - lastFrameTime;
    lastFrameTime = frameTime;

    camera->update(deltaTime);

    for (const auto& object : objects)
    {
        object->update(deltaTime);
    }

    gameManager->update(drawEndScreen);
}

void draw()
{
    glClearColor(186.f / 255, 174.f / 255, 145.f / 255, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    projectionMatrix = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 500.0f);

    auto cameraComponent = camera->getComponent<CameraComponent>();

    tigl::shader->setProjectionMatrix(projectionMatrix);
    tigl::shader->setViewMatrix(cameraComponent->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(true);

    glEnable(GL_DEPTH_TEST);

    glPointSize(10.0f);

    for (auto& o : objects)
    {
        o->draw();
    }

    camera->getComponent<HUDComponent>()->draw();

    camera->getComponent<RayCastComponent>()->lines.clear();
}

void setWindowIcon(GLFWwindow* window, const char* filename) {
    GLFWimage icon;
    int width, height, numChannels;
    unsigned char* imageData = stbi_load(filename, &width, &height, &numChannels, 0);
    if (!imageData) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return;
    }

    icon.width = width;
    icon.height = height;
    icon.pixels = imageData;

    glfwSetWindowIcon(window, 1, &icon);

    // Free the image data
    stbi_image_free(imageData);
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

void enableFog(bool state)
{
    if (state) {
        tigl::shader->enableFog(true);
        tigl::shader->setFogLinear(1, 4);
        tigl::shader->setFogColor(glm::vec3(186.f / 255, 174.f / 255, 145.f / 255));
        tigl::shader->setFogExp(.0025f);
    }
    else {
        tigl::shader->enableFog(false);
    }
}