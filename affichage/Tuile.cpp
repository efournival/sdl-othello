#include "Tuile.h"


Tuile::Tuile(SDL_Surface* surface, int largeurFrame):
Image(surface),
_largeurFrame(largeurFrame),
_nbFrames(_surface->w / _largeurFrame - 1), // Le nombre de frames est �gal � la largeur de l'image divis�e par la largeur d'une frame
_sourceFrameRect() {
    // Largeur d'affichage = largeur de la frame
    _destFrameRect.w = _largeurFrame;
    // La hauteur ne change pas
    _destFrameRect.h = _surface->h;
}


void Tuile::dessinerSousImage(SDL_Surface* destination, int indexImage) {
    // Notre rectangle source partira du coin sup�rieur gauche de la frame
    _sourceFrameRect.x = indexImage*_largeurFrame;
    // Le Y ne change pas
    _sourceFrameRect.y = 0;
    // On ne veut qu'une frame
    _sourceFrameRect.w = _largeurFrame;
    // La hauteur ne change pas
    _sourceFrameRect.h = _surface->h;

    // Et on affiche notre rectangle source sur la surface de rendu
    SDL_BlitSurface(_surface, &_sourceFrameRect, destination, &_destFrameRect);
}


void Tuile::dessiner(SDL_Surface* destination, int frame, int x, int y) {
    // On assigne les coordonn�es d�sir�es � notre rectangle de destination
    _destFrameRect.x = x;
    _destFrameRect.y = y;

    // Et on appelle notre proc�dure d�di�e � l'affihage d'une frame
    dessinerSousImage(destination, frame);
}

