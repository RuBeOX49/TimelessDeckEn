#include "PlayerMovementComponent.h"
#include "../../sdlutils/InputHandler.h"
#include "../../core/SDLApplication.h"
#include "../../data/PlayerData.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr), dashDuration(0){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
	playerSpeed = PlayerData::instance()->getPlayerMoveSpeed();
}

void PlayerMovementComponent::handleInput() {
	Vector2D vel(0, 0);
	Vector2D pos =transform->getPos();

	// Izquierda
	if (pos.getX()>PLAYER_INITIAL_WIDTH&&InputHandler::instance()->isKeyDown(SDLK_a)) {
		vel = vel + Vector2D(-1, 0);
	}
	// Derecha
	if (pos.getX()<FLOOR_WIDTH-PLAYER_INITIAL_WIDTH&&InputHandler::instance()->isKeyDown(SDLK_d)) {
		vel = vel + Vector2D(1, 0);
	}
	// Arriba
	if (pos.getY()>0-PLAYER_INITIAL_HEIGHT/3&&InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -1);
	}
	// Abajo
	if (pos.getY()<FLOOR_HEIGHT-PLAYER_INITIAL_HEIGHT&&InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, 1);
	}

	moveDir = vel;

	// Activar la pausa lanzando su estado
	if (InputHandler::instance()->isKeyJustDown(SDLK_ESCAPE)) {
		SDLApplication::pauseGame();
	}
}

void PlayerMovementComponent::update()
{
	if (dashDuration <= 0) {
		if (moveDir.magnitude() != 0)
			moveDir = moveDir / moveDir.magnitude();
		moveDir = moveDir * playerSpeed;
		transform->setVel(moveDir);
	} else dashDuration -= SDLApplication::instance()->getDeltaTimeSeconds();

}

void PlayerMovementComponent::setPlayerSpeed(float newSpeed) {
	playerSpeed = newSpeed;
}

void PlayerMovementComponent::dash(Vector2D dir) {
	Vector2D vel = dir * DASH_SPEED;
	dashDuration = DASH_DURATION;
	transform->setVel(vel);
}