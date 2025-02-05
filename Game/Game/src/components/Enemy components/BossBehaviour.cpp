#include "BossBehaviour.h"
#include "TentacleBehaviour.h"
#include "../../gameObjects/Enemy Objects/TargetedTentacle.h"
#include "../../gameObjects/Enemy Objects/BossCone.h"
#include "../../gameObjects/Enemy Objects/BossTentacle.h"

// Esta clase maneja el comportamiento del Jefe
BossBehaviour::BossBehaviour(float spd, float safDist, float stptime, float mvTime,
	int dmg, int atck, Player* plyr) :
	EnemyBehaviour(spd, dmg, stptime, atck, plyr),
	safeDistance(safDist), moveTime(mvTime), shotPattern(sdlutils().rand().nextInt(0, 3)),
	attackDelay(RANGED_ATTACK_ANIM_DELAY), attackTime(0),
	meleeSpawnTimer(0), rangedSpawnTimer(0), tankSpawnTimer(0) {}

void BossBehaviour::initComponent() {
	pos = gObj->getComponent<Transform>();
	hc = gObj->getComponent<HealthComponent>();
	pos->setVel(Vector2D(0, 0)); 
	pos->lookAt(playerPos->getPos());
	initlife = hc->getLife();
}
// Se trata de un ciclo de movimiento y parada
void BossBehaviour::update() {
	
	behaviorTime += SDLApplication::instance()->getDeltaTime();

	// Actualizar los temporizadores de spawn
	float deltaTime = SDLApplication::instance()->getDeltaTime();
	meleeSpawnTimer += deltaTime;
	rangedSpawnTimer += deltaTime;
	tankSpawnTimer += deltaTime;

	// Si ha pasado mas tiempo desde que estas parado del que deberia, te mueves
	if (behaviorTime > stopTime)
	{
		pos->setVel(initialDirection);

		// Si te has estado moviendo mas tiempo de lo que deberia, vuelves al ciclo de parada
		if (behaviorTime > stopTime + moveTime) {
			//pos->setVel(Vector2D(0, 0));
			attacking = true; // comienza la animacion de ataque
			behaviorTime -= stopTime + moveTime;
		}
	}
	
	if (attacking) {
		//iniciar la animacion y sumar el delay al ataque
		if (attackDelay < attackTime) {
			attackTime = 0;
			attacking = false;
			//enemyAttack(); // ataca coincidiendo con la animacion  attackState
			switch (attackState) {
			case CONE: // Conos
				coneAttack();
				break;
			case BULLET_HELL: // BulletHell
				bulletHellAttack();
				break;
			case CONE_TWO: // Conos
				coneAttack();
				break;
			case GRENADES: // Granadas
				grenadeAttack();
				break;
			case TARGETED_TENTACLE: // Tentaculo Dirigido
				targetedAttack();
				break;
			case CLOCK: // Aspersor
				clockAttack();
				break;
			case BULLET_GRENADES: // BulletHell + Granadas
				bulletHellAttack();
				grenadeAttack();
				break;
			case TT_CONES: // Tentaculo Dirigido + Conos
				targetedAttack();
				coneAttack();
				break;
			case BULLET_CLOCK: // BulletHell + Aspersor
				bulletHellAttack();
				clockAttack();
				break;
			case GRENADE_TT: // Granadas + Tentaculo Dirigido
				grenadeAttack();
				targetedAttack();
				break;
			default:
				break;
			}
			// Spawn de enemigos
			if (hc->getLife() <= initlife / 2) {
				if (meleeSpawnTimer >= meleeSpawnRate) {
					spawnMeleeEnemy();
					meleeSpawnTimer = 0;
				}
				if (rangedSpawnTimer >= rangedSpawnRate) {
					spawnRangedEnemy();
					rangedSpawnTimer = 0;
				}
				if (tankSpawnTimer >= tankSpawnRate) {
					spawnTankEnemy();
					tankSpawnTimer = 0;
				}
			}

			if (attackState == GRENADE_TT && !listaCompletada)
			{
				listaCompletada = true;
			}
			if (!listaCompletada)
			{
				attackState++;
			}
			else
			{
				attackState = rand() % 10;
			}
			updateAttackDelay();
		}
		else attackTime += SDLApplication::instance()->getDeltaTime();
	}
}
// Permite al enemigo instanciar balas (mismo comportamiento que los RangeEnemies)
void BossBehaviour::enemyAttack() {
	Vector2D vel = playerPos->getPos() - pos->getPos();
	if (vel.magnitude() != 0) {
		vel = vel.normalize();
		float rot = Vector2D(-1, 0).angle(vel);
		Hitbox::HitboxData data = { pos->getPos(), vel * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
		if (shotPattern == 0) {
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
		}
		else if (shotPattern == 1) {
			vel = vel.rotate(BULLET_ANGLE);
			rot = Vector2D(-1, 0).angle(vel);
			data = { pos->getPos(), vel * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			rot = Vector2D(-1, 0).angle(vel);
			data = { pos->getPos(), vel * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
		}
		else if (shotPattern == 2) {	
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
			vel = vel.rotate(BULLET_ANGLE);
			rot = Vector2D(-1, 0).angle(vel);
			data = { pos->getPos(), vel * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
			rot = Vector2D(-1, 0).angle(vel);
			vel = vel.rotate(-2 * BULLET_ANGLE);
			data = { pos->getPos(), vel * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
			gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
		}
	}
}
// Funcion para ejecutar el ataque de Conos
void BossBehaviour::coneAttack() {
	// Obtener la dirección hacia el objetivo (en este caso, el player)
	Vector2D dir = (playerPos->getPos() - pos->getPos());
	dir = dir / dir.magnitude();

	// Generar los ataques de cono en dirección al jugador y en dirección contraria
	for (int i = 0; i < 2; i++) {

		Vector2D hitboxPos = Vector2D(pos->getCenter().getX(), pos->getCenter().getY()) - Vector2D(0,90);
		Vector2D offset = Vector2D(); float rotation = 0;
		if (coneAttacksDone == 0) {
			offset = i == 0 ? Vector2D(150, 0) : Vector2D(-400, 0);
			rotation = i == 0 ? 0 : 180;
		}
		else {
			offset = i == 0 ? Vector2D(-150, BOSS_ENEMY_HEIGHT / 2) : Vector2D(-150, -BOSS_ENEMY_HEIGHT / 2);
			rotation = i == 0 ? 90 : 270;
		}

		gStt->addGameObject<BossCone>(_grp_ENM_ATTACK, hitboxPos + offset, rotation + 90);
	}

	// Incrementar el contador de ataques de cono
	coneAttacksDone++;

	// Si aún no se han realizado los 2 ataques de cono, llamar a coneAttack() nuevamente después de 2 segundos
	if (coneAttacksDone < 2) {
		// Utiliza la función SDL_AddTimer para llamar a coneAttack() nuevamente después de 2 segundos (2000 ms)
		SDL_AddTimer(2000, &BossBehaviour::coneAttackTimerCallback, this);
	}
	else {
		// Reiniciar coneAttacksDone
		coneAttacksDone = 0;
	}

	// Incrementar el contador de ataques y reiniciar el tiempo de ataque
	attackTime = 0;

	// Reiniciar behaviorTime para empezar de nuevo
	behaviorTime = 0;
}

void BossBehaviour::updateAttackDelay()
{
	switch (attackState)
	{
	case BULLET_HELL: // BulletHell
	case BULLET_CLOCK: // BulletHell + Aspersor
		currentBossState = boss_BHELL;
		attackDelay = 1800;
		break;
	case GRENADES: // Granadas
	case GRENADE_TT: // Granadas + Tent�culo Dirigido
		currentBossState = boss_GRENADE;
		attackDelay = 1400;
		break;
	case BULLET_GRENADES: // BulletHell + Granadas
		currentBossState = boss_COMBINED;
		attackDelay = 1800;
		break;
	default:
		currentBossState = boss_IDLE;
		attackDelay = 0;
		break;
	}
	
}

// Función para ejecutar el ataque Bullet Hell
void BossBehaviour::bulletHellAttack() {
	// Definimos la cantidad de balas y la separación entre ellas
	const int numBullets = 25;
	// Obtenemos la dirección hacia el jugador
	Vector2D dir = (playerPos->getPos() - pos->getPos()).normalize();

	//anim->playDiff("BulletHell");
	// Calculamos la posición inicial para las balas
	Vector2D startPos = Vector2D(pos->getPos().getX() + pos->getWidth() / 2, pos->getPos().getY() + pos->getHeight() - 200) + dir * 50.0f;

	// Generamos las balas
	for (int i = 0; i < numBullets; i++) {
		// Calculamos la dirección de la bala
		float angle = (float)i * (360.0f / (float)numBullets);
		Vector2D bulletDir = dir.rotate(angle);
		float rot = Vector2D(-1, 0).angle(bulletDir.normalize());

		// Calculamos la posición de la bala
		Vector2D bulletPos = startPos + bulletDir * 50.0f; // Cambiamos cómo se calcula la posición de la bala

		// Creamos el objeto de la bala
		Hitbox::HitboxData data = { bulletPos, bulletDir * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, BOSS_BULLET, _grp_PLAYER };
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
	}
}


// Funcion para ejecutar el ataque Granadas
void BossBehaviour::grenadeAttack() {

	//anim->playDiff("GrenadeAttack");
	// Implementar l�gica del ataque Granadas
	Vector2D directions[] = { Vector2D(1,0), Vector2D(0,1), Vector2D(-1,0), Vector2D(0,-1) };

	// Creo la funcion que instancia 8 balas al explotar
	CallBackExpl bossGrenade = [myScene = gStt](Transform* tr) {
		// Direcciones de las balas
		Vector2D directs[] = {Vector2D(1,0), Vector2D(-1,0), Vector2D(0,1), Vector2D(0,-1), 
			Vector2D(1,1).normalize(), Vector2D(1,-1).normalize(), Vector2D(-1,1).normalize(), Vector2D(-1,-1).normalize()};
		// Creo las 8 balas
		float rot = 0;
		for (int i = 0; i < 8; i++) {
			rot = Vector2D(-1, 0).angle(directs[i]);
			Hitbox::HitboxData data = { tr->getCenter(), directs[i] * BULLET_SPEED, rot, BOSS_BULLET_W, BOSS_BULLET_H, 
				BOSS_BULLET, _grp_PLAYER};
			myScene->addGameObject<Hitbox>(_grp_ENM_ATTACK, BOSS_BULLET_DMG, true, 10, data);
		}
	};
	// Creo las 4 granadas en direcciones arriba, abajo, izq y der
	for (int i = 0; i < 4; i++) {
		Hitbox::HitboxData data = { gObj->getComponent<Transform>()->getCenter(), 
			directions[i] * BULLET_SPEED, 0, BOSS_GRENADE_DIMENSIONS, BOSS_GRENADE_DIMENSIONS, "BossGrenade", _grp_PLAYER};
		gStt->addGameObject<Hitbox>(_grp_ENM_ATTACK, 5, true, 3, StatusComponent::NONE, 
			BOSS_GRENADE_EXPLOSION, BOSS_GRENADE_EXPLOSION, "BossGrenade", dynamic_cast<BattleScene*>(gStt), data, Vector2D(-1,-1), bossGrenade);
	}
}

// Funcion de devolución de llamada del temporizador para coneAttack
Uint32 BossBehaviour::coneAttackTimerCallback(Uint32 interval, void* param) {
	BossBehaviour* boss = static_cast<BossBehaviour*>(param);
	boss->coneAttack();
	return 0;
}

// Funcion para el ataque de reloj
void BossBehaviour::clockAttack()
{
	Transform* tr = gObj->getComponent<Transform>();
	gStt->addGameObject<BossTentacle>(tr);
}

// Funcion para el ataque teledirigido
void BossBehaviour::targetedAttack()
{
	gStt->addGameObject<TargetedTentacle>(_grp_ENM_ATTACK, player->getComponent<Transform>(), gObj->getComponent<Transform>());
}

void BossBehaviour::spawnMeleeEnemy() {
	// Implementar la lógica para generar enemigos cuerpo a cuerpo en la ubicación deseada
	Vector2D spawnPos = Vector2D(pos->getPos().getX() + pos->getWidth() / 2, pos->getPos().getY() + pos->getHeight() - 200) + Vector2D(1, 0).rotate(rand() % 360) * MELEE_RADIUS;
	//spawnPos = checkPos(spawnPos, MELEE_RADIUS);
	GameObject* enemy = gStt->addGameObject<MeleeEnemy>(_grp_ENEMIES, spawnPos, 10, player);
}

void BossBehaviour::spawnRangedEnemy() {
	// Implementar la lógica para generar enemigos a distancia en la ubicación deseada
	Vector2D spawnPos = Vector2D(pos->getPos().getX() + pos->getWidth() / 2, pos->getPos().getY() + pos->getHeight() - 200) + Vector2D(1, 0).rotate(rand() % 360) * RANGED_RADIUS;
	//spawnPos = checkPos(spawnPos, RANGED_RADIUS);
	GameObject* enemy = gStt->addGameObject<RangedEnemy>(_grp_ENEMIES, spawnPos, 10, player);
}

void BossBehaviour::spawnTankEnemy() {
	// Implementar la lógica para generar enemigos tanque en la ubicación deseada
	Vector2D spawnPos = Vector2D(pos->getPos().getX() + pos->getWidth() / 2, pos->getPos().getY() + pos->getHeight() - 200) + Vector2D(1, 0).rotate(rand() % 360) * TANK_RADIUS;
	//spawnPos = checkPos(spawnPos, TANK_RADIUS);
	GameObject* enemy = gStt->addGameObject<TankEnemy>(_grp_ENEMIES, spawnPos, 10, player);
}
