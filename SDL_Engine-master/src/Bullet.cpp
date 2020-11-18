#include "Bullet.h"
#include "TextureManager.h"
#include "BulletPool.h"

Bullet::Bullet(BulletPool* p)
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");
	auto size = TextureManager::Instance()->getTextureSize("bullet");

	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 50.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	
	pool = p;
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	if (active) {
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		// draw the plane sprite with simple propeller animation
		TextureManager::Instance()->draw("bullet", x, y, 0.f, 255, true);
	}
}

void Bullet::update()
{
	if (active) {
		float deltaTime = 1.f / 60.f;
		getRigidBody()->acceleration = glm::vec2(0, 9.8);
		getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
		if (getTransform()->position.y >= 650) {
			active = false;
			pool->Despawn(this);
			Reset();			
		}
	}

}

void Bullet::clean()
{
}

void Bullet::Reset()
{
	getRigidBody()->velocity = glm::vec2(0, 0);
	getTransform()->position = glm::vec2(getTransform()->position.x, 10);
}

void Bullet::m_buildAnimations()
{
	Animation planeAnimation = Animation();

	planeAnimation.name = "plane";
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane1"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane2"));
	planeAnimation.frames.push_back(getSpriteSheet()->getFrame("plane3"));

	setAnimation(planeAnimation);
}