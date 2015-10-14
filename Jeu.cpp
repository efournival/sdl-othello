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
	chargerImages();

	for (int x = 0; x < MAX; x++) {
		for (int y = 0; y < MAX; y++) {
			_animations[x][y] = NULL;
		}
	}

	_replay = new Replay();

	_coupsPossibles = partie.getCoupsPossibles();
}

void Jeu::chargerImages() {
	_pions = SDL_LoadBMP("ressources/images/pions.bmp");

	_imgPlateau = new Image(SDL_LoadBMP("ressources/images/plateau.bmp"));
	_imgVue_Plateau = new Image(SDL_LoadBMP("ressources/images/vue_plateau.bmp"));
	_tilPions = new Tuile(_pions, 29);
	_tilAidePions = new Tuile(SDL_LoadBMP("ressources/images/aide_pions.bmp"), 29);
	_tilReplay = new Tuile(SDL_LoadBMP("ressources/images/replay.bmp"), 48);
}

void Jeu::libererImages() {
	_imgPlateau->libererSurface();
	_imgVue_Plateau->libererSurface();
	_tilPions->libererSurface();
	_tilAidePions->libererSurface();
	_tilReplay->libererSurface();

	if (_sNomJoueur1) SDL_FreeSurface(_sNomJoueur1);
	if (_sNomJoueur2) SDL_FreeSurface(_sNomJoueur2);
	if (_sScore) SDL_FreeSurface(_sScore);

	delete _imgPlateau;
	delete _imgVue_Plateau;
	delete _tilPions;
	delete _tilAidePions;
	delete _tilReplay;
}

void Jeu::lireReplay(const char* nomFichier) throw(const char*) {
	_replay->setMode(MODE_REPLAY, nomFichier);

	Header header = _replay->getHeader();
	partie.J1.setNom(header.nomJoueur1);
	partie.J2.setNom(header.nomJoueur2);

	vsIA = header.adversaire;

	_coupsReplay = _replay->lireCoups();
}

void Jeu::majScores() {
	if (_sNomJoueur1) 
		SDL_FreeSurface(_sNomJoueur1);

	if (_sNomJoueur2)
		SDL_FreeSurface(_sNomJoueur2);

	if (_sScore) 
		SDL_FreeSurface(_sScore);

	_sNomJoueur1 = TTF_RenderText_Solid(
		(partie.joueurCourant == &(partie.J1)) ? _fontes.fonteGras : _fontes.fonteNormal,
		partie.J1.getNom(), {255, 255, 255, 255});

	_sNomJoueur2 = TTF_RenderText_Solid(
		(partie.joueurCourant == &(partie.J2)) ? _fontes.fonteGras : _fontes.fonteNormal,
		partie.J2.getNom(), {255, 255, 255, 255});

	char texteScore[12];
	sprintf(texteScore, "%d : %d", partie.J1.getScore(), partie.J2.getScore());

	_sScore = TTF_RenderText_Solid(_fontes.fonteNormal, texteScore, {255, 255, 255, 255});

	_posNomJoueur1.x = 15;
	_posNomJoueur1.y = 0;

	_posNomJoueur2.x = _rendu->w - _sNomJoueur2->w - 15;
	_posNomJoueur2.y = 0;

	_posScore.x = (_rendu->w - _sScore->w) / 2;
	_posScore.y = 0;
}

void Jeu::dessinerPions() {
	for (int x = 0; x < MAX; x++) {
		for (int y = 0; y < MAX; y++) {
			if (!_animations[x][y]) {
				if (partie.plateau.getPion(x, y) != X) {
					_tilPions->dessiner(_rendu, (partie.plateau.getPion(x, y) == N) ? 6 : 0, x * 30 + 9, y * 30 + 9 + 15);
				}
			} else {
				_animations[x][y]->dessiner(_rendu, x*30 + 9, y*30 + 9 + 15);

				if (_animations[x][y]->animFinie()) {
					delete _animations[x][y];
					_animations[x][y] = NULL;
				}
			}
		}
	}
}

void Jeu::dessinerPionsCoupsPossibles() {
	for (auto it = _coupsPossibles.begin(); it != _coupsPossibles.end(); ++it) {
		_tilAidePions->dessiner(_rendu, (partie.joueurCourant == &(partie.J1)) ? 0 : 1, (*it).X * 30 + 9, (*it).Y * 30 + 9 + 15);
	}
}

void Jeu::afficher() {
	if (_replay->getMode() == MODE_STANDBY) {
		_replay->setMode(MODE_ENREGISTREMENT);
	}

	majScores();

	_sequenceur->cycler();

	if (_replay->getMode() == MODE_ENREGISTREMENT) {
		_replay->finaliserEnregistrement(MAX, (_finPartie == 0), vsIA, partie.J1.getNom(), partie.J2.getNom());
	}
}

bool Jeu::rendre() {
	if (_retourMenu) 
		return false;

	if (_replay->getMode() == MODE_REPLAY) {
		if (!_coupsReplay.empty()) {
			if (_horloge.temps() >= _coupsReplay.front().temps) {
				placerPion(_coupsReplay.front().X, _coupsReplay.front().Y);
				_coupsReplay.pop_front();
			}
		} else if (_finPartie == 0) {
			_replay->setMode(MODE_ENREGISTREMENT);
			_horloge.setVitesse(1);
		}
	}

	if (_finPartie == 0) {
		if (partie.jeuPlein()) {
			strcpy(_raisonFinPartie, "Plateau plein");
			_finPartie = _horloge.temps() + 1000;
		} else if (!partie.jeuPossible()) {
			char joueur[16];
			strncpy(joueur, partie.joueurCourant->getNom(), 16);

			partie.joueurSuivant();

			if (!partie.jeuPossible()) {
				strcpy(_raisonFinPartie, "Jeu bloqué");
				_finPartie = _horloge.temps() + 1000;
			} else {
				char texte[40];
				sprintf(texte, "%s ne peut pas jouer.", joueur);
				Message message(_rendu, _ecran, _fontes, "Jeu", texte);
				message.afficher();
			}

			_coupsPossibles = partie.getCoupsPossibles();
		}
	} else if (_horloge.temps() >= _finPartie) {
		finPartie(_raisonFinPartie);
	}

	if (_replay->getMode() != MODE_REPLAY && strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 && vsIA && _finPartie == 0 && _horloge.temps() >= _coupIA) {
		placerPion(_coupsPossibles.front().X, _coupsPossibles.front().Y);
	}

	_imgPlateau->dessiner(_rendu);
	_imgVue_Plateau->dessiner(_rendu);

	SDL_BlitSurface(_sNomJoueur1, NULL, _rendu, &_posNomJoueur1);
	SDL_BlitSurface(_sNomJoueur2, NULL, _rendu, &_posNomJoueur2);
	SDL_BlitSurface(_sScore, NULL, _rendu, &_posScore);

	dessinerPions();

	if (_replay->getMode() != MODE_REPLAY && !(strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 && vsIA)) {
		dessinerPionsCoupsPossibles();
	} else if (_replay->getMode() == MODE_REPLAY && (_horloge.temps() - ((int) _horloge.temps() / 1000) * 1000 > 500)) {
		_tilReplay->dessiner(_rendu, (_horloge.getVitesse() > 1) ? 1 : 0, 16, 28);
	}

	SDL_SoftStretch(_rendu, NULL, _ecran, NULL);

	SDL_Flip(_ecran);

	return gererEvenementsSDL() && (!_quitter);
}

void Jeu::finPartie(const char* titre) {
	char vainqueur[16];
	int scoreVainqueur, scorePerdant;
	char contenu[60];

	if (partie.J1.getScore() > partie.J2.getScore()) {
		strcpy(vainqueur, partie.J1.getNom());
		scoreVainqueur = partie.J1.getScore();
		scorePerdant = partie.J2.getScore();
	} else {
		strcpy(vainqueur, partie.J2.getNom());
		scoreVainqueur = partie.J2.getScore();
		scorePerdant = partie.J1.getScore();
	}

	if ((scorePerdant + scoreVainqueur) < MAX * MAX) {
		scoreVainqueur = MAX*MAX - scorePerdant;
	}

	sprintf(contenu, "Victoire %s : %d points à %d.", vainqueur, scoreVainqueur, scorePerdant);

	Message message(_rendu, _ecran, _fontes, titre, (partie.J1.getScore() == partie.J2.getScore()) ? "Egalité !" : contenu);
	message.afficher();

	_retourMenu = true;
}

void Jeu::placerPion(int x, int y) {
	if (x >= 0 && y >= 0 && x < MAX && y < MAX) {
		if (partie.testJeu(x, y)) {
			try {
				if (_replay->getMode() == MODE_ENREGISTREMENT) {
					_replay->coup(_horloge.temps(), x, y);
				}

				partie.jouer(x, y, [&] (int X, int Y) {
					_animations[X][Y] = new Sprite(_pions, &_horloge, 29, 75, (partie.plateau.getPion(X, Y) == B));
				});

				_coupsPossibles = partie.getCoupsPossibles();

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
			case SDL_MOUSEBUTTONDOWN:
				if ((evenement.button.button == SDL_BUTTON_LEFT) && _replay->getMode() != MODE_REPLAY && _finPartie == 0) {
					if (!(strcmp(partie.joueurCourant->getNom(), "Ordinateur") == 0 && vsIA)) {
						// largeur pion = 30 * 2
						placerPion((evenement.button.x - 9 * 2) / 60, (evenement.button.y - 9 * 2 - 15 * 2) / 60);
						_coupIA = _horloge.temps() + 1500;	// prochain coup dans 1,5 sec
					}
				}
				break;

			case SDL_QUIT:
				quitter();
				return false;
				break;

			case SDL_KEYDOWN:
				if ((evenement.key.keysym.sym == SDLK_SPACE) || (evenement.key.keysym.sym == SDLK_ESCAPE)) {
					pause();
				} else if (evenement.key.keysym.sym == SDLK_RIGHT && _replay->getMode() == MODE_REPLAY) {
					_horloge.setVitesse((_horloge.getVitesse() < 8) ? _horloge.getVitesse() * 2 : 8);
				} else if (evenement.key.keysym.sym == SDLK_LEFT && _replay->getMode() == MODE_REPLAY) {
					_horloge.setVitesse((_horloge.getVitesse() > 1) ? _horloge.getVitesse()/2 : 1);
				}
				break;
		}
	}

	return true;
}

void Jeu::pause() {
	_horloge.pause();

	assombrir(_rendu);

	AutoMenu menuPause(_rendu, _ecran, _fontes);

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

	menuPause.afficher();

	_horloge.reprendre();
}

Jeu::~Jeu() {
	libererImages();
	delete _replay;
}
