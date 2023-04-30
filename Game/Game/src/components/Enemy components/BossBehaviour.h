#pragma once
#include "EnemyBehaviour.h"
#include "../../gameObjects/Card Objects/Hitbox.h"
#include "../../scenes/BattleScene.h"
#include "../../core/SDLApplication.h"
#include "../../gameObjects/Enemy Objects/BossTentacle.h"
#include "../../gameObjects/Enemy Objects/TargetedTentacle.h"
#include <cmath>

// Esta clase define el comportamiento del enemigo a distancia
// Se mueve por un tiempo determinado y se queda parado otro
class BossBehaviour :public EnemyBehaviour
{
private:
	float safeDistance = 0;
	Vector2D initialDirection;
	float moveTime = 0;
	bool stopped = false;
	int shotPattern = 0;
	float attackDelay, attackTime;
	int attackState = 0;
	bool listaCompletada = false;
	int coneAttacksDone = 0;
	int initlife;
	// Timers para controlar el spawn de enemigos
	float meleeSpawnTimer;
	float rangedSpawnTimer;
	float tankSpawnTimer;
	// Cadencia de spawn de enemigos
	const float meleeSpawnRate = 2.0f;
	const float rangedSpawnRate = 5.0f;
	const float tankSpawnRate = 10.0f;

	EnemyAnimator* anim;
	HealthComponent* hc;

public:
	static const int id = _ENEMY_BEHAVIOUR;

	BossBehaviour(float spd, float safDist, float stptime, float mvTime,
		int dmg, int atck, Player* plyr);
	virtual void initComponent();
	void setDirectionTo();
	virtual void update();
	void enemyAttack();
	void coneAttack();
	void bulletHellAttack();
	void grenadeAttack();
	void clockAttack();
	void targetedAttack();
	void spawnMeleeEnemy();
	void spawnRangedEnemy();
	void spawnTankEnemy();
	static Uint32 coneAttackTimerCallback(Uint32 interval, void* param);
};

