#include "BulletPool.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


BulletPool::BulletPool(unsigned int size, Player* P) : player(P)
{
	srand(time(NULL));
	
	for (int i = 0; i < size; i++) {
		deactive.push_back(new Bullet(this));
		deactive[i]->getTransform()->position = glm::vec2( 16 + (rand()% 800 - 16) , 10);
	}
	
	
}

void BulletPool::Draw()
{
	if (active.size() > 0)
	{
		for (auto i = 0; i < active.size(); ++i)
		{
			active[i]->draw();
		}
	}

}

void BulletPool::Spawn() {
	if (!deactive.empty()) {
		active.push_back(deactive.back());
		active.back()->active = true;
		active.back()->Reset();
		deactive.pop_back();
	}

}

void BulletPool::Update() {
	if (active.size() > 0) {
		for (int i = 0; i < active.size(); ++i)
		{
			active[i]->setgravity(gravity);
			active[i]->update();
		}
	}
	
	
	std::cout << "Active : " << active.size() << " Deactive : " << deactive.size() << std::endl;
	
}

void BulletPool::Despawn(Bullet* bullet)
{
	
	
	for (int i = 0; i < active.size(); ++i)
	{
		if (bullet == active.at(i)) {
			if (!active.empty())
			{
				deactive.push_back(active[i]);
			    active[i] = active.back();
				active.pop_back();
				return;
			}
		}
	}
}

void BulletPool::setgravity(float a)
{
	gravity = a; 
}

