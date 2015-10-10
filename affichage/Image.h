/*
    Classe : Image

    Définit une classe simple d'affichage d'image sous forme de surface préalablement initialisée.
    Peut servir pour afficher une image toute simple à l'écran ou servir de base à d'autres classes plus complexes.

    Programmeur : Edgar Fournival
*/

#ifndef H_IMAGE
#define H_IMAGE

#include <SDL/SDL.h>


class Image {
    protected:
        // Notre classe source qui servira à l'affichage
        SDL_Surface* _surface;

        // Le rectangle définissant les coordonnées de l'image lors de l'affichage
        SDL_Rect _destFrameRect;

    public:
        // Constructeur de la classe (surface source obligatoire, cf. constructeur dans Interface.h)
        Image(SDL_Surface*);

        // Recopie et affectation impossible
        Image (const Image &source);
        Image& operator=(const Image&);

        // On force la libération de la surface associée
        void libererSurface();

        // Dessine la surface sur la surface donnée en paramètre
        // Si on ne spécifie pas de coordonnées X ou Y, les valeurs 0 seront appliquées ce qui correspond au coin haut-gauche
        virtual void dessiner(SDL_Surface*, int=0, int=0);

        // Destructeur virtuel afin d'éviter des comportements non désirés
        virtual ~Image() {};
};

#endif
