/*
    Classe : Interface

    La classe Interface est une classe abstraite servant � d�finir une m�thode simple de gestion des diverses interfaces
    (jeu, menus, bo�tes de dialogues, etc.) du jeu. Elle regroupe, � partir du principe de base de la classe Composant,
    des fonctions suppl�mentaires comme la gestion d'une deuxi�me surface _ecran qui rafraichira l'affichage, un s�quenceur
    et une fonction locale de gestion des �v�nements.

    Programmeur : Edgar Fournival
*/

#ifndef H_INTERFACE
#define H_INTERFACE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Composant.h"
#include "../Sequenceur.h"


// Une structure qui contient des pointeurs vers les fontes n�cessaires au jeu
struct Fontes {
    TTF_Font* fonteMenu;
    TTF_Font* fonteNormal;
    TTF_Font* fonteGras;
};

class Interface : public Composant {
    // Protected = private mais quand m�me utilisables par les classes d�riv�es
    protected:
        // Un pointeur vers la surface d'affichage principale (afin de la rafra�chir)
        SDL_Surface* _ecran;

        // Un pointeur vers le s�quenceur qui s'occupera de g�rer l'affichage de fa�on fluide
        Sequenceur* _sequenceur;

        // Nos fontes d'affichage
        Fontes _fontes;

        // Fonction virtuelle contenant les fonctions de rendu de la classe
        // Renvoit FALSE quand l'interface ne doit plus �tre plus affich�e
        // C'est la fonction r�p�t�e par le s�quenceur
        virtual bool rendre() =0;

        // Si on s'occupe int�gralement de l'affichage, il faut aussi g�rer les �v�nements, c'est obligatoire donc m�thode virtuelle pure
        virtual bool gererEvenementsSDL() =0;

        // On veut quitter le jeu ? Pas de probl�me, le mot-cl� static propagera l'�v�nement de sortie du jeu
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

        // afficher() d�clenche l'affichage, mais ne s'en occupe pas, il faudra absolument d�finir ce membre
        virtual void afficher() =0;

        // Destructeur virtuel afin d'�viter des comportements non d�sir�s
        virtual ~Interface() { delete _sequenceur; };
};

#endif
