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

    // On parcourt toutes les lignes du tableau représentant le plateau du jeu
    for (int i=0;i<MAX;i++) {
        // On parcourt chaque colonne
        for (int j=0;j<MAX;j++) {
            // Si c'est un pion blanc, alors on incrémente le score des blancs
            if (plateau.getPion(i, j) == J.getCouleur()){
                score++;
            }
        }
    }

    return score;
}

bool Partie::testDirection(int pX, int pY, int oX, int oY, Joueur& J) const throw(const char*) {
    if (pX < 0 || pX > MAX || pY < 0 || pY > MAX) throw("Indices plateau incorrects.");

    // Est-on hors des limites du tableau ?
    // Si oui, alors il n'y a pas de pions après cette case, donc il faut chercher dans une autre direction...
    if (pX+oX*2 > MAX || pX+oX*2 < 0 || pY+oY*2 > MAX || pY+oY*2 < 0) return false;

    // Les caractères représentant les pions des deux joueurs
    char joueur;
    char ennemi;

    // On définit le caractère de l'ennemi en fonction du caractère du joueur passé en paramètre
    if (&J == &J1) {
        joueur = J1.getCouleur();
        ennemi = J2.getCouleur();
    } else {
        joueur = J2.getCouleur();
        ennemi = J1.getCouleur();
    }

    // On a pas trouvé de pion appartenant au joueur dans cette direction
    int i, j;

    // On parcourt chaque case dans la direction indiquée par le vecteur (oX, oY) jusqu'au bord du tableau
    if (plateau.getPion(pX+oX, pY+oY) == ennemi) {
        // On commence par le pion se trouvant après le pion ennemi
        i = pX + oX*2;
        j = pY + oY*2;

        // Tant qu'on ne touche pas un bord du plateau
        while (i >= 0 && i < MAX && j >=0 && j < MAX) {
            // Si le pion en cours appartient au joueur, c'est bon on peut jouer
            if (plateau.getPion(i, j) == joueur) return true;
            // Si c'est une case vide, on sort
            if (plateau.getPion(i, j) == X) return false;
            // Sinon, on continue notre parcours
            i += oX;
            j += oY;
        }

        // Toujours pas de pion appartenant au joueur et on touche les bords ? On ne peut pas jouer
        return false;
    } else {
        // Si le pion adjacent n'est même pas un ennemi, impossible de jouer
        return false;
    }
}


bool Partie::testJeu(int positionLigne, int positionColonne) const throw(const char*) {
    if (positionLigne < 0 || positionLigne > MAX || positionColonne < 0 || positionColonne > MAX) throw("Indices plateau incorrects.");

    // Si la case n'est pas vide, on ne peut pas jouer...
    if (plateau.getPion(positionLigne, positionColonne) != X) return false;

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
    // Déclaration et initialisation variables
    bool plein = true;
    int i = 0;
    int j = 0;

    // Tant que toutes les lignes ne sont pas parcourues et que plein est vrai
    while (i < MAX && plein) {
        // Réinitialisation du compteur
        j = 0;

        // Tant que toutes les colonnes ne sont pas parcourues et que plein est vrai
        while (j < MAX && plein) {
            if (plateau.getPion(i, j) == X) {
                // Plein devient faux car au moins une case n'est pas remplie d'un pion blanc ou noir
                plein = false;
            }
            j++;
        }
        i++;
    }

    return plein;
}


int Partie::retourner(int pX, int pY, int oX, int oY, Joueur& J, animFonction fonction, bool retournerPions) throw(const char*) {
    if (pX < 0 || pX > MAX || pY < 0 || pY > MAX) throw("Indices plateau incorrects.");

    // Déclaration et initialisation variables
    bool continuer = true;
    int cptPions = 0;

    // On se place sur le pion adjacent où un pion ennemi se trouve
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

    // Et tant qu'on n'a pas touché un bord du plateau ET qu'un pion appartenant au joueur n'a pas été rencontré
    while (i >= 0 && i < MAX && j >=0 && j < MAX && continuer) {
        // On remplace les pions ennemis
        if (plateau.getPion(i, j) == ennemi) {
            // Si on joue réellement
            if (retournerPions) {
                // On met ce pion sur le plateau
                plateau.setPion(i, j, joueur);
                // Puis on lance l'animation dans notre classe Jeu
                fonction(i, j);
            }
            cptPions++;
        } else {
            continuer = false;
        }

        // Et on continue notre parcours en appliquant le vecteur (oX, oY)
        i += oX;
        j += oY;
    }

    if (retournerPions) {
        // On recalcule le score des joueurs
        J1.setScore(calculerScore(J1));
        J2.setScore(calculerScore(J2));
    }

    return cptPions;
}


int Partie::jouer(int positionLigne, int positionColonne, animFonction fonction, bool retournerPions) throw(const char*) {
    if (positionLigne < 0 || positionLigne > MAX || positionColonne < 0 || positionColonne > MAX)
        throw("Indices plateau incorrects.");

    // Ce coup vaudra un point dans tous les cas
    int cptPions = 1;

    // On met la case pointée de la couleur du joueur
    if (retournerPions) plateau.setPion(positionLigne, positionColonne, joueurCourant->getCouleur());

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

    // Si le retournement des pions est activé, c'est qu'on joue réellement, il faut donc passer au joueur suivant
    if (retournerPions) joueurSuivant();

    // Retourne le nombre de pions qui seront retournés après ce coup
    return cptPions;
}


bool Partie::jeuPossible() const {
    // Initialisation variables
    bool possible = false;
    int i = 0;
    int j = 0;

    // On parcourt chaque ligne du tableau tant qu'un coup possible n'a pas été trouvé
    while (i < MAX && !possible) {
        // RAZ du compteur
        j = 0;

        // On parcourt chaque colonne du tableau tant qu'un coup possible n'a pas été trouvé
        while (j < MAX && !possible) {
            // Si un coup est possible sur cette case
            if (testJeu(i, j)) {
                // C'est qu'on peut encore jouer
                possible = true;
            }
            j++;
        }
        i++;
    }

    return possible;
}


void Partie::joueurSuivant(){
    // On inverse le joueur courant
    if (joueurCourant == &J1)
        joueurCourant = &J2;
    else
        joueurCourant = &J1;
}


vector<Coup> Partie::getCoupsPossibles() {
    // Le vector que l'on va retourner
    vector<Coup> resultat;

    // Un coup "tampon" qui servira à remplir le vector
    Coup coup;

    // On vérifie si un coup est possible sur chaque case du jeu
    for (int i=0;i<MAX;i++) {
        for (int j=0;j<MAX;j++) {
            // Si on peut jouer ici
            if (testJeu(i, j)) {
                // On construit notre structure Coup
                coup.X = i;
                coup.Y = j;
                // Et on utilise l'attribut temps pour stocker les points associés à ce coup
                coup.temps = jouer(i, j, [] (int, int) {}, false);
                // On l'envoit dans notre vector
                resultat.push_back(coup);
            }
        }
    }

    // Tri des coups pour obtenir le meilleur coup possible en
    sort(resultat.begin(), resultat.end(), [] (Coup a, Coup b) {
        return a.temps > b.temps;
    });

    return resultat;
}
