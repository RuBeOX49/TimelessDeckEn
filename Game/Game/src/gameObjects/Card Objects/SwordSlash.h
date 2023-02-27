#pragma once
#include "../GameObject.h"
#include "../../components/General Components/ColliderComponent.h"
#include "../../components/General Components/LifetimeComponent.h"
#include "../../components/Card Components/SwordSlashBehaviour.h"
#include "../../components/General Components/Transform.h"
#include "../../components/General Components/Image.h"
#include "../../core/SDLApplication.h"



class SwordSlash : public GameObject {
public:
	/*
	Imagen de ataque circular en arco en la direcci�n que apunta el jugador
	Cuando colisiona POR PRIMERA VEZ con un enemigo, el enemigo recibe da�o
	Desaparece a los 60 milisegundos
*/
	virtual void initGameObject(Vector2D playerPos, Vector2D dir, BattleScene* scene, int dmg) {
		Vector2D slashVector = playerPos + dir * 100;
<<<<<<< Updated upstream
		addComponent<Transform>(slashVector, Vector2D(0, 0), 100, 100, slashVector.angle(playerPos));
		addComponent<LifeTimeComponent>(.1);
=======
		addComponent<Transform>(slashVector - Vector2D(WIDTH / 2, HEIGHT / 2), Vector2D(0, 0), WIDTH, HEIGHT, Vector2D(1, 0).angle(dir));
		addComponent<LifeTimeComponent>(1);
>>>>>>> Stashed changes
		addComponent<Image>(SDLApplication::getTexture("SwordSlash"));
		addComponent<ColliderComponent>();
		addComponent<SwordSlashBehaviour>(dmg, scene->getEnemies());
	}

private:
	const float HEIGHT = 100;
	const float WIDTH = 50;
};
