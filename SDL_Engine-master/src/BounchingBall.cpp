#include "BounchingBall.h"
#include "TextureManager.h"

BounchingBall::BounchingBall()
{
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "shape0");
	TextureManager::Instance()->load("../Assets/textures/tile.png", "shape1");
	TextureManager::Instance()->load("../Assets/textures/hexagon.png", "shape2");
	x = y = 10;
}

BounchingBall::~BounchingBall()
{
}

void BounchingBall::draw()
{
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
	/*switch (shapeChoice)
	{
	case 0:
		glm::vec2 a = { 0, 40 }, b = { 40, 35 }, c = {20, 0}; 
		locationOfVertexPoints; 
		break;
	case 1:
		glm::vec2 a = {0,0}, b = {0, 40}, c = {40, 40}, d = {40, 0}; 
		
		break;
	case 2:
		glm::vec2 a = {0, 25}, b = {}, c = {}, d = {50, 25}, e = {}, f = {};
		break;
	default:
		break;
	}*/
}

void BounchingBall::clean()
{
}

void BounchingBall::setShape(int a)
{
	shapeChoice = a;
}
