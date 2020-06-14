//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Projekat.h"
#include <algorithm>
#include <set>
#include <queue>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	pocetna_tacka_duzi = nullptr;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SlikaMouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y)
{
	EditKoordinate->Text = "( " + IntToStr(X) + " , " + IntToStr(Y) + " )";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(DodavanjeDuzi->Checked) {
        if(!pocetna_tacka_duzi) {
			pocetna_tacka_duzi = new Tacka(X,Y);
			pocetna_tacka_duzi->Crtaj(Slika);
		}
		else {
			Duz nova(*pocetna_tacka_duzi, Tacka(X,Y), duzi.size());
			duzi.push_back(nova);
            nova.Crtaj(Slika);
			pocetna_tacka_duzi = nullptr;
        }
	}
	else if(VidikTacka->Checked) {
		T = Tacka(X, Y);
        Slika->Canvas->Brush->Color = clGreen;
		T.Crtaj(Slika);
		Slika->Canvas->Brush->Color = clWhite;
        vidikTackaDuzi();
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ClearClick(TObject *Sender)
{
    Slika->Canvas->FillRect(Rect(0,0,Slika->Width,Slika->Height));
	duzi.clear();
    vidljive.clear();
}
//---------------------------------------------------------------------------
// algoritam radi na nacin da prvo sortira pocetne i krajnje tacke duzi po uglu koje grade sa horizontalnom pravom
// kroz datu tacku udesnu, a potom prolazi kroz pocetne i krajnje tacke duzi, te uvijek dodaje u vidljive
// onu duz koja je u tom trenutku prva vidljiva
void TForm1::vidikTackaDuzi() {

	int n(duzi.size());
	vidljive = vector<bool>(n, false);

    // sortiram po uglu sa horizontalnom polupravom iz tacke T udesno
	priority_queue<pair<Tacka, Duz*>, vector<pair<Tacka, Duz*>>, PoUglu> eventi(T);

	for(int i = 0 ; i < n ; i++) {
		eventi.push({duzi[i].pocetna, &duzi[i]});
		eventi.push({duzi[i].krajnja, &duzi[i]});
	}

	set<Duz*, PrijeSijece> aktivne(T);

	// dodajem one duzi koje horizontalna poluprava udesno sijece na pocetku u aktivne

	Duz horizontalna(T, Tacka(Slika->Width, T.y));
	for(int i = 0 ; i < n ; i++)
		if(DaLiPresjekDuzi(duzi[i], horizontalna))
			aktivne.insert(&duzi[i]);

	if(aktivne.size() != 0) {
		vidljive[(*aktivne.begin())->indeks] = true;
		(*aktivne.begin())->Crtaj(Slika);
	}

	Slika->Canvas->Brush->Color = clRed;
	Slika->Canvas->Pen->Color = clRed;
	while(!eventi.empty()) {
        // duz je vidljiva ako je nekad prva u aktivnim
		auto trenutni = eventi.top();
		eventi.pop();

		if(aktivne.find(trenutni.second) == aktivne.end()) {
			aktivne.insert(trenutni.second);
			vidljive[(*aktivne.begin())->indeks] = true;
			(*aktivne.begin())->Crtaj(Slika);
		}
		else {
			aktivne.erase(trenutni.second);
			if(!aktivne.empty()) {
				(*aktivne.begin())->Crtaj(Slika);
				vidljive[(*aktivne.begin())->indeks] = true;
			}
		}
	}
	Slika->Canvas->Brush->Color = clWhite;
	Slika->Canvas->Pen->Color = clBlack;
}
