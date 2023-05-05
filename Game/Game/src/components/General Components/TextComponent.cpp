#include "TextComponent.h"

// Texto negro sin fondo en una l�nea
TextComponent::TextComponent (Font* _f, std::string _text) :
	Image(&texture),
	font(_f), text(_text), color(build_sdlcolor("0x000000")), wrapped(false), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color) {
}

// Texto negro sin fondo ajustado a una anchura
TextComponent::TextComponent(Font* _f, std::string _text, bool _wrapped) :
	Image(&texture),
	font(_f), text(_text), color(build_sdlcolor("0x000000")), wrapped(_wrapped), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color, 1) {
}

// Texto con color personalizado sin fondo en una l�nea
TextComponent::TextComponent(Font* _f, std::string _text, SDL_Color _color) :
	Image(&texture),
	font(_f), text(_text), color(_color), wrapped(false), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color) {
}

// Texto con color personalizado sin fondo ajustado a una anchura
TextComponent::TextComponent(Font* _f, std::string _text, SDL_Color _color, bool _wrapped) :
	Image(&texture),
	font(_f), text(_text), color(_color), wrapped(_wrapped), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color, 1) {}

// Texto con color personalizado con fondo personalizado
TextComponent::TextComponent(Font* _f, std::string _text, SDL_Color _color, SDL_Color _bgColor) :
	Image(&texture),
	font(_f), text(_text), color(_color), bgColor(_bgColor), wrapped(false), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color, bgColor) {}

// Texto con color personalizado con fondo personalizado ajustado a una anchura
TextComponent::TextComponent(Font* _f, std::string _text, SDL_Color _color, SDL_Color _bgColor, bool _wrapped) :
	Image(&texture),
	font(_f), text(_text), color(_color), bgColor(_bgColor), wrapped(_wrapped), originalWidth(0),
	texture(sdlutils().renderer(), text, *font, color, bgColor) {}

// Ajusta el transform al texto
void TextComponent::initComponent() {
	 Image::initComponent();
	 if (wrapped) {
		 texture = Texture(sdlutils().renderer(), text, *font, color, transform->getWidth());
	 }
	 else {
		 originalWidth = transform->getWidth();
		 transform->setWidth(texture.width());
	 }
	 transform->setHeight(texture.height());
}


// Recarga la textura tras actualizaciones
void TextComponent::reloadTexture() {
	transform->setHeight(transform->getHeight() / texture.height());
	if (wrapped) { // si se ajusta al ancho del transform lo indica a la textura
		texture = Texture(sdlutils().renderer(), text, *font, color, transform->getWidth());
	}
	else { // si es en una sola l�nea ajusta el ancho del transform al texto
		transform->setWidth(transform->getWidth() / texture.width());
		texture = Texture(sdlutils().renderer(), text, *font, color);
		transform->setWidth(transform->getWidth() * texture.width());
	}
	transform->setHeight(transform->getHeight() * texture.height());
}


// Cambia el texto mostrado
void TextComponent::changeText(std::string newText) { 
	text = newText;
	reloadTexture();
}

// Cambia la fuente
void TextComponent::changeFont(Font* newFont) {
	font = newFont; 
	reloadTexture(); 
}

// Cambia el color, recibe SDL_Color
void TextComponent::changeColor(SDL_Color newColor) { 
	color = newColor; 
	reloadTexture(); 
}

// Cambia el color, recibe el color en hexadecimal
void TextComponent::changeColor(std::string newColorHex) {
	changeColor(build_sdlcolor(newColorHex)); 
}


// Asigna si el ancho del texto depende del transform o no
void TextComponent::setWrapped(bool w) {
	if (!wrapped) {
		transform->setWidth(originalWidth);
	}
	else {
		originalWidth = transform->getWidth();
	}
	wrapped = w;
	reloadTexture();
}

// Devuelve si el ancho del texto depende del transform o no
bool TextComponent::isWrapped() {
	return wrapped;
}

// A�ade texto al actual
std::string TextComponent::operator +=(std::string s) {
	changeText(text + s);
	return this->text;
}