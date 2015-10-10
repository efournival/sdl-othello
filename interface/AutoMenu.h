/*
    Classe : AutoMenu

    Cette classe permet de dessiner un menu autonome directement � l'ex�cution : l'interface est enti�rement g�r�e, le menu et ses
    interactions sont �galement prises en compte et gr�ce aux fonctions lambdas on peut associer facilement une action � chaque bouton
    du menu.

    Programmeur : Edgar Fournival
*/

#ifndef H_AUTOMENU
#define H_AUTOMENU

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "../affichage/Image.h"

#include "../interface/Interface.h"
#include "../interface/Menu.h"

using namespace std;


class AutoMenu : public Interface {
    protected:
        // Rendu
        virtual bool rendre();

        // Gestion ind�pendante des �v�nements SDL
        virtual bool gererEvenementsSDL();

    private:
        Image* _fond;

        // Veut-on quitter le menu ?
        bool _quitterMenu;

    public:
        // Pointeur vers la classe g�rant le menu
        Menu* menu;

        // Constructeur de la classe
        AutoMenu(SDL_Surface*, SDL_Surface*, Fontes, const char* =NULL, bool=false, int=150, int=16);

        // Recopie et affectation impossible
        AutoMenu(const AutoMenu &source);
        AutoMenu& operator=(const AutoMenu&);

        // Affichage
        void afficher();

        // Pour quitter le menu
        void quitterMenu();

        // Destructeur (lib�ration m�moire)
        ~AutoMenu();
};

#endif
