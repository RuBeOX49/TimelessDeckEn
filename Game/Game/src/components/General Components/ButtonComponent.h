#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/Animator.h"
#include "../../core/GameControl.h"
#include "../../core/ButtonNavigator.h"

// Estados representados por n�meros
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;

class ButtonComponent : public Component {

protected:	
	// Funci�n a realizar
	CallBack function;

	// Estado del bot�n
	int state;

	// Puntero al marco del bot�n
	GameObject* frame;

	// Punteros a componentes
	Animator* animButton;
	Animator* animFrame;

	//Sonidos de los botones
	SoundEffect* hoverOverSound;
	SoundEffect* clickSound;
	vector<SoundEffect*> soundEffects;

	// Input y navegaci�n
	GameControl& gmCtrl_;
	ButtonNavigator* butNav;
	ButtonData myData;
	bool addToNavigation_;
public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack _f, GameObject* _frame = nullptr, bool addToNav = true) :
		Component(), state(0), function(_f), frame(_frame), animButton(nullptr), animFrame(nullptr),
		clickSound(nullptr), hoverOverSound(nullptr), gmCtrl_(gmCtrl()), butNav(nullptr), addToNavigation_(addToNav) {}

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
	void changeStateAnim(string key, int state);
	// Selecciona el bot�n
	void setAsCurrentButton();
};