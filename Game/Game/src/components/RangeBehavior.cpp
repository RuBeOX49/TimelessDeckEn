#include "RangeBehavior.h"

RangeBehavior::RangeBehavior(float spd, float safDist, float stoptime, float moveTime, 
	int damage, int attack, Player* player, SDLApplication* Game)
	:EnemyBehavior(spd, damage, stoptime, attack, player)
{
    safeDistance = safDist;
	moveTime = moveTime;
	game = Game;
}
void RangeBehavior::initComponent() {
	pos = gObj->getComponent<Transform>();
	pos->setVel(Vector2D(0.0005, 0.0005));
	initialDir = pos->getVel();
	setDirectionTo();
}
// Se encarga de comprobar si el enemigo est� dentro o fuera del radio de peligro
// Dependiendo de eso, se dirije al jugador o se aleja de �l
void RangeBehavior::setDirectionTo() {
	
	//Si no, vuelve a ir hacia �l
    pos->lookAt(playerPos->getPos());
	//Si estas dentro del rango de peligro, da media vuelta para salir de �l
	if (pos->getDistance(playerPos->getPos()) < safeDistance) pos->rotate(180);
}
// Se trata de un ciclo de movimiento y parada
void RangeBehavior::update() {
	actualTime = SDL_GetTicks();

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (actualTime - elapsedTime > stopTime)
	{
		pos->setVel(initialDir);
		// Si te has estado moviendo m�s tiempo de lo que deberia, vuelves al ciclo de parada
		 if (actualTime - elapsedTime > stopTime + moveTime)
		{
			setDirectionTo();
			//pos->setVel(Vector2D(0, 0));
			attack();
			elapsedTime = actualTime;
		}
	}
}
void RangeBehavior:: attack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	vel= vel / vel.magnitude();
	/*vel = vel * bulletSpedd;*/
	gStt->addGameObject<Bullet>(pos->getPos(), vel/500 ,damage, player, game);
}