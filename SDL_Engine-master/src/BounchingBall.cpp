#include "BounchingBall.h"
#include "TextureManager.h"

BounchingBall::BounchingBall() : accelX(100), accelY(100)
{
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "shape0");
	TextureManager::Instance()->load("../Assets/textures/tile.png", "shape1");
	TextureManager::Instance()->load("../Assets/textures/hexagon.png", "shape2");
	
	getTransform()->position = glm::vec2(300, 30);
	friction = 0.2f;
	shapeChoice = 0;
	//Triangle vertext into the vector
	glm::vec2 a = { 0, 40 }, b = { 40, 35 }, c = { 20, 0 }, d , e, f;
	locationOfVertexPoints.push_back(a);
	locationOfVertexPoints.push_back(b);
	locationOfVertexPoints.push_back(c);
	//Square vertext into the vectorvertext into the vector
	a = { 0,0 }, b = { 0, 40 }, c = { 40, 40 }, d = { 40, 0 };
	locationOfVertexPoints.push_back(a);
	locationOfVertexPoints.push_back(b);
	locationOfVertexPoints.push_back(c);
	locationOfVertexPoints.push_back(d);
	//Hexagon vertext into the vector
	a = { 0, 25 }, b = { 14, 50 }, c = { 43, 50 }, d = { 58, 25 }, e = { 14, 0 }, f = { 43, 0 };
	locationOfVertexPoints.push_back(a);
	locationOfVertexPoints.push_back(b);
	locationOfVertexPoints.push_back(c);
	locationOfVertexPoints.push_back(d);
	locationOfVertexPoints.push_back(e);
	locationOfVertexPoints.push_back(f);
	
}

BounchingBall::~BounchingBall()
{
}

void BounchingBall::draw()
{
	auto x = getTransform()->position.x;
	auto y = getTransform()->position.y;
	switch (shapeChoice)
	{
	case 0:
		TextureManager::Instance()->draw("shape0", x, y, 0.f, 255, true);
		break;
	case 1:
		TextureManager::Instance()->draw("shape1", x, y, 0.f, 255, true);
		break;
	case 2:
		TextureManager::Instance()->draw("shape2", x, y, 0.f, 255, true);
		break;
	default:
		break;
	}
}

void BounchingBall::update()
{
	const float deltaTime = 1.f / 60.f;
	getRigidBody()->acceleration = glm::vec2(accelX, accelY);
	getRigidBody()->velocity = getRigidBody()->acceleration;
	getTransform()->position += getRigidBody()->velocity * deltaTime;

	if (getTransform()->position.x > 800)
	{
		getTransform()->position = glm::vec2(800, getTransform()->position.y);
		accelX *= -(1 - friction);
		accelY *= (1 - friction);
		
	}

	if (getTransform()->position.x < 0) {
		
		getTransform()->position = glm::vec2(0, getTransform()->position.y);
		accelX *= -(1-friction);
		accelY *= (1 - friction);
	}

	if (getTransform()->position.y > 600) {
		
		getTransform()->position = glm::vec2(getTransform()->position.x, 600);
		accelX *= (1 - friction);
		accelY *= -(1 - friction);
		std::cout << accelY;
	}

	if (getTransform()->position.y < 0) {
		getTransform()->position = glm::vec2(getTransform()->position.x, 0);
		accelX *= (1 - friction);
		accelY *= -(1 - friction);
	}



}

void BounchingBall::clean()
{
}

void BounchingBall::setShape(int a)
{
	shapeChoice = a;
}

void BounchingBall::setFriction(float x)
{
	friction = x;
}
