#ifndef H_SPRITE
#define H_SPRITE

#include <SDL/SDL.h>
#include "Tuile.h"
#include "../Horloge.h"


class Sprite : public Tuile {
	private:
		unsigned int _delaiFrames;
		unsigned int _frame;
		uint32_t _debut;
		Horloge* _horloge;
		bool _inverse;

	public:
		Sprite(SDL_Surface*, Horloge*, int = 0, int = 1, bool = false);
		bool animFinie() const;
		void dessiner(SDL_Surface*, int = 0, int = 0);
};

#endif
