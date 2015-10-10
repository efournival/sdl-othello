#include "Plateau.h"


char Plateau::getPion(int X, int Y) const throw(const char*) {
    if (X < 0 || X > MAX || Y < 0 || Y > MAX) throw("Indices plateau incorrects.");

    return _pions[X][Y];
}


void Plateau::setPion(int X, int Y, char couleur) throw(const char*) {
    if (X < 0 || X > MAX || Y < 0 || Y > MAX) throw("Indices plateau incorrects.");

    _pions[X][Y] = couleur;
}
