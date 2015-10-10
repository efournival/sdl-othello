/*
    Classe : S�quenceur

    Impl�mente une classe servant � la r�p�tition du rendu d'une interface.
    On donne une fr�quence en Hertz � atteindre et le s�quenceur s'occupera de r�p�ter
    une fonction donn�e � cette fr�quence.

    Programmeur : Edgar Fournival
*/


#ifndef H_SEQUENCEUR
#define H_SEQUENCEUR

#include <SDL/SDL.h>


// R�sout la d�pendance circulaire
class Interface;

// Le type de fonction � r�p�ter, doit retourner FALSE pour arreter la r�p�tition, TRUE pour continuer
typedef bool(Interface::*seqCallback)();

class Sequenceur {
    private:
        // Le nombre de millisecondes � attendre entre chaque r�p�tition
        unsigned int _delai;

        // Fonction � r�p�ter
        seqCallback _callback;

        // Instance de la classe parent du sequenceur
        Interface* _parent;

    public:
        // Constructeur de la classe
        Sequenceur(seqCallback, Interface*, int=60);

        // R�p�tition, rend la main lorsque la fonction � r�p�ter renvoie FALSE
        void cycler();
};

#endif
