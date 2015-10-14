#ifndef H_MENUJOUER
#define H_MENUJOUER

#include <ctime>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../fichiers/Configuration.h"
#include "AutoMenu.h"
#include "SelecteurNom.h"
#include "../Jeu.h"


class MenuJouer : public AutoMenu {
	private:
		Image* _fond;
		SDL_Surface* _texte1;
		SDL_Surface* _texte2;
		bool _typePartie;	// FAUX : 2 joueurs humains, VRAI : joueur humain vs ordinateur
		SelecteurNom* _selecteurJ1;
		SelecteurNom* _selecteurJ2;
		bool gererEvenementsSDL();
		bool rendre();
		void sauvegarderNomsJoueurs();
		void jouer();

	public:
		bool razMenu;
		MenuJouer(SDL_Surface*, SDL_Surface*, Fontes, bool);
		~MenuJouer();
};

#endif
