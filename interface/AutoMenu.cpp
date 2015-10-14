#include "AutoMenu.h"


AutoMenu::AutoMenu(SDL_Surface* rendu,
				   SDL_Surface* ecran,
				   Fontes fontes,
				   const char* fond,
				   bool menuHorizontal,
				   int largeur,
				   int hauteur):
Interface(rendu, ecran, fontes),
_fond(NULL),
_quitterMenu(false),
menu(NULL) {
	if (fond != NULL) 
		_fond = new Image(SDL_LoadBMP(fond));

	menu = new Menu(_rendu,
					(menuHorizontal) ? 38 : (_rendu->w-largeur)/2,
					(menuHorizontal) ? 220 : 95,
					_fontes, menuHorizontal, largeur, hauteur);
}

void AutoMenu::afficher() {
	_sequenceur->cycler();
}

void AutoMenu::quitterMenu() {
	_quitterMenu = true;
}

bool AutoMenu::rendre() {
	if (_fond)
		_fond->dessiner(_rendu);

	int sourisX, sourisY;
	SDL_GetMouseState(&sourisX, &sourisY);
	menu->souris(sourisX/2, sourisY/2, false);

	menu->afficher();

	SDL_SoftStretch(_rendu, NULL, _ecran, NULL);
	SDL_Flip(_ecran);

	return gererEvenementsSDL() && (!_quitter) && (!_quitterMenu);
}


bool AutoMenu::gererEvenementsSDL() {
	SDL_Event evenement;

	while (SDL_PollEvent(&evenement)) {
		if (evenement.type == SDL_QUIT) {
			quitter();
			return false;
		} else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
			int sourisX, sourisY;
			bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
			menu->souris(sourisX/2, sourisY/2, clic);
		}
	}

	return true;
}


AutoMenu::~AutoMenu() {
	delete menu;

	if (_fond) {
		_fond->libererSurface();
		delete _fond;
	}
}
