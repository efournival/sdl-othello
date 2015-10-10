#include "Horloge.h"


Horloge::Horloge():
_pause(0),
_decalage(SDL_GetTicks()),
_vitesse(1),
_decalageVitesse(0),
_changementVitesse(0),
_enPause(false) {}


void Horloge::pause() {
    // Afin de calculer le d�calage, on m�morise le temps en ms lors de la mise en pause
    _pause = SDL_GetTicks();
    _enPause = true;
}


void Horloge::reprendre() {
    // On augmente le d�calage du nombre de ms �coul�es durant la pause
    _decalage += SDL_GetTicks() - _pause;
    _enPause = false;
}


bool Horloge::enPause() const {
    return _enPause;
}


uint32_t Horloge::temps() const {
    // Si on est en pause, on renvoit le temps lors de la mise en pause moins le d�calage
    // Sinon, on renvoit simplement le nombre de ms �coul�es moins le d�calage
    uint32_t tps = (_enPause) ? (_pause - _decalage) : (SDL_GetTicks() - _decalage);

    // On calcule le d�calage li� � la vitesse puis on retourne le temps
    return _changementVitesse + (tps - _changementVitesse)*_vitesse + _decalageVitesse;
}


void Horloge::setVitesse(int vitesse) {
    // Interpolation temporelle (afin de ne pas revenir en arri�re dans le temps quand on ralentit)
    if (vitesse < _vitesse) {
        uint32_t ancienT = _changementVitesse + (SDL_GetTicks() - _decalage - _changementVitesse)*_vitesse;
        uint32_t nouveauT = _changementVitesse + (SDL_GetTicks() - _decalage - _changementVitesse)*vitesse;
        _decalageVitesse += ancienT - nouveauT;
    }

    // Le temps en ms lors du changement de vitesse
    _changementVitesse = SDL_GetTicks() - _decalage;

    // Application du changement
    _vitesse = vitesse;
}

int Horloge::getVitesse() {
    return _vitesse;
}
