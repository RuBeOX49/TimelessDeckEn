#include "BossEnemy.h"
#include "../../components/Enemy components/RangeBehaviour.h"
#include "../../components/Enemy components/EnemyAnimator.h"
#include "../../components/General Components/StatusComponent.h"
#include "../../scenes/BattleScene.h"

void BossEnemy::initGameObject(Vector2D pos, int life, Player* player) {
	addComponent<Transform>(pos, Vector2D(0, 0), BOSS_ENEMY_WIDTH, BOSS_ENEMY_HEIGHT, 0);
	addComponent<RangeBehaviour>(1, 200, 3000, 3000, 50, 3, player);
	addComponent<OnDeath>(3, 1, player->getComponent<Transform>());
	addComponent<HealthComponent>(life);
	addComponent<EnemyAnimator>(getComponent<RangeBehaviour>(), BOSS_ENEMY_TEXTURE_KEY, BOSS_ENEMY_SPRITE_WIDTH,
		BOSS_ENEMY_SPRITE_HEIGHT, BOSS_ENEMY_SPRITE_ROWS, BOSS_ENEMY_SPRITE_COLS,
		BOSS_ENEMY_IDLE_ANIMATION, BOSS_ENEMY_MOVEMENT_ANIMATION, BOSS_ENEMY_ATTACK_ANIMATION);
	addComponent<ColliderComponent>(_grp_PLAYER);
	addComponent<StatusComponent>();
}