/*
    Classe : Menu

    La classe Menu gère un tableau de boutons, gère leur affichage en fonction de la souris et renvoie le choix de l'utilisateur
    dès qu'un clic se produit sur un bouton ou que l'on veut quitter le jeu.
    Permet de customiser le menu à l'exécution.

    Programmeur : Edgar Fournival
*/

#ifndef H_MENU
#define H_MENU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "Composant.h"
#include "Interface.h"
#include "Bouton.h"


// Nombre de boutons maximal dans un menu
// NB : on n'utilise ici un simple tableau de pointeurs au lieu d'un std::vector pour des raisons d'optimisation
// NB : s'assurer avant de compiler qu'on ne met pas plus de 8 boutons dans notre menu, aucune exception ne sera levée
const int MAX_BOUTONS = 8;

class Menu : public Composant {
    private:
        // On a besoin d'écrire du texte dans nos boutons donc il faut une fontes
        Fontes _fontes;

        // Tableau de pointeurs vers notre classe Bouton de taille MAX_BOUTONS
        Bouton* _boutons[MAX_BOUTONS];

        // Nombre de boutons affichés
        // NB : certains boutons peuvent être déclarés comme NULL; dans ce cas, un espace sera affiché
        int _nbBoutons;

        // Position horizontale du menu
        int _x;

        // Position verticale du menu
        int _y;

        // Largeur des boutons du menu
        int _largeur;

        // Hauteur des boutons
        int _hauteur;

        // S'agit-il d'un menu horizontal ? (boutons de gauche à droite ou de haut en bas)
        bool _horizontal;

    public:
        // Constructeur de la classe
        Menu(SDL_Surface*, int, int, Fontes, bool=false, int=150, int=16);

        // Recopie et affectation impossible
        Menu(const Menu &source);
        Menu& operator=(const Menu&);

        // Affichage du menu
        void afficher();

        // Interaction souris
        void souris(int, int, bool);

        // Ajout d'un bouton
        void ajouterBouton(const char*, actionClic);

        // Ajout d'un espace (de la taille d'un bouton afin de séparer deux parties dans le menu par exemple)
        void ajouterEspace();

        // Activation et désactivation de boutons via leur index
        void activerBouton(int);
        void desactiverBouton(int);

        // Destructeur de la classe
        ~Menu();
};

#endif
