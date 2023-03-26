#include "ButtonComponent.h"
#include "../../gameObjects/GameObject.h"

void ButtonComponent::update() {
	// Cambiar animaci�n seg�n el estado
	updateAnimation();

	int mouseX = 0, mouseY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);

	// Cambia el estado seg�n la posici�n del rat�n
	if (state != OnClick) {
	if (isOver(mouseX, mouseY)) {
		state = OnOver;
	}
	else {
		state = OnOut;
	}
	}
}

void ButtonComponent::handleInput() {
	if (InputHandler::instance()->getMouseButtonState(InputHandler::LEFT) && state == OnOver) {
		onClick();
	}
}

void ButtonComponent::initComponent() {
	tr = gObj->getComponent<Transform>();
	animButton = gObj->getComponent<Animator>();
	if (frame != nullptr) animFrame = frame->getComponent<Animator>();
}


// Comprueba si las coordenadas introducidas est�n sobre el mouse
bool ButtonComponent::isOver(int mouseX, int mouseY) {
	return (mouseX >= tr->getPos().getX() && mouseX < tr->getPos().getX() + tr->getWidth()) &&
		(mouseY >= tr->getPos().getY() && mouseY < tr->getPos().getY() + tr->getHeight());
}

// Ejecuta el callback
void ButtonComponent::onClick() {
	state = OnClick;
	function();
}


// Actualiza la animaci�n del bot�n seg�n el estado
void ButtonComponent::updateAnimation() {
	switch (state) {
	case OnOut:
		changeStateAnim(ONOUT);
		break;
	case OnOver:
		changeStateAnim(ONOVER);
		break;
	case OnClick:
		changeStateAnim(ONCLICK);
		break;
	}
}

// Cambia el estado de los animators para mostrar el estado del bot�n recibido
void ButtonComponent::changeStateAnim(string key) {
	// Comprobar si la animaci�n actual no es a la que hay que cambiar
	if (animButton->currentAnimationKey() != key) {
		// Reproducir la correspondiente
		animButton->play(key);

		// Cambiar el estado del frame al correspondiente
		if (frame != nullptr) animFrame->play(key);
	}
}