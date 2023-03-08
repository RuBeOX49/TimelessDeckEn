#include "Cards.h"
#include "../Card Objects/Laser.h"
#include "../../sdlutils/Texture.h"

void LaserShadesCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);
	where->addGameObject<Laser>(_grp_PLYR_ATTACK, playerPos, rotation, damage * attackMult, _grp_ENEMIES);
}

void LaserShadesCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	for (int i = 0; i < 2 * remainingUses; i++)
	{
		float rotation = i * 360 / remainingUses;
		where->addGameObject<Laser>(_grp_PLYR_ATTACK, playerPos, rotation, damage * attackMult,_grp_ENEMIES);
	}
	remainingUses = 0;
}
