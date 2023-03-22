#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "EnemyBehaviour.h"
class EnemyAnimator: public CharacterAnimator
{
private:
	EnemyBehaviour* _bhvr = nullptr;
public:
	// Determina cu�ndo el enemigo est� atacando
	inline bool attacking() {
		return _bhvr->isAttacking() || playingAttack();
	}
public:
	// Llama al constructor del padre con las animaciones correspondientes y a�ade la de ataque
	EnemyAnimator(EnemyBehaviour* enmyBhvr, string txtr_key, int sprtW, int sprtH, int rws, int cols, Animation idle, Animation mvment, Animation atck);
	// Recoge un puntero a RangeBehaviour
	void initComponent();
};
