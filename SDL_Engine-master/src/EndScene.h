#pragma once
#ifndef __END_SCENE__
#define __END_SCENE__

#include "Scene.h"
#include "Label.h"
#include "Button.h"
#include "BounchingBall.h"

class EndScene final : public Scene
{
public:
	EndScene();
	~EndScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	BounchingBall* ball; 

	// IMGUI Function
	void GUI_Function() const;
	std::string m_guiTitle;

};

#endif /* defined (__END_SCENE__) */