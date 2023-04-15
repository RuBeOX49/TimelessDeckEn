#pragma once
#include "GameState.h"
#include <map>
#include <vector>


class Card;
struct InventoryInfo {

	int cuantity = 0;
	int cuantityDeck = 0;
	CardId card;
	GameObject* myText;

	InventoryInfo() : cuantity(0), cuantityDeck(0), card(_card_NULL) { };
};

class InventoryScene : public GameState {
private:
	std::map<string,InventoryInfo> inventory;
	vector<int> stats;
public:
	InventoryScene();
	virtual ~InventoryScene();
	// Crear un bot�n especificado en la escena
	void createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key);
	void createSymbol(Vector2D _pos, string key, string text, int val);
	void createPanels();
	void createMoneyInfo();
	void createObjects();
	void createCards();
	void createCard(Vector2D pos, CardId card, bool deck);
};