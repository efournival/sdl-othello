/*
    Classe : Composant

    La classe Composant est une classe abstraite d�finissant une mani�re simple et efficace d'ajout de composant dans le jeu.
    Un composant est un objet r�alisant un rendu, qui doit �tre initialis�, affich� puis d�truit. Il fournit une classe de base
    pour des structures plus complexes comme Interface.

    Programmeur : Edgar Fournival
*/

#ifndef H_COMPOSANT
#define H_COMPOSANT

#include <SDL/SDL.h>


class Composant {
    // Protected = private mais quand m�me utilisables par les classes d�riv�es
    protected:
        // Le pointeur vers la surface utilis�e pour le rendu du composant
        SDL_Surface* _rendu;

    public:
        // Constructeur de la classe
        // NB : la plupart des classes (d�riv�es ou non d'Interface) du jeu ont besoin d'au moins un param�tre obligatoire
        // qui est la surface utilis�e pour le rendu, il est impossible de d�finir un constructeur vide qui assignerait
        // NULL � _rendu car un appel au constructeur vide ou � la m�thode afficher() se solderait par une erreur de segmentation
        // dans le meilleur des cas (la documentation indique 'comportement inconnu')
        Composant(SDL_Surface* rendu):
        _rendu(rendu) {};

        // Recopie et affectation impossible
        Composant(const Composant &source);
        Composant& operator=(const Composant&);

        // Proc�dure virtuelle pure (=> classe abstraite, impl�mentation obligatoire), d�marre l'affichage du composant
        virtual void afficher() =0;

        // Destructeur virtuel afin d'�viter des comportements non d�sir�s
        virtual ~Composant() {};
};

#endif

