#ifndef H_MENU
#define H_MENU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Composant.h"
#include "Interface.h"
#include "Bouton.h"


const int MAX_BOUTONS = 8;

class Menu : public Composant {
	private:
		Fontes _fontes;
		Bouton* _boutons[MAX_BOUTONS];
		int _nbBoutons;
		int _x;
		int _y;
		int _largeur;
		int _hauteur;
		bool _horizontal;

	public:
		Menu(SDL_Surface*, int, int, Fontes, bool=false, int=150, int=16);
		void afficher();
		void souris(int, int, bool);
		void ajouterBouton(const char*, actionClic);
		void ajouterEspace();
		void activerBouton(int);
		void desactiverBouton(int);
		~Menu();
};

#endif
