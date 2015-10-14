#ifndef H_PARTIE
#define H_PARTIE

#include <algorithm>
#include <functional>
#include <vector>
#include "Joueur.h"
#include "Plateau.h"
#include "../fichiers/Replay.h"


typedef std::function<void(int, int)>(animFonction);

class Partie {
	private:
		bool testDirection(int, int, int, int, Joueur&) const;
		int calculerScore(Joueur&) const;

	public:
		Joueur* joueurCourant;
		Joueur J1, J2;
		Plateau plateau;
		Partie();
		int retourner(int, int, int, int, Joueur&, animFonction, bool = true);
		bool testJeu(int, int) const;
		int jouer(int, int, animFonction, bool = true);
		bool jeuPossible() const;
		bool jeuPlein() const;
		void joueurSuivant();
		vector<Coup> getCoupsPossibles();
};

#endif
