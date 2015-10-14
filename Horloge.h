#ifndef H_HORLOGE
#define H_HORLOGE

#include <SDL/SDL.h>


class Horloge {
	private:
		uint32_t _pause;
		uint32_t _decalage;
		uint32_t _decalageVitesse;
		uint32_t _changementVitesse;
		int _vitesse;
		bool _enPause;

    public:
		Horloge();
		void pause();
		void reprendre();
		bool enPause() const;
		uint32_t temps() const;
		void setVitesse(int);
		int getVitesse();
};

#endif
