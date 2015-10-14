#ifndef H_JOUEUR
#define H_JOUEUR

#include <cstring>
#include "Plateau.h"


class Joueur {
	private:
		char _nom[16];
		char _couleur;
		int _score;

	public:
		Joueur(char = 0, const char* = "");
		void setCouleur(char);
		char getCouleur() const;
		void setNom(const char*);
		const char* getNom() const;
		void setScore(int);
		int getScore() const;
};

#endif
