#include "Menu.h"


Menu::Menu(SDL_Surface* rendu, int pX, int pY, Fontes fontes, bool horizontal, int largeur, int hauteur):
Composant(rendu),
_fontes(fontes),
_nbBoutons(0),
_x(pX),
_y(pY),
_largeur(largeur),
_hauteur(hauteur),
_horizontal(horizontal) {
	for (int i = 0; i < MAX_BOUTONS; i++) {
		_boutons[i] = NULL;
	}
}

void Menu::souris(int pX, int pY, bool clicGauche) {
	for (int i = 0; i < _nbBoutons; i++) {
		if (_boutons[i] != NULL && _boutons[i]->testSurvol(pX, pY) && clicGauche) {
			_boutons[i]->cliquer();
			break;
		}
	}
}

void Menu::afficher() {
	for (int i = 0; i < _nbBoutons; i++) {
		if (_boutons[i] != NULL) {
			_boutons[i]->afficher();
		}
	}
}

void Menu::ajouterBouton(const char* texte, actionClic action) {
	if (_horizontal) {
		_boutons[_nbBoutons] = new Bouton(_rendu,
										  _x+(_nbBoutons % 9) * (_largeur * 1.25),
										  _y+((int) _nbBoutons / 9) * (_hauteur * 1.25),
										  _largeur, _hauteur, texte, _fontes.fonteMenu, action);
	} else {
		_boutons[_nbBoutons] = new Bouton(_rendu, _x, _y + _nbBoutons * (_hauteur * 1.25), _largeur,
										  _hauteur, texte, _fontes.fonteMenu, action);
	}

	_nbBoutons++;
}

void Menu::ajouterEspace() {
	_nbBoutons++;
}

void Menu::activerBouton(int index) {
	_boutons[index]->activer();
}

void Menu::desactiverBouton(int index) {
	_boutons[index]->desactiver();
}

Menu::~Menu() {
	for (int i = 0; i < _nbBoutons; i++) {
		if (_boutons[i] != NULL) {
			delete _boutons[i];
		}
	}
}
