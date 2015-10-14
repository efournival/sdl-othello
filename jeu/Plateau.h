#ifndef H_PLATEAU
#define H_PLATEAU


const int MAX = 8;
const char B = 2;
const char N = 1;
const char X = '.';

class Plateau {
	private:
		char _pions[MAX][MAX] = {{X,X,X,X,X,X,X,X},
								 {X,X,X,X,X,X,X,X},
								 {X,X,X,X,X,X,X,X},
								 {X,X,X,B,N,X,X,X},
								 {X,X,X,N,B,X,X,X},
								 {X,X,X,X,X,X,X,X},
								 {X,X,X,X,X,X,X,X},
								 {X,X,X,X,X,X,X,X}};

	public:
		char getPion(int, int) const;
		void setPion(int, int, char);
};

#endif
