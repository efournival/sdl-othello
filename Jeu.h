/*
    Classe : Jeu

    Singleton gérant l'interface du jeu en lui-même.

    Toute l'équipe vous souhaite un bon courage pour bien comprendre l'intégralité de cette classe.

    Nous espérons néanmoins que vous passerez de bonnes fêtes de fin d'année.
    O:)

    Programmeur : Edgar Fournival

*/

#ifndef H_JEU
#define H_JEU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "interface/Interface.h"
#include "interface/AutoMenu.h"
#include "interface/Message.h"

#include "affichage/Image.h"
#include "affichage/Tuile.h"
#include "affichage/Sprite.h"

#include "jeu/Partie.h"
#include "fichiers/Replay.h"

#include <cstring>


class Jeu : public Interface {
    private:
        // L'horloge qui gérera les animations et autres timing
        Horloge _horloge;

        // Les surfaces et instances d'objets d'affichage utilisés par les procédures de rendu
        SDL_Surface* _pions;
        Image* _imgPlateau;
        Image* _imgVue_Plateau;
        Tuile* _tilPions;
        Tuile* _tilAidePions;
        Tuile* _tilReplay;

        // Surfaces et positions utilisées lors de l'affichage des scores
        SDL_Surface* _sNomJoueur1;
        SDL_Rect _posNomJoueur1;
        SDL_Surface* _sNomJoueur2;
        SDL_Rect _posNomJoueur2;
        SDL_Surface* _sScore;
        SDL_Rect _posScore;

        // Un tableau contenant les éventuelles sprites affichées
        Sprite* _animations[MAX][MAX];

        // Un pointeur vers la classe gérant le système de replay
        Replay* _replay;
        // Un deck (vector bi-directionnel) contenant les coups à jouer
        deque<Coup> _coupsReplay;

        // La liste des coups possibles afin de les afficher
        vector<Coup> _coupsPossibles;

        // Permet de décaler dans le temps le message de fin de partie afin de terminer toutes les animations
        uint32_t _finPartie;
        // Un tableau de char contenant la raison de la fin de partie (plateau plein ou jeu bloqué)
        char _raisonFinPartie[20];

        uint32_t _coupIA;

        // Veut-on retourner au menu principal ?
        bool _retourMenu;

        // Procédure de chargement des images du jeu
        void chargerImages();
        // On libère les images de la mémoire à la fin
        void libererImages();

        // Place un pion sur le plateau
        void placerPion(int, int);

        void jouerIA();

        // Affiche un message avec la raison de fin de partie ainsi que les scores
        void finPartie(const char*);

        // Met en pause la partie
        void pause();

        // Fonctions de rendu locales
        void majScores();
        void dessinerPions();
        void dessinerPionsCoupsPossibles();

        // Rendu
        bool rendre();
        // Gestion des évènements (interaction utilisateur)
        bool gererEvenementsSDL();

    public:
        // Notre classe partie, en public afin que le MenuJouer y ai accès
        Partie partie;

        // Définit si le joueur joue contre l'IA ou pas, modifié par MenuJouer
        bool vsIA;

        // Lance la lecture d'un replay (à appeller avant afficher())
        void lireReplay(const char* nomFichier) throw(const char*);

        // Constructeur de la classe Jeu
        Jeu(SDL_Surface*, SDL_Surface*, Fontes fontes);

        // Recopie et affectation impossible (singleton)
        Jeu(const Jeu &source);
        Jeu& operator=(const Jeu&);

        // Affichage de l'interface
        void afficher();

        // Destructeur (libération mémoire)
        ~Jeu();
};

#endif
