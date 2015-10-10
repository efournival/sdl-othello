/*
    Classe : Joueur

    Programmeur : Swamynathan Candassamy
*/

#ifndef H_JOUEUR
#define H_JOUEUR

#include <cstring>

#include "Plateau.h"


class Joueur {
    private:
        // Nom du joueur
        char _nom[16];

        // Caractère représentant un pion du joueur
        char _couleur;

        // Score du joueur (nb. de pions)
        int _score;

    public:
        // Constructeur de la classe
        Joueur(char=0, const char* ="");

        // Accesseur et modifieur du caractère représentant le pion
        void setCouleur(char);
        char getCouleur() const;

        // Accesseur et modifieur du nom du joueur
        void setNom(const char*);
        const char* getNom() const;

        // Accesseur et modifieur du score
        void setScore(int);
        int getScore() const;
};

#endif
