/*
    Classe : Plateau

    Programmeur : Jean-Pierre Mohamed

*/

#ifndef H_PLATEAU
#define H_PLATEAU


// Nombre de lignes et de colonnes max.
const int MAX = 8;

// Pion blanc
const char B = 2;

// Pion noir
const char N = 1;

// Case vide
const char X = '.';


class Plateau {
    private:
        // Notre tableau représentant le plateau de jeu
        char _pions[MAX][MAX] = {{X,X,X,X,X,X,X,X},
                                 {X,X,X,X,X,X,X,X},
                                 {X,X,X,X,X,X,X,X},
                                 {X,X,X,B,N,X,X,X},
                                 {X,X,X,N,B,X,X,X},
                                 {X,X,X,X,X,X,X,X},
                                 {X,X,X,X,X,X,X,X},
                                 {X,X,X,X,X,X,X,X}};

    public:
        // Accesseur et modifieur d'un pion dans le plateau
        char getPion(int, int) const throw(const char*);
        void setPion(int, int, char) throw(const char*);
};

#endif
