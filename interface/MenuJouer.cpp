#include "MenuJouer.h"


MenuJouer::MenuJouer(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes, bool typePartie):
AutoMenu(rendu, ecran, fontes, NULL, true, 80),
_fond(NULL),
_texte1(NULL),
_texte2(NULL),
_typePartie(typePartie),
_selecteurJ1(NULL),
_selecteurJ2(NULL),
razMenu(false) {
	_fond = new Image(SDL_LoadBMP("ressources/images/sous_menu.bmp"));

	menu->ajouterBouton("Annuler", [&] () {
		quitterMenu();
	});

	menu->ajouterBouton("Jouer !", [&] () {
		jouer();
		razMenu = true;
		quitterMenu();
	});

	_selecteurJ1 = new SelecteurNom(_rendu, 30, 80, "Joueur 1 :", _fontes.fonteMenu);
	_selecteurJ2 = new SelecteurNom(_rendu, 30, 110, "Joueur 2 :", _fontes.fonteMenu);

	Configuration configuration;
	Config config = configuration.lireConfig();

	_selecteurJ1->setNom(config.nomJoueur1);

	if (_typePartie) {
		_selecteurJ2->setNom("Ordinateur");
	} else {
		_selecteurJ2->setNom(config.nomJoueur2);
	}

	_texte1 = TTF_RenderText_Solid(_fontes.fonteMenu, "Veuillez entrer le nom des", {0, 0, 0, 0});
	_texte2 = TTF_RenderText_Solid(_fontes.fonteMenu, "joueurs de cette partie :", {0, 0, 0, 0});
}

void MenuJouer::jouer() {
	sauvegarderNomsJoueurs();

	Jeu Othello(_rendu, _ecran, _fontes);
	Othello.vsIA = _typePartie;

	srand(time(NULL));
	bool commence = rand() % 2;

	Othello.partie.J1.setNom((commence) ? _selecteurJ1->getNom() : _selecteurJ2->getNom());
	Othello.partie.J2.setNom((commence) ? _selecteurJ2->getNom() : _selecteurJ1->getNom());

	Othello.afficher();
}

bool MenuJouer::rendre() {
	_fond->dessiner(_rendu);

	SDL_Rect posTexte;
	posTexte.x = 30;
	posTexte.y = 30;

	SDL_BlitSurface(_texte1, NULL, _rendu, &posTexte);
	posTexte.y = 46;
	SDL_BlitSurface(_texte2, NULL, _rendu, &posTexte);

	int sourisX, sourisY;
	SDL_GetMouseState(&sourisX, &sourisY);

	_selecteurJ1->souris(sourisX / 2, sourisY / 2, false);
	_selecteurJ1->afficher();

	if (!_typePartie) 
		_selecteurJ2->souris(sourisX / 2, sourisY / 2, false);

	_selecteurJ2->afficher();

	if (strlen(_selecteurJ1->getNom()) > 0 && strlen(_selecteurJ2->getNom()) > 0 &&
		strcmp(_selecteurJ1->getNom(), _selecteurJ2->getNom()) != 0) {
		menu->activerBouton(1);
	} else {
		menu->desactiverBouton(1);
	}

	return AutoMenu::rendre();
}

bool MenuJouer::gererEvenementsSDL() {
	SDL_Event evenement;

	while (SDL_PollEvent(&evenement)) {
		if (evenement.type == SDL_QUIT) {
			quitter();
			return false;
		} else if (evenement.type == SDL_KEYDOWN) {
			// Si les deux sélecteurs ne sont pas vides et/ou égaux, et qu'on appuie sur Entrée
			if ((strlen(_selecteurJ1->getNom()) > 0 &&
				 strlen(_selecteurJ2->getNom()) > 0 &&
				 strcmp(_selecteurJ1->getNom(), _selecteurJ2->getNom()) != 0)
				&& (evenement.key.keysym.sym == SDLK_RETURN || evenement.key.keysym.sym == SDLK_KP_ENTER)) {
				jouer();
			} else {
				if (evenement.key.keysym.sym == SDLK_TAB) {
					if (!_typePartie) {
						if (_selecteurJ1->getFocus()) {
							_selecteurJ1->setFocus(false);
							_selecteurJ2->setFocus(true);
						} else {
							_selecteurJ1->setFocus(true);
							_selecteurJ2->setFocus(false);
						}
					}
				} else if (evenement.key.keysym.sym != SDLK_ESCAPE) {
					_selecteurJ1->clavier(evenement.key.keysym);
					if (!_typePartie)
						_selecteurJ2->clavier(evenement.key.keysym);
				}
			}

		} else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
			int sourisX, sourisY;
			bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
			menu->souris(sourisX/2, sourisY/2, clic);
			_selecteurJ1->souris(sourisX/2, sourisY/2, clic);
			if (!_typePartie) 
				_selecteurJ2->souris(sourisX/2, sourisY/2, clic);
		}
	}

	return true;
}

void MenuJouer::sauvegarderNomsJoueurs() {
	Configuration configuration;
	Config config = configuration.lireConfig();
	configuration.ecrireConfig(_selecteurJ1->getNom(), _typePartie ? config.nomJoueur2 : _selecteurJ2->getNom());
}

MenuJouer::~MenuJouer() {
	delete _fond;
	delete _selecteurJ1;
	delete _selecteurJ2;

	SDL_FreeSurface(_texte1);
	SDL_FreeSurface(_texte2);
}
