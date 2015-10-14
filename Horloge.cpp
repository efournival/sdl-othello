#include "Horloge.h"


Horloge::Horloge():
_pause(0),
_decalage(SDL_GetTicks()),
_decalageVitesse(0),
_changementVitesse(0),
_vitesse(1),
_enPause(false) {}

void Horloge::pause() {
	_pause = SDL_GetTicks();
	_enPause = true;
}

void Horloge::reprendre() {
	_decalage += SDL_GetTicks() - _pause;
	_enPause = false;
}

bool Horloge::enPause() const {
	return _enPause;
}

uint32_t Horloge::temps() const {
	uint32_t tps = (_enPause) ? (_pause - _decalage) : (SDL_GetTicks() - _decalage);
	return _changementVitesse + (tps - _changementVitesse)*_vitesse + _decalageVitesse;
}

void Horloge::setVitesse(int vitesse) {
	if (vitesse < _vitesse) {
		uint32_t ancienT = _changementVitesse + (SDL_GetTicks() - _decalage - _changementVitesse)*_vitesse;
		uint32_t nouveauT = _changementVitesse + (SDL_GetTicks() - _decalage - _changementVitesse)*vitesse;
		_decalageVitesse += ancienT - nouveauT;
	}

	_changementVitesse = SDL_GetTicks() - _decalage;
	_vitesse = vitesse;
}

int Horloge::getVitesse() {
	return _vitesse;
}
