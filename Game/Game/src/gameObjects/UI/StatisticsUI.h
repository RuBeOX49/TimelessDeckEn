#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include "../../components/Player components/BarComponent.h"

class StatisticsUI : public GameObject {
private:
	// Objeto
	GameObject* statistics;

	// Indicador de �ter
	GameObject* etherMeter;
	// Barras de vida y man�
	GameObject* manaBar;
	GameObject* healthBar;

	// Contadores
	vector<GameObject*> lifeCounter;
	vector<GameObject*> manaCounter;

	float fullMana;
	float fullLife;

public:
	void initGameObject(int life, int mana);

	// M�todos virtuales
	virtual void render() const;
	virtual void update();

	void createLifeBar(int value);
	void createManaBar(int value);

	void OnManaChanges(float value);
	void OnHealthChanges(float value);
};