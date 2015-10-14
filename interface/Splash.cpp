#include "Splash.h"


Splash::Splash(SDL_Surface* destination, SDL_Surface* ecran):
Interface(destination, ecran),
_image(NULL),
_assombrissement(NULL),
_horloge() {
	_image = new Image(SDL_LoadBMP("ressources/images/splash.bmp"));

	uint32_t rMask, gMask, bMask, aMask;
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rMask = 0xff000000;
		gMask = 0x00ff0000;
		bMask = 0x0000ff00;
		aMask = 0x000000ff;
	#else
		rMask = 0x000000ff;
		gMask = 0x0000ff00;
		bMask = 0x00ff0000;
		aMask = 0xff000000;
	#endif

	_assombrissement = SDL_CreateRGBSurface(SDL_HWSURFACE, 257, 272, 32, rMask, gMask, bMask, aMask);
}

void Splash::assombrir(unsigned int intensite) {
	// Remplissage avec du gris
	SDL_FillRect(_assombrissement, NULL, SDL_MapRGBA(_assombrissement->format, 0, 0, 0, intensite));
	SDL_BlitSurface(_assombrissement, NULL, _rendu, NULL);
}

void Splash::afficher() {
	_sequenceur->cycler();
}

bool Splash::rendre() {
	_image->dessiner(_rendu);

	unsigned int intensite = _horloge.temps() / 3;
	intensite = (intensite > 255) ? 0 : 255 - intensite;

	assombrir(intensite);

	SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

	SDL_Flip(_ecran);

	return (_horloge.temps() < 3 * 1000) && gererEvenementsSDL();
}

bool Splash::gererEvenementsSDL() {
	SDL_Event evenement;

	while (SDL_PollEvent(&evenement)) {
		switch (evenement.type) {
			case SDL_MOUSEBUTTONDOWN:
			case SDL_KEYDOWN:
				return false;
				break;
			case SDL_QUIT:
				quitter();
				return false;
				break;
		}
	}

	return true;
}

Splash::~Splash() {
	SDL_FreeSurface(_assombrissement);
}
