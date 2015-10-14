#ifndef H_SELECTEURNOM
#define H_SELECTEURNOM

#include <cstring>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "../Horloge.h"
#include "Composant.h"


class SelecteurNom : public Composant {
	private:
		TTF_Font* _fonte;
		SDL_Surface* _texte;
		SDL_Surface* _champ;
		int _x;
		int _y;
		char _nomJoueur[16];
		bool _focus;
		Horloge _horloge;

	public:
		SelecteurNom(SDL_Surface*, int, int, const char*, TTF_Font*);
		void afficher();
		void souris(int, int, bool);
		void clavier(SDL_keysym);
		char* getNom() { return _nomJoueur; }
		void setNom(const char*);
		bool getFocus() { return _focus; }
		void setFocus(bool focus) { _focus = focus; }
		~SelecteurNom();
};

#endif
