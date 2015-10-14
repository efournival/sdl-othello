#include "Image.h"


Image::Image(SDL_Surface* surface):
_surface(surface),
_destFrameRect() {
	SDL_SetColorKey(_surface, SDL_SRCCOLORKEY, SDL_MapRGB(_surface->format, 255, 0, 255));
}

void Image::libererSurface() {
	SDL_FreeSurface(_surface);
}

void Image::dessiner(SDL_Surface* destination, int x, int y) {
	_destFrameRect.x = x;
	_destFrameRect.y = y;
	SDL_BlitSurface(_surface, NULL, destination, &_destFrameRect);
}
