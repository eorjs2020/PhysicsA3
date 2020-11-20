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
	void setFriction(float x);
	std::vector<glm::vec2> locationVerTri, locationVerSqu, locationVerHex, screenBoundry;

private:
	void lineCheckAgainstScreenBoundry(std::vector<glm::vec2> a, int b, float c, float d);
	int shapeChoice;
	float accelX, accelY;
	float friction;
	glm::vec2 triDim, squDim, hexDim; 
	
};

#endif