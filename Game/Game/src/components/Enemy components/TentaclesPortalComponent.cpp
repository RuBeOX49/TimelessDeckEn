#include "TentaclesPortalComponent.h"
#include "../../gameObjects/GameObject.h"
#include "../../core/SDLApplication.h"
#include "../General Components/Image.h"

TentaclesPortalComponent::TentaclesPortalComponent(Transform* b) :
	Component(), boss(b), tr(nullptr), tentDer(nullptr), tentIzq(nullptr), ti(nullptr), td(nullptr), 
	state(INITIAL), timeOffset(0) {}

void TentaclesPortalComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
}

void TentaclesPortalComponent::update() {
	switch (state) {
	case INITIAL:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		//Instancio los tentaculos
		if (timeOffset >= 0.25) {
			ti = gStt->addGameObject(_grp_ENM_ATTACK);
			tentIzq = ti->addComponent<Transform>(tr->getPos() + Vector2D(0, tr->getHeight() / 2 - 20), Vector2D(), 50, 40, 180);
			ti->addComponent<Image>(&sdlutils().images().at(BOSS_TENTACLE));
			ti->addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
				{
					player->getComponent<HealthComponent>()->receiveDamage(10);
				}
			);
			
			td = gStt->addGameObject(_grp_ENM_ATTACK);
			tentDer = td->addComponent<Transform>(tr->getPos() + Vector2D(tr->getWidth() - 45, tr->getHeight() / 2 - 20), Vector2D(), 50, 40);
			td->addComponent<Image>(&sdlutils().images().at(BOSS_TENTACLE));
			td->addComponent<ColliderComponent>(_grp_PLAYER)->addFunction([&](GameObject* player)
				{
					player->getComponent<HealthComponent>()->receiveDamage(10);
				}
			);
			state = SPREAD;
			timeOffset = 0;
		}
		break;
	case SPREAD:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();

		// Los alargo
		if (timeOffset >= 0.1) {
			tentIzq->setWidth(tentIzq->getWidth() + 20);
			tentDer->setWidth(tentDer->getWidth() + 20);
			if (tentIzq->getWidth() >= TENTACLE_MAX_W && tentDer->getWidth() >= TENTACLE_MAX_W) {
				state = MOVE;
			}
			timeOffset = 0;
		}
		break;

	case MOVE:
		// Rotamos los tres a la vez
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 0.11) {
			calculatePos();
			tr->rotate(5);
			if (tr->getRotation() == 180) {
				state = AWAIT;
			}
			timeOffset = 0;
		}
		break;
		// Cuento un segundo y me borro
	case AWAIT:
		timeOffset += SDLApplication::instance()->getDeltaTimeSeconds();
		if (timeOffset >= 1) { ti->setAlive(false); td->setAlive(false); gObj->setAlive(false); }
		break;
	}
}

// Magia de vectores
void TentaclesPortalComponent::calculatePos() {
	// Calculo la direccion del tentaculo derecho con respecto al centro del boss
	Vector2D dir = Vector2D(1, 0).rotate(tentDer->getRotation()) * tr->getWidth()/2;
	// Seteo la posicion (suma de la direccion mas el centro y la posicion inicial de los portales menos la posicion actual)
	tentDer->setPos(dir + boss->getCenter() -  Vector2D(0, tentDer->getHeight() / 2) + boss->getInitialPosition() - boss->getPos());
	// Roto el tentaculo
	tentDer->rotate(5);

	// Calculo la direccion del tentaculo izquierdo con respecto al centro del boss
	dir = Vector2D(-1, 0).rotate(tentIzq->getRotation()) * tr->getWidth() / 2;
	// Seteo la posicion y roto el tentaculo
	tentIzq->setPos(boss->getCenter() - Vector2D(0, tentIzq->getHeight() / 2) + boss->getInitialPosition() - boss->getPos() - dir);
	tentIzq->rotate(5);
}