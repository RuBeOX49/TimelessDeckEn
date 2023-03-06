#include "PlayerMovementComponent.h"
#include "../../sdlutils/InputHandler.h"

PlayerMovementComponent::PlayerMovementComponent() :transform(nullptr){}

void PlayerMovementComponent::initComponent() {
	transform = gObj->getComponent<Transform>();
}

void PlayerMovementComponent::handleInput() {
	Vector2D vel(0, 0);
	Vector2D pos =transform->getPos();
	if (pos.getX()>PLAYER_INITIAL_WIDTH&&InputHandler::instance()->isKeyDown(SDLK_a)) {
		vel = vel + Vector2D(-1, 0);
	}
	if (pos.getX()<FLOOR_WIDTH-PLAYER_INITIAL_WIDTH&&InputHandler::instance()->isKeyDown(SDLK_d)) {
		vel = vel + Vector2D(1, 0);
	}
	if (pos.getY()>0-PLAYER_INITIAL_HEIGHT/3&&InputHandler::instance()->isKeyDown(SDLK_w)) {
		vel = vel + Vector2D(0, -1);
	}
	if (pos.getY()<FLOOR_HEIGHT-PLAYER_INITIAL_HEIGHT&&InputHandler::instance()->isKeyDown(SDLK_s)) {
		vel = vel + Vector2D(0, 1);
	}
	if(vel.magnitude()!=0)
	vel = vel / vel.magnitude();
	vel = vel * playerSpeed;
	transform->setVel(vel);
}

void PlayerMovementComponent::setPlayerSpeed(int newSpeed) {
	playerSpeed = newSpeed;
}