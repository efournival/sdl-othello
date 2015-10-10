/*
    Classe : Séquenceur

    Implémente une classe servant à la répétition du rendu d'une interface.
    On donne une fréquence en Hertz à atteindre et le séquenceur s'occupera de répéter
    une fonction donnée à cette fréquence.

    Programmeur : Edgar Fournival
*/


#ifndef H_SEQUENCEUR
#define H_SEQUENCEUR

#include <SDL/SDL.h>


// Résout la dépendance circulaire
class Interface;

// Le type de fonction à répéter, doit retourner FALSE pour arreter la répétition, TRUE pour continuer
typedef bool(Interface::*seqCallback)();

class Sequenceur {
    private:
        // Le nombre de millisecondes à attendre entre chaque répétition
        unsigned int _delai;

        // Fonction à répéter
        seqCallback _callback;

        // Instance de la classe parent du sequenceur
        Interface* _parent;

    public:
        // Constructeur de la classe
        Sequenceur(seqCallback, Interface*, int=60);

        // Répétition, rend la main lorsque la fonction à répéter renvoie FALSE
        void cycler();
};

#endif
