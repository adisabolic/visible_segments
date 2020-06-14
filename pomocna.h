//---------------------------------------------------------------------------

#ifndef pomocnaH
#define pomocnaH
#include <vector>
				#include <vcl.h>
                #include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
using namespace std;

struct Tacka {
	int x;
	int y;
	Tacka():x(0),y(0) {}
	Tacka(int X, int Y):x(X),y(Y) {}
    void Crtaj(TImage*) const;
};

bool operator==(Tacka,Tacka);
bool operator<(Tacka,Tacka);

struct Duz {
	Tacka pocetna;
	Tacka krajnja;
	int indeks;
	Duz(Tacka A,Tacka B, int indeks = -1):pocetna(A), krajnja(B), indeks(indeks){
		if(krajnja < pocetna)
			swap(pocetna,krajnja);
	}
	void Crtaj(TImage*) const;
};

struct Trougao {
	Tacka A;
	Tacka B;
	Tacka C;
	Trougao(Tacka A, Tacka B, Tacka C):A(A),B(B),C(C) {}
	void Crtaj(TImage*) const;
};

bool DaLiPresjekDuzi(Duz, Duz);

int Orijentacija(Tacka,Tacka,Tacka);

bool daLiJeTackaUnutarTrougla(Tacka,Trougao);

class PoUglu {

	Tacka T;

public:
	PoUglu(Tacka T): T(T) {}
	bool operator()(const pair<Tacka, Duz*> &prva, const pair<Tacka, Duz*> &druga) const {
		// ako su duzi sa suprotne strane poluprave, ona koja je gore dolazi prije, inace
		// ako su sa iste strane, odredjujem pomocu orijentacije koja gradi manji ugao

		if(prva.first.y <= T.y) {
			if(druga.first.y <= T.y)
				return Orijentacija(T, prva.first, druga.first) < 0;
			else
				return false;
		}
		else {
			if(druga.first.y <= T.y)
				return true;
			else
				return Orijentacija(T, prva.first, druga.first) < 0;
		}
	}
};

class PrijeSijece {

	Tacka T;

public:
	PrijeSijece(Tacka T): T(T) {}
	bool operator()(const Duz* prva, const Duz* druga) const {
		// ako su iste duzi
		if(prva == druga)
			return false;
		// ako neka duz iz T sa nekom od krajnjih tacaka prve ili druge duzi
		// sijece onu drugu, to znaci da se ta druga vidi prije,
		// a ukoliko to ne vrijedi, to znaci da je druga duz ili unutar trougla
		// kojeg gradi prva duz sa T (u tom slucaju se ona prije vidi), ili je van
		// tog trougla (u tom slucaju se prva duz prije vidi)

		if(DaLiPresjekDuzi(Duz(T, prva->pocetna), *druga) ||
			DaLiPresjekDuzi(Duz(T, prva->krajnja), *druga))
			return false;
		if(DaLiPresjekDuzi(Duz(T, druga->pocetna), *prva) ||
			DaLiPresjekDuzi(Duz(T, druga->krajnja), *prva))
			return true;

        Trougao t(T, prva->pocetna, prva->krajnja);
		return !daLiJeTackaUnutarTrougla(druga->pocetna, t);
	}
};

//---------------------------------------------------------------------------
#endif

