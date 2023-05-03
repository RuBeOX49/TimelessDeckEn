﻿#include "InventoryScene.h"
#include "../core/SDLApplication.h"


// Se encarga de cargar todos los datos desde el dataplayer, así como obtener los datos del deck y de la library
InventoryScene::InventoryScene() : GameState() {
	
	vector<CardId> const& currentLibrary = PlayerData::instance()->getLibrary();
	vector<CardId> const& currentDeck = PlayerData::instance()->getDeck();

	for (CardId crd : currentLibrary) {
		auto invCard = inventory.find(Card::getCardIDfromEnum(crd));
		// Si la carta no está, se añade al inventario
		if (invCard == inventory.end()) {
			invCard = inventory.insert({ Card::getCardIDfromEnum(crd), InventoryInfo() }).first;
			invCard->second.card = crd;
		}
		// Aumentar su cantidad en el inventario
		++invCard->second.cuantity;
	}

	for (CardId crd : currentDeck) {
		inventory[Card::getCardIDfromEnum(crd)].cuantityDeck++;
	}

	// Llamamos a Player data para pillar la info de las cartas que se tienen
	stats.push_back(PlayerData::instance()->getMaxHP());
	stats.push_back(PlayerData::instance()->getMaxMana());
	stats.push_back(PlayerData::instance()->getPlayerMoveSpeed() / 2);
	stats.push_back(PlayerData::instance()->getAttackMult() * 100);
	stats.push_back(PlayerData::instance()->getFireRateMult() * 100);

	//Imagen de fondo
	GameObject* background = addGameObject();
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("InventoryBackground"));

	createMoneyInfo();
	createObjects(); 
	createCards();
	createPanels();

	// Los simbolos
	for (int i = 0; i < 5; i++) {
		createSymbol(SYMBOL_POSITIONS[i], SYMBOLS_KEYS[i], STATS_TEXTS[i], stats[i]);
	}
	// Creamos el boton de salir
	AnimatorInfo aI = AnimatorInfo(EXIT);
	exitButton = addGameObject<Button>(_grp_UI,
		[&]() {
			int cardsInDeck = 0;
			for (auto& crd : inventory) {
				if (inventory[Card::getCardIDfromEnum(crd.second.card)].cuantityDeck > 0) {
					cardsInDeck += inventory[Card::getCardIDfromEnum(crd.second.card)].cuantityDeck;
				}
			}
			if (cardsInDeck >= 4) SDLApplication::popGameState();
		}, IS_EXIT_BUTTON_POS , aI);
}

void InventoryScene::createSymbol(Vector2D _pos, string key, string text, int val) {
	GameObject* symbol = addGameObject();
	symbol->addComponent<Transform>(_pos, VECTOR_ZERO, SYMBOL_DIMENSIONS, SYMBOL_DIMENSIONS);
	symbol->addComponent<Image>(SDLApplication::getTexture(key));

	GameObject* stat = addGameObject();
	stat->addComponent<Transform>(_pos + STAT_OFFSET, VECTOR_ZERO, 100, 24);
	stat->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), text);

	GameObject* value = addGameObject();
	value->addComponent<Transform>(_pos + STAT_VALUE_OFFSET, VECTOR_ZERO, 50, 24);
	value->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR20"), to_string(val));
}

// Crea los paneles en los que se colocan las cartas
void InventoryScene::createPanels() {
	deckPanel = createPanel(DP_POSITION, DP_WIDTH, PANEL_HEIGHT, DECK_PANEL);
	createPanel(OP_POSITION, OP_WIDTH, PANEL_HEIGHT, OBJECTS_PANEL);
	inventoryPanel = createPanel(IP_POSITION, IP_WIDTH, PANEL_HEIGHT, INVENTORY_PANEL);
	createPanel(SP_POSITION, SP_WIDTH, PANEL_HEIGHT, STATS_PANEL);

	deckPanel->removeComponent<Image>();
	inventoryPanel->removeComponent<Image>();
}

GameObject* InventoryScene::createPanel(Vector2D pos, int w, int h, string textureKey) {
	GameObject* panel = addGameObject();
	panel->addComponent<Transform>(pos, VECTOR_ZERO, w, h);
	panel->addComponent<Image>(SDLApplication::getTexture(textureKey));

	return panel;
}

void InventoryScene::createMoneyInfo() {
	//Icono de moneda
	GameObject* coin = addGameObject();
	Vector2D pos = Vector2D(WIN_WIDTH - 100, 15);
	coin->addComponent<Transform>(pos, Vector2D(), 64, 64);
	coin->addComponent<Image>(SDLApplication::getTexture("Coin"));

	// Texto con el numero de monedas
	int m = PlayerData::instance()->getMoney();
	GameObject* mon = addGameObject();
	if (m / 100 == 0) {
		if (m / 10 == 0) mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 220, 15), VECTOR_ZERO, 50, 48);
		else mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 245, 15), VECTOR_ZERO, 50, 48);
	}
	else mon->addComponent<Transform>(Vector2D(WIN_WIDTH - 270, 15), VECTOR_ZERO, 50, 48);
	mon->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_BOLD46"), to_string(m));
}

void InventoryScene::createObjects() {
	auto objs = PlayerData::instance()->getRelics();

	int i = 0;
	for (auto& rel : objs) {
		GameObject* g = addGameObject();
		g->addComponent<Transform>(OBJECTS_POSITIONS[i], VECTOR_ZERO, OBJECTS_DIMENSIONS, OBJECTS_DIMENSIONS);
		g->addComponent<Image>(rel->texture);
		++i;
	}
}

// Se encarga de crear las imagenes de las cartas en el inventario con sus cantidades
void InventoryScene::createCards() {
	bool row = true;
	int column = 0;
	int deckColumn = 0;

	for (auto& crd : inventory) {
		Vector2D pos = Vector2D(20 + (ALB_CARD_W + 20) * column, 10 + (ALB_CARD_H + 20) * (row ? 0 : 1));
		Button* cardButton = createCard(pos, crd.second.card, false);
		if (column == 0 && !row) cardButton->setAsDefaultButton();

		if (crd.second.cuantityDeck > 0) {
			createDeckCards(crd.second.card, deckColumn);
			deckColumn++;
		}

		row = !row;
		if (row) {
			column++;
		}
	}
}
// Se encarga de crear las imagenes de las cartas en la zona del deck
void InventoryScene::createDeckCards(CardId crd, int column) {
	Vector2D posD = Vector2D(20 + 160 * column, DECK_HEIGHT - 30);
	createCard(posD, crd, true);
}
// Se encarga de crear el objeto de la carta, así como sus botones y le añaden la funcionalidad para quitar o poner en el deck
Button* InventoryScene::createCard(Vector2D pos, CardId crd, bool dck) {
	CardData const& cardDt = cardsData().get(Card::getCardIDfromEnum(crd));

	// Imagen de la carta
	GameObject* cardObj = addGameObject();
	cardObj->addComponent<Transform>(pos, VECTOR_ZERO, ALB_CARD_W, ALB_CARD_H);
	cardObj->addComponent<Image>(cardDt.texture);
	// Botón de la carta con su función 
	Button* b = addGameObject<Button>([&, deck = dck, card = crd]()
		{
			InventoryInfo& invCard = inventory.find(Card::getCardIDfromEnum(card))->second;
			// Si se dice que es deck y en el deck hay alguna carta de ese tipo o si se dice que no es deck y hay en deck menos que el total disponible
			if (deck? invCard.cuantityDeck > 0 : invCard.cuantityDeck < invCard.cuantity) {
				// Si era el botón en el deck reduce su cantidad
				if (deck) {
					--invCard.cuantityDeck;
					// Si se borra por completo del deck este se reorganiza
					if (invCard.cuantityDeck == 0) {
						reloadDeckCards();
					}
				}
				// Si era el botón fuera del deck se aumente su canidad en este
				else {
					invCard.cuantityDeck++;
					// Si se añade por primera vez al deck este se reorganiza
					if (invCard.cuantityDeck == 1) {
						reloadDeckCards();
					}
				}

				invCard.myText->changeText(to_string(invCard.cuantity - invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
				invCard.myDeckText->changeText(to_string(invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
			}
		}
		, pos, AnimatorInfo("CardSelection", ALB_CARD_W, ALB_CARD_H, cardDt.texture->width(), cardDt.texture->height(), 1, 4),
			-1, nullptr, 0.5f, 0.5f); 
	
	Animator* a = b->getComponent<Animator>();
	a->createAnim(ONOUT, UNSELECTED_CARD_ANIM);
	a->createAnim(ONOVER, SELECTED_CARD_ANIM);
	a->createAnim(ONCLICK, CLICKED_CARD_ANIM);
	a->play(ONOUT);

	// Texto que indica cuantas cartas hay en el deck
	GameObject* textFrame = addGameObject();
	GameObject* text = addGameObject();
	InventoryInfo& invCard = inventory.find(Card::getCardIDfromEnum(crd))->second;
	Transform* tr = text->addComponent<Transform>(Vector2D (pos.getX() + ALB_CARD_W - 20, pos.getY()), VECTOR_ZERO, 70, 48);
	(dck ? invCard.myDeckText : invCard.myText) = text->addComponent<TextComponent>(SDLApplication::getFont("SILKSCREEN_REGULAR16"),  to_string(dck ? invCard.cuantityDeck : invCard.cuantity - invCard.cuantityDeck) + "/" + to_string(invCard.cuantity));
	textFrame->addComponent<Transform>(tr->getPos() - Vector2D(3, 7), VECTOR_ZERO, tr->getWidth() + 5, tr->getWidth() + 5);
	textFrame->addComponent<Image>(SDLApplication::getTexture("CardCircle"));

	if (dck) {
		deckButtons[crd].deckButton = b;
		deckButtons[crd].deckImage = cardObj;
		deckButtons[crd].deckText = text;
		deckButtons[crd].deckTextFrame = textFrame;
	}

	return b;
}

InventoryScene::~InventoryScene() {
	vector<CardId> newDeck;
	for (auto& crd : inventory) {
		for (int i = 0; i < crd.second.cuantityDeck; i++) {
			newDeck.push_back(crd.second.card);
		}
	}

	PlayerData::instance()->setDeck(newDeck);
}


void InventoryScene::handleInput() {
	GameState::handleInput();
	if (gmCtrl_.goBack()) {
		if (exitButton->isCurrentButton()) butNavigator->selectDefaultButton();
		else exitButton->setAsCurrentButton();
	}
}

void InventoryScene::reloadDeckCards() {
	for (auto obj : deckButtons) {
		obj.second.deckButton->setAlive(false);
		obj.second.deckImage->setAlive(false);
		obj.second.deckText->setAlive(false);
		obj.second.deckTextFrame->setAlive(false);
	}
	int column = 0;
	for (auto& crd : inventory) {
		if (crd.second.cuantityDeck > 0) {
			createDeckCards(crd.second.card, column);
			column++;
		}
	}
}

void InventoryScene::update() {
	GameState::update();

	int x; int y;
	SDL_GetMouseState(&x, &y);

	if (x >= 0 && x <= 942 && y >= 0 && y <= 461) {
		if (!inventoryPanel->hasComponent<Image>()) {
			inventoryPanel->addComponent<Image>(SDLApplication::getTexture("InventoryPanel"));
			deckPanel->removeComponent<Image>();
		}
	}
	else if (x >= 0 && x <= 942 && y > 461 && y <= 720) {
		if (!deckPanel->hasComponent<Image>()) {
			deckPanel->addComponent<Image>(SDLApplication::getTexture("DeckPanel"));
			inventoryPanel->removeComponent<Image>();
		}
	}
	else {
		if (inventoryPanel->hasComponent<Image>()) inventoryPanel->removeComponent<Image>();
		if (deckPanel->hasComponent<Image>()) deckPanel->removeComponent<Image>();
	}
}