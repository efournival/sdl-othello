/*
    Classe : SelecteurNom

    Implémente un composant permettant au joueur de rentrer son nom dans un champ de texte grâce au clavier.

    Programmeur : Edgar Fournival
*/


#ifndef H_SELECTEURNOM
#define H_SELECTEURNOM

#include <cstring>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../Horloge.h"
#include "Composant.h"


class SelecteurNom : public Composant {
    private:
        // Fonte d'affichage des textes
        TTF_Font* _fonte;

        // Surface contenant le texte devant le champ
        SDL_Surface* _texte;

        // Surface contenant le texte du champ
        SDL_Surface* _champ;

        // Coordonnées d'affichage du composant
        int _x;
        int _y;

        // Nom du joueur
        char _nomJoueur[16];

        // Détermine si le composant a le focus ou pas (est-il sélectionné par l'utilisateur pour entrée clavier ?)
        bool _focus;

        // Une horloge locale afin de gérer le clignotement du curseur
        Horloge _horloge;

    public:
        // Constructeur de la classe
        SelecteurNom(SDL_Surface*, int, int, const char*, TTF_Font*);

        // Recopie et affectation impossible
        SelecteurNom(const SelecteurNom &source);
        SelecteurNom& operator=(const SelecteurNom&);

        // Affichage du composant
        void afficher();

        // Afin de gérer le focus
        void souris(int, int, bool);

        // À appeler dès qu'un évènement clavier est détecté par l'interface mère
        void clavier(SDL_keysym);

        // Retourne le nom du joueur
        char* getNom() { return _nomJoueur; }

        // Définit le nom du joueur
        void setNom(const char*);

        // Le composant a-t-il le focus ?
        bool getFocus() { return _focus; }

        // Force le focus sur le composant
        void setFocus(bool focus) { _focus = focus; }

        // Destructeur (libération mémoire)
        ~SelecteurNom();
};

#endif
