#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Bullet.h"

PlayScene::PlayScene()
{
	PlayScene::start();

}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	TextureManager::Instance()->draw("background", 400, 300, 0, 255, true);

	if(EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}

	drawDisplayList();
	poolTemp->Draw();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update()
{
	updateDisplayList();
	poolTemp->Update();
	float const deltaTime = 1.f / 60.f;

	if (timer > deltaTime* poolTemp->getDelay()) {
		timer = 0;
		poolTemp->Spawn();
	}
	timer += deltaTime;

}

void PlayScene::clean()
{
	removeAllChildren();
}

void PlayScene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
			if(m_pPlayer->getTransform()->position.x > 26.5f)
				m_pPlayer->getTransform()->position += glm::vec2(-2, 0);
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
			if (m_pPlayer->getTransform()->position.x < 773.5f)
				m_pPlayer->getTransform()->position += glm::vec2(2, 0);
		}
		else
		{
			if (m_playerFacingRight)
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}
	

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}
}

void PlayScene::start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Background load
	TextureManager::Instance()->load("../Assets/textures/field.png", "background");
	
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);
	m_playerFacingRight = true;
	
	// Bullet Pool
	poolTemp = new BulletPool(10, m_pPlayer);
	

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas");
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 500.0f);
	addChild(m_pInstructionsLabel);
}


void PlayScene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Simple 2D Collision Detection", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	
	if (ImGui::Button("Start Scene"))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}
	
	if(ImGui::Button("Scene 2"))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	ImGui::Separator();

	static float gravity = 9.8f;
	if (ImGui::SliderFloat("Gravity in m/s^2", &gravity, 8.0f, 100.0f))
	{
		poolTemp->setgravity(gravity);
	}

	static int bulletAmount = 10;
	if (ImGui::SliderInt("Control amount of bullets falling", &bulletAmount, 10, 30))
	{
		poolTemp->reSize(bulletAmount);
	}
	
	static int DELAY = 50;
	if (ImGui::SliderInt("Time Delay", &DELAY, 1, 240))
	{
		poolTemp->setDelay(DELAY);
	}

	static int soundVolume = 10;
	if (ImGui::SliderInt("Control the sound volume", &soundVolume, 0, 50))
	{
		SoundManager::Instance().setAllVolume(soundVolume);
	}

	ImGui::Separator();
	ImGui::Text("PPM is 1 meter per pixel"); 
	ImGui::Text("Amount of bullets on screen = %.i ", poolTemp->getBulletActive());
	ImGui::Text("Amount of bullets off screen = %.i ", poolTemp->getBulletDeactive());
	ImGui::Text("Amount of bullets that hit player = %.i ", m_pPlayer->getAmountHit());
	if (poolTemp->getBulletActive() > 0 ) {
		ImGui::Text("Velocity of the bullet with a box around it in the y direction = %.2f", poolTemp->getbullet()[0]->getRigidBody()->velocity.y);
	}
	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}