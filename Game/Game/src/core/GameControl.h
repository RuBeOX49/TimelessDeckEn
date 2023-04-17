#pragma once
#include "../utils/Singleton.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
class GameControl : public Singleton<GameControl> {
private:
	bool controller_;
	InputHandler& ih_;

	uint lastMovement, lastMovementU, lastMovementD, lastMovementL, lastMovementR;
	const uint movementDelay, sameDirMovementDelay;

	float movement(SDL_GameControllerAxis axis, SDL_KeyCode minus, SDL_KeyCode plus) const;
	bool attack(SDL_GameControllerButton button, SDL_GameControllerAxis trigger, InputHandler::MOUSEBUTTON mouseButton) const;
	bool adjustCursorToJoystick(SDL_GameControllerAxis xAxis, SDL_GameControllerAxis yAxis) const;
public:
	GameControl();

	// Eje de movimiento en X, entre -1 y 1
	float movementX() const;
	// Eje de movimiento en Y, entre -1 y 1
	float movementY() const;

	// Acci�n de ataque b�sico
	bool basic() const;
	// Acci�n de habilidad
	bool ability() const;
	// Cambia la posici�n del cursos en funci�n a los joysticks del mando si el control por este est� activado
	bool controllerToCursor() const;

	// Cambiar en partida la carta seleccionada a la izquierda
	bool selectLeftCard() const;
	// Cambiar en partida la carta seleccionada a la derecha
	bool selectRightCard() const;

	// Activar el portal para salir del nivel
	bool completeLevel() const;
	// Pausar el juego
	bool pause() const;

	// Pulsar un bot�n
	bool click() const;
	// 
	bool moveMouse(float x, float y) const;

	bool selectUpButton();
	bool selectDownButton();
	bool selectLeftButton();
	bool selectRightButton();

	float scroll() const;
	bool goBack() const;

	// Cambiar entre control por mando y control por teclado
	inline void changeControl() {
		controller_ = !controller_;
	}
};

inline GameControl& gmCtrl() { return *GameControl::instance(); }
