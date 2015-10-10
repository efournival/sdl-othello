#include "MenuJouer.h"


MenuJouer::MenuJouer(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes, bool typePartie):
AutoMenu(rendu, ecran, fontes, NULL, true, 80),
_fond(NULL),
_texte1(NULL),
_texte2(NULL),
_typePartie(typePartie),
_selecteurJ1(NULL),
_selecteurJ2(NULL),
razMenu(false) {
    // On cr�� une image de fond
    _fond = new Image(SDL_LoadBMP("ressources/images/sous_menu.bmp"));

    // On ajoute nos deux boutons en bas de l'interface
    menu->ajouterBouton("Annuler", [&] () {
        quitterMenu();
    });

    menu->ajouterBouton("Jouer !", [&] () {
        jouer();
        razMenu = true;
        quitterMenu();
    });

    // On cr�� 2 selecteurs de nom
    _selecteurJ1 = new SelecteurNom(_rendu, 30, 80, "Joueur 1 :", _fontes.fonteMenu);
    _selecteurJ2 = new SelecteurNom(_rendu, 30, 110, "Joueur 2 :", _fontes.fonteMenu);

    // On ouvre notre fichier de configuration et on lit les infos
    Configuration configuration;
    Config config = configuration.lireConfig();

    // On r�cup�re le nom du joueur 1 depuis le fichier de config
    _selecteurJ1->setNom(config.nomJoueur1);
    // Et si la partie est jou�e � deux joueurs humains, on r�cup�re aussi le nom du joueur 2
    if (!_typePartie) _selecteurJ2->setNom(config.nomJoueur2);
    // Si c'est une partie contre l'IA, on d�finit le nom du deuxi�me joueur comme �tant un "Ordinateur"
    if (_typePartie) _selecteurJ2->setNom("Ordinateur");

    // On effectue le rendu de nos deux lignes de texte en haut de l'interface
    _texte1 = TTF_RenderText_Solid(_fontes.fonteMenu, "Veuillez entrer le nom des", {0, 0, 0, 0});
    _texte2 = TTF_RenderText_Solid(_fontes.fonteMenu, "joueurs de cette partie :", {0, 0, 0, 0});
}


void MenuJouer::jouer() {
    // On sauvegarde le noms des joueurs dans notre config
    sauvegarderNomsJoueurs();

    // On initialise une instance d'Othello
    Jeu Othello(_rendu, _ecran, _fontes);
    Othello.vsIA = _typePartie;

    // On veut d�finir le joueur qui commence de mani�re al�atoire
    srand(time(NULL));
    bool commence = rand()%2;

    // D�finition des noms
    Othello.partie.J1.setNom((commence) ? _selecteurJ1->getNom() : _selecteurJ2->getNom());
    Othello.partie.J2.setNom((commence) ? _selecteurJ2->getNom() : _selecteurJ1->getNom());

    // C'est parti !
    Othello.afficher();
}


bool MenuJouer::rendre() {
    // On affiche tout d'abord le fond
    _fond->dessiner(_rendu);

    // Puis on positionne notre premi�re ligne de texte
    SDL_Rect posTexte;
    posTexte.x = 30;
    posTexte.y = 30;

    // On l'affiche
    SDL_BlitSurface(_texte1, NULL, _rendu, &posTexte);
    // On se d�cale de 16 pixels vers le bas pour notre deuxi�me ligne
    posTexte.y = 46;
    // Et on affiche
    SDL_BlitSurface(_texte2, NULL, _rendu, &posTexte);


    // Afin de g�rer constamment la souris, on place les proc�dures d'int�raction dans rendre()
    // On r�cup�re les coordonn�es de la souris (X et Y) ainsi que l'�tat du clic gauche
    int sourisX, sourisY;
    SDL_GetMouseState(&sourisX, &sourisY);

    // On fait int�r�agir le premier s�lecteur et on l'affiche
    _selecteurJ1->souris(sourisX/2, sourisY/2, false);
    _selecteurJ1->afficher();

    // Si la partie comporte deux joueurs humains, on fait int�r�agir le deuxi�me s�lecteur
    if (!_typePartie) _selecteurJ2->souris(sourisX/2, sourisY/2, false);
    // Dans tous les cas, on l'affiche aussi
    _selecteurJ2->afficher();

    // Si les deux s�lecteurs ne sont pas vides et qu'ils ne sont pas identiques
    if (strlen(_selecteurJ1->getNom()) > 0 && strlen(_selecteurJ2->getNom()) > 0 &&
        strcmp(_selecteurJ1->getNom(), _selecteurJ2->getNom()) != 0)
        // On active le deuxi�me bouton du menu ("Jouer !")
        menu->activerBouton(1);
    else
        // Sinon il reste d�sactiver afin de ne pas lancer la partie avec des noms vides
        menu->desactiverBouton(1);

    // Et on appelle la fonction rendre() de la classe AutoMenu dont MenuJouer est d�riv�e
    return AutoMenu::rendre();
}


bool MenuJouer::gererEvenementsSDL() {
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) {
        // Si le joueur veut carr�ment fermer le programme
        if (evenement.type == SDL_QUIT) {
            // Lance la propagation de la sortie du jeu
            quitter();
            // Force le s�quenceur � rendre la main
            return false;

        // Si le joueur presse une touche clavier
        } else if (evenement.type == SDL_KEYDOWN) {
            // Si les deux s�lecteurs ne sont pas vides et/ou �gaux, et qu'on appuie sur Entr�e
            if ((strlen(_selecteurJ1->getNom()) > 0 &&
                 strlen(_selecteurJ2->getNom()) > 0 &&
                 strcmp(_selecteurJ1->getNom(), _selecteurJ2->getNom()) != 0)
                && (evenement.key.keysym.sym == SDLK_RETURN || evenement.key.keysym.sym == SDLK_KP_ENTER)) {
                // On lance la partie
                jouer();
            } else {
                // Si c'est la touche TABULATION qui a �t� press�e, on change de selecteur
                if (evenement.key.keysym.sym == SDLK_TAB) {
                    // Si un seul s�lecteur n'est activ�, on ne fait rien
                    if (!_typePartie) {
                        if (_selecteurJ1->getFocus()) {
                            _selecteurJ1->setFocus(false);
                            _selecteurJ2->setFocus(true);
                        } else {
                            _selecteurJ1->setFocus(true);
                            _selecteurJ2->setFocus(false);
                        }
                    }
                } else if (evenement.key.keysym.sym != SDLK_ESCAPE) {
                    // On fait int�r�agir les selecteurs
                    _selecteurJ1->clavier(evenement.key.keysym);
                    if (!_typePartie) _selecteurJ2->clavier(evenement.key.keysym);
                }
            }

        } else if (evenement.type == SDL_MOUSEBUTTONDOWN) {
            // On r�cup�re les coordonn�es et l'�tat de la souris
            int sourisX, sourisY;
            bool clic = SDL_GetMouseState(&sourisX, &sourisY) & SDL_BUTTON(SDL_BUTTON_LEFT);
            // Puis on les transmet aux diff�rents composants
            menu->souris(sourisX/2, sourisY/2, clic);
            _selecteurJ1->souris(sourisX/2, sourisY/2, clic);
            if (!_typePartie) _selecteurJ2->souris(sourisX/2, sourisY/2, clic);
        }
    }

    // Indique au s�quenceur qu'on peut continuer le rendu
    return true;
}


void MenuJouer::sauvegarderNomsJoueurs() {
    // On recharge la configuration
    Configuration configuration;
    Config config = configuration.lireConfig();

    configuration.ecrireConfig(
        // On sauvegarde le nom du joueur 1
        _selecteurJ1->getNom(),
        // Ainsi que celui du joueur 2 si c'est une partie � deux joueurs humains
        (!_typePartie) ? _selecteurJ2->getNom() : config.nomJoueur2
    );
}


MenuJouer::~MenuJouer() {
    // On supprime nos classes dynamiquement allou�es
    delete _fond;
    delete _selecteurJ1;
    delete _selecteurJ2;

    // On lib�re les surface contenant les deux lignes de texte
    SDL_FreeSurface(_texte1);
    SDL_FreeSurface(_texte2);
}
