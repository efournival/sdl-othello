/*
    Classe : Image

    D�finit une classe simple d'affichage d'image sous forme de surface pr�alablement initialis�e.
    Peut servir pour afficher une image toute simple � l'�cran ou servir de base � d'autres classes plus complexes.

    Programmeur : Edgar Fournival
*/

#ifndef H_IMAGE
#define H_IMAGE

#include <SDL/SDL.h>


class Image {
    protected:
        // Notre classe source qui servira � l'affichage
        SDL_Surface* _surface;

        // Le rectangle d�finissant les coordonn�es de l'image lors de l'affichage
        SDL_Rect _destFrameRect;

    public:
        // Constructeur de la classe (surface source obligatoire, cf. constructeur dans Interface.h)
        Image(SDL_Surface*);

        // Recopie et affectation impossible
        Image (const Image &source);
        Image& operator=(const Image&);

        // On force la lib�ration de la surface associ�e
        void libererSurface();

        // Dessine la surface sur la surface donn�e en param�tre
        // Si on ne sp�cifie pas de coordonn�es X ou Y, les valeurs 0 seront appliqu�es ce qui correspond au coin haut-gauche
        virtual void dessiner(SDL_Surface*, int=0, int=0);

        // Destructeur virtuel afin d'�viter des comportements non d�sir�s
        virtual ~Image() {};
};

#endif
