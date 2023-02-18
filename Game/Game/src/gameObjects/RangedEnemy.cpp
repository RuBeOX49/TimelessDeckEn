#include "RangedEnemy.h"
#include "../components/RangeBehavior.h"
#include "../scenes/BattleScene.h"


RangedEnemy::RangedEnemy()
{
	//addComponent<ColliderComponent>();
	//addComponent<HealthComponent>(life);
}
void RangedEnemy::initGameObject(SDLApplication* game, Vector2D pos,int life, Player* player)
{
	addComponent<Transform>(pos, Vector2D(0,0), 30, 60, 0);
	addComponent<Image>(game->getTexture("Enemy"));
	addComponent<RangeBehavior>(1, 200, 3000, 3000, 5, 4, player, game);
}