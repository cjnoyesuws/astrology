object NumDBMaintForm: TNumDBMaintForm
  Left = 195
  Top = 167
  Width = 696
  Height = 489
  ActiveControl = DBNavigator1
  Caption = 'Database Maintenance'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 64
    Width = 53
    Height = 13
    Caption = 'List Name: '
  end
  object Label2: TLabel
    Left = 48
    Top = 104
    Width = 47
    Height = 13
    Caption = 'Birth Date'
  end
  object Label3: TLabel
    Left = 48
    Top = 144
    Width = 58
    Height = 13
    Caption = 'Birth Name: '
  end
  object Label4: TLabel
    Left = 48
    Top = 168
    Width = 22
    Height = 13
    Caption = 'First:'
  end
  object Label5: TLabel
    Left = 232
    Top = 168
    Width = 37
    Height = 13
    Caption = 'Middle: '
  end
  object Label6: TLabel
    Left = 400
    Top = 168
    Width = 23
    Height = 13
    Caption = 'Last:'
  end
  object Label7: TLabel
    Left = 48
    Top = 208
    Width = 68
    Height = 13
    Caption = 'Current Name:'
  end
  object Label9: TLabel
    Left = 232
    Top = 232
    Width = 37
    Height = 13
    Caption = 'Middle: '
  end
  object Label10: TLabel
    Left = 400
    Top = 232
    Width = 23
    Height = 13
    Caption = 'Last:'
  end
  object Label11: TLabel
    Left = 48
    Top = 272
    Width = 82
    Height = 13
    Caption = 'Optional Name 1:'
  end
  object Label8: TLabel
    Left = 48
    Top = 232
    Width = 22
    Height = 13
    Caption = 'First:'
  end
  object Label12: TLabel
    Left = 48
    Top = 296
    Width = 22
    Height = 17
    Caption = 'First:'
  end
  object Label13: TLabel
    Left = 232
    Top = 296
    Width = 37
    Height = 13
    Caption = 'Middle: '
  end
  object Label14: TLabel
    Left = 400
    Top = 296
    Width = 23
    Height = 13
    Caption = 'Last:'
  end
  object Label15: TLabel
    Left = 48
    Top = 336
    Width = 82
    Height = 13
    Caption = 'Optional Name 2:'
  end
  object Label16: TLabel
    Left = 48
    Top = 360
    Width = 22
    Height = 13
    Caption = 'First:'
  end
  object Label17: TLabel
    Left = 232
    Top = 360
    Width = 37
    Height = 13
    Caption = 'Middle: '
  end
  object Label18: TLabel
    Left = 400
    Top = 360
    Width = 23
    Height = 13
    Caption = 'Last:'
  end
  object DBNavigator1: TDBNavigator
    Left = 40
    Top = 16
    Width = 240
    Height = 25
    DataSource = DmNumerow.SrcNumLst
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
  end
  object DBEdListName: TDBEdit
    Left = 120
    Top = 64
    Width = 257
    Height = 21
    DataField = 'ListName'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 1
  end
  object DBEdBirthDate: TDBEdit
    Left = 120
    Top = 104
    Width = 97
    Height = 21
    DataField = 'BirthDate'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 2
  end
  object DBCkbdtInclude: TDBCheckBox
    Left = 240
    Top = 104
    Width = 65
    Height = 17
    Caption = 'Include'
    DataField = 'BirthDateInclude'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 3
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object DBEdBirthFirst: TDBEdit
    Left = 80
    Top = 168
    Width = 145
    Height = 21
    DataField = 'BirthFirst'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 4
  end
  object DBEdBirthMid: TDBEdit
    Left = 272
    Top = 168
    Width = 121
    Height = 21
    DataField = 'BirthMiddle'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 5
  end
  object DBEdBirthLast: TDBEdit
    Left = 432
    Top = 168
    Width = 153
    Height = 21
    DataField = 'BirthLast'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 6
  end
  object DBCkBirthInclude: TDBCheckBox
    Left = 600
    Top = 168
    Width = 57
    Height = 17
    Caption = 'Include'
    DataField = 'BirthInclude'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 7
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object DBEdCurrFirst: TDBEdit
    Left = 80
    Top = 232
    Width = 145
    Height = 21
    DataField = 'CurrentFirst'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 8
  end
  object DBEdCurrMid: TDBEdit
    Left = 272
    Top = 232
    Width = 121
    Height = 21
    DataField = 'CurrentMiddle'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 9
  end
  object DBEdCurrLast: TDBEdit
    Left = 432
    Top = 232
    Width = 153
    Height = 21
    DataField = 'CurrentLast'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 10
  end
  object DBCkCurInc: TDBCheckBox
    Left = 600
    Top = 232
    Width = 57
    Height = 17
    Caption = 'Include'
    DataField = 'CurrentInclude'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 11
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object DBEdOpt1First: TDBEdit
    Left = 80
    Top = 296
    Width = 145
    Height = 21
    DataField = 'Opt1First'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 12
  end
  object DBEdOpt1Mid: TDBEdit
    Left = 272
    Top = 296
    Width = 121
    Height = 21
    DataField = 'Opt1Middle'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 13
  end
  object DbEdOpt1Last: TDBEdit
    Left = 432
    Top = 296
    Width = 153
    Height = 21
    DataField = 'Opt1Last'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 14
  end
  object DBCkOpt1Include: TDBCheckBox
    Left = 600
    Top = 296
    Width = 57
    Height = 17
    Caption = 'Include'
    DataField = 'Opt1Include'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 15
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object DBEdOpt2First: TDBEdit
    Left = 80
    Top = 360
    Width = 145
    Height = 21
    DataField = 'Opt2First'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 16
  end
  object DBEdOpt2Mid: TDBEdit
    Left = 272
    Top = 360
    Width = 121
    Height = 21
    DataField = 'Opt2Middle'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 17
  end
  object DBEdOpt2Last: TDBEdit
    Left = 432
    Top = 360
    Width = 153
    Height = 21
    DataField = 'Opt2Last'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 18
  end
  object DBCkOpt2Include: TDBCheckBox
    Left = 600
    Top = 360
    Width = 57
    Height = 17
    Caption = 'Include'
    DataField = 'Opt2Include'
    DataSource = DmNumerow.SrcNumLst
    TabOrder = 19
    ValueChecked = 'True'
    ValueUnchecked = 'False'
  end
  object OkBtn: TBitBtn
    Left = 48
    Top = 400
    Width = 97
    Height = 33
    TabOrder = 20
    Kind = bkOK
  end
  object CancelBtn: TBitBtn
    Left = 176
    Top = 400
    Width = 97
    Height = 33
    TabOrder = 21
    Kind = bkCancel
  end
end
