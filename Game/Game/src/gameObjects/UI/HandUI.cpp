#include "HandUI.h"

void HandUI::initGameObject(CardComponent* _cComp) {
	// Puntero al cardcomponent
	cardComp = _cComp;

	// Crear las cartas reflejadas por pantalla
	createUI();
}


HandUI::~HandUI() {
	for (auto gobj : handUI) delete gobj;
}

void HandUI::update() {
	for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) {
			auto object = handUI[i];
			object->ammoBar->update();
		}
	}
}

// Renderizar los GameObjects del deque (de lo contrario solo se renderiza un objeto vac�o)
void HandUI::render() const {
	for (int i = 0; i < handUI.size(); i++) {
		if (handUI[i] != nullptr) {
			auto object = handUI[i];
			object->card->render();
			object->ammoNumber.first->render();
			object->ammoNumber.second->render();
			object->ammoBar->render();
		}
	}
}

// Cambia la carta seleccionada, deseleccionando la anterior
void HandUI::changeSelected(bool key, int number) {
	// Deseleccionar la carta anterior, volviendo a su posici�n original si no es esta llamada debida a un descarte
	if (active != handUI.end()) {
		(*active)->card->getComponent<Transform>()->setY(Y_CARD_POS);
		auto trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
		auto trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
		auto trBar = (*active)->ammoBar->getComponent<Transform>();
		trDecs->setY(trDecs->getY() + 60);
		trUnits->setY(trUnits->getY() + 60);
		trBar->setY(trBar->getY() + 60);
	}

	// Si se ha cambiado pulsando teclas
	if (key) {
		// Avanzar el iterador que apunta a la carta activa hasta la correspondiente
		active = handUI.begin();
		std::advance(active, number);
	}
	// ... si ha sido por la rueda del rat�n
	else {
		// Scroll hacia arriba
		if (number == 1) ++active;
		// ... scroll hacia abajo
		else --active;
	}

	// Seleccionar la carta escogida
	(*active)->card->getComponent<Transform>()->setY(Y_CARD_POS_SELECTED);
	auto trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
	auto trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
	auto trBar = (*active)->ammoBar->getComponent<Transform>();
	trDecs->setY(trDecs->getY() - 60);
	trUnits->setY(trUnits->getY() - 60);
	trBar->setY(trBar->getY() - 60);
}

// Borrar la carta correspondiente
void HandUI::discard(deque<Card*>::iterator discarded) {
	// Buscar y borrar carta y asignar la nueva activa
	auto aux = searchCard(discarded);
	delete *aux;
	active = handUI.erase(aux);

	// Si la mano no se ha vaciado, marcar la carta inicial
	if (handUI.size() > 0) {
		changeSelected(true, 0);
		switch (handUI.size()) {
			case 1: rearrangeOne(); break;
			case 2: rearrangeTwo(); break;
			case 3: rearrangeThree(); break;
		}
	}
}

// Reduce la munici�n
void HandUI::changeAmmo(deque<Card*>::iterator used) {
	// Buscar y reducir su munici�n
	auto aux = searchCard(used);
	(*aux)->ammo--;

	// Mostrar n�mero correcto
	(*aux)->ammoNumber.first->getComponent<Animator>()->play(to_string((*aux)->ammo / 10));
	(*aux)->ammoNumber.second->getComponent<Animator>()->play(to_string((*aux)->ammo - (*aux)->ammo / 10));

	// Reducir tama�o de la barra
	changeAnimatorSrcRelativeWidth((*aux)->ammoBar, (*aux)->maxAmmo, (*aux)->ammo);
	auto tr = (*aux)->ammoBar->getComponent<Transform>();
}

// Crear las cartas de la UI seg�n la mano del jugador, iniciando variables y posicion�ndolas correctamente
void HandUI::createUI() {
	// Borrar la mano anterior y obtener la mano actual del jugador
	handUI.clear();
	handPlayer = cardComp->getHand();

	// Crear las 4 cartas con sus posiciones correspondientes
	createCard(0, X1_4CARDS_POS, Y_CARD_POS_SELECTED, -10);
	createCard(1, X2_4CARDS_POS, Y_CARD_POS, -5);
	createCard(2, X3_4CARDS_POS, Y_CARD_POS, 5);
	createCard(3, X4_4CARDS_POS, Y_CARD_POS, 10);

	// Marcar como activa la primera carta
	active = handUI.begin();
}

void HandUI::createCard(int i, int posX, int posY, int rotation) {
	// Crear estructura
	UICard* newCard = new UICard(); 

	// Crear la carta y a�adirle sus componentes image y tansform
	newCard->card = new GameObject();
	newCard->card->addComponent<Transform>(Vector2D(posX, posY), Vector2D(), UI_CARD_WIDTH, UI_CARD_HEIGHT, rotation);
	newCard->card->addComponent<Image>(handPlayer[i]->getTexture());

	// Guardar munici�n
	newCard->maxAmmo = handPlayer[i]->getUses();
	newCard->ammo = handPlayer[i]->getUses();

	// Variables de posici�n de n�meros y barra de munici�n
	Vector2D posDecs; Vector2D posUnits;
	Vector2D posBar;
	switch (i) {
		case 0:
			posDecs = Vector2D(posX + X1_XOFFSET_DECS, posY + X1_YOFFSET_DECS);
			posUnits = Vector2D(posX + X1_XOFFSET_UNITS, posY + X1_YOFFSET_UNITS);
			posBar = Vector2D(posX + 22, posY + 17.5);
			break;
		case 1:
			posDecs = Vector2D(posX + X2_XOFFSET_DECS, posY + X2_YOFFSET_DECS);
			posUnits = Vector2D(posX + X2_XOFFSET_UNITS, posY + X2_YOFFSET_UNITS);
			posBar = Vector2D(posX + 32, posY + 17.5);
			break;
		case 2:
			posDecs = Vector2D(posX + X3_XOFFSET_DECS, posY + X3_YOFFSET_DECS); 
			posUnits = Vector2D(posX + X3_XOFFSET_UNITS, posY + X3_YOFFSET_UNITS);
			posBar = Vector2D(posX + 52, posY + 20);
			break;
		case 3:
			posDecs = Vector2D(posX + X4_XOFFSET_DECS, posY + X4_YOFFSET_DECS);
			posUnits = Vector2D(posX + X4_XOFFSET_UNITS, posY + X4_YOFFSET_UNITS);
			posBar = Vector2D(posX + 61, posY + 22);
			break;
	}

	// Crear n�meros
	newCard->ammoNumber.first = createNumber(posDecs, rotation, newCard->maxAmmo / 10);
	newCard->ammoNumber.second = createNumber(posUnits, rotation, newCard->maxAmmo - (newCard->maxAmmo / 10));

	// Crear barra de munici�n
	newCard->ammoBar = new GameObject();
	newCard->ammoBar->addComponent<Transform>(posBar, Vector2D(), 40 * 3, 5 * 3, rotation);
	auto anim = newCard->ammoBar->addComponent<Animator>(SDLApplication::getTexture(CARD_AMMO), 40, 5, 4, 1);

	// Mantener en la c�mara y crear y reproducir animaciones
	anim->attachToCamera();
	anim->createAnim(CARD_AMMO, 0, 4, 6, -1);
	anim->play(CARD_AMMO);

	// A�adir a la deque de la UI
	handUI.push_back(newCard);
}

// Crear un n�mero seg�n los datos recibidos
GameObject* HandUI::createNumber(Vector2D pos, float rotation, int value) {
	// Crear objeto
	auto number = new GameObject();

	// A�adir componentes (transform y animator)
	number->addComponent<Transform>(pos, Vector2D(), UI_AMMO_NUMBERS_WIDTH, UI_AMMO_NUMBERS_HEIGHT, rotation);
	createNumberAnims(number, value);

	// Devolver el n�mero creado
	return number;
}

// Posiciona las 3 cartas restantes de forma que una est� en medio sin rotaci�n, y las otras a su alrededor ligeramente rotadas
void HandUI::rearrangeThree() {
	// Iterador para recorrer la mano y puntero a transforms para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	Transform* trBar = nullptr;

	// Primera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X1_3CARDS_POS); tr->setRotation(-5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X2_XOFFSET_DECS, tr->getY() + X2_YOFFSET_DECS)); trDecs->setRotation(-5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X2_XOFFSET_UNITS, tr->getY() + X2_YOFFSET_UNITS)); trUnits->setRotation(-5);
	trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 32, tr->getY() + 17)); trBar->setRotation(-5);
	it++;

	// Segunda carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(CENTERED_CARD_POS); tr->setRotation(0);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + XC_XOFFSET_DECS, tr->getY() + XC_YOFFSET)); trDecs->setRotation(0);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + XC_XOFFSET_UNITS, tr->getY() + XC_YOFFSET)); trUnits->setRotation(0);
	trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 42, tr->getY() + 18)); trBar->setRotation(0);
	it++;

	// Tercera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X3_3CARDS_POS); tr->setRotation(5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X3_XOFFSET_DECS, tr->getY() + X3_YOFFSET_DECS)); trDecs->setRotation(5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X3_XOFFSET_UNITS, tr->getY() + X3_YOFFSET_UNITS)); trUnits->setRotation(5);
	trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 51.5, tr->getY() + 20)); trBar->setRotation(5);
}

// Posiciona las 2 cartas restantes correctamente, ligeramente rotadas
void HandUI::rearrangeTwo() {
	// Iterador para recorrer la mano y puntero a transform para posicionar
	auto it = handUI.begin();
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	Transform* trBar = nullptr;

	// Primera carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X2_4CARDS_POS); tr->setRotation(-5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X2_XOFFSET_DECS, tr->getY() + X2_YOFFSET_DECS)); trDecs->setRotation(-5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X2_XOFFSET_UNITS, tr->getY() + X2_YOFFSET_UNITS)); trUnits->setRotation(-5);
	trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 32, tr->getY() + 17)); trBar->setRotation(-5);
	it++;

	// Segunda carta
	tr = (*it)->card->getComponent<Transform>();
	tr->setX(X3_4CARDS_POS); tr->setRotation(5);
	trDecs = (*it)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + X3_XOFFSET_DECS, tr->getY() + X3_YOFFSET_DECS)); trDecs->setRotation(5);
	trUnits = (*it)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + X3_XOFFSET_UNITS, tr->getY() + X3_YOFFSET_UNITS)); trUnits->setRotation(5);
	trBar = (*it)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 51.5, tr->getY() + 20)); trBar->setRotation(5);
}

// Posiciona la carta restante en el centro sin rotaci�n
void HandUI::rearrangeOne() {
	Transform* tr = nullptr;
	Transform* trDecs = nullptr;
	Transform* trUnits = nullptr;
	Transform* trBar = nullptr;

	tr = (*active)->card->getComponent<Transform>();
	tr->setX(CENTERED_CARD_POS);
	tr->setRotation(0);
	trDecs = (*active)->ammoNumber.first->getComponent<Transform>();
	trDecs->setPos(Vector2D(tr->getX() + XC_XOFFSET_DECS, tr->getY() + XC_YOFFSET)); trDecs->setRotation(0);
	trUnits = (*active)->ammoNumber.second->getComponent<Transform>();
	trUnits->setPos(Vector2D(tr->getX() + XC_XOFFSET_UNITS, tr->getY() + XC_YOFFSET)); trUnits->setRotation(0);
	trBar = (*active)->ammoBar->getComponent<Transform>();
	trBar->setPos(Vector2D(tr->getX() + 42, tr->getY() + 18)); trBar->setRotation(0);
}

// Buscar la carta correspondiente y devolver un iterador apuntando a esta
deque<UICard*>::iterator HandUI::searchCard(deque<Card*>::iterator searched) {
	// Busqueda de la carta correspondiente. Aux: iterador que referencia al mazo de la UI, para saber cual borrar
	int i = 0;
	auto aux = handUI.begin();
	handPlayer = cardComp->getHand();
	bool discard = false;
	while (i < handPlayer.size() && !discard) {
		// Si la carta es la buscada, en aux ya debe de estar la carta de la UI, se sale del bucle
		if (handPlayer[i] == *searched) discard = true;
		// ... de lo contrario, continuar iterando comprobando si es la siguiente carta de la UI
		else { i++; aux++; }
	}

	return aux;
}

// Crear los n�meros de la interfaz
void HandUI::createNumberAnims(GameObject* obj, int value) {
	// A�adir animator y crear animaciones
	auto anim = obj->addComponent<Animator>(SDLApplication::getTexture(STATISTICS_NUMBERS), ST_NUMBERS_WIDTH, ST_NUMBERS_HEIGHT, ST_NUMBERS_ROWS, ST_NUMBERS_COLUMNS);
	for (int j = 0; j < N_NUMBERS; j++) anim->createAnim(to_string(j), j, j, 1, 0);
	
	// Reproducir animaci�n correspondiente
	anim->play(to_string(value));
}

// C�lcula y cambia el ancho de animaci�n al correspondiente
void HandUI::changeAnimatorSrcRelativeWidth(GameObject* bar, float maxValue, float value) {
	bar->getComponent<Animator>()->setSrcRectRelativeWidth(getFactored(maxValue, value));
}

// Devuelve en 0.XX el valor del factor que usar en el animator
float HandUI::getFactored(float maxValue, float value) {
	return value / maxValue;
}