#pragma once
#ifndef __BULLET_POOL__
#define __BULLET_POOL__

#include "Bullet.h"
#include <vector>
#include "Player.h"

class BulletPool
{
public:
	BulletPool(unsigned int size, Player*);
	~BulletPool();
	void Update();
	int size;
	int index = 0;
	void Draw();
	void Spawn();
	void Despawn(Bullet* p);
	Player* player;
	void setgravity(float a);
	void reSize(unsigned int size);
	void setDelay(float a);
	float getDelay(); 
	int getBulletActive();
	int getBulletDeactive();
	std::vector<Bullet*> getbullet();

private:	
	std::vector<Bullet*> active;
	std::vector<Bullet*> deactive;
	float gravity; 
	float delay;
	int bulletActive, bulletDeactive;
};

#endif // !__BULLET_POOL__