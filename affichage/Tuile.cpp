#include "Tuile.h"


Tuile::Tuile(SDL_Surface* surface, int largeurFrame):
Image(surface),
_largeurFrame(largeurFrame),
_nbFrames(_surface->w / _largeurFrame - 1),
_sourceFrameRect() {
	_destFrameRect.w = _largeurFrame;
	_destFrameRect.h = _surface->h;
}

void Tuile::dessinerSousImage(SDL_Surface* destination, int indexImage) {
	_sourceFrameRect.x = indexImage * _largeurFrame;
	_sourceFrameRect.y = 0;
	_sourceFrameRect.w = _largeurFrame;
	_sourceFrameRect.h = _surface->h;
	SDL_BlitSurface(_surface, &_sourceFrameRect, destination, &_destFrameRect);
}

void Tuile::dessiner(SDL_Surface* destination, int frame, int x, int y) {
	_destFrameRect.x = x;
	_destFrameRect.y = y;
	dessinerSousImage(destination, frame);
}

