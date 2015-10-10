/*
    Classe : Tuile

    Une tuile (ou plut�t set de tuiles, tileset) est une image s�par�e en diff�rentes sous-images qui seront affich�es
    ind�pendamment. Cette classe Tuile, d�riv�e de la classe Image, met � disposition des fonctions d'affichage simples �
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

        // Rectangle source utilis� pour l'extraction de la frame voulue
        SDL_Rect _sourceFrameRect;

        // Proc�dure de dessin de la frame correspondante
        void dessinerSousImage(SDL_Surface*, int=0);

    public:
        // Constructeur de la classe
        Tuile(SDL_Surface*, int);

        // Affichage
        virtual void dessiner(SDL_Surface*, int=0, int=0, int=0);
};


#endif
