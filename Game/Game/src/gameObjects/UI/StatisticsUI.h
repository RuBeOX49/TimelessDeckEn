#pragma once
#include "../../core/SDLApplication.h"
#include "../GameObject.h"
#include "../../components/Player components/BarComponent.h"
#include <tuple>

// Tipos propios
using decs = int;
using cents = int;
using unids = int;

class StatisticsUI : public GameObject {
private:
	// Objeto
	GameObject* statistics;

	// Indicador de �ter
	GameObject* etherMeterFrame;
	GameObject* etherMeter;
	// Barras de vida y man�
	GameObject* manaBar;
	GameObject* healthBar;

	// Contadores
	vector<GameObject*> lifeCounter;
	vector<GameObject*> manaCounter;
	vector<GameObject*> etherCounter;

	float fullMana;
	float fullLife;

public:
	// Inicializar objeto
	void initGameObject(int life, int mana);

	// M�todos virtuales
	virtual void render() const;
	virtual void update();

	// N�meros de man� y vida
	void createNumberAnims(GameObject* obj, int value, int i, bool isBar = true);

	// Crear las barras de mana y de vida
	void createLifeBar(int value);
	void createManaBar(int value);
	void createEtherMeter();

	// M�todos para cambios en las barras anteriores
	void OnManaChanges(float value);
	void OnHealthChanges(float value);
	void OnEtherChanges(float value);
	void changeNumbers(vector<GameObject*> vect, int value);

	// C�lculos
	tuple<cents, decs, unids> getUnits(int value);
	void changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value);
	void changeAnimatorSrcRelativeHeight(GameObject* bar, float maxValue, float value);
};