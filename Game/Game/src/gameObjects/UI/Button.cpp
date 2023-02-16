#include "Button.h"
#include "../../core/SDLApplication.h"

// A�ade los componentes al bot�n y crea sus animaciones
Button::Button(CallBack _cb, SDLApplication* game, Vector2D _pos, string key, int _w, int _h, int _r, int _c, GameObject* _frame) : GameObject() {
	// Transform
	addComponent<Transform>(_pos, Vector2D(0, 0), BUTTON_WIDTH, BUTTON_HEIGHT);

	// Animator y sus animaciones
	createButtonAnimations(addComponent<Animator>(game->getTexture(key), _w, _h, _r, _c));
	if (_frame != nullptr) createButtonAnimations(_frame->getComponent<Animator>());

	// Componente de botones
	addComponent<ButtonComponent>(_cb, game, _frame);
}

// Crea las animaciones esenciales de un bot�n: OnClick, OnOver y Idle
void Button::createButtonAnimations(Animator* animator) {
	animator->createAnim(ONOUT, ONOUT_ALL_FRAMES, ONOUT_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONOVER, ONONVER_START_FRAME, ONOVER_END_FRAME, ONOVER_SPEED, -1);
	animator->createAnim(ONCLICK, ONCLICK_ALL_FRAMES, ONCLICK_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->play(ONOUT);
}