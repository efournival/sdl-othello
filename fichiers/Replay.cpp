#include "Replay.h"


Replay::Replay():
_fichier(),
_header(),
_mode(MODE_STANDBY),
_tamponCoups() { }

void Replay::setMode(Mode mode, const char* nomFichier) throw(const char*) {
	if (mode == MODE_REPLAY) {
		_fichier.open(nomFichier, ios::in | ios::binary);
		if (_fichier.is_open()) {
			lireHeader();
		} else {
			throw("Impossible d'ouvrir le fichier.");
		}
		_mode = mode;
	} else if (mode == MODE_ENREGISTREMENT) {
		if (_fichier.is_open()) 
			_fichier.close();

		_fichier.open("ressources/replay.otlo", ios::out | ios::binary);

		if (!_fichier.is_open())
			throw("Impossible d'enregistrer le replay.");

		_mode = mode;
	} else {
		_mode = mode;
	}
}

Mode Replay::getMode() {
	return _mode;
}

void Replay::lireHeader() throw(const char*) {
	_fichier.read((char*) &_header.chaineMagique, sizeof(_header.chaineMagique));
	if (strcmp(_header.chaineMagique, "OtheLLo") != 0) 
		throw("Le fichier n'est pas un replay valide.");

	_fichier.read((char*) &_header.version, sizeof(_header.version));
	if (_header.version > REPLAY_VERSION) 
		throw("Version du jeu trop ancienne.");

	_fichier.read((char*) &_header.max, sizeof(_header.max));

	_fichier.read((char*) &_header.partieEnCours, sizeof(_header.partieEnCours));

	_fichier.read((char*) &_header.adversaire, sizeof(_header.adversaire));

	_fichier.read((char*) &_header.nomJoueur1, sizeof(_header.nomJoueur1));
	_fichier.read((char*) &_header.nomJoueur2, sizeof(_header.nomJoueur2));

	_fichier.read((char*) &_header.tailleContenu, sizeof(_header.tailleContenu));

	if (_fichier.fail())
		throw("Fichier tronqué.");
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

	if (_fichier.fail()) 
		throw("Fichier tronqué.");

	return resultat;
}

void Replay::ecrireCoup(Coup coup) {
	_fichier.write((char*) &coup.temps, sizeof(coup.temps));
	_fichier.put(coup.X);
	_fichier.put(coup.Y);
}

void Replay::coup(uint32_t temps, uint8_t X, uint8_t Y) {
	Coup coup;
	coup.temps = temps;
	coup.X = X;
	coup.Y = Y;
	_tamponCoups.push_back(coup);
}

deque<Coup> Replay::lireCoups() throw(const char*) {
	const int finContenu = (int) _fichier.tellp() + _header.tailleContenu;

	while (_fichier.tellp() < finContenu) {
		_tamponCoups.push_back(lireCoup());
	}

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

	_header.tailleContenu = _tamponCoups.size() * 6;	// 6 octets

	ecrireHeader();

	for (auto it = _tamponCoups.begin(); it != _tamponCoups.end(); ++it) {
		ecrireCoup(*it);
	}

	_fichier.flush();
}

Replay::~Replay() {
	if (_fichier.is_open()) 
		_fichier.close();
}
