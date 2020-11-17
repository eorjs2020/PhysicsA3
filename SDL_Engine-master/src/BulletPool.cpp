#include "BulletPool.h"
#include <iostream>

BulletPool::BulletPool(unsigned int size)
{
	
	for (int i = 0; i < size; i++) {
		active.push_back(new Bullet(this));
		active[i]->getTransform()->position = glm::vec2(100 * i + 30, 0);
	}
	
	
}

void BulletPool::Draw()
{
	if (active.size() > 0)
	{
		for (auto i = 0; i < active.size(); ++i)
		{
			active[i]->draw();
			std::cout << i;
		}
	}
}

Bullet* BulletPool::Spawn() {
	Bullet* bullet = nullptr;
	if (deactive.size() > 0) {
		bullet = deactive.back();
		bullet->active = true;
		deactive.pop_back();
		active.push_back(bullet);
	}
	
	return bullet;
}

void BulletPool::Update() {
	if (active.size() > 0) {
		for (auto i = 0; i < active.size(); ++i)
		{
			active[i]->update();
		}
	}

}

void BulletPool::Despawn(Bullet* bullet)
{
	deactive.push_back(bullet);
	
	for (auto i = 0; i < active.size(); ++i)
	{
		if (bullet == active.at(i)) {
			delete active[i];
			active[i] = nullptr;
			active.erase(remove(active.begin(), active.end(), nullptr), active.end());
			active.shrink_to_fit();
			return;
		}
	}
	Spawn();
	
}

