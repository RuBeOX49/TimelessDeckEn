#include "MainMenuScene.h"
#include "../core/SDLApplication.h"
#include "../gameObjects/GameObject.h"

MainMenuScene::MainMenuScene() : GameState() {
	// Imagen de fondo
	GameObject* background = addGameObject(_grp_GENERAL);
	background->addComponent<Transform>(Vector2D(), Vector2D(), WIN_WIDTH, WIN_HEIGHT);
	background->addComponent<Image>(SDLApplication::getTexture("MainMenuBackground"));

	// Logo del juego
	GameObject* logo = addGameObject(_grp_GENERAL);
	logo->addComponent<Transform>(LOGO_POSITION, Vector2D(), LOGO_WIDTH, LOGO_HEIGHT);
	Animator* a = logo->addComponent<Animator>(SDLApplication::getTexture("GameLogo"), LOGO_FRAME_WIDTH, LOGO_FRAME_HEIGHT, LOGO_ROWS, LOGO_COLUMNS);
	a->createAnim(LOGO_ANIM_KEY, LOGO_START_FRAME, LOGO_END_FRAME, LOGO_FRAME_RATE, -1);
	a->play(LOGO_ANIM_KEY);

	// Logo del estudio
	GameObject* estudio = addGameObject(_grp_GENERAL);
	estudio->addComponent<Transform>(STUDIO_POSITION, Vector2D(), STUDIO_WIDTH, STUDIO_HEIGTH);
	estudio->addComponent<Image>(SDLApplication::getTexture("StudioLogo"));

	// Botón jugar
	createButton(MM_PLAY_BUTTON_POS, MM_PLAYFRAME_BUTTON_POS, []() { SDLApplication::newScene<MapScene>(); }, PLAY);	

	// Botón options
	createButton(MM_OPTIONS_BUTTON_POS, MM_OPTIONSFRAME_BUTTON_POS, []() { SDLApplication::newScene<OptionsMenuScene>(); }, OPTIONS);

	// Botón album
	createButton(MM_ALBUM_BUTTON_POS, MM_ALUBMFRAME_BUTTON_POS, []() { SDLApplication::newScene<AlbumScene>(); }, ALBUM);

	// Botón salir
	createButton(MM_EXIT_BUTTON_POS, MM_EXITFRAME_BUTTON_POS, []() { SDLApplication::instance()->quitGame(); }, EXIT);
}

// Crear un botón especificado en la escena
void GameOverScene::createButton(Vector2D _bPos, Vector2D _fPos, CallBack _cb, string key) {
	AnimatorInfo aI = AnimatorInfo(key);

	// Crear marco
	GameObject* frame = addGameObject(_grp_GENERAL);
	frame->addComponent<Transform>(_fPos, Vector2D(), MM_BUTTONFRAME_WIDTH, MM_BUTTONFRAME_HEIGHT);
	frame->addComponent<Animator>(SDLApplication::getTexture("ButtonFrame"), BUTTON_FRAME_SPRITE_WIDTH, BUTTON_FRAME_SPRITE_HEIGTH, aI.rows, aI.cols);
	
	// Crear botón
	addGameObject<Button>(_grp_GENERAL, _cb, SDLApplication::instance(), _bPos, aI, frame);
}