#include "RangeBehaviour.h"

// Esta clase maneja el comportamiento de los enemigos a distancia
// Como su movimento y su habilidad para atacar
RangeBehaviour::RangeBehaviour(float spd, float safDist, float stptime, float mvTime, 
	int dmg, int atck, Player* plyr) :
	EnemyBehaviour(spd, dmg, stptime, atck, plyr), 
	safeDistance(safDist), moveTime(mvTime), shotPattern(sdlutils().rand().nextInt(0, 3)), 
	attacking(false), attackDelay(RANGED_ATTACK_ANIM_DELAY), attackTime(0) {}


void RangeBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(ENEMY_SPEED, ENEMY_SPEED)); // El 0.0005 es temporal hasta que hagamos la velocidad bien
	                                       // Es un valor adecuado para que el movimiento funcione
	initialDirection = pos->getVel();
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo est� dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de �l
void RangeBehaviour::setDirectionTo() {
	
	//Si no, vuelve a ir hacia �l
    pos->lookAt(playerPos->getPos());
	//Si estas dentro del rango de peligro, da media vuelta para salir de �l
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
}
// Se trata de un ciclo de movimiento y parada
void RangeBehaviour::update() {
	behaviorTime += SDLApplication::instance()->getDeltaTime();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (behaviorTime > stopTime)
	{
		pos->setVel(initialDirection);

		// Si te has estado moviendo m�s tiempo de lo que deberia, vuelves al ciclo de parada
		 if (behaviorTime > stopTime + moveTime) {
			setDirectionTo();
			//pos->setVel(Vector2D(0, 0));
			//enemyAttack();
			attacking = true; // comienza la animación de ataque
			behaviorTime -= stopTime + moveTime;
		 }
	}

	if (attacking) {
		if (attackDelay < attackTime) {
			attackTime = 0;
			attacking = false;
			enemyAttack(); // ataca coincidiendo con la animación
		}
		else attackTime += SDLApplication::instance()->getDeltaTime();
	}
}

// Permite al enemigo instanciar balas
void RangeBehaviour::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel / vel.magnitude();
		/*vel = vel * bulletSpedd;*/
		if(shotPattern==0) gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
		else if (shotPattern == 1) {
			vel = vel.rotate(BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
			vel = vel.rotate(-2*BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
		}
		else if (shotPattern == 2) {
			gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
			vel = vel.rotate(BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
			vel = vel.rotate(-2*BULLET_ANGLE);
			gStt->addGameObject<Bullet>(pos->getPos(), vel, damage, player);
		}
	}
}