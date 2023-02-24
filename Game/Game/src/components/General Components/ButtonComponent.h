#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/Animator.h"

// Estados representados por n�meros
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;

class ButtonComponent : public Component {

protected:
	// Puntero al juego
	SDLApplication* game;
	
	// Funci�n a realizar
	CallBack function;

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
	ButtonComponent(CallBack _f, SDLApplication* _g, GameObject* _frame = nullptr) :
		Component(), state(0), function(_f), game(_g), frame(_frame), tr(nullptr), animButton(nullptr), animFrame(nullptr) {}

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	// Comprueba si las coordenadas introducidas est�n sobre el mouse
	bool isOver(int mouseX, int mouseY);
	// Ejecuta el callback
	virtual void onClick();
	// Actualiza la animaci�n del bot�n seg�n el estado
	virtual void updateAnimation();

	// Cambia el estado de los animators para mostrar el estado del bot�n recibido
	void changeStateAnim(string key);
};