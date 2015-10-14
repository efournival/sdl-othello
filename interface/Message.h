#ifndef H_MESSAGE
#define H_MESSAGE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Interface.h"
#include "Bouton.h"


class Message : public Interface {
	private:
		SDL_Surface* _titre;
		SDL_Surface* _contenu;
		Bouton* _bouton;
		bool _sortir;
		bool rendre();
		bool gererEvenementsSDL();

	public:
		Message(SDL_Surface*, SDL_Surface*, Fontes, const char*, const char*);
		void afficher();
		~Message();
};

void assombrir(SDL_Surface*);

#endif
