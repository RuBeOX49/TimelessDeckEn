#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HeatlhComponent.h"
#include <vector>

// Este componente maneja toda la l�gica de las balas, como su interacci�n con otros objetos
class BulletBehavior:public Component
{
private:
	int damage;
public:
	static const int id = _BULLET_COMPONENT;
	// Recibe un player que se mete en el vector target, que hace las veces de matriz de colision
	BulletBehavior(int dmg) {
		damage = dmg;
	}
	CollisionCallBack getAttack() const
	{
		return[&](GameObject* gameObject)
		{
			gameObject->getComponent<HealthComponent>()->receiveDamage(damage);
			gObj->setAlive(false); // Al colisionar, la bala se destruye
		};
	}
};
