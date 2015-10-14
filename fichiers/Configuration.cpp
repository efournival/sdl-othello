#include "Configuration.h"


Config Configuration::lireConfig() {
	ifstream fichier(CHEMIN_CONFIG, ios::binary);

	if (fichier.is_open()) {
		Config resultat;

		fichier.read((char*) &resultat.chaineMagique, sizeof(resultat.chaineMagique));

		if (strcmp(resultat.chaineMagique, "OthC0nf") != 0) {
			fichier.close();
			reinitConfig();
			return defautConfig();
		}

		fichier.read((char*) &resultat.version, sizeof(resultat.version));

		if (resultat.version > CONFIG_VERSION) {
			fichier.close();
			return defautConfig();
		}

		fichier.read((char*) &resultat.nomJoueur1, sizeof(resultat.nomJoueur1));
		fichier.read((char*) &resultat.nomJoueur2, sizeof(resultat.nomJoueur2));

		if (fichier.fail()) {
			fichier.close();
			reinitConfig();
			return defautConfig();
		}

		return resultat;
	} else {
		reinitConfig();
		return defautConfig();
	}
}

Config Configuration::defautConfig() {
	Config resultat;

	strcpy(resultat.chaineMagique, "OthC0nf");
	resultat.version = CONFIG_VERSION;
	strcpy(resultat.nomJoueur1, "");
	strcpy(resultat.nomJoueur2, "");

	return resultat;
}

void Configuration::ecrireConfig(Config config) {
	ofstream fichier(CHEMIN_CONFIG, ios::binary | ios::trunc);

	if (fichier.is_open()) {
		fichier.write(config.chaineMagique, sizeof(config.chaineMagique));
		fichier.put(config.version);
		fichier.write(config.nomJoueur1, sizeof(config.nomJoueur1));
		fichier.write(config.nomJoueur2, sizeof(config.nomJoueur2));
		fichier.close();
	}
}

void Configuration::ecrireConfig(const char nomJoueur1[16], const char nomJoueur2[16]) {
	Config config = defautConfig();
	strncpy(config.nomJoueur1, nomJoueur1, 16);
	strncpy(config.nomJoueur2, nomJoueur2, 16);
	ecrireConfig(config);
}

void Configuration::reinitConfig() {
	ecrireConfig(defautConfig());
}
