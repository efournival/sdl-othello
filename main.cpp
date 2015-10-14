#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "interface/Splash.h"
#include "interface/AutoMenu.h"
#include "interface/MenuJouer.h"
#include "fichiers/Replay.h"
#include "Jeu.h"


const int LARGEUR = 257;
const int HAUTEUR = 272;

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

	atexit(SDL_Quit);

	SDL_WM_SetCaption("Othello", NULL);

	SDL_EnableUNICODE(true);

	SDL_Surface* ecran = SDL_SetVideoMode(LARGEUR * 2, HAUTEUR * 2, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);

	const SDL_PixelFormat& fmt = *(ecran->format);
	SDL_Surface* rendu = SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

	TTF_Init();

	Fontes fontes;
	fontes.fonteMenu = TTF_OpenFont("ressources/fontes/DejaVuSerif-Bold.ttf", 11);
	fontes.fonteNormal = TTF_OpenFont("ressources/fontes/Philosopher-Regular.ttf", 12);
	fontes.fonteGras = TTF_OpenFont("ressources/fontes/Philosopher-Bold.ttf", 12);

	if (argc > 1) {
		try {
			Jeu Othello(rendu, ecran, fontes);
			Othello.lireReplay(argv[1]);
			Othello.afficher();
		} catch (const char* ex) {
			Message message(rendu, ecran, fontes, "Erreur replay", ex);
			message.afficher();
		}
	}

	AutoMenu menuPrincipal(rendu, ecran, fontes, "ressources/images/menu.bmp");

	menuPrincipal.menu->ajouterEspace();

	menuPrincipal.menu->ajouterBouton("Jouer", [&] () {
		AutoMenu typeJeu(rendu, ecran, fontes, "ressources/images/menu.bmp");

		bool replayOk = false;
		Replay* replay = new Replay();
		Header header;

		try {
			replay->setMode(MODE_REPLAY, "ressources/replay.otlo");
			header = replay->getHeader();
			replayOk = true;
		} catch (const char*) {
			replayOk = false;
		}

		delete replay;

		if (replayOk) {
			typeJeu.menu->ajouterBouton((header.partieEnCours) ? "Continuer la partie" : "Revoir la partie", [&] () {
				try {
					Jeu Othello(rendu, ecran, fontes);
					Othello.lireReplay("ressources/replay.otlo");
					Othello.afficher();
					typeJeu.quitterMenu();
				} catch (const char* ex) {
					Message message(rendu, ecran, fontes, "Erreur replay", ex);
					message.afficher();
				}
			});

			typeJeu.menu->ajouterEspace();
		} else {
			typeJeu.menu->ajouterEspace();
		}

		typeJeu.menu->ajouterBouton("2 joueurs", [&] () {
			MenuJouer menuJouer(rendu, ecran, fontes, false);
			menuJouer.afficher();
			if (menuJouer.razMenu) typeJeu.quitterMenu();
		});

		typeJeu.menu->ajouterBouton("1 joueur contre l'IA", [&] () {
			MenuJouer menuJouer(rendu, ecran, fontes, true);
			menuJouer.afficher();
			if (menuJouer.razMenu) typeJeu.quitterMenu();
		});

		typeJeu.menu->ajouterEspace();

		typeJeu.menu->ajouterBouton("Menu principal", [&] () {
			typeJeu.quitterMenu();
		});

		typeJeu.afficher();
	});

	menuPrincipal.menu->ajouterEspace();

	menuPrincipal.menu->ajouterEspace();

	menuPrincipal.menu->ajouterBouton("Quitter", [&] () {
		menuPrincipal.quitterMenu();
	});

	menuPrincipal.afficher();

	SDL_FreeSurface(rendu);

	return 0;
}
