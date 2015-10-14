#include "Bouton.h"


Bouton::Bouton(SDL_Surface* rendu, int pX, int pY, int largeur, int hauteur, const char* texte, TTF_Font* fonte, actionClic action):
Composant(rendu),
_position(),
_sNormal(NULL),
_sSurvol(NULL),
_sDesactive(NULL),
_survol(false),
_desactive(false),
_action(action) {
	_position.x = pX;
	_position.y = pY;
	_position.w = largeur;
	_position.h = hauteur;

	SDL_Surface* sTexte = TTF_RenderText_Solid(fonte, texte, {0, 0, 0, 0});

	_sNormal = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 24, 0, 0, 0, 0);
	_sSurvol = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 24, 0, 0, 0, 0);
	_sDesactive = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 24, 0, 0, 0, 0);

	SDL_FillRect(_sNormal, NULL, SDL_MapRGBA(_sNormal->format, 0, 0, 0, 255));
	SDL_FillRect(_sSurvol, NULL, SDL_MapRGBA(_sSurvol->format, 0, 0, 0, 255));
	SDL_FillRect(_sDesactive, NULL, SDL_MapRGBA(_sSurvol->format, 0, 0, 0, 255));

	SDL_Rect contenuBouton;
	contenuBouton.x = 1;
	contenuBouton.y = 1;
	contenuBouton.w = _position.w - 2;
	contenuBouton.h = _position.h - 2;

	SDL_FillRect(_sNormal, &contenuBouton, SDL_MapRGBA(_sNormal->format, 255, 255, 255, 255));
	SDL_FillRect(_sSurvol, &contenuBouton, SDL_MapRGBA(_sSurvol->format, 0, 80, 14, 255));
	SDL_FillRect(_sDesactive, &contenuBouton, SDL_MapRGBA(_sSurvol->format, 64, 64, 64, 255));

	SDL_Rect posTexte;
	posTexte.x = (_position.w - sTexte->w) / 2;
	posTexte.y = (_position.h - sTexte->h) / 2;

	SDL_BlitSurface(sTexte, NULL, _sNormal, &posTexte);
	SDL_BlitSurface(sTexte, NULL, _sSurvol, &posTexte);
	SDL_BlitSurface(sTexte, NULL, _sDesactive, &posTexte);

	SDL_FreeSurface(sTexte);
}

void Bouton::afficher() {
	if (_desactive) {
		SDL_BlitSurface(_sDesactive, NULL, _rendu, &_position);
	} else {
		SDL_BlitSurface(_survol ? _sSurvol : _sNormal, NULL, _rendu, &_position);
	}
}

bool Bouton::testSurvol(int pX, int pY) {
	return _survol = (pX >= _position.x && pX <= _position.x + _position.w) && (pY >= _position.y && pY <= _position.y + _position.h);
}

void Bouton::cliquer() {
	_action();
}

void Bouton::activer() {
	_desactive = false;
}

void Bouton::desactiver() {
	_desactive = true;
}

Bouton::~Bouton() {
	SDL_FreeSurface(_sNormal);
	SDL_FreeSurface(_sSurvol);
	SDL_FreeSurface(_sDesactive);
}
