#ifndef H_SEQUENCEUR
#define H_SEQUENCEUR

#include <SDL/SDL.h>


class Interface;

typedef bool(Interface::*seqCallback)();

class Sequenceur {
	private:
		unsigned int _delai;
		seqCallback _callback;
		Interface* _parent;

	public:
		Sequenceur(seqCallback, Interface*, int=60);
		void cycler();
};

#endif
