#include "ChargedPortalComponent.h"
#include "../../core/SDLApplication.h"

ChargedPortalComponent::ChargedPortalComponent(vector<GameObject*>& nums) : Component(), 
							numbers(nums), exit(false), deltaTime(0), gmCtrl_(gmCtrl()) {
	
}

void ChargedPortalComponent::initComponent() {
	brComp = gObj->getComponent<BarComponent>();
}

void ChargedPortalComponent::update() {
	if (deltaTime != 0) {
		// Sumar al contador y reflejar cambios en el n�mero
		deltaTime += SDLApplication::instance()->getDeltaTimeSeconds();
		brComp->changeEtherNumbers(countDownNumber, 5 - (int)deltaTime);
				
		// Salir al men� principal si han pasad 5.6 secs (5 de mostrar del 5 al 1 y 0.6 del 0)
		if (deltaTime > COUNTDOWN_TIME) SDLApplication::returnToMapScene();
	}
}

// Activar la salida para que el update empiece a recoger input
void ChargedPortalComponent::activateExit() {
	exit = true;
}

// Prepara el contador y el n�mero para la cuenta atr�s
void ChargedPortalComponent::countDownSetup() {
	if (exit && deltaTime == 0) {
		// Empezar el contador
		deltaTime += SDLApplication::instance()->getDeltaTimeSeconds();

		// Guardar el primer n�mero del vector y borrar el resto
		countDownNumber = numbers[0];
		for (int i = N_ETHER_COUNTER - 1; i > 0; i--) numbers[i]->setAlive(false);


		// Reposicionar el n�mero
		Transform* tr = countDownNumber->getComponent<Transform>();
		tr->setPos(UI_COUNTDOWN_ETHER_POS);
		tr->setWidth(tr->getWidth() * 1.5);
		tr->setHeight(tr->getHeight() * 1.5);
	}
}