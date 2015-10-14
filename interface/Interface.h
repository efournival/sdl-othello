#ifndef H_INTERFACE
#define H_INTERFACE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "Composant.h"
#include "../Sequenceur.h"


struct Fontes {
	TTF_Font* fonteMenu;
	TTF_Font* fonteNormal;
	TTF_Font* fonteGras;
};

class Interface : public Composant {
	protected:
		SDL_Surface* _ecran;
		Sequenceur* _sequenceur;
		Fontes _fontes;
		virtual bool rendre() =0;
		virtual bool gererEvenementsSDL() =0;
		static bool _quitter;
		void quitter() { _quitter = true; }

	public:
		Interface(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes):
		Composant(rendu),
		_ecran(ecran),
		_sequenceur(new Sequenceur(&Interface::rendre, this)),
		_fontes(fontes) {};
		virtual void afficher() =0;
		virtual ~Interface() { delete _sequenceur; };
};

#endif
