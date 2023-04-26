﻿#pragma once
#include "../Component.h"
#include "../General Components/Transform.h"
#include "../../sdlutils/InputHandler.h"
#include "../General Components/Animator.h"
#include "../../core/GameControl.h"
#include "../../core/ButtonNavigator.h"

// Estados representados por números
enum State { OnOut = 0, OnOver, OnClick };

class SDLApplication;

class ButtonComponent : public Component {

protected:	
	// Funci�n a realizar
	CallBack function;

	// Estado del botón
	int state;

	// Puntero al marco del botón
	GameObject* frame;

	// Punteros a componentes
	Animator* animButton;
	Animator* animFrame;
	int index;

	//Sonidos de los botones
	SoundEffect* hoverOverSound;
	SoundEffect* clickSound;
	vector<SoundEffect*> soundEffects;

	// Input y navegaci�n
	GameControl& gmCtrl_;
	ButtonNavigator* butNav;
	ButtonData myData;
	bool addToNavigation_;
	float horizontalMultt, verticalMultt;
	std::function<void(Transform*)> onSelected_;
	Transform* tr_;
	bool currentButton;
public:
	static const int id = _BUTTON;
	ButtonComponent(CallBack _f, GameObject* _frame = nullptr, int _index = -1, bool addToNav = true, float horizontalMult = 1.0f, float verticalMult = 1.0f) :
		Component(), state(0), function(_f), frame(_frame), animButton(nullptr), animFrame(nullptr), index(_index),
		clickSound(nullptr), hoverOverSound(nullptr), gmCtrl_(gmCtrl()), butNav(nullptr), addToNavigation_(addToNav),
		onSelected_(nullptr), tr_(nullptr), currentButton(false), horizontalMultt(horizontalMult), verticalMultt(verticalMult) {}

	virtual ~ButtonComponent();

	virtual void update();
	virtual void handleInput();
	virtual void initComponent();

	// Comprueba si las coordenadas introducidas est�n sobre el mouse
	bool isOver(int mouseX, int mouseY);
	// Ejecuta el callback
	virtual void onClick();
	// Actualiza la animación del botón según el estado
	virtual void updateAnimation();

	// Cambia el estado de los animators para mostrar el estado del bot�n recibido
	void changeStateAnim(string key, int state);
	// Convierte al botón en el por defecto de la escena
	void setAsDefaultButton();
	// Selecciona el bot�n
	void setAsCurrentButton();

	void setOnSelected(std::function<void(Transform*)> onSel);

	inline bool isCurrentButton() { return butNav->isCurrentButton(animButton); }
};