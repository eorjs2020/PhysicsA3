#pragma once
#ifndef __BULLET__
#define __BULLET__
#include "Sprite.h"

class BulletPool;
class Bullet final : public Sprite
{
public:
	Bullet(BulletPool* pool);
	~Bullet();
	
	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void Reset();
	bool active = false;
	bool dead = false;
private:
	void m_buildAnimations();
	BulletPool* pool;
};

#endif /* defined (__BULLET__) */
