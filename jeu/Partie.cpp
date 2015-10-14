#include "Partie.h"


Partie::Partie():
joueurCourant(&J1),
J1(), J2(),
plateau() {
	J1.setNom("Joueur 1");
	J1.setCouleur(N);
	J1.setNom("Joueur 2");
	J2.setCouleur(B);
}

int Partie::calculerScore(Joueur &J) const {
	int score = 0;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (plateau.getPion(i, j) == J.getCouleur()){
				score++;
			}
		}
	}

	return score;
}

bool Partie::testDirection(int pX, int pY, int oX, int oY, Joueur& J) const {
	if (pX + oX * 2 > MAX || pX + oX * 2 < 0 || pY + oY * 2 > MAX || pY + oY * 2 < 0) {
		return false;
	}

	char joueur;
	char ennemi;

	if (&J == &J1) {
		joueur = J1.getCouleur();
		ennemi = J2.getCouleur();
	} else {
		joueur = J2.getCouleur();
		ennemi = J1.getCouleur();
	}

	int i, j;

	if (plateau.getPion(pX+oX, pY+oY) == ennemi) {
		i = pX + oX * 2;
		j = pY + oY * 2;

		while (i >= 0 && i < MAX && j >=0 && j < MAX) {
			if (plateau.getPion(i, j) == joueur) 
				return true;

			if (plateau.getPion(i, j) == X) 
				return false;

			i += oX;
			j += oY;
		}
	}

	return false;
}

bool Partie::testJeu(int positionLigne, int positionColonne) const {
	if (plateau.getPion(positionLigne, positionColonne) != X) 
		return false;

	if (testDirection(positionLigne, positionColonne, 1, 0, *joueurCourant)) return true; // Bas
	if (testDirection(positionLigne, positionColonne,-1, 0, *joueurCourant)) return true; // Haut
	if (testDirection(positionLigne, positionColonne, 0, 1, *joueurCourant)) return true; // Droite
	if (testDirection(positionLigne, positionColonne, 0,-1, *joueurCourant)) return true; // Haut
	if (testDirection(positionLigne, positionColonne, 1, 1, *joueurCourant)) return true; // Bas-droite
	if (testDirection(positionLigne, positionColonne, 1,-1, *joueurCourant)) return true; // Bas-gauche
	if (testDirection(positionLigne, positionColonne,-1, 1, *joueurCourant)) return true; // Haut-droite
	if (testDirection(positionLigne, positionColonne,-1,-1, *joueurCourant)) return true; // Haut-gauche

	return false;
}

bool Partie::jeuPlein() const {
	bool plein = true;
	int i = 0;
	int j = 0;

	while (i < MAX && plein) {
		j = 0;

		while (j < MAX && plein) {
			if (plateau.getPion(i, j) == X) {
				plein = false;
			}

			j++;
		}

		i++;
	}

	return plein;
}

int Partie::retourner(int pX, int pY, int oX, int oY, Joueur& J, animFonction fonction, bool retournerPions) {
	bool continuer = true;
	int cptPions = 0;

	int i = pX + oX;
	int j = pY + oY;

	char joueur;
	char ennemi;

	if (&J == &J1) {
		joueur = J1.getCouleur();
		ennemi = J2.getCouleur();
	} else {
		joueur = J2.getCouleur();
		ennemi = J1.getCouleur();
	}

	while (i >= 0 && i < MAX && j >=0 && j < MAX && continuer) {
		if (plateau.getPion(i, j) == ennemi) {
			if (retournerPions) {
				plateau.setPion(i, j, joueur);
				fonction(i, j);
			}

			cptPions++;
		} else {
			continuer = false;
		}

		i += oX;
		j += oY;
	}

	if (retournerPions) {
		J1.setScore(calculerScore(J1));
		J2.setScore(calculerScore(J2));
	}

	return cptPions;
}

int Partie::jouer(int positionLigne, int positionColonne, animFonction fonction, bool retournerPions) {
	int cptPions = 1;

	if (retournerPions) 
		plateau.setPion(positionLigne, positionColonne, joueurCourant->getCouleur());

	if (testDirection(positionLigne, positionColonne, 1, 0, *joueurCourant))  // Bas
		cptPions += retourner(positionLigne, positionColonne, 1, 0, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne,-1, 0, *joueurCourant))  // Haut
		cptPions += retourner(positionLigne, positionColonne,-1, 0, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne, 0, 1, *joueurCourant))  // Droite
		cptPions += retourner(positionLigne, positionColonne, 0, 1, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne, 0,-1, *joueurCourant))  // Haut
		cptPions += retourner(positionLigne, positionColonne, 0,-1, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne, 1, 1, *joueurCourant))  // Bas-droite
		cptPions += retourner(positionLigne, positionColonne, 1, 1, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne, 1,-1, *joueurCourant))  // Bas-gauche
		cptPions += retourner(positionLigne, positionColonne, 1,-1, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne,-1, 1, *joueurCourant))  // Haut-droite
		cptPions += retourner(positionLigne, positionColonne,-1, 1, *joueurCourant, fonction, retournerPions);

	if (testDirection(positionLigne, positionColonne,-1,-1, *joueurCourant))  // Haut-gauche
		cptPions += retourner(positionLigne, positionColonne,-1,-1, *joueurCourant, fonction, retournerPions);

	if (retournerPions) 
		joueurSuivant();

	return cptPions;
}

bool Partie::jeuPossible() const {
	bool possible = false;
	int i = 0;
	int j = 0;

	while (i < MAX && !possible) {
		j = 0;

		while (j < MAX && !possible) {
			if (testJeu(i, j)) {
				possible = true;
			}

			j++;
		}

		i++;
	}

	return possible;
}

void Partie::joueurSuivant(){
	if (joueurCourant == &J1) {
		joueurCourant = &J2;
	} else {
		joueurCourant = &J1;
	}
}

vector<Coup> Partie::getCoupsPossibles() {
	vector<Coup> resultat;
	Coup coup;

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (testJeu(i, j)) {
				coup.X = i;
				coup.Y = j;
				coup.temps = jouer(i, j, [] (int, int) {}, false);
				resultat.push_back(coup);
			}
		}
	}

	sort(resultat.begin(), resultat.end(), [] (Coup a, Coup b) {
		return a.temps > b.temps;
	});

	return resultat;
}
