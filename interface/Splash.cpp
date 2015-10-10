#include "Splash.h"

#include <iostream>

using namespace std;

Splash::Splash(SDL_Surface* destination, SDL_Surface* ecran):
Interface(destination, ecran),
_image(NULL),
_assombrissement(NULL),
_horloge() {
    _image = new Image(SDL_LoadBMP("ressources\\images\\splash.bmp"));

    // On a besoin d'accéder aux pixels lors de l'alpha blending
    // Pour cela, il va falloir déclarer les masques d'accès aux composantes couleurs des pixels
    // L'accès à ces valeurs dépend de la façon (boutisme) dont sont stockée les surfaces en mémoire
    uint32_t rMask, gMask, bMask, aMask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rMask = 0xff000000;
        gMask = 0x00ff0000;
        bMask = 0x0000ff00;
        aMask = 0x000000ff;
    #else
        rMask = 0x000000ff;
        gMask = 0x0000ff00;
        bMask = 0x00ff0000;
        aMask = 0xff000000;
    #endif

    // On initialise la surface avec nos masques
    _assombrissement = SDL_CreateRGBSurface(SDL_HWSURFACE, 257, 272, 32, rMask, gMask, bMask, aMask);
}


void Splash::assombrir(unsigned int intensite) {
    // On la remplit avec du gris
    SDL_FillRect(_assombrissement, NULL, SDL_MapRGBA(_assombrissement->format, 0, 0, 0, intensite));

    // On l'affiche sur la surface de destination
    SDL_BlitSurface(_assombrissement, NULL, _rendu, NULL);
}


void Splash::afficher() {
    _sequenceur->cycler();
}


bool Splash::rendre() {
    _image->dessiner(_rendu);

    unsigned int intensite = _horloge.temps() / 3;
    intensite = (intensite > 255) ? 0 : 255-intensite;

    assombrir(intensite);

    // On étire notre surface _rendu pour qu'elle fasse la taille de la surface de rendu
    SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

    // On rafraichit notre surface d'affichage principale
    SDL_Flip(_ecran);

    return (_horloge.temps() < 3*1000) && gererEvenementsSDL();
}


bool Splash::gererEvenementsSDL() {
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) {
        switch (evenement.type) {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_KEYDOWN:
                return false;
                break;
            case SDL_QUIT:
                quitter();
                return false;
                break;
        }
    }

    return true;
}


Splash::~Splash() {
    SDL_FreeSurface(_assombrissement);
}
