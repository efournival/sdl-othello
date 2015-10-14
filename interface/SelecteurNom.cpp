#include "SelecteurNom.h"


SelecteurNom::SelecteurNom(SDL_Surface* rendu, int x, int y, const char* texte, TTF_Font* fonte):
Composant(rendu),
_fonte(fonte),
_texte(),
_champ(NULL),
_x(x),
_y(y),
_focus(false),
_horloge() {
	_nomJoueur[0] = '\0';
	_texte = TTF_RenderText_Solid(_fonte, texte, {0, 0, 0, 0});
}

void SelecteurNom::afficher() {
	SDL_Rect champTexte;
	champTexte.x = _x + 75;
	champTexte.y = _y;
	champTexte.w = 120;
	champTexte.h = 17;

	// Contour noir
	SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 0, 0, 0, 255));

	champTexte.x = _x + 76;
	champTexte.y = _y + 1;
	champTexte.w = 118;
	champTexte.h = 15;

	// Contour vert
	SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 0, 80, 14, 255));

	SDL_Rect posTexte;
	posTexte.x = _x;
	posTexte.y = _y + 2;

	SDL_BlitSurface(_texte, NULL, _rendu, &posTexte);

	if (_champ) {
		posTexte.x = _x + 191 - _champ->w;
		SDL_BlitSurface(_champ, NULL, _rendu, &posTexte);
	}

	if (_focus) {
		champTexte.x = _x + 95 + 96;
		champTexte.y = _y + 3;
		champTexte.w = 2;
		champTexte.h = 11;

		// Clignotement
		if (_horloge.temps() - ((int) _horloge.temps() / 1000) * 1000 > 500) {
			SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 255, 255, 255, 255));
		}
	}
}

void SelecteurNom::souris(int x, int y, bool clic) {
	if (clic && x >= _x && y >= _y && x <= _x + 195 && y <= _y + 18) {
		_focus = true;
	} else if (clic) {
		_focus = false;
	}
}

void SelecteurNom::clavier(SDL_keysym keysym) {
	if (_focus) {
		unsigned int taille = strlen(_nomJoueur);

		if (keysym.sym == SDLK_BACKSPACE) {
			if (taille > 0) 
				_nomJoueur[taille - 1] = 0;
		} else if ((keysym.unicode & 0xFF80) == 0) {	// ASCII char
			char caractere = keysym.unicode & 0x7F;
			int largeurSurface = _champ ? _champ->w : 0;
			if (taille < sizeof(_nomJoueur) - 1 && largeurSurface < 108) {
				_nomJoueur[taille] = caractere;
				_nomJoueur[taille + 1] = '\0';
			}
		}

		if (_champ)
			SDL_FreeSurface(_champ);

		_champ = TTF_RenderText_Solid(_fonte, _nomJoueur, {255, 255, 255, 255});
	}
}

void SelecteurNom::setNom(const char* nomJoueur) {
	strcpy(_nomJoueur, nomJoueur);

	if (_champ)
		SDL_FreeSurface(_champ);

	_champ = TTF_RenderText_Solid(_fonte, _nomJoueur, {255, 255, 255, 255});
}

SelecteurNom::~SelecteurNom() {
	if (_champ) 
		SDL_FreeSurface(_champ);

	SDL_FreeSurface(_texte);
}
