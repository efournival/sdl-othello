/*
    Classe : Horloge

    D�finit une classe servant au timing interne des animations et au minutage. Cette classe se base sur la fonction
    SDL_GetTicks qui retourne le nombre de millisecondes �coul�es depuis le lancement de l'application. Gr�ce � la
    classe Horloge, on a d�sormais un timing pr�cis qui peut �tre mis en pause ou acc�l�r�.

    NB : on travaille ici avec des entiers non sign�s sur 4 octets (32 bits) GARANTIS.

    Programmeur : Edgar Fournival
*/

#ifndef H_HORLOGE
#define H_HORLOGE

#include <SDL/SDL.h>


class Horloge {
    private:
        // Temps en millisecondes lors de la mise en pause
        uint32_t _pause;

        // D�calage prennant en compte les pauses pr�c�dentes
        uint32_t _decalage;

        // Si on veut que le temps passe plus rapidement
        int _vitesse;

        // D�calage pour prendre en compte les changements de vitesse
        uint32_t _decalageVitesse;

        // Utilis� pour le calcul du temps acc�l�r�
        uint32_t _changementVitesse;

        // L'horloge est-elle en pause ?
        bool _enPause;

    public:
        // Constructeur de la classe
        Horloge();

        // Met en pause l'horloge
        void pause();

        // Sort du mode pause et calcule le d�calage afin d'avoir un timing correct
        void reprendre();

        // Accesseur de _enPause, retourne VRAI si l'horloge est en pause, FAUX sinon
        bool enPause() const;

        // Retourne le nombre de millisecondes �coul�es depuis le lancement de l'appli
        // mais avec un timing calcul� pour prendre en compte des pauses
        uint32_t temps() const;

        // Change la vitesse interne de l'horloge
        void setVitesse(int);

        // R�cup�re la vitesse interne de l'horloge
        int getVitesse();
};

#endif
