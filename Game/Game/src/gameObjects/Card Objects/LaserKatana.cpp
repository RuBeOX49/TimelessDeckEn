#include "Cards.h"
#include "../Card Objects/Hitbox.h"

void LaserKatanaCard::attack(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {
	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset()).normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	Hitbox::HitboxData data = { playerPos, VECTOR_ZERO, rotation, 250, 70, LASER, _grp_ENEMIES };
	data.pos = data.pos + Vector2D(data.width / 2, 0);

	where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, DASH_DURATION, data, Vector2D(0, data.height / 2));
	where->getPlayer()->getComponent<PlayerMovementComponent>()->dash(dir);
	where->getPlayer()->getComponent<HealthComponent>()->setInvencibility(DASH_DURATION*3);
}

void LaserKatanaCard::ability(Vector2D playerPos, Vector2D mousePos, float attackMult, BattleScene* where) {

	Vector2D dir = (mousePos - playerPos - where->getCamera()->getOffset());
	dir = dir.normalize();
	float rotation = Vector2D(1, 0).angle(dir);

	for (int i = 0; i < remainingUses; i++) {
		
		Vector2D aux = dir * LASER_KATANA_BURST * (i - 1);
		Hitbox::HitboxData data = { playerPos + aux, dir * BULLET_SPEED, rotation, 15, 150, LASER, _grp_ENEMIES};

		where->addGameObject<Hitbox>(_grp_PLYR_ATTACK, damage * attackMult, false, 10, data);
	}

	remainingUses = 0;
}
