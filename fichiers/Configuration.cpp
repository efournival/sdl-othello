#include "Configuration.h"


Config Configuration::lireConfig() {
    // On ouvre notre fichier de configuration en mode lecture binaire
    ifstream fichier(CHEMIN_CONFIG, ios::binary);

    // Si le fichier existe et qu'on peut l'ouvrir
    if (fichier.is_open()) {
        Config resultat;

        // On commence par lire la chaîne magique qui détermine si c'est un bien un fichier de configuration
        fichier.read((char*) &resultat.chaineMagique, sizeof(resultat.chaineMagique));
        // Si la chaîne magique ne correspond pas
        if (strcmp(resultat.chaineMagique, "OthC0nf") != 0) {
            // On ferme le fichier qu'on vient juste d'ouvrir
            fichier.close();
            // On réinitialise la configuration
            reinitConfig();
            // Et on retourne les valeurs par défaut
            return defautConfig();
        }

        // On vérifie la version de la configuration
        fichier.read((char*) &resultat.version, sizeof(resultat.version));
        // Si c'est une configuration enregistrée par une version plus récente du jeu
        if (resultat.version > CONFIG_VERSION) {
            // On ferme le fichier
            fichier.close();
            // Et on renvoit les valeurs par défaut sans réinitialiser la config
            // Les valeurs sont sûrement correctes mais on ne va pas se risquer à les lire
            return defautConfig();
        }

        // On lit le nom des joueurs
        fichier.read((char*) &resultat.nomJoueur1, sizeof(resultat.nomJoueur1));
        fichier.read((char*) &resultat.nomJoueur2, sizeof(resultat.nomJoueur2));

        // Si une erreur de lecture est survenue
        if (fichier.fail()) {
            // On ferme, réinitialise puis renvoie des bonnes valeurs
            fichier.close();
            reinitConfig();
            return defautConfig();
        }

        // Si tout est bon, on renvoie ce qu'on vient de lire
        return resultat;

    // Si on a pas réussi à ouvrir le fichier
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
    // On ouvre notre fichier de config en mode écriture binaire
    ofstream fichier(CHEMIN_CONFIG, ios::binary | ios::trunc);

    // Si on peut écrire (si on ne peut pas, il ne se passe rien et le jeu utilisera toujours les valeurs par défaut)
    if (fichier.is_open()) {
        // On écrit nos valeurs
        fichier.write(config.chaineMagique, sizeof(config.chaineMagique));
        fichier.put(config.version);

        // Si on a activé la sauvegarde des noms
        fichier.write(config.nomJoueur1, sizeof(config.nomJoueur1));
        fichier.write(config.nomJoueur2, sizeof(config.nomJoueur2));

        // On ferme le fichier proprement
        fichier.close();
    }
}


void Configuration::ecrireConfig(const char nomJoueur1[16], const char nomJoueur2[16]) {
    // On part sur une base saine
    Config config = defautConfig();

    // On envoie tout ça dans notre structure de configuration modifiée
    strncpy(config.nomJoueur1, nomJoueur1, 16);
    strncpy(config.nomJoueur2, nomJoueur2, 16);

    // Et on écrit dans le fichier
    ecrireConfig(config);
}


void Configuration::reinitConfig() {
    // On écrit avec les valeurs par défaut
    ecrireConfig(defautConfig());
}
