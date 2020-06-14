object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 559
  ClientWidth = 890
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 120
  TextHeight = 16
  object Slika: TImage
    Left = 16
    Top = 24
    Width = 722
    Height = 505
    OnMouseDown = SlikaMouseDown
    OnMouseMove = SlikaMouseMove
  end
  object EditKoordinate: TEdit
    Left = 753
    Top = 505
    Width = 121
    Height = 24
    TabOrder = 0
    Text = 'EditKoordinate'
  end
  object DodavanjeDuzi: TRadioButton
    Left = 761
    Top = 48
    Width = 113
    Height = 17
    Caption = 'Dodavanje duzi'
    TabOrder = 1
  end
  object VidikTacka: TRadioButton
    Left = 761
    Top = 88
    Width = 113
    Height = 17
    Caption = 'Vidik iz tacke'
    TabOrder = 2
  end
  object Clear: TButton
    Left = 761
    Top = 128
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 3
    OnClick = ClearClick
  end
end
