#ifndef H_AUTOMENU
#define H_AUTOMENU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../affichage/Image.h"
#include "../interface/Interface.h"
#include "../interface/Menu.h"


class AutoMenu : public Interface {
	protected:
		virtual bool rendre();
		virtual bool gererEvenementsSDL();

	private:
		Image* _fond;
		bool _quitterMenu;

	public:
		Menu* menu;
		AutoMenu(SDL_Surface*, SDL_Surface*, Fontes, const char* = NULL, bool = false, int = 150, int = 16);
		void afficher();
		void quitterMenu();
		~AutoMenu();
};

#endif
