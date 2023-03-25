#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include <cmath>

struct UICard {
	GameObject* card;
	pair<GameObject*, GameObject*> ammoNumber;
	GameObject* ammoBar;
	Vector2D initialAmmoBarPosition;
	int ammo;
	int maxAmmo;

	UICard() : card(nullptr), ammo(0), maxAmmo(INT_MAX) {};
	~UICard() {
		delete card;
		delete ammoNumber.first;
		delete ammoNumber.second;
		delete ammoBar;
	}
};

class HandUI : public GameObject
{
private:
	// Puntero al componente de cartas del jugador
	CardComponent* cardComp = nullptr;

	// Deque con la mano del jugador e iterador con la carta activa
	deque<UICard*> handUI;
	deque<Card*> handPlayer;
	deque<UICard*>::iterator active;

public:
	// Constructora
	virtual void initGameObject(CardComponent* _cComp);
	virtual ~HandUI();
	// M�todos virtuales
	virtual void render() const;

	// Crear o recrear la UI
	void createUI();
	void createCard(int i, int posX, int posY, int rotation);

	// Cambiar de selecci�n (llamado SIEMPRE por BattleScene)
	void changeSelected(bool key, int number);

	// Descartar una carta
	void discard(deque<Card*>::iterator discarded);

	// Cambiar la munici�n de una carta
	void changeAmmo(deque<Card*>::iterator used);
	void changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value);
	float getFactored(float maxValue, float value);

	// Reposiciona las cartas seg�n el n�mero de cartas que quedan en la mano
	void rearrangeThree();
	void rearrangeTwo();
	void rearrangeOne();

	// Buscar la carta recibida del cardComp en la mano de la UI
	deque<UICard*>::iterator searchCard(deque<Card*>::iterator searched);

	GameObject* createNumber(Vector2D pos, float rotation, int value);
	void createNumberAnims(GameObject* obj, int value);
};

