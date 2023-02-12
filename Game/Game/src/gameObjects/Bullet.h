#pragma once
#include "../core/GameObject.h"
#include "../components/Transform.h"
class Bullet:public GameObject
{
private:
	int damage;
public:
	// Se le pasa la posici�n de inicio de quien lo ha disparado y la direcci�n a la que va

	Bullet(Vector2D pos, Vector2D dir, int damage)
	{
		addComponent<Transform>(pos, dir, 30, 30);
		//Colisiones? CallBack? Necesita damage para bajar la vida
	}
};
