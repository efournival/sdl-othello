#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "interface/Splash.h"
#include "interface/AutoMenu.h"
#include "interface/MenuJouer.h"

#include "fichiers/Replay.h"

#include "Jeu.h"


const int FENETRE_LARGEUR = 257*2;
const int FENETRE_HAUTEUR = 272*2;

int main(int argc, char** argv) {
    // Initialisation du module VIDEO de la librairie SDL
    // Ainsi que du module TIMER qui nous permet d'avoir le nombre de millisecondes écoulées grâce à SDL_GetTicks
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);

    // On veut bien vider la mémoire quand on quitte
    atexit(SDL_Quit);

    // Titre de la fenêtre
    SDL_WM_SetCaption("Othello", NULL);

    // Active le format Unicode pour le clavier
    SDL_EnableUNICODE(true);

    // On ouvre une fenêtre
    SDL_Surface* ecran = SDL_SetVideoMode(FENETRE_LARGEUR, FENETRE_HAUTEUR, 24, SDL_HWSURFACE|SDL_DOUBLEBUF);

    // Création d'une deuxième surface servant au rendu, elle sera ensuite étirée pour un effet pixellisé
    const SDL_PixelFormat& fmt = *(ecran->format);
    SDL_Surface* rendu = SDL_CreateRGBSurface(SDL_HWSURFACE, 257, 272, fmt.BitsPerPixel, fmt.Rmask, fmt.Gmask, fmt.Bmask, fmt.Amask);

    // Chargement de SDL_ttf pour l'affichage des fontes
    TTF_Init();

    // Chargement des fontes
    Fontes fontes;
    fontes.fonteMenu = TTF_OpenFont("ressources/fontes/DejaVuSerif-Bold.ttf", 11);
    fontes.fonteNormal = TTF_OpenFont("ressources/fontes/Philosopher-Regular.ttf", 12);
    fontes.fonteGras = TTF_OpenFont("ressources/fontes/Philosopher-Bold.ttf", 12);

    // Si un replay est passé en paramètre, on le lit
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

    // Création d'un menu automatique qui représentera notre menu principal
    AutoMenu menuPrincipal(rendu, ecran, fontes, "ressources/images/menu.bmp");

    menuPrincipal.menu->ajouterEspace();

    menuPrincipal.menu->ajouterBouton("Jouer", [&] () {
        AutoMenu typeJeu(rendu, ecran, fontes, "ressources/images/menu.bmp");

        // Initialisation d'un replay temporaire
        bool replayOk = false;
        Replay* replay = new Replay();
        Header header;

        // On vérifie si il est possible d'ouvrir le replay
        try {
            replay->setMode(MODE_REPLAY, "ressources/replay.otlo");
            header = replay->getHeader();
            replayOk = true;

        // Si une exception est levée, c'est qu'on ne peut pas le lire
        } catch (const char*) {
            replayOk = false;
        }

        // On libère la mémoire et ferme le replay
        delete replay;

        // Si le replay existe
        if (replayOk) {
            // On ajoute un bouton qui aura pour nom 'Continuer la partie' si la partie est en cours ou 'Revoir la partie' si la partie est terminée
            typeJeu.menu->ajouterBouton((header.partieEnCours) ? "Continuer la partie" : "Revoir la partie", [&] () {
                // On lance le replay
                try {
                    Jeu Othello(rendu, ecran, fontes);
                    Othello.lireReplay("ressources/replay.otlo");
                    Othello.afficher();
                    typeJeu.quitterMenu();

                // Attention : le système de replay peut lever des exceptions en cas de soucis avec le fichier, il faudra bien les afficher
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

        // Affichage interface
        typeJeu.afficher();
    });

    menuPrincipal.menu->ajouterEspace();

    menuPrincipal.menu->ajouterEspace();

    menuPrincipal.menu->ajouterBouton("Quitter", [&] () {
        menuPrincipal.quitterMenu();
    });

    // Affichage interface
    menuPrincipal.afficher();

    // Libération mémoire
    SDL_FreeSurface(rendu);

    return 0;
}
