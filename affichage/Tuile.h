/*
    Classe : Tuile

    Une tuile (ou plutôt set de tuiles, tileset) est une image séparée en différentes sous-images qui seront affichées
    indépendamment. Cette classe Tuile, dérivée de la classe Image, met à disposition des fonctions d'affichage simples à
    utiliser.

    Programmeur : Edgar Fournival
*/

#ifndef H_TUILE
#define H_TUILE

#include <SDL/SDL.h>
#include "Image.h"

using namespace std;


class Tuile : public Image {
    protected:
        // Largeur d'une sous-image (frames) dans le tileset
        unsigned int _largeurFrame;

        // Nombre de frames total
        unsigned int _nbFrames;

        // Rectangle source utilisé pour l'extraction de la frame voulue
        SDL_Rect _sourceFrameRect;

        // Procédure de dessin de la frame correspondante
        void dessinerSousImage(SDL_Surface*, int=0);

    public:
        // Constructeur de la classe
        Tuile(SDL_Surface*, int);

        // Affichage
        virtual void dessiner(SDL_Surface*, int=0, int=0, int=0);
};


#endif
