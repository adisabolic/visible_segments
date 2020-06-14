//---------------------------------------------------------------------------

#ifndef ProjekatH
#define ProjekatH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "pomocna.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TImage *Slika;
	TEdit *EditKoordinate;
	TRadioButton *DodavanjeDuzi;
	TRadioButton *VidikTacka;
	TButton *Clear;
	void __fastcall SlikaMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall SlikaMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall ClearClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);

private:

	vector<Duz> duzi;
    vector<bool> vidljive;
    Tacka T;
	Tacka *pocetna_tacka_duzi; //za crtanje duzi, pamti se prethodni klik, nullptr ako ga nije bilo
    void vidikTackaDuzi();
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
