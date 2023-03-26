#pragma once
#include "../utils/Singleton.h"
#include "CardsDataContainer.h"
#include <fstream>
#include <unordered_set>
class Album : public Singleton<Album> {
	friend Singleton<Album>;
private:
	std::vector<CardData> foundCards;
	std::unordered_set<std::string> foundCardsNames;
	std::string filename;

	std::array<std::vector<bool>, 3> foundCardsByTime;

	// Constructora
	Album();
	// Carga las cartas del �lbum desde archivo json
	void loadFromJSON();
	// Guarda las cartas del �lbum en archivo json
	void saveToJSON();
public:
	// Destructora, guarda el album
	virtual ~Album();
	// A�ade una carta al �lbum si no est� ya en �l
	void addCard(CardData cData);
	// Devuelve el vector de cartas encontradas
	inline std::vector<CardData> const& getFoundCards() { return foundCards; }
	// Devuelve el vector de cartas encontradas
	inline auto const& getFoundCardsByTime() { return foundCardsByTime; }
};