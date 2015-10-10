/*
    Classe : Configuration

    Cette classe permet au jeu de charger des options dans un fichier prédéfini et de gérer tous les cas possibles d'erreurs de manière
    silencieuse tout en garantissant que les options retournées seront valides.
    À la base prévue pour un grand nombre d'options, le fichier a été réduit à deux noms de joueurs par manque de temps, il pourra être
    complété par la suite, il suffit de rajouter des membres dans la struct Config et gérer leur lecture/enregistrement.

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
    // Chaîne qui DEVRA toujours être 'OthC0nf'
	char chaineMagique[8];
	// Version de la configuration
	uint8_t version;
	// Noms des joueurs si 'sauvegarderNomsJoueurs' est VRAI
	char nomJoueur1[16];
	char nomJoueur2[16];
};

class Configuration {
    private:
        // Réinitialise le fichier de configuration avec les valeurs par défaut
        void reinitConfig();

        // Renvoie les valeurs par défaut
        Config defautConfig();

        // Ecrit dans le fichier les valeurs fournies
        void ecrireConfig(Config);

    public:
        // Lit les valeurs de configuration si c'est possible, s'assure qu'on aura de bons paramètres dans tous les cas
        Config lireConfig();

        // Ecrit les valeurs dans le fichier de configuration de manière simple
        void ecrireConfig(const char* ="", const char* ="");
};

#endif
