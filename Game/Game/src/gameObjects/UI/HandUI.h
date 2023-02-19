#pragma once
#include "../../core/SDLApplication.h"
#include "../../core/GameObject.h"

class HandUI : public GameObject
{
private:
	// Puntero al componente de cartas del jugador
	CardComponent* cardComp = nullptr;

	// Deque con la mano del jugador e iterador con la carta activa
	deque<GameObject*> handUI;
	deque<Card*> handPlayer;
	deque<GameObject*>::iterator active;

public:
	// Constructora
	virtual void initGameObject(CardComponent* _cComp);

	// M�todos virtuales
	virtual void render() const;

	// Crear o recrear la UI
	void createUI();

	// Cambiar de selecci�n (llamado SIEMPRE por BattleScene)
	void changeSelected(bool key, int number);

	// Descartar una carta
	void discard(deque<Card*>::iterator discarded);
};

