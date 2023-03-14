#include "TankEnemy.h"

void TankEnemy::initGameObject(Vector2D pos, int life, Player* player, BattleScene* where) {
	addComponent<Transform>(pos, Vector2D(0, 0), ENEMY_WIDTH, ENEMY_HEIGHT, 0);
	addComponent<Image>(SDLApplication::getTexture("Player"));
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<TankBehaviour>(TANK_SPEED, TANK_ATTACK_DAMAGE, TANK_STOP_TIME, TANK_ATTACK_TIME, player);
	addComponent<OnDeath>(3, 1, where);
	addComponent<ColliderComponent>(getComponent<TankBehaviour>()->tankAttack(),_grp_PLAYER);
	addComponent<HealthComponent>(life);
}