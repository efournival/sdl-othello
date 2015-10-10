#ifndef H_MENUJOUER
#define H_MENUJOUER

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <ctime>

#include "../fichiers/Configuration.h"

#include "AutoMenu.h"
#include "SelecteurNom.h"

#include "../Jeu.h"


class MenuJouer : public AutoMenu {
    private:
        // On va gérer notre propre image de fond afin de pouvoir utiliser AutoMenu::rendre() après nos fonctions d'affichage locales
        Image* _fond;

        // Surfaces contenant nos deux lignes de texte
        SDL_Surface* _texte1;
        SDL_Surface* _texte2;

        // FAUX : 2 joueurs humains, VRAI : joueur humain vs ordinateur
        bool _typePartie;

        // Les composants sélecteurs permettant de saisir les noms des joueurs
        SelecteurNom* _selecteurJ1;
        SelecteurNom* _selecteurJ2;

        // Gestion indépendante des évènements SDL
        bool gererEvenementsSDL();

        // Rendu
        bool rendre();

        // Sauvegarde du nom des joueurs dans le fichier de config
        void sauvegarderNomsJoueurs();

        // Lance une partie
        void jouer();

    public:
        // Indique si on doit revenir au menu principal après une partie
        bool razMenu;

        // Constructeur de la classe
        MenuJouer(SDL_Surface*, SDL_Surface*, Fontes, bool);

        // Recopie et affectation impossible
        MenuJouer(const MenuJouer &source);
        MenuJouer& operator=(const MenuJouer&);

        // Destructeur
        ~MenuJouer();
};

#endif
