#include "NodeButton.h"
#include "../../core/SDLApplication.h"

void NodeButton::initGameObject(Node* nodeIt, CallBack _cb) {

	addComponent<Transform>(VECTOR_ZERO, VECTOR_ZERO, NODE_WIDTH, NODE_HEIGHT);
	Animator* animator = addComponent<Animator>(SDLApplication::getTexture(nodeIt->getTextureKey()), NODE_FRAME_WIDTH, NODE_FRAME_HEIGHT, NODE_FRAME_ROWS, NODE_FRAME_COLUMNS);
	addComponent<NodeButtonComponent>(_cb, nodeIt->getState());

	animator->createAnim(ONOUT, NODE_BUTTON_ONOUT_START_FRAME, NODE_BUTTON_ONOUT_END_FRAME, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONOVER, NODE_BUTTON_ONOVER_START_FRAME, NODE_BUTTON_ONOVER_END_FRAME, ONOVER_SPEED, -1);
	animator->createAnim(ONCLICK, NODE_BUTTON_ONCLICK_START_FRAME, NODE_BUTTON_ONCLICK_END_FRAME, ONCLICK_ONOUT_SPEED, -1);
	animator->createAnim(ONLOCKED, NODE_BUTTON_ONLOCKED_START_FRAME, NODE_BUTTON_ONLOCKED_END_FRAME, LOGO_FRAME_RATE, -1);
	animator->createAnim(ONCOMPLETED, NODE_BUTTON_ONCOMPLETED_START_FRAME, NODE_BUTTON_ONCOMPLETED_END_FRAME, LOGO_FRAME_RATE, -1);
	animator->play(ONOUT);
}