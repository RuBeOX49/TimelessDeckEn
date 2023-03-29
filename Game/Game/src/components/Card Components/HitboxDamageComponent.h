#pragma once
#include "../Component.h"
#include "../General Components/ColliderComponent.h"
#include "../General Components/HealthComponent.h"
#include "../../gameObjects/GameObject.h"
#include <vector>
#include <unordered_set>

class RitualAxeCard;
// Este componente maneja toda la l�gica de las balas, como su interacci�n con otros objetos
class HitboxDamageComponent : public Component
{
private:
	int damage; //da�o que causa
	bool destroy; //Si el objeto se destruye al colisionar
	bool knockback; //Si el objeto causa knockback
	RitualAxeCard* axe; //Si el ataque es del Hacha Ritual
	unordered_set<GameObject*> hitRegistry; //Set que registra los choques anteriores

public:
	static const int id = _HITBOX_DAMAGE_COMPONENT;

	HitboxDamageComponent(int dmg, bool dstry, bool knback, RitualAxeCard* axeC = nullptr) : damage(dmg), destroy(dstry), knockback(knback), axe(axeC) {}

	// Se le a�ade al colider la funcion de da�o
	void initComponent() override{
		gObj->getComponent<ColliderComponent>()->addFunction(damageFunction());
	}

	//Funcion que se llama al colisionar, causa da�o al objeto con el que se ha colisionado
	CallBackCol damageFunction() {
		return [&](GameObject* trgt)
		{
			if (hitRegistry.count(trgt) == 0) {
				trgt->getComponent<HealthComponent>()->receiveDamage(damage, axe);
				if (knockback) {
					Transform* tr = trgt->getComponent<Transform>();
					tr->setPos(tr->getPos() + tr->getVel() * -20);
				}
				if (destroy) gObj->setAlive(false);
				else hitRegistry.insert(trgt);
			}
		};
	}
};
