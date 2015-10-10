/*
    Classe : Composant

    La classe Composant est une classe abstraite définissant une manière simple et efficace d'ajout de composant dans le jeu.
    Un composant est un objet réalisant un rendu, qui doit être initialisé, affiché puis détruit. Il fournit une classe de base
    pour des structures plus complexes comme Interface.

    Programmeur : Edgar Fournival
*/

#ifndef H_COMPOSANT
#define H_COMPOSANT

#include <SDL/SDL.h>


class Composant {
    // Protected = private mais quand même utilisables par les classes dérivées
    protected:
        // Le pointeur vers la surface utilisée pour le rendu du composant
        SDL_Surface* _rendu;

    public:
        // Constructeur de la classe
        // NB : la plupart des classes (dérivées ou non d'Interface) du jeu ont besoin d'au moins un paramètre obligatoire
        // qui est la surface utilisée pour le rendu, il est impossible de définir un constructeur vide qui assignerait
        // NULL à _rendu car un appel au constructeur vide ou à la méthode afficher() se solderait par une erreur de segmentation
        // dans le meilleur des cas (la documentation indique 'comportement inconnu')
        Composant(SDL_Surface* rendu):
        _rendu(rendu) {};

        // Recopie et affectation impossible
        Composant(const Composant &source);
        Composant& operator=(const Composant&);

        // Procédure virtuelle pure (=> classe abstraite, implémentation obligatoire), démarre l'affichage du composant
        virtual void afficher() =0;

        // Destructeur virtuel afin d'éviter des comportements non désirés
        virtual ~Composant() {};
};

#endif

