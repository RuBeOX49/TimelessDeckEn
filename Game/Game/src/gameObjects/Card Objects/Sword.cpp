#include "Cards.h"
#include "../../sdlutils/Texture.h"
#include "../Card Objects/SwordSlash.h"
#include "../Card Objects/SwordSpin.h"

#include <iostream>

//SwordCard::SwordCard() {
//	damage = 20;
//	maxUses = 5;
//	remainingUses = maxUses;
//	mana = 80;
//	downtime = 2;
//	name = "Espada";
//	abilityText = "";
//	attackText = "";
//	texture = nullptr;
//}

// Crea un gObj Slash en la direcci�n que apunta el jugador
void SwordCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	std::cout << "slash"<<std::endl;
	
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());

	dir = dir.normalize() * bulletSpeed;
	

	where->addGameObject<SwordSlash>(_grp_PLYR_ATTACK, playerPos, dir, where, damage * attackMult);

}

// Crea un gObj Spin en el centro del jugador
void SwordCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	
	where->addGameObject<SwordSpin>(_grp_PLYR_ATTACK, playerPos, where, damage * remainingUses * attackMult);

}
