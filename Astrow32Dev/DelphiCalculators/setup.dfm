object CalcSetupForm: TCalcSetupForm
  Left = 0
  Top = 0
  BorderStyle = bsToolWindow
  Caption = 'Calculator Setup'
  ClientHeight = 236
  ClientWidth = 271
  Color = clGradientInactiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 32
    Width = 47
    Height = 13
    Caption = 'Longitude'
  end
  object Label2: TLabel
    Left = 32
    Top = 72
    Width = 39
    Height = 13
    Caption = 'Latitude'
  end
  object Label3: TLabel
    Left = 32
    Top = 112
    Width = 112
    Height = 13
    Caption = 'GMT Off Hours:Minutes'
  end
  object edtLong: TEdit
    Left = 96
    Top = 32
    Width = 121
    Height = 21
    CharCase = ecUpperCase
    TabOrder = 0
    Text = '70W25'
  end
  object edtLatitude: TEdit
    Left = 96
    Top = 72
    Width = 121
    Height = 21
    CharCase = ecUpperCase
    TabOrder = 1
    Text = '40N45'
  end
  object edtGmt: TEdit
    Left = 152
    Top = 112
    Width = 65
    Height = 21
    TabOrder = 2
    Text = '5:0'
  end
  object BitBtn1: TBitBtn
    Left = 32
    Top = 192
    Width = 75
    Height = 25
    TabOrder = 3
    OnClick = BitBtn1Click
    Kind = bkOK
  end
  object BitBtn2: TBitBtn
    Left = 136
    Top = 192
    Width = 75
    Height = 25
    TabOrder = 4
    OnClick = BitBtn2Click
    Kind = bkCancel
  end
  object ckMidnight: TCheckBox
    Left = 32
    Top = 144
    Width = 121
    Height = 17
    Alignment = taLeftJustify
    Caption = 'Midnight Ephemeris?'
    Checked = True
    State = cbChecked
    TabOrder = 5
  end
end
