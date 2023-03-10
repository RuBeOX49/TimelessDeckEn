#pragma once
#include "../../sdlutils/SDLUtils.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/CharacterAnimator.h"
#include "MeleeBehaviour.h"
class MeleeEnemyAnimator : public CharacterAnimator {
private:
	MeleeBehaviour* bhvr_;

	// Determina cu�ndo el enemigo est� atacando
	inline bool attacking() {
		return bhvr_->isAttacking() || playingAttack();
	}
public:
	// Llama al constructor del padre con las animaciones correspondientes y a�ade la de ataque
	MeleeEnemyAnimator();
	// Recoge un puntero a RangeBehaviour
	void initComponent();
};

