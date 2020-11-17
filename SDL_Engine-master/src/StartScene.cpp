#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	}
}

void StartScene::start()
{
	const SDL_Color blue = { 0, 0, 255, 255 };
	m_pStartLabel = new Label("Team members", "Consolas", 80, blue, glm::vec2(400.0f, 40.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pInstructionsLabel = new Label("Daekoen Lee - 101076401", "Consolas", 40, blue, glm::vec2(400.0f, 120.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel = new Label("Michael Shular - 101273089", "Consolas", 40, blue, glm::vec2(400.0f, 160.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Scene 2 Button
	m_pScene1Button = new Button();
	m_pScene1Button->getTransform()->position = glm::vec2(400.0f, 400.0f);

	m_pScene1Button->addEventListener(CLICK, [&]()-> void
	{
			m_pScene1Button->setActive(false);
		TheGame::Instance()->changeSceneState(PLAY_SCENE);
	});
	
	m_pScene1Button->addEventListener(MOUSE_OVER, [&]()->void
	{
			m_pScene1Button->setAlpha(128);
	});

	m_pScene1Button->addEventListener(MOUSE_OUT, [&]()->void
	{
			m_pScene1Button->setAlpha(255);
	});
	addChild(m_pScene1Button);

	// Scene 2 Button
	m_pScene2Button = new Button("../Assets/textures/nextButton.png", "nextButton", NEXT_BUTTON);
	m_pScene2Button->getTransform()->position = glm::vec2(400.0f, 500.0f);

	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(END_SCENE);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(128);
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
		});
	addChild(m_pScene2Button);

	
}

