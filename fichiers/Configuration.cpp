#include "Configuration.h"


Config Configuration::lireConfig() {
    // On ouvre notre fichier de configuration en mode lecture binaire
    ifstream fichier(CHEMIN_CONFIG, ios::binary);

    // Si le fichier existe et qu'on peut l'ouvrir
    if (fichier.is_open()) {
        Config resultat;

        // On commence par lire la cha�ne magique qui d�termine si c'est un bien un fichier de configuration
        fichier.read((char*) &resultat.chaineMagique, sizeof(resultat.chaineMagique));
        // Si la cha�ne magique ne correspond pas
        if (strcmp(resultat.chaineMagique, "OthC0nf") != 0) {
            // On ferme le fichier qu'on vient juste d'ouvrir
            fichier.close();
            // On r�initialise la configuration
            reinitConfig();
            // Et on retourne les valeurs par d�faut
            return defautConfig();
        }

        // On v�rifie la version de la configuration
        fichier.read((char*) &resultat.version, sizeof(resultat.version));
        // Si c'est une configuration enregistr�e par une version plus r�cente du jeu
        if (resultat.version > CONFIG_VERSION) {
            // On ferme le fichier
            fichier.close();
            // Et on renvoit les valeurs par d�faut sans r�initialiser la config
            // Les valeurs sont s�rement correctes mais on ne va pas se risquer � les lire
            return defautConfig();
        }

        // On lit le nom des joueurs
        fichier.read((char*) &resultat.nomJoueur1, sizeof(resultat.nomJoueur1));
        fichier.read((char*) &resultat.nomJoueur2, sizeof(resultat.nomJoueur2));

        // Si une erreur de lecture est survenue
        if (fichier.fail()) {
            // On ferme, r�initialise puis renvoie des bonnes valeurs
            fichier.close();
            reinitConfig();
            return defautConfig();
        }

        // Si tout est bon, on renvoie ce qu'on vient de lire
        return resultat;

    // Si on a pas r�ussi � ouvrir le fichier
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
    // On ouvre notre fichier de config en mode �criture binaire
    ofstream fichier(CHEMIN_CONFIG, ios::binary | ios::trunc);

    // Si on peut �crire (si on ne peut pas, il ne se passe rien et le jeu utilisera toujours les valeurs par d�faut)
    if (fichier.is_open()) {
        // On �crit nos valeurs
        fichier.write(config.chaineMagique, sizeof(config.chaineMagique));
        fichier.put(config.version);

        // Si on a activ� la sauvegarde des noms
        fichier.write(config.nomJoueur1, sizeof(config.nomJoueur1));
        fichier.write(config.nomJoueur2, sizeof(config.nomJoueur2));

        // On ferme le fichier proprement
        fichier.close();
    }
}


void Configuration::ecrireConfig(const char nomJoueur1[16], const char nomJoueur2[16]) {
    // On part sur une base saine
    Config config = defautConfig();

    // On envoie tout �a dans notre structure de configuration modifi�e
    strncpy(config.nomJoueur1, nomJoueur1, 16);
    strncpy(config.nomJoueur2, nomJoueur2, 16);

    // Et on �crit dans le fichier
    ecrireConfig(config);
}


void Configuration::reinitConfig() {
    // On �crit avec les valeurs par d�faut
    ecrireConfig(defautConfig());
}
