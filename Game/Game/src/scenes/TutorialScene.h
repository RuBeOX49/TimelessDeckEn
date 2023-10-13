#pragma once
#include "BattleScene.h"
#include "../gameObjects/General Objects/Tuto.h"
#include "../components/General Components/TutorialComponent.h"

class TutorialScene : public BattleScene {
private:
	// Objetos de tutorial
	TutorialComponent* tutorialController;
	Tuto* tuto;
	// Enemigo para testear
	GameObject* testEnemy;
	// Cosas del popup
	GameObject* screen;
	GameObject* tutoPopUp;
	GameObject* textOne;
	GameObject* textTwo;
	Button* exitButton;
	Button* skipButton;
	// Paso en el que estamos
	int current;

	string tutorialTexts[14] = {
		// Movimiento
		"¡Bienvenido a Timeless Deck! Yo soy Tuto y voy a ser tu guía en este lugar.\nPara empezar, siempre que aparezca aquí debes pulsar 'REANUDAR' para continuar.",
		"\nDicho esto, prueba a moverte con los controles que te voy a mostrar por pantalla.",
		
		// Carta
		"¡Muy bien! Pues ya va siendo hora de enseñarte la magia de este lugar... ¡tus armas son cartas!",
		"\nMira, voy a darte una para probar, aunque realmente puedes llevar hasta 4 como máximo en tu mano.\nFíjate en mi pantalla para aprender a apuntar y disparar y en la carta para ver sus usos.",
		
		// Mano
		"¡Genial! Además de las 4 cartas de tu mano, contarás con una pila de descartes y un mazo, cada uno a un lado.",
		"Cuando gastes una carta, pasará a los descartes y, de ser la última de la mano, cogerás 4 nuevas del mazo. Estos mazos ciclarán entre ellos y el mazo se barajeará cada vez que se acabe con la pila. ¡Pruébalo!",
		
		// Enemigos
		"¡Aprendes rápido, eh! En este lugar deberás derrotar enemigos para poder avanzar. Estos enemigos te quitarán vida si te golpean, así que dalo todo para derrotarlos.",
		"\nPor ahora, cuentas con 100 puntos de vida (barra roja), pero cada enemigo te hará un daño diferente. Recuerda que puedes seleccionar qué carta usas.",
		
		// Habilidad
		"¿Has visto eso? ¡El enemigo te ha soltado maná! (piedras azules).\nEl maná (barra azul) será necesario para usar las habilidades de las cartas y para recogerlo deberás pasar sobre él.",
		"\nLas habilidades vienen indicadas en la zona superior de las cartas junto al maná que consumen, ¡prueba a usar una!",
	
		// Portal
		"El enemigo te puede soltar otra cosa... ¡éter! (polvo morado).\nEl éter (barra blanca) será necesario para cargar el portal, teniendo que llegar al 100% del medidor para poder avanzar al siguiente nivel.",
		"\nSe recogerá solo tras cierto tiempo, así que tú preocupate de derrotar a cuantos más enemigos mejor.",
	
		// Fin
		"¡Bien hecho, eso es todo! Ahora llenaré tu barra de éter al 100% y podrás salir del nivel tal y como te voy a indicar por pantalla.",
		"\nCon esto dicho, solo me queda despedirme. ¡Ánimo en tu aventura! ¡Nos vemos en el espacio, cowboy!"
	};

	string tutorialTextsEn[14] = {
		// Movimiento
		"Welcome to Timeless Deck! I am Tuto and I will be your guide in this place.\n For starters, every time I show up you must press 'REANUDAR' to continue.",
		"\nThat being said, try moving with the controls I will show you on screen",

		// Carta
		"Very well! It's about time I show you the magic of this place... your weapons are cards!",
		"\nLook, Im gonna give you a card for you to try, although you can have 4 maximum cards in your hand.\nCheck my screen to learn how to aim and shoot and check the card to see their uses.",

		// Mano
		"Great! On top of the four cards in your hand, you will have a discard pile and a deck, each one on one side.",
		"When you consume a card, it will be discarded and if you have no more cards after that, you will draw 4 more from the deck. When the deck runs out of cards, the discard pile will shuffle and make a new deck. Try it!",

		// Enemigos
		"You're a fast learner! Here in this place you must defeat enemies in order to continue. These enemies will try to hurt you bad, so give it your everything to defeat them.",
		"\nFor now, you have 100 health points (red bar), but every enemy will deal you different damage. Remember: you can choose which card you use.",

		// Habilidad
		"See that? The enemy has dropped mana! (blue stones).\nMana (blue bar) is required to use the cards' skills. Run over them to pick them up.",
		"\nCard skills show up in their upper zone with how much mana costs to activate, and will consume ALL card uses. Try using one!",

		// Portal
		"The enemy drops other stuff... aether! (purple dust).\nYou will need aether (white circle) to charge the portal, having to load it to 100% in order to get to the next nivel.",
		"\nAether will fly to you after a time, so you just have to worry about defeating the more enemies the better!.",

		// Fin
		"Alright, that is all! Im going to top up you aether charge and you will be able to leave the zone as you will see on my screen.",
		"\nWith this said, it's time for me to leave. Good luck in your adventure! See you in space, cowboy!"
	};

public:
	// Constructora
	TutorialScene(BattleType bt);

	// Notifica de que se ha descartado una carta, que se crea una nueva mano y que se ha usado una habilidad
	void notifyDiscard() {
		tutorialController->setDiscarted(true);
	}

	void notifyNewHand() {
		tutorialController->setNewHand(true);
	}

	void notifyAbility() {
		tutorialController->setAbility(true);
	}

	void hideTuto();

	// PASOS DEL TUTORIAL
	// Activar input 
	void activateInput();
	// Añadir carta (enseñar como se apunta y como se usan)	
	void addCard();
	// Enseña sobre el sistema de cartas
	void explainCardSystem();
	// Añadir enemigos (matarlos) y las barras de vida y mana
	void addMeleeEnemy();
	// Enseñar a usar las habilidades de las cartas (y que el mana baja)
	void showAbility();
	// Añadir aun mas enemigos y mostrar que sube el maná si droppean
	void showDrops();
	// Explicar que los enemigos cargan el portal
	void showPortalCharges();
	// Activa el popup
	void activatePopUp();
	// Desactiva el popup
	void deactivatePopUp();
	
	// Salta el tutorial
	void exit();

	// Texto del popup
	void showPopUpText();

	// Comprueba si hay enemigos o mana en la escena
	bool getTestEnemy() { return getEntitiesByGroup(_grp_ENEMIES).size() == 0; };
	bool getManaNumber() { return getEntitiesByGroup(_grp_MANA).size() == 0; }

	// Devuelve los callbacks con sus respectivos tiempos
	vector<CallBack> getSteps();
};