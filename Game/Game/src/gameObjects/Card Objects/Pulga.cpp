#include "Cards.h"
#include "Bomb.h"
#include "FlashBang.h"


void PulgaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize();

	where->addGameObject<Bomb>(playerPos, dir, damage * attackMult, where);
}

void PulgaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where)
{
	where->addGameObject<FlashBang>(playerPos, where, remainingUses);
	remainingUses=0;
}
