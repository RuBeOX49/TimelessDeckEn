#include "GameControl.h"


GameControl::GameControl() : 
	ih_(ih()), 
	controller_(ih().isControllerConnected()),
	lastMovement(0),
	lastMovementU(0),
	lastMovementD(0),
	lastMovementL(0),
	lastMovementR(0),
	movementDelay(200),
	sameDirMovementDelay(250)
{}

float GameControl::movement(SDL_GameControllerAxis axis, SDL_KeyCode minus, SDL_KeyCode plus) const {
	if (controller_) {
		return ih_.getNormalizedControllerAxis(axis);
	}
	float ctrl = 0;
	if (ih_.isKeyDown(minus)) ctrl -= 1;
	if (ih_.isKeyDown(plus)) ctrl += 1;
	return ctrl;
}

bool GameControl::attack(SDL_GameControllerButton button, SDL_GameControllerAxis trigger, InputHandler::MOUSEBUTTON mouseButton) const {
	if (controller_) {
		return ih_.isControllerButtonDown(button)
			|| ih_.getControllerAxis(trigger) > 0;
	}
	return ih_.getMouseButtonState(mouseButton) == 1;
}

// Eje de movimiento en X, entre -1 y 1
float GameControl::movementX() const {
	return movement(SDL_CONTROLLER_AXIS_LEFTX, SDLK_a, SDLK_d);
}
// Eje de movimiento en Y, entre -1 y 1
float GameControl::movementY() const {
	return movement(SDL_CONTROLLER_AXIS_LEFTY, SDLK_w, SDLK_s);
}


// Acci�n de ataque b�sico
bool GameControl::basic() const {
	return attack(SDL_CONTROLLER_BUTTON_A, SDL_CONTROLLER_AXIS_TRIGGERRIGHT, InputHandler::LEFT);		
}
// Acci�n de habilidad
bool GameControl::ability() const {
	return attack(SDL_CONTROLLER_BUTTON_B, SDL_CONTROLLER_AXIS_TRIGGERLEFT, InputHandler::RIGHT);
}

bool GameControl::adjustCursorToJoystick(SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis) const {
	float x = ih_.getNormalizedControllerAxis(xAxis);
	float y = ih_.getNormalizedControllerAxis(yAxis);
	if (x != 0 || y != 0) {
		SDL_WarpMouseInWindow(sdlutils().window(), (sdlutils().width() - 1) / 2 + (sdlutils().width() - 1) / 2 * x, (sdlutils().height() - 1) / 2 + (sdlutils().height() - 1) / 2 * y);
		return true;
	}
	return false;
}

// Cambia la posici�n del cursos en funci�n a los joysticks del mando si el control por este est� activado
bool GameControl::controllerToCursor() const {
	if (controller_) {
		if (adjustCursorToJoystick(SDL_CONTROLLER_AXIS_RIGHTX, SDL_CONTROLLER_AXIS_RIGHTY)) return true;
		return adjustCursorToJoystick(SDL_CONTROLLER_AXIS_LEFTX, SDL_CONTROLLER_AXIS_LEFTY);
	}
	return false;
}


// Cambiar en partida la carta seleccionada a la izquierda
bool GameControl::selectLeftCard() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
			|| ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	}
	return ih_.mouseWheelUp() || ih_.isKeyDown(SDLK_q);
}
// Cambiar en partida la carta seleccionada a la derecha
bool GameControl::selectRightCard() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
			|| ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	}
	return ih_.mouseWheelDown() || ih_.isKeyDown(SDLK_e);
}

// Activar el portal para salir del nivel
bool GameControl::completeLevel() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_Y);
	}
	return ih_.isKeyJustDown(SDLK_SPACE);
}
// Pausar el juego
bool GameControl::pause() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_START);
	}
	return ih_.isKeyDown(SDLK_ESCAPE);
}

// Pulsar un bot�n
bool GameControl::click() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_A);
	}
	return ih_.getMouseButtonState(InputHandler::LEFT) && ih_.mouseButtonEvent();
}


// Si est� activado el control por mando se mueve el mouse a la posici�n indicada
bool GameControl::moveMouse(float x, float y) const {
	if (controller_) {
		SDL_WarpMouseInWindow(sdlutils().window(), x, y);
		return true;
	}
	return false;
}


// Seleccionar el bot�n superior
bool GameControl::selectUpButton() {
	if (controller_) {
		uint ticks = SDL_GetTicks();
		if (ticks > lastMovement + movementDelay && ticks > lastMovementU + sameDirMovementDelay && ih_.getControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) < -0.4f) {
			lastMovement = ticks;
			lastMovementU = ticks;
			return true;
		}

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP);
	}
	return false;
}
// Seleccionar el bot�n inferior
bool GameControl::selectDownButton() {
	if (controller_) {
		uint ticks = SDL_GetTicks();
		if (ticks > lastMovement + movementDelay && ticks > lastMovementD + sameDirMovementDelay && ih_.getControllerAxis(SDL_CONTROLLER_AXIS_LEFTY) > 0.4f) {
			lastMovement = ticks;
			lastMovementD = ticks;
			return true;
		}

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN);

	}
	return false;
}
// Seleccionar el bot�n a la izquierda
bool GameControl::selectLeftButton() {
	if (controller_) {
		uint ticks = SDL_GetTicks();
		if (ticks > lastMovement + movementDelay && ticks > lastMovementL + sameDirMovementDelay && ih_.getNormalizedControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) < -0.4f) {
			lastMovement = ticks;
			lastMovementL = ticks;
			return true;
		}

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	}
	return false;
}
// Seleccionar el bot�n a la derecha
bool GameControl::selectRightButton() {
	if (controller_) {
		uint ticks = SDL_GetTicks();
		if (ticks > lastMovement + movementDelay && ticks > lastMovementR + sameDirMovementDelay && ih_.getNormalizedControllerAxis(SDL_CONTROLLER_AXIS_LEFTX) > 0.4f) {
			lastMovement = ticks;
			lastMovementR = ticks;
			return true;
		}

		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	}
	return false;
}


// Devuelve en valor en el que se deber� mover la c�mara cuando se hace scroll
float GameControl::scroll(bool controllerScroll) const {
	if (controller_) {
		return (controllerScroll) ? 20 * ih_.getNormalizedControllerAxis(SDL_CONTROLLER_AXIS_RIGHTY) / 200.0f : 0.0f;
	}

	return 20 * (ih_.mouseWheelUp()) ? -1 : (ih_.mouseWheelDown()) ? 1 : 0;
}


// Ir atr�s
bool GameControl::goBack() const {
	if (controller_) {
		return ih_.isControllerButtonDown(SDL_CONTROLLER_BUTTON_B);
	}
	return false;
}

// Cambiar entre control por mando y control por teclado
void GameControl::changeControl() {
	if (!controller_) {
		changeToGamepad();
	}
	else {
		changeToKeyboard();
	}
}

// Cambiar a control por teclado
void GameControl::changeToKeyboard() {
	controller_ = false;
}

// Cambiar a control por mando
void GameControl::changeToGamepad() {
	controller_ = ih().isControllerConnected();
}