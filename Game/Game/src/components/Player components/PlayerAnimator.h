#pragma once
#include "../General Components/CharacterAnimator.h"

class PlayerAnimator : public CharacterAnimator {


public:
	// Constructora
	PlayerAnimator(Texture* _texture, int _w, int _h, int _r, int _c);
};
