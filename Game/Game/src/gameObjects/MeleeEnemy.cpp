#include "MeleeEnemy.h"
#include "../core/SDLApplication.h"

MeleeEnemy::MeleeEnemy() {}

void MeleeEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0,0), 30, 60, 0);
	addComponent<Image>(SDLApplication::getTexture("Enemy"));
	addComponent<MeleeBehaviour>(1000, float(0.001), 3, 30, 1000, player);
	addComponent<ColliderComponent>();
	addComponent<HealthComponent>(life);
}