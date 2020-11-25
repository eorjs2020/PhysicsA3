#include "Scene2.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"
#include "ShapeForSence2.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"


EndScene::EndScene()
{
	EndScene::start();
}

EndScene::~EndScene()
= default;

void EndScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);
	drawDisplayList();
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void EndScene::update()
{
	updateDisplayList();
	player->getTransform()->position = EventManager::Instance().getMousePosition();
	
}

void EndScene::clean()
{
	removeAllChildren();
}

void EndScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

}

void EndScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/field.png", "background");
	// Set GUI Title
	m_guiTitle = "Play Scene";

	//Player 
	player = new Ship();
	addChild(player);

	//Ball sprite
	ball = new BounchingBall(player); 
	addChild(ball);

}


void EndScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Your Window Title Goes Here", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Scene 1"))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	ImGui::Separator();

	if (ImGui::Button("Triangle"))
	{
		ball->setShape(Triangle);
	}
	if (ImGui::Button("Square"))
	{
		ball->setShape(Square);
	}
	if (ImGui::Button("Hexagon"))
	{
		ball->setShape(Ball);
	}

	ImGui::Separator();

	static float float3[3] = { 0.0f, 1.0f, 1.5f };
	if (ImGui::SliderFloat3("My Slider", float3, 0.0f, 2.0f))
	{
		std::cout << float3[0] << std::endl;
		std::cout << float3[1] << std::endl;
		std::cout << float3[2] << std::endl;
		std::cout << "---------------------------\n";
	}
	static float frictionloss = 0.2f;
	if (ImGui::SliderFloat("Wall Friction", &frictionloss, 0.0, 1.0))
	{
		ball->setFriction(frictionloss);
	}
	ImGui::Separator();

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}