#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class SwordSpin : public GameObject {
public:
/*
	Imagen de ataque circular en el centro del jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe da�o
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, BattleScene* scene, int dmg) {
		addComponent<Transform>(playerPos - Vector2D(100, 100), Vector2D(0, 0), 200, 200);
		addComponent<LifeTimeComponent>(60);
		addComponent<Image>(SDLApplication::getTexture("SwordSpin"));
		addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
		addComponent<ColliderComponent>();
	}
};