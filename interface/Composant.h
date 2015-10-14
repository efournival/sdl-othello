#ifndef H_COMPOSANT
#define H_COMPOSANT

#include <SDL/SDL.h>


class Composant {
	protected:
		SDL_Surface* _rendu;

	public:
		Composant(SDL_Surface* rendu):_rendu(rendu) {};
		virtual void afficher() =0;
		virtual ~Composant() {};
};

#endif
