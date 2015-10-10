/*
    Classe : Sprite

    Affiche un sprite (animation � partir d'un tileset) qui est une classe d�riv�e de Tuile mais avec des fonctions de timing afin
    d'animer notre image de mani�re fluide.

    Programmeur : Edgar Fournival
*/

#ifndef H_SPRITE
#define H_SPRITE

#include <SDL/SDL.h>

#include "Tuile.h"

#include "../Horloge.h"


class Sprite : public Tuile {
    private:
        // D�lai en ms entre deux frames
        unsigned int _delaiFrames;

        // La frame en cours
        unsigned int _frame;

        // Le temps au d�but de l'animation
        uint32_t _debut;

        // Un pointeur vers l'horloge du jeu
        Horloge* _horloge;

        // L'animation doit-elle �tre invers�e ?
        bool _inverse;

    public:
        // Constructeur de la classe
        Sprite(SDL_Surface*, Horloge*, int=0, int=1, bool=false);

        // Recopie et affectation impossible
        Sprite (const Sprite &source);
        Sprite& operator=(const Sprite&);

        // Retourne TRUE si l'animation est termin�e, FALSE sinon
        bool animFinie() const;

        // On affiche
        void dessiner(SDL_Surface*, int=0, int=0);
};


#endif
