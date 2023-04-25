#include "TankEnemy.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../components/General Components/EffectController.h"
void TankEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), TANK_WIDTH, ENEMY_HEIGHT, 0);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<TankBehaviour>(TANK_SPEED, TANK_ATTACK_DAMAGE, TANK_STOP_TIME, TANK_ATTACK_TIME, player);
	addComponent<OnDeath>(3, 1,player->getComponent<Transform>());
	ColliderComponent* collider=addComponent<ColliderComponent>(_grp_PLAYER);
	collider->addFunction(getComponent<TankBehaviour>()->tankAttack());
	auto anim = addComponent<EnemyAnimator>(TANK_ENEMY_TEXTURE_KEY, TANK_ENEMY_SPRITE_WIDTH, TANK_ENEMY_SPRITE_HEIGHT,
		TANK_ENEMY_SPRITE_ROWS, TANK_ENEMY_SPRITE_COLS, TANK_ENEMY_IDLE_ANIMATION, TANK_ENEMY_MOVEMENT_ANIMATION, TANK_ENEMY_ATTACK_ANIMATION);
	
	addComponent<EffectController>(anim);
	addComponent<HealthComponent>(life);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}