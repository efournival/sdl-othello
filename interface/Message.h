/*
    Classe : Message

    Définit une interface autonome destinée à afficher à message.
    L'interface disparait et est libérée dès que le bouton 'OK' est pressé.

    Programmeur : Edgar Fournival
*/

#ifndef H_MESSAGE
#define H_MESSAGE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Interface.h"
#include "Bouton.h"


class Message : public Interface {
    private:
        // Surfaces de stockage des textes
        SDL_Surface* _titre;
        SDL_Surface* _contenu;

        // Le bouton 'OK'
        Bouton* _bouton;

        // Interrompt le rendu via le clic du bouton
        bool _sortir;

        // Rendu
        bool rendre();

        // Gestion indépendante des évènements SDL
        bool gererEvenementsSDL();

    public:
        // Constructeur de la classe
        Message(SDL_Surface*, SDL_Surface*, Fontes, const char*, const char*);

        // Affichage
        void afficher();

        // Recopie et affectation impossible
        Message(const Message &source);
        Message& operator=(const Message&);

        // Destructeur
        ~Message();
};

// Permet d'assombrir une surface pour un effet 'modal'
void assombrir(SDL_Surface*);

#endif
