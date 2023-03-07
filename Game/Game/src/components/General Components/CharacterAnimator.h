#pragma once
#include "Animator.h"
class CharacterAnimator : public Animator {
private:
	bool wantToAdjustDirection;
	unordered_map<string, BoolCallBack> actions;
public:
	// Constructora, recibe animaciones de idle y movimiento
	CharacterAnimator(Texture* _texture, int _w, int _h, int _r, int _c, Animation idle, Animation move);
	// Actualiza la animacion del personaje en funci�n a sus acciones
	virtual void update();


	// Inicia una nueva animaci�n si es diferente a la actual
	bool playDiff(string key);
	// Actualiza a la animaci�n correspondiente, devuelve si ha cambiado de animaci�n o no
	virtual bool updatePlayingAnimation();


	// A�ade una nueva animaci�n que iniciar� cuando el callback pasado devuelva true
	void addAction(string key, Animation anim, BoolCallBack cb);
	// A�ade animaci�n de ataque que iniciar� cuando el callback pasado devuelva true
	void addAttack(Animation anim, BoolCallBack cb);


	// Devuelve si la acci�n del jugador es idle, siempre se comprueba la �ltima
	virtual bool idling();
	// Devuelve si la acci�n del jugador es movimiento, siempre se coprueba justo antes de idling
	virtual bool moving();


	// Si el jugador se mueve a la izquierda hace flip horizontal y viceversa
	void adjustDirection();
	// Asigna si quiere que el sprite haga flip en funci�n de su direcci�n
	inline void setWantToAdjustDirection(bool want) {
		wantToAdjustDirection = want;
	}
};

