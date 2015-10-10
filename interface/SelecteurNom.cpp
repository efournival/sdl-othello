#include "SelecteurNom.h"


SelecteurNom::SelecteurNom(SDL_Surface* rendu, int x, int y, const char* texte, TTF_Font* fonte):
Composant(rendu),
_fonte(fonte),
_texte(),
_champ(NULL),
_x(x),
_y(y),
_focus(false),
_horloge() {
    // On veut une cha�ne vide
    _nomJoueur[0] = '\0';

    // On initialise notre surface contenant le texte devant le champ
    _texte = TTF_RenderText_Solid(_fonte, texte, {0, 0, 0, 0});
}


void SelecteurNom::afficher() {
    // Les coordonn�es d'affichage du rectangle repr�sentant la zone de texte
    SDL_Rect champTexte;
    champTexte.x = _x + 75;
    champTexte.y = _y;
    champTexte.w = 120;
    champTexte.h = 17;

    // On remplit avec du noir afin d'avoir le contour du rectangle
    SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 0, 0, 0, 255));

    // Puis on se d�cale de un pixel sur chaque c�t� vers l'int�rieur du rectangle
    champTexte.x = _x + 76;
    champTexte.y = _y + 1;
    champTexte.w = 118;
    champTexte.h = 15;

    // On remplit avec du vert pour avoir juste le contour
    SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 0, 80, 14, 255));

    // Position du texte � c�t� du rectangle
    SDL_Rect posTexte;
    posTexte.x = _x;
    posTexte.y = _y + 2;

    // On affiche
    SDL_BlitSurface(_texte, NULL, _rendu, &posTexte);

    // On affiche le nom du joueur si la surface a d�j� �t� allou�e
    if (_champ) {
        // Position du texte repr�sentant le nom du joueur
        posTexte.x = _x + 191 - _champ->w;
        // Affichage
        SDL_BlitSurface(_champ, NULL, _rendu, &posTexte);
    }

    // Si le composant a le focus
    if (_focus) {
        // On se place � la fin du rectangle
        champTexte.x = _x + 95 + 96;
        champTexte.y = _y + 3;
        champTexte.w = 2;
        champTexte.h = 11;

        // Clignotement toutes les 500 ms
        if (_horloge.temps()-((int) _horloge.temps()/1000)*1000 > 500)
            // Et on remplit de noir afin d'afficher un curseur
            SDL_FillRect(_rendu, &champTexte, SDL_MapRGBA(_rendu->format, 255, 255, 255, 255));
    }
}


void SelecteurNom::souris(int x, int y, bool clic) {
    // Si le clic se trouve aux environs de notre composant, on active le focus
    if (clic && x >= _x && y >= _y && x <= _x+195 && y <= _y+18)
        _focus = true;
    // Sinon, si le clic n'est pas dans la zone, on d�sactive le focus
    else if (clic)
        _focus = false;
    // NB : le focus ne s'active/d�sactive qu'au clic
}


void SelecteurNom::clavier(SDL_keysym keysym) {
    // On s'assure d'abord d'avoir le focus
    if (_focus) {
        // On r�cup�re la taille de notre cha�ne contenant le nom du joueur
        unsigned int taille = strlen(_nomJoueur);

        // Si on veut effacer le dernier caract�re
        if (keysym.sym == SDLK_BACKSPACE) {
            // On s'assure que la cha�ne n'est pas vide puis on remplace le dernier caract�re par le symb�le de fin de cha�ne
            if (taille > 0) _nomJoueur[taille-1] = 0;

        // Ensuite on v�rifie qu'on peut r�cup�rer le caract�re ASCII du caract�re Unicode retourn� par SDL
        // En effet, la pression d'une touche sp�ciale ne renverra pas de code ASCII et l'�v�nement clavier pourra �tre ignor�
        } else if ((keysym.unicode & 0xFF80) == 0) {
            // On r�cup�re ce caract�re ASCII
            char caractere = keysym.unicode & 0x7F;
            // Puis, si la surface repr�sentant cette cha�ne n'est pas nulle, on r�cup�re sa largeur
            int largeurSurface = _champ ? _champ->w : 0;
            // On v�rifie ensuite qu'on ne d�passe pas le tableau de char ET qu'on ne d�passe pas du champ de texte
            if (taille < sizeof(_nomJoueur)-1 && largeurSurface < 108) {
                // On met le caract�re tap� � la fin du tableau de char
                _nomJoueur[taille] = caractere;
                // Sans oublier le '\0' terminal car il s'agit d'une cha�ne
                _nomJoueur[taille+1] = '\0';
            }
        }

        // Pour �viter les fuites m�moire, on lib�re la surface si elle a d�j� �t� allou�e
        if (_champ) SDL_FreeSurface(_champ);
        // Et on l'a re-alloue avec notre nouvelle surface repr�sentant la cha�ne du nom du joueur
        _champ = TTF_RenderText_Solid(_fonte, _nomJoueur, {255, 255, 255, 255});
    }
}


void SelecteurNom::setNom(const char* nomJoueur) {
    strcpy(_nomJoueur, nomJoueur);
    if (_champ) SDL_FreeSurface(_champ);
    _champ = TTF_RenderText_Solid(_fonte, _nomJoueur, {255, 255, 255, 255});
}


SelecteurNom::~SelecteurNom() {
    // On lib�re la surface si elle a d�j� �t� allou�e
    if (_champ) SDL_FreeSurface(_champ);
    SDL_FreeSurface(_texte);
}
