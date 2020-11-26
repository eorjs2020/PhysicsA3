#pragma once
#ifndef __SHIP__
#define __SHIP__

#include "DisplayObject.h"
#include "TextureManager.h"
#include <array>

class Ship final : public DisplayObject
{
public:
	Ship();
	~Ship();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void turnRight();
	void turnLeft();
	void moveForward();
	void moveBack();
	void giveMomentum();
	void move();

	// getters
	glm::vec2 getTargetPosition() const;
	glm::vec2 getCurrentDirection() const;
	float getMaxSpeed() const;
	glm::vec2 getVector();

	// setters
	void setTargetPosition(glm::vec2 newPosition);
	void setCurrentDirection(glm::vec2 newDirection);
	void setMaxSpeed(float newSpeed);
	
	std::vector<glm::vec2> vertexPoints;
private:
	void m_checkBounds();
	void m_reset();

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;
	int a = 0;
	void m_changeDirection();
	float m_currentHeading;
	int pointCheck;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
	glm::vec2 positionVector;
};


#endif /* defined (__SHIP__) */

