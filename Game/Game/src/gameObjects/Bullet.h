#pragma once
#include "../core/GameObject.h"
#include "../core/SDLApplication.h"
#include "../components/Transform.h"
#include "../components/ColliderComponent.h"
#include "../components/BulletBehavior.h"
#include "../components/Image.h"


class Bullet:public GameObject
{
public:
	// Se le pasa la posici�n de inicio de quien lo ha disparado y la direcci�n a la que va

	Bullet(Vector2D pos, Vector2D dir, int dmg, vector<GameObject*> target, SDLApplication* game)
	{
		addComponent<BulletBehavior>(dmg, target);
		addComponent<Transform>(pos, dir, 30, 30);
		addComponent<Image>(game->getTexture("Bullet"));
		addComponent<ColliderComponent>();
	}
	Bullet(Vector2D pos, Vector2D dir, int dmg, GameObject* target, SDLApplication* game)
	{
		addComponent<BulletBehavior>(dmg, target);
		addComponent<Transform>(pos, dir, 30, 30);
		addComponent<Image>(game->getTexture("Bullet"));
		addComponent<ColliderComponent>();
	}
};
