#include "BounchingBall.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Config.h"

BounchingBall::BounchingBall() : accelX(100), accelY(100)
{
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "shape0");
	TextureManager::Instance()->load("../Assets/textures/tile.png", "shape1");
	TextureManager::Instance()->load("../Assets/textures/hexagon.png", "shape2");
	
	getTransform()->position = glm::vec2(300, 30);
	friction = 0.2f;
	shapeChoice = 0;
	//Triangle vertext into the vector
	glm::vec2 a = { 0, 35 }, b = { 40, 35 }, c = { 20, 0 }, d , e, f;
	locationVerTri.push_back(a);
	locationVerTri.push_back(b);
	locationVerTri.push_back(c);
	//Square vertext into the vectorvertext into the vector
	a = { 0,0 }, b = { 0, 40 }, c = { 40, 40 }, d = { 40, 0 };
	locationVerSqu.push_back(a);
	locationVerSqu.push_back(b);
	locationVerSqu.push_back(c);
	locationVerSqu.push_back(d);
	//Hexagon vertext into the vector
	a = { 0, 25 }, b = { 14, 50 }, c = { 43, 50 }, d = { 58, 25 }, e = { 43, 0 }, f = { 14, 0 };
	locationVerHex.push_back(a);
	locationVerHex.push_back(b);
	locationVerHex.push_back(c);
	locationVerHex.push_back(d);
	locationVerHex.push_back(e);
	locationVerHex.push_back(f);
	//Screen Boundry vertex position
	a = { 0, 0 }, b = { 0, Config::SCREEN_HEIGHT  }, c = { Config::SCREEN_WIDTH, Config::SCREEN_HEIGHT }, d = { Config::SCREEN_WIDTH, 0 };
	screenBoundry.push_back(a);
	screenBoundry.push_back(b);
	screenBoundry.push_back(c);
	screenBoundry.push_back(d);

	//Shape Sizes (used to make sure shapes dont get stick on wall)
	triDim = { 40, 35};
	squDim = { 40, 40 };
	hexDim = {58 ,50 };
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
	
	//Updating Vertex Cords
	switch (shapeChoice)
	{
	case 0:
		locationVerTri[0] = { this->getTransform()->position.x - 20, this->getTransform()->position.y + 17.5 };
		locationVerTri[1] = { this->getTransform()->position.x + 20, this->getTransform()->position.y + 17.5 };
		locationVerTri[2] = { this->getTransform()->position.x, this->getTransform()->position.y - 17.5 };
		break;
	case 1:
		locationVerSqu[0] = { this->getTransform()->position.x - 20, this->getTransform()->position.y - 20 };
		locationVerSqu[1] = { this->getTransform()->position.x - 20, this->getTransform()->position.y + 20 };
		locationVerSqu[2] = { this->getTransform()->position.x + 20, this->getTransform()->position.y + 20 };
		locationVerSqu[3] = { this->getTransform()->position.x + 20, this->getTransform()->position.y - 20 };
		break;
	case 2:
		locationVerHex[0] = { this->getTransform()->position.x - 29 , this->getTransform()->position.y };
		locationVerHex[1] = { this->getTransform()->position.x - 11, this->getTransform()->position.y + 25 };
		locationVerHex[2] = { this->getTransform()->position.x + 11, this->getTransform()->position.y + 25 };
		locationVerHex[3] = { this->getTransform()->position.x + 29, this->getTransform()->position.y };
		locationVerHex[4] = { this->getTransform()->position.x + 11, this->getTransform()->position.y - 25 };
		locationVerHex[5] = { this->getTransform()->position.x - 11, this->getTransform()->position.y - 25 };
		break;
	default:
		break;
	}

	//used to check if shape hit boundry 
	switch (shapeChoice)
	{
	case 0:
		lineCheckAgainstScreenBoundry(locationVerTri, size(locationVerTri), triDim.x, triDim.y);
		break;
	case 1:
		lineCheckAgainstScreenBoundry(locationVerSqu, size(locationVerSqu), squDim.x, squDim.y);
		break;
	case 2:
		lineCheckAgainstScreenBoundry(locationVerHex, size(locationVerHex), hexDim.x, hexDim.y);
		break;
	default:
		break;
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

void BounchingBall::lineCheckAgainstScreenBoundry(std::vector<glm::vec2> a, int b, float c, float d)
{
	bool check[4];
	for (size_t i = 0; i < b ; i++)
	{
		//checks to see if the two line touch and if true one of the two if will be tiggered depending on the wall hit
		if(i + 1 == b)
		{
			check[0] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(0), screenBoundry.at(1));
			check[1] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(1), screenBoundry.at(2));
			check[2] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(2), screenBoundry.at(3));
			check[3] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(0), screenBoundry.at(3));
		}
		else
		{
			check[0] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(0), screenBoundry.at(1));
			check[1] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(1), screenBoundry.at(2));
			check[2] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(2), screenBoundry.at(3));
			check[3] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(0), screenBoundry.at(3));
		}
		
		if (check[0] || check[2])
		{
			accelX *= -(1 - friction);
			accelY *= (1 - friction);
			if(check[0])
			{
				getTransform()->position = glm::vec2(0 + c/2, getTransform()->position.y);
				break;
			}
			else
			{
				getTransform()->position = glm::vec2(800 - c/2, getTransform()->position.y);
				break;
			}
		}
		if (check[1] || check[3])
		{
			accelX *= (1 - friction);
			accelY *= -(1 - friction);
			if (check[1])
			{
				getTransform()->position = glm::vec2(getTransform()->position.x, 600 - d/2);
				break;
			}
			else
			{
				getTransform()->position = glm::vec2(getTransform()->position.x, 1 + d/2);
				break;
			}
		}

	}
}
