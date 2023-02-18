#pragma once
#include "Component.h"
#include "Transform.h"
#include "../sdlutils/InputHandler.h"
#include "../components/Animator.h"
#include "../GameObjects/UI/Button.h"

// Estados representados por n�meros
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;
typedef void CallBack(SDLApplication* game);

class ButtonComponent : public Component {

private:
	// Puntero al juego
	SDLApplication* game;
	
	// Funci�n a realizar
	CallBack* function;

	// Estado del bot�n
	int state;

	// Puntero al marco del bot�n
	GameObject* frame;

	// Punteros a componentes
	Transform* tr;
	Animator* animButton;
	Animator* animFrame;

public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack* _f, SDLApplication* _g, GameObject* _frame = nullptr) :
		Component(), state(0), function(_f), game(_g), frame(_frame), tr(nullptr), animButton(nullptr), animFrame(nullptr) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	void changeStateAnim(string key);
};