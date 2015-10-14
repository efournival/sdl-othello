#ifndef H_REPLAY
#define H_REPLAY

#include <fstream>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cstdint>

using namespace std;


const uint8_t REPLAY_VERSION = 1;

enum Mode {
	MODE_STANDBY,
	MODE_REPLAY,
	MODE_ENREGISTREMENT
};

struct Header {
	char chaineMagique[8];
	uint8_t version;
	uint8_t max;
	uint8_t partieEnCours;
	uint8_t adversaire;
	char nomJoueur1[16];
	char nomJoueur2[16];
	uint32_t tailleContenu;
};

struct Coup {
	uint32_t temps;
	uint8_t X;
	uint8_t Y;
};

class Replay {
	private:
		fstream _fichier;
		Header _header;
		Mode _mode;
		deque<Coup> _tamponCoups;
		void lireHeader() throw(const char*);
		void ecrireHeader();
		Coup lireCoup() throw(const char*);
		void ecrireCoup(Coup);

	public:
		Replay();
		Mode getMode();
		void setMode(Mode, const char* = "") throw(const char*);
		Header getHeader();
		void coup(uint32_t, uint8_t, uint8_t);
		deque<Coup> lireCoups() throw(const char*);
		void finaliserEnregistrement(uint8_t, uint8_t, uint8_t, const char[16], const char[16]);
		~Replay();
};

#endif
