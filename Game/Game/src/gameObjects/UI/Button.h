#pragma once
#include "../../components/ecs.h"
#include "../../core/GameObject.h"
#include "../../components/Transform.h"
#include "../../components/Image.h"
#include "../../components/ButtonComponent.h"
#include "../../components/Animator.h"

class SDLApplication;
typedef void CallBack();
class Button : public GameObject {
private:
public:
	// A�ade los componentes al bot�n y crea sus animaciones
	virtual void initGameObject(CallBack _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _r, int _c, GameObject* _frame = nullptr);

	// Crear animaciones
	void createButtonAnimations(Animator* animator);
};