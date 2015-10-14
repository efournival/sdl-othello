#include "Sequenceur.h"


Sequenceur::Sequenceur(seqCallback callback, Interface* parent, int frequence):
_delai(1000 / frequence),
_callback(callback),
_parent(parent) {}

void Sequenceur::cycler() {
	int attente, debut;
	debut = SDL_GetTicks();

	while ((_parent->*_callback)()) {
		attente = (debut + _delai) - SDL_GetTicks();
		if (attente > 0) SDL_Delay(attente);
		debut = SDL_GetTicks();
	}
}
