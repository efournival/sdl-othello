/*
    Classe : Configuration

    Cette classe permet au jeu de charger des options dans un fichier pr�d�fini et de g�rer tous les cas possibles d'erreurs de mani�re
    silencieuse tout en garantissant que les options retourn�es seront valides.
    � la base pr�vue pour un grand nombre d'options, le fichier a �t� r�duit � deux noms de joueurs par manque de temps, il pourra �tre
    compl�t� par la suite, il suffit de rajouter des membres dans la struct Config et g�rer leur lecture/enregistrement.

    Programmeur : Edgar Fournival
*/

#ifndef H_CONFIGURATION
#define H_CONFIGURATION

#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdint>
#include <iostream>

using namespace std;


const uint8_t CONFIG_VERSION = 1;
const char CHEMIN_CONFIG[] = "ressources/othello.conf";

struct Config {
    // Cha�ne qui DEVRA toujours �tre 'OthC0nf'
	char chaineMagique[8];
	// Version de la configuration
	uint8_t version;
	// Noms des joueurs si 'sauvegarderNomsJoueurs' est VRAI
	char nomJoueur1[16];
	char nomJoueur2[16];
};

class Configuration {
    private:
        // R�initialise le fichier de configuration avec les valeurs par d�faut
        void reinitConfig();

        // Renvoie les valeurs par d�faut
        Config defautConfig();

        // Ecrit dans le fichier les valeurs fournies
        void ecrireConfig(Config);

    public:
        // Lit les valeurs de configuration si c'est possible, s'assure qu'on aura de bons param�tres dans tous les cas
        Config lireConfig();

        // Ecrit les valeurs dans le fichier de configuration de mani�re simple
        void ecrireConfig(const char* ="", const char* ="");
};

#endif
