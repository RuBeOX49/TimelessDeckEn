#include "Button.h"
#include "../../core/SDLApplication.h"

// Añade los componentes al botón y crea sus animaciones
void Button::initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, int _index, GameObject* _frame, float horizontalMult, float verticalMult) {
	// Transform
	addComponent<Transform>(_pos, VECTOR_ZERO, _animInfo.w, _animInfo.h);

	// Animator y sus animaciones
	createButtonAnimations(addComponent<Animator>(SDLApplication::getTexture(_animInfo.key), _animInfo.fw, _animInfo.fh, _animInfo.rows, _animInfo.cols));

	if (_frame != nullptr) createButtonAnimations(_frame->getComponent<Animator>());

	// Componente de botones
	bComp = addComponent<ButtonComponent>(_cb, _frame, _index, true, horizontalMult, verticalMult);
}

void Button::initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, GameObject* _frame) {
	initGameObject(_cb, _pos, _animInfo, -1, _frame, 1.0f, 1.0f);
}

void Button::initGameObject(CallBack _cb, Vector2D _pos, AnimatorInfo _animInfo, Animation _onOutAnimation, Animation _onOverAnimation, Animation _onClickAnimation, int index, GameObject* _frame, float horizontalMult, float verticalMult) {
	// Transform
	addComponent<Transform>(_pos, VECTOR_ZERO, _animInfo.w, _animInfo.h);

	createButtonAnimations(addComponent<Animator>(SDLApplication::getTexture(_animInfo.key), _animInfo.fw, _animInfo.fh, _animInfo.rows, _animInfo.cols), _onOutAnimation, _onOverAnimation, _onClickAnimation);

	// Componente de botones
	bComp = addComponent<ButtonComponent>(_cb, _frame, index, true, horizontalMult, verticalMult);
}

// Crea las animaciones esenciales de un bot�n: OnClick, OnOver y Idle
void Button::createButtonAnimations(Animator* animator) {
	animator->attachToCamera();
	animator->createAnim(ONOUT, ONOUT_ALL_FRAMES, ONOUT_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONOVER, ONONVER_START_FRAME, ONOVER_END_FRAME, ONOVER_SPEED, -1);
	animator->createAnim(ONCLICK, ONCLICK_ALL_FRAMES, ONCLICK_ALL_FRAMES, ONCLICK_ONOUT_SPEED, -1);
	animator->play(ONOUT);
}

void Button::createButtonAnimations(Animator* animator, Animation onOut, Animation onOver, Animation onClick) {
	animator->attachToCamera();
	animator->createAnim(ONOUT, onOut);
	animator->createAnim(ONOVER, onOver);
	animator->createAnim(ONCLICK, onClick);
	animator->play(ONOUT);
}

void Button::setAsDefaultButton() {
	bComp->setAsDefaultButton();
}

void Button::setAsCurrentButton() {
	bComp->setAsCurrentButton();
}


bool Button::isCurrentButton() {
	return bComp->isCurrentButton();
}