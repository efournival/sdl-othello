#ifndef H_IMAGE
#define H_IMAGE

#include <SDL/SDL.h>


class Image {
	protected:
		SDL_Surface* _surface;
		SDL_Rect _destFrameRect;

	public:
		Image(SDL_Surface*);
		void libererSurface();
		virtual void dessiner(SDL_Surface*, int = 0, int = 0);
		virtual ~Image() {};
};

#endif
