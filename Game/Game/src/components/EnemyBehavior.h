#pragma once
#include "Component.h"
#include "Transform.h"
#include "ColliderComponent.h"
#include "HeatlhComponent.h"
#include "../core/Manager.h"
#include "../gameObjects/Player.h"

// Clase abstracta que junta la logica com�n del comportamiento enemigo como su posici�n,
// la del jugador y su velocidad

class EnemyBehavior: public Component
{
protected:
	Transform* pos;
	Transform* playerPos;
	HealthComponent* life;
	HealthComponent* playerLife;
	float stopTime;
	float elapsedTime;
	float actualTime;
	float attackInterval;
	float speed;
	int damage;
	// AttackComponent* attack (cuando este cerca del player, envia un mensaje para atacar)
public:
	EnemyBehavior(float spd, int dmg, float stop, float attack, Player* player) : speed(spd), damage(dmg), stopTime(stop), attackInterval(attack) {
		playerPos = player->getComponent<Transform>();
		//playerLife = player->getComponent<HealthComponent>();
		//life = gObj->getComponent<HealthComponent>();
		actualTime = SDL_GetTicks();

		
	};

	virtual void update();
	/*virtual void attack() = 0;*/
};

