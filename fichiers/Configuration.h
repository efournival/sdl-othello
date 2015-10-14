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
	char chaineMagique[8];	// OthC0nf
	uint8_t version;
	char nomJoueur1[16];
	char nomJoueur2[16];
};

class Configuration {
	private:
		void reinitConfig();
		Config defautConfig();
		void ecrireConfig(Config);

	public:
		Config lireConfig();
		void ecrireConfig(const char* = "", const char* = "");
};

#endif
