#pragma once

#ifndef __BOUNCHINGBALL__
#define __BOUNCHINGBALL__

#include "PlayerAnimationState.h"
#include "Sprite.h"

class BounchingBall : public Sprite
{
public:
	BounchingBall();
	~BounchingBall();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void setShape(int a); 
	
	std::vector<glm::vec2> locationOfVertexPoints;

private:
	int shapeChoice;
	float x, y;
};

#endif