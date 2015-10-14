#ifndef H_SPLASH
#define H_SPLASH

#include <SDL/SDL.h>
#include "../affichage/Image.h"
#include "Interface.h"
#include "../Horloge.h"


class Splash : public Interface {
	private:
		Image* _image;
		SDL_Surface* _assombrissement;
		Horloge _horloge;
		void assombrir(unsigned int);
		bool rendre();
		bool gererEvenementsSDL();

	public:
		Splash(SDL_Surface*, SDL_Surface*);
		void afficher();
		~Splash();
};

#endif
