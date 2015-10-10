/*
    Classe : Interface

    La classe Interface est une classe abstraite servant à définir une méthode simple de gestion des diverses interfaces
    (jeu, menus, boîtes de dialogues, etc.) du jeu. Elle regroupe, à partir du principe de base de la classe Composant,
    des fonctions supplémentaires comme la gestion d'une deuxième surface _ecran qui rafraichira l'affichage, un séquenceur
    et une fonction locale de gestion des évènements.

    Programmeur : Edgar Fournival
*/

#ifndef H_INTERFACE
#define H_INTERFACE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Composant.h"
#include "../Sequenceur.h"


// Une structure qui contient des pointeurs vers les fontes nécessaires au jeu
struct Fontes {
    TTF_Font* fonteMenu;
    TTF_Font* fonteNormal;
    TTF_Font* fonteGras;
};

class Interface : public Composant {
    // Protected = private mais quand même utilisables par les classes dérivées
    protected:
        // Un pointeur vers la surface d'affichage principale (afin de la rafraîchir)
        SDL_Surface* _ecran;

        // Un pointeur vers le séquenceur qui s'occupera de gérer l'affichage de façon fluide
        Sequenceur* _sequenceur;

        // Nos fontes d'affichage
        Fontes _fontes;

        // Fonction virtuelle contenant les fonctions de rendu de la classe
        // Renvoit FALSE quand l'interface ne doit plus être plus affichée
        // C'est la fonction répétée par le séquenceur
        virtual bool rendre() =0;

        // Si on s'occupe intégralement de l'affichage, il faut aussi gérer les évènements, c'est obligatoire donc méthode virtuelle pure
        virtual bool gererEvenementsSDL() =0;

        // On veut quitter le jeu ? Pas de problème, le mot-clé static propagera l'évènement de sortie du jeu
        static bool _quitter;

        // Modifieur du membre _quitter
        void quitter() { _quitter = true; }

    public:
        // Constructeur de la classe
        Interface(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes):
        Composant(rendu),
        _ecran(ecran),
        _sequenceur(new Sequenceur(&Interface::rendre, this)),
        _fontes(fontes) {};

        // Recopie et affectation impossible
        Interface(const Interface &source);
        Interface& operator=(const Interface&);

        // afficher() déclenche l'affichage, mais ne s'en occupe pas, il faudra absolument définir ce membre
        virtual void afficher() =0;

        // Destructeur virtuel afin d'éviter des comportements non désirés
        virtual ~Interface() { delete _sequenceur; };
};

#endif
