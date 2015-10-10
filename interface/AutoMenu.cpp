#include "AutoMenu.h"


AutoMenu::AutoMenu(SDL_Surface* rendu,
                   SDL_Surface* ecran,
                   Fontes fontes,
                   const char* fond,
                   bool menuHorizontal,
                   int largeur,
                   int hauteur):
Interface(rendu, ecran, fontes),
_fond(NULL),
_quitterMenu(false),
menu(NULL) {
    if (fond != NULL) _fond = new Image(SDL_LoadBMP(fond));

    // On créé notre menu
    menu = new Menu(_rendu,
                    (menuHorizontal) ? 38 : (_rendu->w-largeur)/2,
                    (menuHorizontal) ? 220 : 95,
                    _fontes, menuHorizontal, largeur, hauteur);
}

void AutoMenu::afficher() {
    // Et on répète
    _sequenceur->cycler();
}


void AutoMenu::quitterMenu() {
    _quitterMenu = true;
}


bool AutoMenu::rendre() {
    // Si l'image de fond existe, on l'affiche
    if (_fond) _fond->dessiner(_rendu);

    // On gère la souris dans rendre() pour mieux afficher les effets de survol
    int sourisX, sourisY;
    SDL_GetMouseState(&sourisX, &sourisY);
    menu->souris(sourisX/2, sourisY/2, false); // Mais on ne gère pas les clics ici

    // Affichage du menu
    menu->afficher();

    // On étire notre surface 'preRendu' pour qu'elle fasse la taille de la surface de rendu
    SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

    // On rafraichit notre surface d'affichage principale
    SDL_Flip(_ecran);

    // Gestion des évènements
    return gererEvenementsSDL() && (!_quitter) && (!_quitterMenu);
}


bool AutoMenu::gererEvenementsSDL() {
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) {
        // On veut quitter le programme ?
        if (evenement.type == SDL_QUIT) {
            quitter();
            return false;

        // Clic sur l'interface
        } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
            int sourisX, sourisY;
            bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
            menu->souris(sourisX/2, sourisY/2, clic);
        }
    }

    return true;
}


AutoMenu::~AutoMenu() {
    // On oublie pas de vider la mémoire
    delete menu;

    if (_fond) {
        _fond->libererSurface();
        delete _fond;
    }
}
