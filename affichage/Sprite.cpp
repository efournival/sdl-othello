#include "Sprite.h"


Sprite::Sprite(SDL_Surface* rendu, Horloge* horloge, int largeurFrame, int delaiFrames, bool inverse):
Tuile(rendu, largeurFrame),
_delaiFrames(delaiFrames),
_frame(0),
_debut(horloge->temps()),
_horloge(horloge),
_inverse(inverse) {}


bool Sprite::animFinie() const {
    // Si la frame en cours est la derni�re frame de notre tileset, l'animation est termin�e
    return (_frame >= _nbFrames);
}


void Sprite::dessiner(SDL_Surface* destination, int x, int y) {
    _destFrameRect.x = x;
    _destFrameRect.y = y;

    // On extrait la frame actuelle en calculant tout d'abord le temps �coul� depuis le d�but de l'animation
    // puis on divise ce temps par la dur�e d'une frame calcul�e dans le constructeur
    _frame = (_horloge->temps() - _debut) / _delaiFrames;

    // On v�rifie ensuite qu'on a pas d�pass� le nombre total de frames
    // Correspond aux instructions suivantes : _frame = min(_frame, _nbFrames)
    _frame = (_frame >= _nbFrames) ? _nbFrames : _frame;

    // Utilise la m�thode de la classe Tuile
    // La frame affich�e sera le nombre de frames total moins la frame en cours si on veut inverser l'animation
    dessinerSousImage(destination, (_inverse) ? _nbFrames-_frame : _frame);
}
