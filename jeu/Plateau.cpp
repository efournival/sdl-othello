#include "Plateau.h"


char Plateau::getPion(int X, int Y) const {
	return _pions[X][Y];
}

void Plateau::setPion(int X, int Y, char couleur) {
	_pions[X][Y] = couleur;
}
