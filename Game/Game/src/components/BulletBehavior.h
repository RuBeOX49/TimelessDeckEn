#pragma once
#include "Component.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include <vector>
class BulletBehavior:public Component
{
private:
	int damage;
	vector<GameObject*>* target;
public:
	static const int id = _BULLET_COMPONENT;
	BulletBehavior(int dmg, GameObject* Target) {
		target = new vector<GameObject*>();
		target->push_back(Target);
		damage = dmg;
	}
	BulletBehavior(int dmg, vector<GameObject*>*Target)
	{
		target = Target;
		damage = dmg;
	}
	virtual void update()
	{
		// Comprueba si ha chocado con el objetivo y, si lo hace, le baja vida
		for (int i = 0; i < target->size(); i++) {
			if (gObj->getComponent<ColliderComponent>()->
				hasCollided((* target)[i]->getComponent<Transform>())) {
				(* target)[i]->getComponent<HealthComponent>()->receiveDamage(damage);
				gObj->setAlive(false);
			}
		}
	}
};
