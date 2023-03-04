#include "EnemyGenerator.h"
#include "../../core/PlayerData.h"

void EnemyGenerator::initComponent() {
	int level = PlayerData::instance()->getLevel();
	playerPos = player->getComponent<Transform>();
	levelType = (level == 1 ? level : (level < 5 ? 2 : 5));
	depth = level - levelType;
	timePerWave = STARTING_TIME_PER_WAVE - depth * 500;
}

void EnemyGenerator::update() {
	if (nextSpawn <= SDLApplication::instance()->getCurrentTime()) {
		nextWave();
	}
}

const int* EnemyGenerator::calcWave() {
	bool startingSpawns;
	switch (levelType)
	{
	case 1: 
		return WAVES[0];
	case 2:
		startingSpawns = true;
		break;
	case 5:
		startingSpawns = false;
		break;
	default:
		cout << "levelType erroneo";
		break;
	}

	int roll = rand() % 100;
	for (int i = 0; i < (startingSpawns ? 3 : 7); i++) {
		if (roll < (startingSpawns ? STARTING_SPAWNS[depth > 6 ? 6 : depth][i] : STANDARD_SPAWNS[depth][i])) return WAVES[i];
	}
}

Vector2D EnemyGenerator::checkPos(Vector2D pos, const int rad) {
	
	//variables a borrar cuando sepamos la constante
	int x = 1500, y = 1500;

    if (pos.getX() < x && pos.getX() > 0 && pos.getY() < y && pos.getY() > 0) {
		return pos;
	}
	if (pos.getX() > x ) {
		if (pos.getY() > y) {
			//esquina inferior derecha 90-180
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(90 + rand() % 90) * rad);
		}
		if (pos.getY() < 0) {
			//esquina superior derecha 180-270
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(180 + rand() % 90) * rad);
			
		}

		// Pared derecha 90-270
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(90 + rand() % 180) * rad);
	}

	if (pos.getX() < 0) {
		if (pos.getY() > y) {
			// esquina inferior izquierda 0-90
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate( rand() % 90) * rad);
		}
		if (pos.getY() < 0) {
			//esquina superior izquierda 270-360
			return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(270 + rand() % 90) * rad);
		}

		// pared izquierda 270-450
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(270 + rand() % 180) * rad);
	}

	if (pos.getY() < 0) {
		//pared superior 180-360
		return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(180 + rand() % 180) * rad);
		
	}

	//pared inferior 0-180 
	return Vector2D(playerPos->getCenter() + Vector2D(1, 0).rotate(rand() % 180) * rad);
	
}

void EnemyGenerator::nextWave() {
	spawnWave(calcWave());
	nextSpawn = SDLApplication::instance()->getCurrentTime() + timePerWave;
	if (depth < 29) depth += 1;
	timePerWave = STARTING_TIME_PER_WAVE - depth * 500;
}

void EnemyGenerator::spawnWave(const int wave[3]) {
	//Coger la posicion del player
	Vector2D spawn = playerPos->getCenter();

	//Hacemos un for y a�adimos enemigos melee
	for (int i = 0; i < wave[0]; i++) {
		
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * MELEE_RADIUS;
		spawnPos = checkPos(spawnPos, MELEE_RADIUS);
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos,10, player);
		where->addEnemy(enemy);
	}
	//Hacemos un for y a�adimos enemigos ranged
	for (int i = 0; i < wave[1]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * RANGED_RADIUS;
		spawnPos = checkPos(spawnPos, RANGED_RADIUS);
		//CAMBIAR POR RANGED ENEMY CUANDO FUNCIONE BIEN EL LIFETIME COMPONENT
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos, 10, player);
		where->addEnemy(enemy);
	}
	//Hacemos un for y a�adimos enemigos tank
	for (int i = 0; i < wave[2]; i++) {
		Vector2D spawnPos = spawn + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
		spawnPos = checkPos(spawnPos, TANK_RADIUS);

		//CAMBIAR POR TANK ENEMY CUANDO EXISTA
		GameObject* enemy = where->addGameObject<MeleeEnemy>(spawnPos, 10, player);
		where->addEnemy(enemy);
	}
}

