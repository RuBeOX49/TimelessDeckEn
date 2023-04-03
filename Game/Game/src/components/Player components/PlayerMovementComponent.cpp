#include "PlayerMovementComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../core/SDLApplication.h"
#include "../../data/PlayerData.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr), gmCtrl_(gmCtrl()) {}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	playerSpeed = PlayerData::instance()->getPlayerMoveSpeed();
}

void PlayerMovementComponent::setDirection(Vector2D dir) {
	// L�mites
	Vector2D pos = transform->getPos();
	if (pos.getX() < PLAYER_INITIAL_WIDTH) transform->setX(PLAYER_INITIAL_WIDTH);
	else if (pos.getX() > FLOOR_WIDTH - PLAYER_INITIAL_WIDTH) transform->setX(FLOOR_WIDTH - PLAYER_INITIAL_WIDTH);

	if (pos.getY() < 0 - PLAYER_INITIAL_HEIGHT / 3) transform->setY(0 - PLAYER_INITIAL_HEIGHT / 3);
	else if (pos.getY() > FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT) transform->setY(FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT);

	// Normalizar y cambiar m�dulo
	transform->setVel(dir.normalize() * playerSpeed);
}
void PlayerMovementComponent::handleInput() {
	//// Direcci�n
	//Vector2D vel(0, 0);
	//vel = vel + Vector2D(gmCtrl_.movementX(), gmCtrl_.movementY());

	//// L�mites
	//Vector2D pos = transform->getPos();
	//if (pos.getX() < PLAYER_INITIAL_WIDTH) transform->setX(PLAYER_INITIAL_WIDTH);
	//else if (pos.getX() > FLOOR_WIDTH - PLAYER_INITIAL_WIDTH) transform->setX(FLOOR_WIDTH - PLAYER_INITIAL_WIDTH);

	//if (pos.getY() < 0 - PLAYER_INITIAL_HEIGHT / 3) transform->setY(0 - PLAYER_INITIAL_HEIGHT / 3);
	//else if (pos.getY() > FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT) transform->setY(FLOOR_HEIGHT - PLAYER_INITIAL_HEIGHT);

	//// Normalizar y cambiar m�dulo 
	//vel = vel.normalize() * playerSpeed;
	//transform->setVel(vel);

	//// Activar la pausa lanzando su estado
	//if (gmCtrl_.pause()) {
	//	SDLApplication::pauseGame();
	//}
}

void PlayerMovementComponent::setPlayerSpeed(float newSpeed) {
	playerSpeed = newSpeed;
}