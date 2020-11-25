#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "BulletPool.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;


private:
	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	float timer;
	Player* m_pPlayer;
	bool m_playerFacingRight;
	BulletPool* poolTemp;
	// UI Items
	Label* m_pInstructionsLabel;
	int delay;

};

#endif /* defined (__PLAY_SCENE__) */