#include "Message.h"


Message::Message(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes, const char* titre, const char* contenu):
Interface(rendu, ecran, fontes),
_titre(NULL),
_contenu(NULL),
_bouton(NULL),
_sortir(false) {
    // Rendu du titre du message
    _titre = TTF_RenderText_Solid(_fontes.fonteGras, titre, {0, 0, 0, 255});

    // Le texte
    _contenu = TTF_RenderText_Solid(_fontes.fonteNormal, contenu, {0, 0, 0, 255});

    // Création du bouton Ok
    _bouton = new Bouton(_rendu, _rendu->w/2-25, _rendu->h/2+13, 50, 16, "OK", _fontes.fonteNormal, [&] () {
        _sortir = true;
    });
}

void Message::afficher() {
    // On assombrit
    assombrir(_rendu);

    // Puis on fait cycler le séquenceur sur notre fonction de rendu
    _sequenceur->cycler();
}


bool Message::rendre() {
    // Contour du message
    SDL_Rect posRectangle;
    posRectangle.x = 25;
    posRectangle.y = _rendu->h / 2 - 30;
    posRectangle.w = _rendu->w - 50;
    posRectangle.h = 70;
    SDL_FillRect(_rendu, &posRectangle, SDL_MapRGBA(_rendu->format, 0, 0, 0, 255));

    // Intérieur (en blanc)
    posRectangle.x = 27;
    posRectangle.y = _rendu->h / 2 - 28;
    posRectangle.w = _rendu->w - 54;
    posRectangle.h = 66;
    SDL_FillRect(_rendu, &posRectangle, SDL_MapRGBA(_rendu->format, 255, 255, 255, 255));

    // Positionnement et affichage
    SDL_Rect posTexte;
    posTexte.x = 40;
    posTexte.y = _rendu->h / 2 - 22;
    SDL_BlitSurface(_titre, NULL, _rendu, &posTexte);
    posTexte.y = _rendu->h / 2 - 8;
    SDL_BlitSurface(_contenu, NULL, _rendu, &posTexte);

    // On a pas de menu qui gère les boutons tout seul, on transmet donc la position de la souris pour les effets de survol
    int sourisX, sourisY;
    SDL_GetMouseState(&sourisX, &sourisY);
    _bouton->testSurvol(sourisX/2, sourisY/2);
    _bouton->afficher();

    // On étire notre surface 'preRendu' pour qu'elle fasse la taille de la surface de rendu
    SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

    // On rafraichit notre surface d'affichage principale
    SDL_Flip(_ecran);

    // Gestion des évènements
    return gererEvenementsSDL() && (!_quitter) && (!_sortir);
}


bool Message::gererEvenementsSDL() {
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) {
        if (evenement.type == SDL_QUIT) {
            quitter();
            return false;

        // Si on clique sur le bouton, on ferme le message
        } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
            int sourisX, sourisY;
            bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
            if (_bouton->testSurvol(sourisX/2, sourisY/2) & clic)
                _bouton->cliquer();
        }
    }

    return true;
}


Message::~Message() {
    // Libération mémoire
    SDL_FreeSurface(_titre);
    SDL_FreeSurface(_contenu);

    delete _bouton;
}


void assombrir(SDL_Surface* destination) {
    // On a besoin d'accéder aux pixels lors de l'alpha blending
    // Pour cela, il va falloir déclarer les masques d'accès aux composantes couleurs des pixels
    // L'accès à ces valeurs dépend de la façon (boutisme) dont sont stockée les surfaces en mémoire
    uint32_t rMask, gMask, bMask, aMask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rMask = 0xff000000;
        gMask = 0x00ff0000;
        bMask = 0x0000ff00;
        aMask = 0x000000ff;
    #else
        rMask = 0x000000ff;
        gMask = 0x0000ff00;
        bMask = 0x00ff0000;
        aMask = 0xff000000;
    #endif

    // On initialise la surface avec nos masques
    SDL_Surface* assombrissement = SDL_CreateRGBSurface(SDL_HWSURFACE, 257, 272, 32, rMask, gMask, bMask, aMask);

    // On la remplit avec du gris
    SDL_FillRect(assombrissement, NULL, SDL_MapRGBA(assombrissement->format, 0, 0, 0, 128));

    // On l'affiche sur la surface de destination
    SDL_BlitSurface(assombrissement, NULL, destination, NULL);

    // On vide la mémoire
    SDL_FreeSurface(assombrissement);
}
