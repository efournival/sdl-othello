#ifndef H_BOUTON
#define H_BOUTON

#include <functional>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Composant.h"


typedef std::function<void()>(actionClic);

class Bouton : public Composant {
	private:
		SDL_Rect _position;
		SDL_Surface* _sNormal;
		SDL_Surface* _sSurvol;
		SDL_Surface* _sDesactive;
		bool _survol;
		bool _desactive;
		actionClic _action;

	public:
		Bouton(SDL_Surface*, int, int, int, int, const char*, TTF_Font*, actionClic);
		void afficher();
		bool testSurvol(int, int);
		void cliquer();
		void activer();
		void desactiver();
		~Bouton();
};

#endif
