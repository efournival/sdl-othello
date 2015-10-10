/*
    Classe : Partie

    Etend les fonctions de la classe Jeu, correspond aux fonctions de la partie 1.
    Cette classe existe afin de bien s�parer la grosse classe d'interfa�age et les fonctions du jeu en elles-m�mes.

    Programmeurs : Jean-Pierre Mohamed et Swamynathan Candassamy
*/

#ifndef H_PARTIE
#define H_PARTIE

#include <algorithm>
#include <functional>
#include <vector>

#include "Joueur.h"
#include "Plateau.h"
#include "../fichiers/Replay.h"


// Le type de fonction lambda requit par retourner() afin de lancer les animations de retournement de pions
typedef std::function<void(int, int)>(animFonction);

class Partie {
    private:
        // V�rifie si la direction contient au moins un pion ennemi
        bool testDirection(int, int, int, int, Joueur&) const throw(const char*);

        // Calcule le score d'un joueur
        int calculerScore(Joueur&) const;

    public:
        // Un pointeur vers le joueur courant
        Joueur* joueurCourant;

        // Les deux joueurs
        Joueur J1, J2;

        // Notre plateau de jeu
        Plateau plateau;

        // Constructeur de la classe
        Partie();

        // Retourne les pions dans la direction indiqu�e
        int retourner(int, int, int, int, Joueur&, animFonction, bool=true) throw(const char*);

        // Teste si il est possible de jouer aux coordonn�es indiqu�es
        bool testJeu(int, int) const throw(const char*);

        // Joue un coup en retournant les pions � partir d'une position donn�e
        int jouer(int, int, animFonction, bool=true) throw(const char*);

        // V�rifie qu'il est possible de jouer (qu'au moins un coup soit possible sur le plateau)
        bool jeuPossible() const;

        // V�rifie si le jeu est plein
        bool jeuPlein() const;

        // Le joueur courant sera d�sormais l'autre joueur
        void joueurSuivant();

        vector<Coup> getCoupsPossibles();
};

#endif
