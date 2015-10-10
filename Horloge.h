/*
    Classe : Horloge

    Définit une classe servant au timing interne des animations et au minutage. Cette classe se base sur la fonction
    SDL_GetTicks qui retourne le nombre de millisecondes écoulées depuis le lancement de l'application. Grâce à la
    classe Horloge, on a désormais un timing précis qui peut être mis en pause ou accéléré.

    NB : on travaille ici avec des entiers non signés sur 4 octets (32 bits) GARANTIS.

    Programmeur : Edgar Fournival
*/

#ifndef H_HORLOGE
#define H_HORLOGE

#include <SDL/SDL.h>


class Horloge {
    private:
        // Temps en millisecondes lors de la mise en pause
        uint32_t _pause;

        // Décalage prennant en compte les pauses précédentes
        uint32_t _decalage;

        // Si on veut que le temps passe plus rapidement
        int _vitesse;

        // Décalage pour prendre en compte les changements de vitesse
        uint32_t _decalageVitesse;

        // Utilisé pour le calcul du temps accéléré
        uint32_t _changementVitesse;

        // L'horloge est-elle en pause ?
        bool _enPause;

    public:
        // Constructeur de la classe
        Horloge();

        // Met en pause l'horloge
        void pause();

        // Sort du mode pause et calcule le décalage afin d'avoir un timing correct
        void reprendre();

        // Accesseur de _enPause, retourne VRAI si l'horloge est en pause, FAUX sinon
        bool enPause() const;

        // Retourne le nombre de millisecondes écoulées depuis le lancement de l'appli
        // mais avec un timing calculé pour prendre en compte des pauses
        uint32_t temps() const;

        // Change la vitesse interne de l'horloge
        void setVitesse(int);

        // Récupère la vitesse interne de l'horloge
        int getVitesse();
};

#endif
