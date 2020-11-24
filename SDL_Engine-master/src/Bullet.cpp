#include "Bullet.h"
#include "TextureManager.h"
#include "BulletPool.h"
#include "CollisionManager.h"
#include "SoundManager.h"

Bullet::Bullet(BulletPool* p) :explosionAni(false)
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "bullet");
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet");
	SoundManager::Instance().load("../Assets/audio/explode.wav", "explode", SOUND_SFX);
		
	setSpriteSheet(TextureManager::Instance()->getSpriteSheet("spritesheet"));
	auto size = TextureManager::Instance()->getTextureSize("bullet");

	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 50.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLANE);

	
	pool = p;
	m_buildAnimations();

	gravity = 9.8; 
}

Bullet::~Bullet()
= default;

void Bullet::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	if (active) {
		// alias for x and y
		
		// draw the plane sprite with simple propeller animation
		TextureManager::Instance()->draw("bullet", x, y, 0.f, 255, true);
	}
	if (explosionAni && !active)
	{
		TextureManager::Instance()->playAnimation("spritesheet", getAnimation("explosion"),
			x, y, 0.12f, 0, 255, true);
	}
}

void Bullet::update()
{
	if (active) {
		float PixelPerMeter = 1.f;
		float deltaTime = 1.f / 60.f;
		getRigidBody()->acceleration = glm::vec2(0, gravity);
		getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime * PixelPerMeter);
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;

		//collision with boundery
		if (getTransform()->position.y >= 650) {
			active = false;
			pool->Despawn(this);
			Reset();			
		}
		//Collision with player
		if (CollisionManager::AABBCheck(this, pool->player))
		{
			SoundManager::Instance().playSound("explode", 0, 1);
			active = false;
			explosionAni = true;
			
		}

	}
	//explosion animating function
	else {
		if (getAnimation("explosion").current_frame == 6)
		{
			getAnimation("explosion").current_frame = 0;
			explosionAni = false;
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

void Bullet::setgravity(float a)
{
	gravity = a;
}

void Bullet::m_buildAnimations()
{
	Animation explosionAnimation = Animation();
	explosionAnimation.name = "explosion";
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion1"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion2"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion3"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion4"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion5"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion6"));
	explosionAnimation.frames.push_back(getSpriteSheet()->getFrame("explosion7"));

	setAnimation(explosionAnimation);
}