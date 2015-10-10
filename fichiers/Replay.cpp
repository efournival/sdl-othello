#include "Replay.h"


Replay::Replay():
_fichier(),
_header(),
_mode(MODE_STANDBY),
_tamponCoups() { }


void Replay::setMode(Mode mode, const char* nomFichier) throw(const char*) {
    // Si on est en mode lecture
    if (mode == MODE_REPLAY) {
        // On ouvre notre fichier en mode lecture binaire
        _fichier.open(nomFichier, ios::in | ios::binary);
        // Si le fichier a �t� ouvert avec succ�s
        if (_fichier.is_open()) {
            // On lit son ent�te (header)
            lireHeader();
        } else {
            // Sinon, on lance une exception
            throw("Impossible d'ouvrir le fichier.");
        }
        // On valide le changement de mode
        _mode = mode;

    // Si on est en mode enregistrement standard
    } else if (mode == MODE_ENREGISTREMENT) {
        // Si le fichier est d�j� ouvert, on le ferme
        if (_fichier.is_open()) _fichier.close();
        // On ouvre un fichier pr�d�fini en mode �criture binaire avec �crasement
        _fichier.open("ressources/replay.otlo", ios::out | ios::binary);
        // Si on ne peut pas �crire dans ce fichier, on lance une exception
        if (!_fichier.is_open()) throw("Impossible d'enregistrer le replay.");
        // On valide le changement de mode
        _mode = mode;

    } else {
        // Stand-by
        _mode = mode;
    }
}


Mode Replay::getMode() {
    return _mode;
}


void Replay::lireHeader() throw(const char*) {
    _fichier.read((char*) &_header.chaineMagique, sizeof(_header.chaineMagique));
    if (strcmp(_header.chaineMagique, "OtheLLo") != 0) throw("Le fichier n'est pas un replay valide.");

    _fichier.read((char*) &_header.version, sizeof(_header.version));
    if (_header.version > REPLAY_VERSION) throw("Version du jeu trop ancienne.");

    _fichier.read((char*) &_header.max, sizeof(_header.max));

    _fichier.read((char*) &_header.partieEnCours, sizeof(_header.partieEnCours));

    _fichier.read((char*) &_header.adversaire, sizeof(_header.adversaire));

    _fichier.read((char*) &_header.nomJoueur1, sizeof(_header.nomJoueur1));
    _fichier.read((char*) &_header.nomJoueur2, sizeof(_header.nomJoueur2));

    _fichier.read((char*) &_header.tailleContenu, sizeof(_header.tailleContenu));

    // Si une erreur est survenue durant la lecture
    if (_fichier.fail()) throw("Fichier tronqu�.");
}


void Replay::ecrireHeader() {
    _fichier.write(_header.chaineMagique, sizeof(_header.chaineMagique));
    _fichier.put(_header.version);
    _fichier.put(_header.max);
    _fichier.put(_header.partieEnCours);
    _fichier.put(_header.adversaire);
    _fichier.write(_header.nomJoueur1, sizeof(_header.nomJoueur1));
    _fichier.write(_header.nomJoueur2, sizeof(_header.nomJoueur2));
    _fichier.write((char*) &_header.tailleContenu, sizeof(_header.tailleContenu));
}


Header Replay::getHeader() {
    return _header;
}


Coup Replay::lireCoup() throw(const char*) {
    Coup resultat;
    _fichier.read((char*) &resultat.temps, sizeof(resultat.temps));
    _fichier.read((char*) &resultat.X, sizeof(resultat.X));
    _fichier.read((char*) &resultat.Y, sizeof(resultat.Y));

    // V�rifie si une erreur est survenue
    if (_fichier.fail()) throw("Fichier tronqu�.");

    // Et retourne le coup qui vient d'�tre lu
    return resultat;
}


void Replay::ecrireCoup(Coup coup) {
    _fichier.write((char*) &coup.temps, sizeof(coup.temps));
    _fichier.put(coup.X);
    _fichier.put(coup.Y);
}


void Replay::coup(uint32_t temps, uint8_t X, uint8_t Y) {
    // D�clare un coup
    Coup coup;
    coup.temps = temps;
    coup.X = X;
    coup.Y = Y;
    // Puis on l'envoie � la fin de notre deck tampon
    _tamponCoups.push_back(coup);
}


deque<Coup> Replay::lireCoups() throw(const char*) {
    // On d�finit la position dans le fichier repr�sentant la fin des coups
    const int finContenu = (int) _fichier.tellp() + _header.tailleContenu;
    // Puis on lit les coups tant que la position courante n'a pas d�pass� la position repr�sentant la fin des coups
    while (_fichier.tellp() < finContenu) {
        // On envoie � la fin du deck le coup qui vient d'�tre lu
        _tamponCoups.push_back(lireCoup());
    }

    // Et on retourne une copie de notre deck
    return _tamponCoups;
}

void Replay::finaliserEnregistrement(uint8_t max, uint8_t partieEnCours, uint8_t adversaire, const char nomJoueur1[16], const char nomJoueur2[16]) {
    strcpy(_header.chaineMagique, "OtheLLo");

    _header.version = REPLAY_VERSION;
    _header.max = max;
    _header.partieEnCours = partieEnCours;
    _header.adversaire = adversaire;
    strncpy(_header.nomJoueur1, nomJoueur1, 16);
    strncpy(_header.nomJoueur2, nomJoueur2, 16);

    // On sait qu'un coup prend 6 octets � stocker, donc on multiplie 6 octets par le nombre de coups stock�s dans le deck tampon
    // NB : il ne faut pas utiliser sizeof car il retournera le nombre d'octets n�cessaire au stockage en RAM de la structure, qui est align�
    // sur 4 octets par soucis d'optimisation, il faudrait alors utiliser l'attribut 'packed' mais cela est inutile car �crire/lire des structures
    // directement dans un fichier n'est pas une bonne m�thode de programmation
    _header.tailleContenu = _tamponCoups.size()*6;

    // On �crit le header qui vient d'�tre form�
    ecrireHeader();

    // Pour chaque coup dans notre deck tampon
    for (auto it = _tamponCoups.begin(); it != _tamponCoups.end(); ++it) {
        // On l'�crit dans le fichier
        ecrireCoup(*it);
    }

    // Force l'�criture du tampon d'entr�e/sortie sur le disque
    _fichier.flush();
}


Replay::~Replay() {
    // Si notre fichier est ouvert, on le ferme
    if (_fichier.is_open()) _fichier.close();
}
