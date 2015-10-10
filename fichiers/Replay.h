#ifndef H_REPLAY
#define H_REPLAY

#include <fstream>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cstdint>

using namespace std;


const uint8_t REPLAY_VERSION = 1;

// Mode de fonctionnement syst�me de replay
enum Mode {
    // Ne fait rien
    MODE_STANDBY,
    // Lecture d'un replay
    MODE_REPLAY,
    // Enregistrement d'un replay
    MODE_ENREGISTREMENT
};

struct Header {
    // Cha�ne qui DEVRA toujours �tre 'OtheLLo'
	char chaineMagique[8];
	// Version du syst�me de replay
	uint8_t version;
	// Nombre de lignes/colonnes (8, car le jeu ne supporte pas plus actuellement)
	uint8_t max;
	// Bool�en, indique si la partie est en cours ou termin�e
	uint8_t partieEnCours;
	// Bool�en (0 : humain, 1 : ordinateur)
	uint8_t adversaire;
	// Noms des joueurs
	char nomJoueur1[16];
	char nomJoueur2[16];
	// Taille du fichier (header exclu, afin de savoir le nombre pr�cis d'octets que l'on va lire)
	uint32_t tailleContenu;
};

struct Coup {
    // Un entier non sign� sur 32 bits garantis, repr�sente le timing interne de l'horloge
    uint32_t temps;
    // Colonne
    uint8_t X;
    // Ligne
    uint8_t Y;
};

class Replay {
    private:
        // Notre fichier sur lequel faire des op�rations d'entr�e/sortie
        // NB : on veut g�rer les 2 modes (lecture et enregistrement) donc on ne sp�cifie pas de ifstream ou ofstream
        fstream _fichier;

        // Le header du fichier, qui devra �tre �crit au bon moment car peut �tre vide
        Header _header;

        // Mode de fonctionnement du syst�me de replay (stand-by, enregistrement ou lecture)
        Mode _mode;

        // Notre liste de coups
        // NB : deque = vector mais supporte push/pop_front, plus lourd � l'ex�cution mais plus pratique
        deque<Coup> _tamponCoups;

        // Lit le header et retourne une exception si le fichier est inutilisable
        void lireHeader() throw(const char*);
        // Enregistre le header
        void ecrireHeader();

        // Lit un coup depuis le fichier et le retourne, lance une exception si on ne peut pas lire
        Coup lireCoup() throw(const char*);
        // Ecrit un coup dans le fichier
        void ecrireCoup(Coup);

    public:
        // Constructeur de la classe
        Replay();

        // Retourne le mode de fonctionnement du replay
        Mode getMode();

        // D�finit le mode de fonctionnement du replay
        void setMode(Mode, const char* ="") throw(const char*);

        // Retourne le header afin de d�marrer la partie
        Header getHeader();

        // Met un coup dans le tampon (attention : il ne sera pas encore �crit dans le fichier)
        void coup(uint32_t, uint8_t, uint8_t);

        // Retourne une copie du tampon apr�s avoir lu tous les coups du fichier
        deque<Coup> lireCoups() throw(const char*);

        // Finalise l'enregistrement d'un replay en �crivant le header et le tampon de coups dans le fichier
        void finaliserEnregistrement(uint8_t, uint8_t, uint8_t, const char[16], const char[16]);

        // Destructeur
        ~Replay();
};

#endif
