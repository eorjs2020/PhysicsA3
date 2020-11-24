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
private:	
	std::vector<Bullet*> active;
	std::vector<Bullet*> deactive;
};

#endif // !__BULLET_POOL__