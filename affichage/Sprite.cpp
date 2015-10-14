#include "Sprite.h"


Sprite::Sprite(SDL_Surface* rendu, Horloge* horloge, int largeurFrame, int delaiFrames, bool inverse):
Tuile(rendu, largeurFrame),
_delaiFrames(delaiFrames),
_frame(0),
_debut(horloge->temps()),
_horloge(horloge),
_inverse(inverse) {}

bool Sprite::animFinie() const {
	return _frame >= _nbFrames;
}

void Sprite::dessiner(SDL_Surface* destination, int x, int y) {
	_destFrameRect.x = x;
	_destFrameRect.y = y;
	_frame = (_horloge->temps() - _debut) / _delaiFrames;
	_frame = (_frame >= _nbFrames) ? _nbFrames : _frame;
	dessinerSousImage(destination, (_inverse) ? _nbFrames - _frame : _frame);
}
