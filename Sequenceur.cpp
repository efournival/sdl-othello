#include "Sequenceur.h"


Sequenceur::Sequenceur(seqCallback callback, Interface* parent, int frequence):
_delai(1000 / frequence), // On veut le d�lai entre deux r�p�titions en millisecondes
_callback(callback),
_parent(parent) {}


void Sequenceur::cycler() {
    int attente, debut;

    // Temps avant ex�cution de la fonction
    debut = SDL_GetTicks();

    // Tant qu'on veut r�p�ter
    while ((_parent->*_callback)()) {
        // On attend jusqu'� notre prochaine r�p�tition
        attente = (debut + _delai) - SDL_GetTicks();

        // Si on doit attendre, alors on "relache" l'ex�cution pendant 'attente' millisecondes
        if (attente > 0) SDL_Delay(attente);

        // On r�initialise le temps avant l'ex�cution de la fonction
        debut = SDL_GetTicks();
    }
}
