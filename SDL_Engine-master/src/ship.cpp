#include "ship.h"
#include "glm/gtx/string_cast.hpp"
#include "PlayScene.h"
#include "TextureManager.h"
#include "Util.h"
#include "EventManager.h"


Ship::Ship() : m_maxSpeed(10.0f)
{
	TextureManager::Instance()->load("../Assets/textures/brick.png","brick");

	auto size = TextureManager::Instance()->getTextureSize("brick");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(SHIP);
	
	m_currentHeading = 0.0f; // current facing angle
	m_currentDirection = glm::vec2(1.0f, 0.0f); // facing right
	m_turnRate = 5.0f; // 5 degrees per frame


	glm::vec2 a = { 2, 2 }, b = { 2, 37 }, c = { 65, 37 }, d = { 65, 2 };
	vertexPoints.push_back(a);
	vertexPoints.push_back(b);
	vertexPoints.push_back(c);
	vertexPoints.push_back(d);
	mass = 1;
}


Ship::~Ship()
= default;

void Ship::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TextureManager::Instance()->draw("brick", x, y, m_currentHeading, 255, true);

	//Update vertex coords 
	vertexPoints[0] = { this->getTransform()->position.x - 34, this->getTransform()->position.y + 20 };
	vertexPoints[1] = { this->getTransform()->position.x + 34, this->getTransform()->position.y + 20 };
	vertexPoints[2] = { this->getTransform()->position.x + 34, this->getTransform()->position.y - 20 };
	vertexPoints[3] = { this->getTransform()->position.x - 34, this->getTransform()->position.y - 20 };

}


void Ship::update()
{
	const float deltaTime = 1.f / 60.f;
	if (a == 1) {
		getTransform()->position = EventManager::Instance().getMousePosition();
		a = 0;
	}
	
	if (pointCheck == 4)
		positionVector = getTransform()->position;
	
	if (pointCheck == 12)
		pointCheck = 2;
	
	++a; ++pointCheck;
}

void Ship::clean()
{
}

void Ship::turnRight()
{
	m_currentHeading += m_turnRate;
	if (m_currentHeading >= 360) 
	{
		m_currentHeading -= 360.0f;
	}
	m_changeDirection();
}

void Ship::turnLeft()
{
	m_currentHeading -= m_turnRate;
	if (m_currentHeading < 0)
	{
		m_currentHeading += 360.0f;
	}

	m_changeDirection();
}

void Ship::moveForward()
{
	getRigidBody()->velocity = m_currentDirection * m_maxSpeed;
}

void Ship::moveBack()
{
	getRigidBody()->velocity = m_currentDirection * -m_maxSpeed;
}

void Ship::giveMomentum()
{

}

void Ship::move()
{
	getTransform()->position += getRigidBody()->velocity;
	getRigidBody()->velocity *= 0.9f;
}

glm::vec2 Ship::getTargetPosition() const
{
	return m_targetPosition;
}

glm::vec2 Ship::getCurrentDirection() const
{
	return m_currentDirection;
}

float Ship::getMaxSpeed() const
{
	return m_maxSpeed;
}

void Ship::setTargetPosition(glm::vec2 newPosition)
{
	m_targetPosition = newPosition;

}

void Ship::setCurrentDirection(glm::vec2 newDirection)
{
	m_currentDirection = newDirection;
}

void Ship::setMaxSpeed(float newSpeed)
{
	m_maxSpeed = newSpeed;
}

void Ship::setMass(float a)
{
	mass = a;
}

glm::vec2 Ship::getVector()
{
	
	float temp = sqrt(pow(getTransform()->position.x - positionVector.x, 2) + pow(getTransform()->position.y - positionVector.y, 2));
	float tempX = getTransform()->position.x - positionVector.x;
	float tempY = getTransform()->position.y - positionVector.y;
	float velX, velY;
	if (pointCheck - 2 == 0 ){
		 velX = tempX / ( 2 / 2);
		 velY = tempY / (2 / 2);
	}
	else {
		velX = tempX / (pointCheck - 2 / 2);
		velY = tempY / (pointCheck - 2 / 2);
	}
	return glm::vec2(velX, velY);
}

float Ship::getMass()
{
	return mass;
}



void Ship::m_checkBounds()
{

	if (getTransform()->position.x > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(0.0f, getTransform()->position.y);
	}

	if (getTransform()->position.x < 0)
	{
		getTransform()->position = glm::vec2(800.0f, getTransform()->position.y);
	}

	if (getTransform()->position.y > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.0f);
	}

	if (getTransform()->position.y < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 600.0f);
	}

}

void Ship::m_reset()
{
	getRigidBody()->isColliding = false;
	const int halfWidth = getWidth() * 0.5f;
	const auto xComponent = rand() % (640 - getWidth()) + halfWidth + 1;
	const auto yComponent = -getHeight();
	getTransform()->position = glm::vec2(xComponent, yComponent);
}

void Ship::m_changeDirection()
{
	const auto x = cos(m_currentHeading * Util::Deg2Rad);
	const auto y = sin(m_currentHeading * Util::Deg2Rad);
	m_currentDirection = glm::vec2(x, y);

	glm::vec2 size = TextureManager::Instance()->getTextureSize("ship");
}

