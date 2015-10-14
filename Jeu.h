#ifndef H_JEU
#define H_JEU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "interface/Interface.h"
#include "interface/AutoMenu.h"
#include "interface/Message.h"
#include "affichage/Image.h"
#include "affichage/Tuile.h"
#include "affichage/Sprite.h"
#include "jeu/Partie.h"
#include "fichiers/Replay.h"
#include <cstring>


class Jeu : public Interface {
	private:
		Horloge _horloge;
		SDL_Surface* _pions;
		Image* _imgPlateau;
		Image* _imgVue_Plateau;
		Tuile* _tilPions;
		Tuile* _tilAidePions;
		Tuile* _tilReplay;
		SDL_Surface* _sNomJoueur1;
		SDL_Rect _posNomJoueur1;
		SDL_Surface* _sNomJoueur2;
		SDL_Rect _posNomJoueur2;
		SDL_Surface* _sScore;
		SDL_Rect _posScore;
		Sprite* _animations[MAX][MAX];
		Replay* _replay;
		deque<Coup> _coupsReplay;
		vector<Coup> _coupsPossibles;
		uint32_t _finPartie;
		char _raisonFinPartie[20];
		uint32_t _coupIA;
		bool _retourMenu;
		void chargerImages();
		void libererImages();
		void placerPion(int, int);
		void jouerIA();
		void finPartie(const char*);
		void pause();
		void majScores();
		void dessinerPions();
		void dessinerPionsCoupsPossibles();
		bool rendre();
		bool gererEvenementsSDL();

	public:
		Partie partie;
		bool vsIA;
		void lireReplay(const char* nomFichier) throw(const char*);
		Jeu(SDL_Surface*, SDL_Surface*, Fontes fontes);
		Jeu(const Jeu &source);
		Jeu& operator=(const Jeu&);
		void afficher();
		~Jeu();
};

#endif
