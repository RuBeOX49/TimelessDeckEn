#pragma once
#include "../core/GameObject.h"
#include "../components/MeleeBehaviour.h"
#include "../components/Image.h"
#include "../components/ColliderComponent.h"

class MeleeEnemy :public GameObject
{
public:
	MeleeEnemy(SDLApplication* game, Vector2D pos, Vector2D vel,int life, Player* player)
	{
		addComponent<Transform>(pos, vel, 30, 60, 0);
		addComponent<Image>(game->getTexture("Enemy"));
		addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 4, player);
		//addComponent<ColliderComponent>();
		//addComponent<HealthComponent>(life);

	}
};


