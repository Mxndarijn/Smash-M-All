#include "GUIManager.h"

#include <iostream>
#include <string>

#include "Camera.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "MoveToComponent.h"
#include "RotateComponent.h"
#include "Spawnpoint.h"

#define GUI_HEIGHT 400
#define GUI_WIDTH 400

Spawnpoint Spawnpoints[] = { Spawnpoint(glm::vec3(-140, 30, -170), 1), Spawnpoint(glm::vec3(-170, 110, 150), 270), Spawnpoint(glm::vec3(188, 20, -20), 180) };

GUIManager::GUIManager(bool& drawGUI, bool& drawEndGUI, irrklang::ISoundEngine* soundEngine, int& volume) : drawGUI(drawGUI), drawEndGUI(drawEndGUI), soundEngine(soundEngine), volume(volume)
{
}

GUIManager::~GUIManager()
{
	
}

void GUIManager::renderGUI(const std::shared_ptr<GameObject>& camera)
{
    createFrame();

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 guiSize = ImVec2(GUI_WIDTH, GUI_HEIGHT);
    ImVec2 windowSize = io.DisplaySize;

    // Bereken de positie van het midden van het scherm
    ImVec2 guiPosition = ImVec2((windowSize.x - guiSize.x) * 0.5f, (windowSize.y - guiSize.y) * 0.5f);

    ImGui::SetNextWindowPos(guiPosition);
    ImGui::SetNextWindowSize(guiSize);

    // GUI-opbouw
    ImGui::Begin("Mijn GUI", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    // Title
    ImGui::SetWindowFontScale(2.2f);
    ImGui::Text("");
    auto title = "Smash'm'all!";
    auto textWidth = ImGui::CalcTextSize(title).x;
    ImGui::SetCursorPosX((GUI_WIDTH - textWidth) * 0.5f);
    ImGui::Text(title);
    ImGui::Text("");

    //Play button
    ImGui::SetWindowFontScale(2.0f);
    ImVec2 buttonSize = ImVec2(GUI_WIDTH - 30, 80);
    ImGui::SetCursorPosX((GUI_WIDTH - buttonSize.x) * 0.5f);
    if (ImGui::Button("PLAY!", buttonSize))
    {
        // Actie wanneer er op de knop wordt geklikt
        std::cout << "De knop is geklikt!" << std::endl;
        camera->removeComponent<RotateComponent>();
        int pos = rand() % 3;
        auto i = Spawnpoints[pos];

        camera->addComponent(std::make_shared<MoveToComponent>(i.pos, i.rot, drawEndGUI));
        drawGUI = false;
    }

    ImGui::Text("");

    //ImGui::SetCursorPosX((GUI_WIDTH - buttonSize.x) * 0.5f);
    if (ImGui::SliderInt(" Volume", &volume, 0, 100))
    {
        soundEngine->setSoundVolume(static_cast<float>(volume) / 100);
    }

    ImGui::End();

    // ImGui-renderen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (drawGUI) return;

    //shutdown();
}

void GUIManager::renderEndGUI(const std::shared_ptr<GameObject>& camera, int score)
{
    createFrame();

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 guiSize = ImVec2(GUI_WIDTH, GUI_HEIGHT);
    ImVec2 windowSize = io.DisplaySize;

    ImVec2 guiPosition = ImVec2((windowSize.x - guiSize.x) * 0.5f, (windowSize.y - guiSize.y) * 0.5f);

    ImGui::SetNextWindowPos(guiPosition);
    ImGui::SetNextWindowSize(guiSize);

    ImGui::Begin("EndScreen", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

    ImGui::SetWindowFontScale(2.2f);
    ImGui::Text("");
    auto title = "Smash'm'all!";
    auto textWidth = ImGui::CalcTextSize(title).x;
    std::string sScore = std::to_string(score);
    const char* cScore = sScore.c_str();
    ImGui::SetCursorPosX((GUI_WIDTH - textWidth) * 0.5f);
    ImGui::Text(title);
    ImGui::Text("");
    ImGui::Text("Score:");
    ImGui::Text(cScore);

    ImGui::SetWindowFontScale(2.0f);
    ImVec2 buttonSize = ImVec2(GUI_WIDTH - 30, 80);
    ImGui::SetCursorPosX((GUI_WIDTH - buttonSize.x) * 0.5f);
    if (ImGui::Button("Restart", buttonSize))
    {
        // Actie wanneer er op de knop wordt geklikt
        std::cout << "De knop is geklikt!" << std::endl;
        auto i = Spawnpoints[rand() % 2];
        camera->addComponent(std::make_shared<MoveToComponent>(i.pos, i.rot, drawEndGUI));
        drawEndGUI = false;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (drawEndGUI) return;

    //shutdown();
}

void GUIManager::update()
{
	
}

void GUIManager::init(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330 core");
    setColors();
}

void GUIManager::shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUIManager::createFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUIManager::setColors()
{
    ImGui::StyleColorsDark();
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.01f, 0.01f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.14f, 0.92f);
    colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.43f, 0.43f, 0.43f, 0.39f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.69f, 0.47f, 0.47f, 0.40f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.64f, 0.41f, 0.41f, 0.69f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.54f, 0.27f, 0.27f, 0.83f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.63f, 0.32f, 0.32f, 0.87f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.80f, 0.40f, 0.40f, 0.20f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.55f, 0.40f, 0.40f, 0.80f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.25f, 0.30f, 0.60f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.40f, 0.40f, 0.30f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.80f, 0.40f, 0.40f, 0.40f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.80f, 0.39f, 0.39f, 0.60f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
    colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.39f, 0.39f, 0.60f);
    colors[ImGuiCol_Button] = ImVec4(0.74f, 0.17f, 0.17f, 0.62f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.39f, 0.39f, 0.79f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.86f, 0.09f, 0.09f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.81f, 0.23f, 0.23f, 0.45f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.80f, 0.14f, 0.14f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.92f, 0.08f, 0.08f, 0.80f);
    colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.90f, 0.70f, 0.70f, 1.00f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.10f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.78f, 0.78f, 0.60f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.78f, 0.82f, 1.00f, 0.90f);
    colors[ImGuiCol_Tab] = ImVec4(0.41f, 0.01f, 0.01f, 0.79f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.68f, 0.43f, 0.43f, 0.80f);
    colors[ImGuiCol_TabActive] = ImVec4(0.78f, 0.10f, 0.10f, 0.84f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.57f, 0.28f, 0.28f, 0.82f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.65f, 0.35f, 0.35f, 0.84f);
    colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.27f, 0.38f, 1.00f);
    colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.45f, 1.00f);
    colors[ImGuiCol_TableBorderLight] = ImVec4(0.26f, 0.26f, 0.28f, 1.00f);
    colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.90f, 0.45f, 0.45f, 0.80f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}