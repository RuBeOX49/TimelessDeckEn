#pragma once

#include "Image.h"
#include <unordered_map>


using AnimationMap = unordered_map<string, Animation>;

class Animator : public Image {
private:
	// Variables de tama�o, filas y columnas de la spritesheet
	int fw, fh, rows, cols;
	int currentFrame;
	int repetitions;
	double currTime;
	AnimationMap anims;
	string currentAnimKey;
	Animation* currentAnimation;
	float srcRectRelativeWidth = 1;
	float srcRectRelativeHeight = 1;

public:
	// Constructora
	Animator(Texture* _texture, int _w, int _h, int _r, int _c) :
		Image(_texture), fw(_w), fh(_h), rows(_r), cols(_c), currentFrame(0), currTime(0), repetitions(0), currentAnimation(nullptr) { };

	// Crea una animacion nueva
	void createAnim(string key, Animation anim);
	// Crea una animacion nueva
	void createAnim(string key, int start, int end, int rate, int _rep = 0);

	// Empieza una nueva animacion
	void play(string key);

	// Para la animacion actual
	void stop();

	// Continua la ultima animacion
	void resume();
	
	// Inicia una nueva animaci�n si es diferente a la actual
	bool playDiff(string key);

	// Actualiza el frame actual dependiendo del frameRate
	virtual void update();

	// Renderiza el frame actual
	virtual void render() const;

	// Settea el valor para el cambio del tama�o del srcRect
	inline void setSrcRectRelativeWidth(float rw) {
		if (rw > 1) rw = 1;
		else if (rw < 0) rw = 0;
		srcRectRelativeWidth = rw;
	}

	// Settea el valor para el cambio del tama�o del srcRect
	inline void setSrcRectRelativeHeight(float rh) {
		if (rh > 1) rh = 1;
		else if (rh < 0) rh = 0;
		srcRectRelativeHeight = rh;
	}

	// Devuelve el nombre de la animacion actual
	inline string currentAnimationKey() { return currentAnimKey; }

	// Devuelve el numero del frame actual
	inline int getCurrentFrame() { return currentFrame; }

	// Devuelve si la animaci�n actual est� corriendo
	inline bool isPlaying() {
		return currentAnimation != nullptr && repetitions != currentAnimation->repeat;
	}

	// Devuelve si la animaci�n actual se ha completado
	inline bool animationComplete() {
		return currentAnimation != nullptr && repetitions == currentAnimation->repeat;
	}

	// Devuelve si la animaci�n actual es la introducida
	inline bool isCurrentAnimation(string key) {
		return currentAnimKey == key;
	}

	//Devuelve si la animacion introducida esta siendo reproducida
	bool isPlaying(string key) {
		return isCurrentAnimation(key) && isPlaying();
	}
};