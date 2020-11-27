#include "BounchingBall.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "Config.h"
#include <iostream>

BounchingBall::BounchingBall(Ship * player) : accelX(100), accelY(100), player(player)
{
	TextureManager::Instance()->load("../Assets/textures/triangle.png", "shape0");
	TextureManager::Instance()->load("../Assets/textures/tile.png", "shape1");
	TextureManager::Instance()->load("../Assets/textures/circle.png", "shape2");
	
	getRigidBody()->velocity = glm::vec2(accelX, accelY);
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

	mass = 1;

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
	locationVerHex[2] = { this->getTransform()->position.x + 10, this->getTransform()->position.y + 24 };
	locationVerHex[3] = { this->getTransform()->position.x + 29, this->getTransform()->position.y };
	locationVerHex[4] = { this->getTransform()->position.x + 11, this->getTransform()->position.y - 25 };
	locationVerHex[5] = { this->getTransform()->position.x - 10, this->getTransform()->position.y - 24 };
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
	ballCollision();
	break;
default:
	break;
}


//std::cout << getRigidBody()->velocity.x << "   " << getRigidBody()->velocity.y << std::endl;
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

void BounchingBall::setMass(float a)
{
	mass = a;
}

void BounchingBall::lineCheckAgainstScreenBoundry(std::vector<glm::vec2> a, int b, float c, float d)
{
	bool check[9];
	check[8] = false;
	for (size_t i = 0; i < b; i++)
	{
		if (i + 1 == b)
		{
			//Wall
			check[0] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(0), screenBoundry.at(1));
			check[1] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(1), screenBoundry.at(2));
			check[2] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(2), screenBoundry.at(3));
			check[3] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), screenBoundry.at(0), screenBoundry.at(3));
			//Player
			check[4] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), player->vertexPoints[0], player->vertexPoints[1]);
			check[5] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), player->vertexPoints[1], player->vertexPoints[2]);
			check[6] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), player->vertexPoints[2], player->vertexPoints[3]);
			check[7] = CollisionManager::lineLineCheck(a.at(i), a.at(i - i), player->vertexPoints[0], player->vertexPoints[3]);
			if (a[i].x == a[i- i].x || a[i].y == a[i - i].y)
			{
				//Create a line between the two shapes and have line check which face it is collide  with face on player
				if (CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[0], player->vertexPoints[1])
					|| CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[2], player->vertexPoints[3]))
				{
					check[5] = check[7] = false;
				}
				if (CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[1], player->vertexPoints[2])
					|| CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[0], player->vertexPoints[3]))
				{
					check[4] = check[6] = false;
				}
			}
			if ( (check[4] || check[5] || check[4] || check[7]) && (a[i].x != a[i - i].x && a[i].y != a[i - i].y))
			{
				check[8] = true;
			}
		}
		else
		{
			//Wall
			check[0] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(0), screenBoundry.at(1));
			check[1] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(1), screenBoundry.at(2));
			check[2] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(2), screenBoundry.at(3));
			check[3] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), screenBoundry.at(0), screenBoundry.at(3));
			//Player
			check[4] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), player->vertexPoints[0], player->vertexPoints[1]);
			check[5] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), player->vertexPoints[1], player->vertexPoints[2]);
			check[6] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), player->vertexPoints[2], player->vertexPoints[3]);
			check[7] = CollisionManager::lineLineCheck(a.at(i), a.at(i + 1), player->vertexPoints[0], player->vertexPoints[3]);
			if (a[i].x == a[i + 1].x || a[i].y == a[i + 1].y)
			{
				//Create a line between the two shapes and have line check which face it is collide  with face on player
				if (CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[0], player->vertexPoints[1])
					|| CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[2], player->vertexPoints[3]))
				{
					check[5] = check[7] = false;
				}
				if (CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[1], player->vertexPoints[2])
					|| CollisionManager::lineLineCheck(getTransform()->position, player->getTransform()->position, player->vertexPoints[0], player->vertexPoints[3]))
				{
					check[4] = check[6] = false;
				}
			}
			if ((check[4] || check[5] || check[4] || check[7]) && (a[i].x != a[i + 1].x && a[i].y != a[i + 1].y))
			{
				check[8] = true;
			}
		}
		
		//Wall Check
		if (check[0] || check[2])
		{
			getTransform()->position = glm::vec2(getTransform()->position.x - ((getRigidBody()->velocity.x) / 60.f), getTransform()->position.y - getRigidBody()->velocity.y / 60.f);
			getRigidBody()->velocity.x *= -(1 - friction);
			getRigidBody()->velocity.y *= (1 - friction);
			break;
		}
		if (check[1] || check[3])
		{
			getTransform()->position = glm::vec2(getTransform()->position.x - getRigidBody()->velocity.x / 60.f, getTransform()->position.y - ((getRigidBody()->velocity.y) / 60.f));
			
			getRigidBody()->velocity.x *= (1 - friction);
			getRigidBody()->velocity.y *= -(1 - friction);
			break;	
		}
		
		int sign = 0;
		//Player check
		if (check[4])
		{		
			if (getRigidBody()->velocity.x > 0)
				sign = 1;
			else
				sign = -1;
			
			if (player->getTransform()->position.x - player->getWidth() /2 > getTransform()->position.x) {
				
				getRigidBody()->velocity.x = -abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
				getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
				//getRigidBody()->velocity.x = -abs(getRigidBody()->velocity.x);
				//getRigidBody()->velocity.y = abs(getRigidBody()->velocity.y);
				getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 30.f), getTransform()->position.y + getRigidBody()->velocity.y / 30.f);
				
				break;
				
			}
			else if (player->getTransform()->position.x + player->getWidth() / 2 < getTransform()->position.x)
			{				
				getRigidBody()->velocity.x = abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
				getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			
				getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 30.f), getTransform()->position.y + getRigidBody()->velocity.y / 30.f);
				
				break;
				
			}
			else  {
				
				
				
				getRigidBody()->velocity.x = sign * abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
				getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
				
				getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 30.f), getTransform()->position.y + getRigidBody()->velocity.y / 30.f);
				
				/*getRigidBody()->velocity.y *= -1;*/
				break;
			}
			
		}
		
		else if (check[6]) {
			
			if (this->getRigidBody()->velocity.x > 0)
			{
				sign = 1;
			}
			else
			{
				sign = -1;
			}
			getRigidBody()->velocity.x = sign*abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = -abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			/*getRigidBody()->velocity.x *= (1 - friction);
			getRigidBody()->velocity.y *= -(1 - friction);*/
		}
		else if (check[5])
		{
			if (this->getRigidBody()->velocity.y > 0)
			{
				sign = 1;
			}
			else
			{
				sign = -1;
			}
			
			getRigidBody()->velocity.x =  abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = sign*abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			/*getRigidBody()->velocity.x *= -(1 - friction);
			getRigidBody()->velocity.y *= (1 - friction);*/
			
		}
		else if (check[7])
		{
			
			if (this->getRigidBody()->velocity.y > 0)
			{
				sign = 1;
			}
			else
			{
				sign = -1;
			}
			getRigidBody()->velocity.x = -abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = sign * abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			/*getRigidBody()->velocity.x *= -(1 - friction);
			getRigidBody()->velocity.y *= (1 - friction);*/
			
		}
	}
}

void BounchingBall::ballCollision()
{
	bool check[4];
	check[0] = CollisionManager::circleLineCheck(player->vertexPoints[0], player->vertexPoints[1], getTransform()->position, 20);
	check[1] = CollisionManager::circleLineCheck(player->vertexPoints[1], player->vertexPoints[2], getTransform()->position, 20);
	check[2] = CollisionManager::circleLineCheck(player->vertexPoints[2], player->vertexPoints[3], getTransform()->position, 20);
	check[3] = CollisionManager::circleLineCheck(player->vertexPoints[3], player->vertexPoints[0], getTransform()->position, 20);
	
	// Wall vs Ball
	if (getTransform()->position.x > 800 - 20) {
		getRigidBody()->velocity.x *= -(1 - friction);
		getRigidBody()->velocity.y *= (1 - friction);
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
	}
	if(getTransform()->position.x < 0 +  20) {
		getRigidBody()->velocity.x *= -(1 - friction);
		getRigidBody()->velocity.y *= (1 - friction);
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
		
	}
	if (getTransform()->position.y < 0 + 20) {
		getRigidBody()->velocity.x *= (1 - friction);
		getRigidBody()->velocity.y *= -(1 - friction);
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
	}
	if (getTransform()->position.y > 600 - 20) {
		getRigidBody()->velocity.x *= (1 - friction);
		getRigidBody()->velocity.y *= -(1 - friction);
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
	}
	
	// Brick vs Ball
	if (check[0] && check[1])
		check[1] = false;
	if (check[0] && check[3])
		check[3] = false;
	if (check[2] && check[1])
		check[1] = false;
	if (check[2] && check[3])
		check[3] = false;

	int signX;
	if (getRigidBody()->velocity.x > 0)
		signX = 1;
	else
		signX = -1;
	int signY;
	if (getRigidBody()->velocity.y > 0)
		signY = 1;
	else
		signY = -1;

	if (check[0]) {
		
	
		if (player->getTransform()->position.x - player->getWidth() / 2 > getTransform()->position.x) {

			getRigidBody()->velocity.x = -abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
	
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			

		}
		else if (player->getTransform()->position.x + player->getWidth() / 2 < getTransform()->position.x)
		{
			getRigidBody()->velocity.x = abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());

			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			

		}
		else {
			
			getRigidBody()->velocity.x = signX * abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());

			
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
			
		}
	}
	if (check[1]) {
		getRigidBody()->velocity.x = abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
		getRigidBody()->velocity.y = signY * abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
	}
	else if (check[2])
	{
		if (player->getTransform()->position.x - player->getWidth() / 2 > getTransform()->position.x) {
						
			getRigidBody()->velocity.x = -abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = -abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
		}
		else if (player->getTransform()->position.x + player->getWidth() / 2 < getTransform()->position.x)
		{
			getRigidBody()->velocity.x = abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = -abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
		}
		else {
			
			getRigidBody()->velocity.x = signX * abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
			getRigidBody()->velocity.y = -abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
			getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);
		}

	}
	else if (check[3])
	{
		getRigidBody()->velocity.x = -abs(abs(this->getRigidBody()->velocity.x) * this->mass + player->getVector().x * player->getMass());
		getRigidBody()->velocity.y = signY * abs(abs(this->getRigidBody()->velocity.y) * this->mass + player->getVector().y * player->getMass());
		getTransform()->position = glm::vec2(getTransform()->position.x + ((getRigidBody()->velocity.x) / 20.f), getTransform()->position.y + getRigidBody()->velocity.y / 20.f);

	}
	
}
