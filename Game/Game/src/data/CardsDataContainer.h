#pragma once

#include "../utils/Singleton.h"
#include "../components/ecs.h"
#include "CardData.h"
#include "json/JSON.h"
#include "../sdlutils/SDLUtils.h"
#include <array>

class CardsDataContainer : public Singleton<CardsDataContainer> {
	friend Singleton<CardsDataContainer>;
private:
	unordered_map<std::string, CardData> cardsDataMap;
	SDLUtils::map_access_wrapper<CardData> cardsDatas;

	std::array<vector<CardData>, 3> cardsByTime;
	std::array<unordered_map<std::string, int>, 3> cardsIndexByTime;

	// Constructora
	CardsDataContainer();
	// Lee la información de las cartas desde JSON
	void readFromJSON(std::string filename);
	CardTime stringToCardTime(std::string t);
public:
	inline int numOfCards() { return cardsDataMap.size(); }
	// Devuelve el struct CardData pedido
	inline auto& get(std::string key) {
		return cardsDatas.at(key);
	}

	inline auto const& getCardsByTime() { return cardsByTime; }
	inline auto const& getCardsIndexByTime() { return cardsIndexByTime; }
};

// Devuelve una referencia a la instancia a CardsDataContainer
inline CardsDataContainer& cardsData() {
	return *CardsDataContainer::instance();
}