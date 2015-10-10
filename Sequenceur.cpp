#include "Sequenceur.h"


Sequenceur::Sequenceur(seqCallback callback, Interface* parent, int frequence):
_delai(1000 / frequence), // On veut le délai entre deux répétitions en millisecondes
_callback(callback),
_parent(parent) {}


void Sequenceur::cycler() {
    int attente, debut;

    // Temps avant exécution de la fonction
    debut = SDL_GetTicks();

    // Tant qu'on veut répéter
    while ((_parent->*_callback)()) {
        // On attend jusqu'à notre prochaine répétition
        attente = (debut + _delai) - SDL_GetTicks();

        // Si on doit attendre, alors on "relache" l'exécution pendant 'attente' millisecondes
        if (attente > 0) SDL_Delay(attente);

        // On réinitialise le temps avant l'exécution de la fonction
        debut = SDL_GetTicks();
    }
}
