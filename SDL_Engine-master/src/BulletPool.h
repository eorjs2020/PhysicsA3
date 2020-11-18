#pragma once
#ifndef __BULLET_POOL__
#define __BULLET_POOL__

#include "Bullet.h"
#include <vector>

class BulletPool
{
public:
	BulletPool(unsigned int size);
	~BulletPool();
	void Update();
	int size;
	int index = 0;
	void Draw();
	void Spawn();
	void Despawn(Bullet* p);
private:	
	std::vector<Bullet*> active;
	std::vector<Bullet*> deactive;
};

#endif // !__BULLET_POOL__