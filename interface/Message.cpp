#include "Message.h"


Message::Message(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes, const char* titre, const char* contenu):
Interface(rendu, ecran, fontes),
_titre(NULL),
_contenu(NULL),
_bouton(NULL),
_sortir(false) {
	_titre = TTF_RenderText_Solid(_fontes.fonteGras, titre, {0, 0, 0, 255});
	_contenu = TTF_RenderText_Solid(_fontes.fonteNormal, contenu, {0, 0, 0, 255});

	_bouton = new Bouton(_rendu, _rendu->w / 2 - 25, _rendu->h / 2 + 13, 50, 16, "OK", _fontes.fonteNormal, [&] () {
		_sortir = true;
	});
}

void Message::afficher() {
	assombrir(_rendu);
	_sequenceur->cycler();
}

bool Message::rendre() {
	// Contour du message
	SDL_Rect posRectangle;
	posRectangle.x = 25;
	posRectangle.y = _rendu->h / 2 - 30;
	posRectangle.w = _rendu->w - 50;
	posRectangle.h = 70;
	SDL_FillRect(_rendu, &posRectangle, SDL_MapRGBA(_rendu->format, 0, 0, 0, 255));

	// Intérieur blanc
	posRectangle.x = 27;
	posRectangle.y = _rendu->h / 2 - 28;
	posRectangle.w = _rendu->w - 54;
	posRectangle.h = 66;
	SDL_FillRect(_rendu, &posRectangle, SDL_MapRGBA(_rendu->format, 255, 255, 255, 255));

	SDL_Rect posTexte;
	posTexte.x = 40;
	posTexte.y = _rendu->h / 2 - 22;
	SDL_BlitSurface(_titre, NULL, _rendu, &posTexte);
	posTexte.y = _rendu->h / 2 - 8;
	SDL_BlitSurface(_contenu, NULL, _rendu, &posTexte);

	int sourisX, sourisY;
	SDL_GetMouseState(&sourisX, &sourisY);
	_bouton->testSurvol(sourisX/2, sourisY/2);
	_bouton->afficher();

	SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

	SDL_Flip(_ecran);

	return gererEvenementsSDL() && (!_quitter) && (!_sortir);
}

bool Message::gererEvenementsSDL() {
	SDL_Event evenement;

	while (SDL_PollEvent(&evenement)) {
		if (evenement.type == SDL_QUIT) {
			quitter();
			return false;
		} else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
			int sourisX, sourisY;
			bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
			if (_bouton->testSurvol(sourisX / 2, sourisY / 2) & clic)
				_bouton->cliquer();
		}
	}

	return true;
}

Message::~Message() {
	SDL_FreeSurface(_titre);
	SDL_FreeSurface(_contenu);
	delete _bouton;
}

void assombrir(SDL_Surface* destination) {
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

	SDL_Surface* assombrissement = SDL_CreateRGBSurface(SDL_HWSURFACE, 257, 272, 32, rMask, gMask, bMask, aMask);
	SDL_FillRect(assombrissement, NULL, SDL_MapRGBA(assombrissement->format, 0, 0, 0, 128));
	SDL_BlitSurface(assombrissement, NULL, destination, NULL);
	SDL_FreeSurface(assombrissement);
}
