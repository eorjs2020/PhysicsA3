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
	ball->setShape(Ball);
}


void EndScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Simple 2D Collision Detection and Response", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	
	if (ImGui::Button("Start Scene"))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (ImGui::Button("Scene 1"))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}

	ImGui::Separator();
	
	if (ImGui::Button("Ball"))
	{
		ball->setShape(Ball);
	}
	if (ImGui::Button("Triangle"))
	{
		ball->setShape(Triangle);
	}
	if (ImGui::Button("Square"))
	{
		ball->setShape(Square);
	}
	

	ImGui::Separator();

	
	static float frictionloss = 0.2f;
	if (ImGui::SliderFloat("Wall Friction", &frictionloss, 0.0, 1.0))
	{
		ball->setFriction(frictionloss);
	}

	static float  massa = 1.0f;
	if (ImGui::SliderFloat("Ball Mass", &massa, 1.0, 40.0))
	{
		ball->setMass(massa);
	}
	static float  massb = 1.0f;
	if (ImGui::SliderFloat("Brick Mass", &massb, 1.0, 40.0))
	{
		player->setMass(massb);
	}

	ImGui::Separator();

	ImGui::Text("PPM is 1 meter per pixel");
	ImGui::Text("Velocity of ball in x = %.2f", ball->getRigidBody()->velocity.x);
	ImGui::Text("Velocity of ball in y = %.2f ", ball->getRigidBody()->velocity.y);
	ImGui::Text("Velocity of brick in x = %.2f ", player->getVector().x);
	ImGui::Text("Velocity of brick in y = %.2f ", player->getVector().y);


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}