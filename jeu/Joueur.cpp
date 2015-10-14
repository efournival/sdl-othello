#include "Joueur.h"


Joueur::Joueur(char couleur, const char nom[16]):
_nom(),
_couleur(couleur),
_score(2) {
	strncpy(_nom, nom, 16);
}

void Joueur::setCouleur(char couleur) {
	_couleur = couleur;
}

char Joueur::getCouleur() const {
	return _couleur;
}

void Joueur::setNom(const char nom[16]) {
	strcpy(_nom, nom);
}

const char* Joueur::getNom() const {
	return _nom;
}

void Joueur::setScore(int score) {
	_score = score;
}

int Joueur::getScore() const {
	return _score;
}
