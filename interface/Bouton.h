/*
    Classe : Bouton

    Définit une classe regroupant les fonctions d'affichage et d'interaction d'un composant de type bouton.
    Les évènements tels que les clics sont à la charge de la classe mère.

    Programmeur : Edgar Fournival
*/

#ifndef H_BOUTON
#define H_BOUTON

#include <functional>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Composant.h"


typedef std::function<void()>(actionClic);

class Bouton : public Composant {
    private:
        // La position (coordonnées X et Y) du bouton
        SDL_Rect _position;

        // Les surfaces représentant le bouton à l'état normal, survolé par la souris, et désactivé si besoin
        SDL_Surface* _sNormal;
        SDL_Surface* _sSurvol;
        SDL_Surface* _sDesactive;

        // Est-ce que notre bouton est actuellement survolé ?
        bool _survol;

        // Est-il désactivé ?
        bool _desactive;

        actionClic _action;

    public:
        // Constructeur de la classe
        Bouton(SDL_Surface*, int, int, int, int, const char*, TTF_Font*, actionClic);

        // Recopie et affectation impossible
        Bouton(const Bouton &source);
        Bouton& operator=(const Bouton&);

        // Toujours notre fonction d'affichage dont l'implémentation est obligatoire
        void afficher();

        // Renvoie TRUE si le bouton est actuellement survolé
        bool testSurvol(int, int);

        // Lance l'action associée au bouton
        void cliquer();

        // Activation et désactivation
        void activer();
        void desactiver();

        // Destructeur (libération mémoire)
        ~Bouton();
};


#endif
