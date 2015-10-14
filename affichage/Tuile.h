#ifndef H_TUILE
#define H_TUILE

#include <SDL/SDL.h>
#include "Image.h"


class Tuile : public Image {
	protected:
		unsigned int _largeurFrame;
		unsigned int _nbFrames;
		SDL_Rect _sourceFrameRect;
		void dessinerSousImage(SDL_Surface*, int = 0);

	public:
		Tuile(SDL_Surface*, int);
		virtual void dessiner(SDL_Surface*, int = 0, int = 0, int = 0);
};

#endif
