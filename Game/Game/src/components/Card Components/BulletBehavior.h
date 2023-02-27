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
	vector<GameObject*>* target; // cleon says: adi�s, gatitos. adi�s.
public:
	static const int id = _BULLET_COMPONENT;
	// Recibe un player que se mete en el vector target, que hace las veces de matriz de colision
	BulletBehavior(int dmg, GameObject* Target) {
		target = new vector<GameObject*>();
		target->push_back(Target);
		damage = dmg;
	}
	// Recibe un vector de enemigos con los que debera colisionar la bala del player
	BulletBehavior(int dmg, vector<GameObject*>*Target)
	{
		target = Target;
		damage = dmg;
	}

	virtual void update()
	{
		// cleon says: 1�: usad loops modernos (C++11).
		// no us�is "vector" como un array. // Probalemente ni nos haga falta esto
		
		// Comprueba si ha chocado con el objetivo y, si lo hace, le baja vida
		for (int i = 0; i < target->size(); i++) {
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided((* target)[i]->getComponent<Transform>())) {
				(* target)[i]->getComponent<HealthComponent>()->receiveDamage(damage);
				gObj->setAlive(false); // Al colisionar, la bala se destruye
			}
		}
	}
};
