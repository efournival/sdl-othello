#include "Menu.h"


Menu::Menu(SDL_Surface* rendu, int pX, int pY, Fontes fontes, bool horizontal, int largeur, int hauteur):
Composant(rendu),
_fontes(fontes),
_nbBoutons(0),
_x(pX),
_y(pY),
_largeur(largeur),
_hauteur(hauteur),
_horizontal(horizontal) {
    // On remplit notre tableau de boutons avec la valeur NULL
    for (int i=0;i<MAX_BOUTONS;i++) {
        _boutons[i] = NULL;
    }
}


void Menu::souris(int pX, int pY, bool clicGauche) {
    // Pour chaque bouton
    for (int i=0;i<_nbBoutons;i++) {
        // Si :
        //  - le bouton existe (il a été dynamiquement alloué)
        //  - il est survolé par la souris
        //  - le bouton gauche de la souris est actuellement pressé
        if (_boutons[i] != NULL && _boutons[i]->testSurvol(pX, pY) && clicGauche) {
            // On lance l'action associée au bouton
            _boutons[i]->cliquer();
            // On sort de la boucle for car un seul bouton ne peut être cliqué
            break;
        }
    }
}


void Menu::afficher() {
    // Pour chaque bouton
    for (int i=0;i<_nbBoutons;i++) {
        // Si il a été alloué
        if (_boutons[i] != NULL) {
            // On l'affiche
            _boutons[i]->afficher();
        }
    }
}


void Menu::ajouterBouton(const char* texte, actionClic action) {
    // On l'ajoute à notre tableau de bouton en l'allouant dynamiquement
    if (_horizontal)
        _boutons[_nbBoutons] = new Bouton(_rendu,
                                          _x+(_nbBoutons%9)*(_largeur*1.25),
                                          _y+((int)_nbBoutons/9)*(_hauteur*1.25),
                                          _largeur, _hauteur, texte, _fontes.fonteMenu, action);
    else
        _boutons[_nbBoutons] = new Bouton(_rendu, _x, _y+_nbBoutons*(_hauteur*1.25), _largeur,
                                          _hauteur, texte, _fontes.fonteMenu, action);

    // On augmente le nombre de boutons total
    _nbBoutons++;
}


void Menu::ajouterEspace() {
    // On augmente le nombre de boutons total sans en allouer un, ce qui affichera un espace vide car la boucle d'affichage du menu
    // ne prend pas en compte les boutons 'NULL'
    _nbBoutons++;
}


void Menu::activerBouton(int index) {
    _boutons[index]->activer();
}


void Menu::desactiverBouton(int index) {
    _boutons[index]->desactiver();
}


Menu::~Menu() {
    // On supprime chaque bouton précédement alloué
    for (int i=0;i<_nbBoutons;i++) {
        if (_boutons[i] != NULL) {
            delete _boutons[i];
        }
    }
}
