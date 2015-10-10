#include "Jeu.h"


Jeu::Jeu(SDL_Surface* rendu, SDL_Surface* ecran, Fontes fontes):
Interface(rendu, ecran, fontes),
_horloge(),
_pions(NULL),
_imgPlateau(NULL),
_imgVue_Plateau(NULL),
_tilPions(NULL),
_tilAidePions(NULL),
_tilReplay(NULL),
_sNomJoueur1(NULL),
_posNomJoueur1(),
_sNomJoueur2(NULL),
_posNomJoueur2(),
_sScore(NULL),
_posScore(),
_replay(NULL),
_coupsReplay(),
_coupsPossibles(),
_finPartie(0),
_raisonFinPartie(),
_coupIA(_horloge.temps()+1500),
_retourMenu(false),
partie(),
vsIA(false) {
    // Chargement des images
    chargerImages();

    // On remplit notre tableau de Sprite de NULL afin d'indiquer aux fonctions de rendu qu'il n'y a pas d'animation dans cette case
    for (int x=0;x<MAX;x++)
        for (int y=0;y<MAX;y++)
            _animations[x][y] = NULL;

    // On créé un nouveau replay en stand-by pour l'instant
    _replay = new Replay();

    // Récupère la liste des coups possible
    _coupsPossibles = partie.getCoupsPossibles();
}


void Jeu::chargerImages() {
    // Chargement séparé de la surface car elle sera réutilisée plus tard dans le jeu (animations)
    _pions = SDL_LoadBMP("ressources/images/pions.bmp");

    // Chargement de nos objets d'affichage
    _imgPlateau = new Image(SDL_LoadBMP("ressources/images/plateau.bmp"));
    _imgVue_Plateau = new Image(SDL_LoadBMP("ressources/images/vue_plateau.bmp"));
    _tilPions = new Tuile(_pions, 29);
    _tilAidePions = new Tuile(SDL_LoadBMP("ressources/images/aide_pions.bmp"), 29);
    _tilReplay = new Tuile(SDL_LoadBMP("ressources/images/replay.bmp"), 48);
}


void Jeu::libererImages() {
    // On libère chaque surface manuellement
    // La libération mémoire n'est pas implementée dans le destructeur de la classe Image car des occurences de classes
    // dérivées peuvent être créées/détruites durant le jeu, libérant ainsi la surface qui devra être rechargée pour
    // pouvoir être réutilisée

    // Le chargement d'une image en mémoire prend beaucoup de temps et ne sera donc effectué qu'à l'initialisation
    _imgPlateau->libererSurface();
    _imgVue_Plateau->libererSurface();
    _tilPions->libererSurface();
    _tilAidePions->libererSurface();
    _tilReplay->libererSurface();

    // Surfaces score
    if (_sNomJoueur1) SDL_FreeSurface(_sNomJoueur1);
    if (_sNomJoueur2) SDL_FreeSurface(_sNomJoueur2);
    if (_sScore) SDL_FreeSurface(_sScore);

    // On détruit nos occurences de classes créées dynamiquement
    delete _imgPlateau;
    delete _imgVue_Plateau;
    delete _tilPions;
    delete _tilAidePions;
    delete _tilReplay;
}


void Jeu::lireReplay(const char* nomFichier) throw(const char*) {
    // Passe en mode lecture
    _replay->setMode(MODE_REPLAY, nomFichier);

    // Récupère le header afin d'afficher le nom des joueurs correspondant
    Header header = _replay->getHeader();
    partie.J1.setNom(header.nomJoueur1);
    partie.J2.setNom(header.nomJoueur2);

    // Joue-t-on contre l'IA ?
    vsIA = header.adversaire;

    // Récupère les coups du replay
    _coupsReplay = _replay->lireCoups();
}


void Jeu::majScores() {
    // Si les surfaces ont déjà été initialisées, on les libère pour ne pas créer de fuite mémoire
    if (_sNomJoueur1) SDL_FreeSurface(_sNomJoueur1);
    if (_sNomJoueur2) SDL_FreeSurface(_sNomJoueur2);
    if (_sScore) SDL_FreeSurface(_sScore);

    // Affichage des deux textes représentant les noms des deux joueurs
    _sNomJoueur1 = TTF_RenderText_Solid(
        (partie.joueurCourant == &(partie.J1)) ? _fontes.fonteGras : _fontes.fonteNormal,
        partie.J1.getNom(), {255, 255, 255, 255});

    _sNomJoueur2 = TTF_RenderText_Solid(
        (partie.joueurCourant == &(partie.J2)) ? _fontes.fonteGras : _fontes.fonteNormal,
        partie.J2.getNom(), {255, 255, 255, 255});

    // Formatage du score
    char texteScore[12];
    sprintf(texteScore, "%d : %d", partie.J1.getScore(), partie.J2.getScore());

    // Rendu du score
    _sScore = TTF_RenderText_Solid(_fontes.fonteNormal, texteScore, {255, 255, 255, 255});

    // Positionnement des 3 textes sur l'interface
    _posNomJoueur1.x = 15;
    _posNomJoueur1.y = 0;

    _posNomJoueur2.x = _rendu->w - _sNomJoueur2->w - 15;
    _posNomJoueur2.y = 0;

    _posScore.x = (_rendu->w - _sScore->w) / 2;
    _posScore.y = 0;
}


void Jeu::dessinerPions() {
    // On parcourt chaque case de notre plateau de jeu
    for (int x=0;x<MAX;x++) {
        for (int y=0;y<MAX;y++) {
            // Si il n'y a pas d'animation (== NULL)
            if (!_animations[x][y]) {
                // On affiche le pion présent dans cette case du plateau
                // NB : ces deux lignes peuvent lancer des exceptions, mais on est certain qu'elles ne le ferront jamais...
                //      On ne s'encombrera donc pas d'un message à cet endroit
                if (partie.plateau.getPion(x, y) != X)
                    _tilPions->dessiner(_rendu, (partie.plateau.getPion(x, y) == N) ? 6 : 0, x*30 + 9, y*30 + 9 + 15);

            // Si une animation a lieu à cet endroit du plateau (la case du tableau != NULL)
            } else {
                // On dessine la sous-image (frame) du sprite correspondant
                _animations[x][y]->dessiner(_rendu, x*30 + 9, y*30 + 9 + 15);
                // Si l'animation est terminée (on a affiché toutes les frames)
                if (_animations[x][y]->animFinie()) {
                    // On libère la mémoire associée à notre sprite
                    delete _animations[x][y];
                    // On assigne NULL à la case du tableau pour ne pas fausser le premier test
                    _animations[x][y] = NULL;
                }
            }
        }
    }
}


void Jeu::dessinerPionsCoupsPossibles() {
    // On affiche tous les coups possibles
    // NB : auto = type automatique, c'est juste plus rapide à écrire
    for (auto it=_coupsPossibles.begin();it != _coupsPossibles.end(); ++it)
        // On dessine un pion noir ou blanc "transparent" pour indiquer qu'un coup est possible
        _tilAidePions->dessiner(_rendu, (partie.joueurCourant == &(partie.J1)) ? 0 : 1, (*it).X*30 + 9, (*it).Y*30 + 9 + 15);
}


void Jeu::afficher() {
    // Si on est toujours en stand-by, on passe en mode enregistrement
    // Le passage en mode lecture doit se faire avant l'affichage du jeu
    if (_replay->getMode() == MODE_STANDBY) _replay->setMode(MODE_ENREGISTREMENT);

    // Actualisation des surfaces & positions
    majScores();

    // Et on répète notre fonction de rendu
    _sequenceur->cycler();

    // Si on est en mode enregistrement replay, ne pas oublier de finaliser l'enregistrement
    if (_replay->getMode() == MODE_ENREGISTREMENT)
        _replay->finaliserEnregistrement(MAX, (_finPartie == 0), vsIA, partie.J1.getNom(), partie.J2.getNom());
}


bool Jeu::rendre() {
    // En première instruction : évite les crashs liés aux retours menus causés par des exceptions
    if (_retourMenu) return false;

    // Si on est en mode lecture de replay
    if (_replay->getMode() == MODE_REPLAY) {
        // Et que notre liste de coups à jouer n'est pas vide
        if (!_coupsReplay.empty()) {
            // Qu'il est temps de jouer le prochain coup
            if (_horloge.temps() >= _coupsReplay.front().temps) {
                // Alors on fait jouer automatiquement le jeu
                placerPion(_coupsReplay.front().X, _coupsReplay.front().Y);
                // Et on retire ce coup du haut du deck
                _coupsReplay.pop_front();
            }

        // Si la liste est vide, on passe en mode enregistrement afin que le joueur continue sa partie
        } else if (_finPartie == 0) {
            _replay->setMode(MODE_ENREGISTREMENT);
            _horloge.setVitesse(1);
        }
    }

    // Si la partie n'est pas encore terminée
    if (_finPartie == 0) {
        // Si le jeu est plein
        if (partie.jeuPlein()) {
            // On se prépare à afficher la victoire pour un des joueurs dans une seconde
            strcpy(_raisonFinPartie, "Plateau plein");
            _finPartie = _horloge.temps() + 1000;

        // Sinon, et qu'il est impossible de jouer
        } else if (!partie.jeuPossible()) {
            char joueur[16];
            strncpy(joueur, partie.joueurCourant->getNom(), 16);

            // Le joueur courant passe son tour
            partie.joueurSuivant();

            // Si on ne peut toujours pas jouer, c'est que le jeu est bloqué
            if (!partie.jeuPossible()) {
                strcpy(_raisonFinPartie, "Jeu bloqué");
                _finPartie = _horloge.temps() + 1000;

            // Sinon c'est qu'un joueur a passé son tour, on l'affiche sous forme de message
            } else {
                char texte[40];
                sprintf(texte, "%s ne peut pas jouer.", joueur);
                Message message(_rendu, _ecran, _fontes, "Jeu", texte);
                message.afficher();
            }

            // Recharge la liste des coups possibles
            _coupsPossibles = partie.getCoupsPossibles();
        }

    // Si la partie est terminée, on attend un peu afin de terminer les animations
    } else if (_horloge.temps() >= _finPartie) {
        // Puis on affiche un message nous indiquant le vainqueur
        finPartie(_raisonFinPartie);
    }

    // Si on est pas en mode replay
    // Si le joueur courant a pour nom "Ordinateur"
    // Si c'est bien une partie contre l'IA
    // Si on a pas fini la partie
    // Et si il est temps de faire jouer l'IA
    if (_replay->getMode() != MODE_REPLAY &&
        strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 &&
        vsIA &&
        _finPartie == 0 &&
        _horloge.temps() >= _coupIA)
        // On joue le coup qui rapporte le plus de points
        placerPion(_coupsPossibles.front().X, _coupsPossibles.front().Y);

    // On dessine des images statiques toutes simples (plateau et vue du plateau qui se trouve juste au dessus)
    _imgPlateau->dessiner(_rendu);
    _imgVue_Plateau->dessiner(_rendu);

    // Affichage des surfaces score
    SDL_BlitSurface(_sNomJoueur1, NULL, _rendu, &_posNomJoueur1);
    SDL_BlitSurface(_sNomJoueur2, NULL, _rendu, &_posNomJoueur2);
    SDL_BlitSurface(_sScore, NULL, _rendu, &_posScore);

    dessinerPions();

    // Si on est en pas en mode lecture de replay, on affiche les coups possibles
    if (_replay->getMode() != MODE_REPLAY && !(strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 && vsIA))
        dessinerPionsCoupsPossibles();
    // Sinon on affiche les indicateurs de replay (lecture, accéleré) + clignotement toutes les 500 ms
    else if (_replay->getMode() == MODE_REPLAY && (_horloge.temps()-((int) _horloge.temps()/1000)*1000 > 500))
        _tilReplay->dessiner(_rendu, (_horloge.getVitesse() > 1) ? 1 : 0, 16, 28);

    // On étire notre surface _rendu pour qu'elle fasse la taille de la surface de rendu
    SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

    // On rafraichit notre surface d'affichage principale
    SDL_Flip(_ecran);

    // Cette fonction nous indique si un évènement de sortie du jeu a été déclenché, et lance la fermeture dans le main
    return gererEvenementsSDL() && (!_quitter);
}


void Jeu::finPartie(const char* titre) {
    // Déclaration variables
    char vainqueur[16];
    int scoreVainqueur, scorePerdant;
    char contenu[60];

    // Si c'est le joueur 1 qui a le meilleur score
    if (partie.J1.getScore() > partie.J2.getScore()) {
        // On affecte les valeurs de la partie à nos variables locales pour l'affichage du message
        strcpy(vainqueur, partie.J1.getNom());
        scoreVainqueur = partie.J1.getScore();
        scorePerdant = partie.J2.getScore();
    } else {
        strcpy(vainqueur, partie.J2.getNom());
        scoreVainqueur = partie.J2.getScore();
        scorePerdant = partie.J1.getScore();
    }

    // On donne les cases vides au vainqueur
    if ((scorePerdant + scoreVainqueur) < MAX*MAX) scoreVainqueur = MAX*MAX - scorePerdant;

    // On formate notre châine grâce à la bonne vieille fonction du C
    sprintf(contenu, "Victoire %s : %d points à %d.", vainqueur, scoreVainqueur, scorePerdant);

    // Puis on affiche le message
    Message message(_rendu, _ecran, _fontes, titre,
        (partie.J1.getScore() == partie.J2.getScore()) ? "Egalité !" : contenu);
    message.afficher();

    // Et on indique au séquenceur qu'on souhaite revenir au menu principal du jeu, donc il faut stopper le séquenceur
    _retourMenu = true;
}


void Jeu::placerPion(int x, int y) {
    // Si le clic provient bien du plateau de jeu et pas autour par exemple
    if (x >= 0 && y >= 0 && x < MAX && y < MAX) {
        // Si un coup est possible
        if (partie.testJeu(x, y)) {
            try {
                // Si on est actuellement en train d'enregistrer un replay
                if (_replay->getMode() == MODE_ENREGISTREMENT) _replay->coup(_horloge.temps(), x, y);
                // Fait jouer le jeu et transmet la fonction de création de Sprite à notre classe Partie
                partie.jouer(x, y, [&] (int X, int Y) {
                    // On a déjà vérifié qu'aucune exception ne sera lancée en première ligne
                    _animations[X][Y] = new Sprite(_pions, &_horloge, 29, 75, (partie.plateau.getPion(X, Y) == B));
                });
                // Recharge la liste des coups possibles
                _coupsPossibles = partie.getCoupsPossibles();
                // Actualisation des surfaces & positions score
                majScores();

            } catch (const char* ex) {
                Message message(_rendu, _ecran, _fontes, "Erreur", ex);
                message.afficher();
                _retourMenu = true;
            }
        }
    }
}


bool Jeu::gererEvenementsSDL() {
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) {
        switch (evenement.type) {
            // Clic souris
            case SDL_MOUSEBUTTONDOWN:
                // Si on est pas en mode replay et que la partie n'est pas terminée
                if ((evenement.button.button == SDL_BUTTON_LEFT) && _replay->getMode() != MODE_REPLAY && _finPartie == 0) {
                    // Si ce n'est pas à l'IA de jouer
                    if (!(strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 && vsIA)) {
                        // On lance placerPion en décalant les coordonnées du clic en fonction des coordonnées de notre plateau de jeu sur
                        // la surface de rendu, de la même manière ne pas oublier qu'on joue sur une surface zoomée * 2
                        // 60 correspond à la largeur d'une case (30) * 2
                        placerPion((evenement.button.x - 9*2) / 60, (evenement.button.y - 9*2 - 15*2) / 60);
                        // Prochain coup de l'IA dans une seconde et demie
                        _coupIA = _horloge.temps() + 1500;
                    }
                }
                break;

            // Fermeture programme (croix rouge Windows)
            case SDL_QUIT:
                 // On propage la fermeture du jeu
                quitter();
                // On indique au séquenceur qu'il faut rendre la main et s'arréter
                return false;
                break;

            // Pression d'une touche clavier
            case SDL_KEYDOWN:
                // Met en pause si c'est ESPACE ou ECHAP
                if ((evenement.key.keysym.sym == SDLK_SPACE) || (evenement.key.keysym.sym == SDLK_ESCAPE)) {
                    pause();

                // Si on veut accélérer durant un replay
                } else if (evenement.key.keysym.sym == SDLK_RIGHT && _replay->getMode() == MODE_REPLAY) {
                    // Variation : 1 2 4 8
                    _horloge.setVitesse((_horloge.getVitesse() < 8) ? _horloge.getVitesse()*2 : 8);

                // Ou ralentir
                } else if (evenement.key.keysym.sym == SDLK_LEFT && _replay->getMode() == MODE_REPLAY) {
                    _horloge.setVitesse((_horloge.getVitesse() > 1) ? _horloge.getVitesse()/2 : 1);
                }
                break;
        }
    }

    // Ok on peut continuer la répétition du rendu via le séquenceur
    return true;
}


void Jeu::pause() {
    // On met en pause le timing afin que les animations repartent là où elles se sont arretées
    _horloge.pause();

    // Assombrissement de la surface pour un effet 'modal'
    assombrir(_rendu);

    // Initialise l'interface de pause
    AutoMenu menuPause(_rendu, _ecran, _fontes);

    // Et on dessine notre menu
    menuPause.menu->ajouterBouton("Reprendre", [&] () {
        menuPause.quitterMenu();
    });

    menuPause.menu->ajouterEspace();

    menuPause.menu->ajouterBouton("Menu principal", [&] () {
        _retourMenu = true;
        menuPause.quitterMenu();
    });

    menuPause.menu->ajouterBouton("Quitter le jeu", [&] () {
        quitter();
    });

    // Puis on affiche jusqu'à ce que l'utilisateur veuille quitter ou qu'il ait fait un choix
    menuPause.afficher();

    // On reprend les animations
    _horloge.reprendre();
}


Jeu::~Jeu() {
    // Libération mémoire
    libererImages();

    // On oublie pas de fermer le replay
    delete _replay;
}
