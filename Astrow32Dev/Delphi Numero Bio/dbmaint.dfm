object DbMaintForm: TDbMaintForm
  Left = 333
  Top = 211
  ActiveControl = DBNavigator1
  BorderStyle = bsToolWindow
  Caption = 'Database Maintenance'
  ClientHeight = 269
  ClientWidth = 287
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 80
    Width = 28
    Height = 13
    Caption = 'Name'
  end
  object Label2: TLabel
    Left = 24
    Top = 128
    Width = 50
    Height = 13
    Caption = 'Birth Date:'
  end
  object DBNavigator1: TDBNavigator
    Left = 24
    Top = 16
    Width = 240
    Height = 25
    DataSource = nameDataSource
    TabOrder = 0
  end
  object dbName: TDBEdit
    Left = 80
    Top = 80
    Width = 121
    Height = 21
    DataField = 'Name'
    DataSource = nameDataSource
    TabOrder = 1
  end
  object dbDate: TDBEdit
    Left = 80
    Top = 128
    Width = 121
    Height = 21
    DataField = 'BirthDate'
    DataSource = nameDataSource
    TabOrder = 2
  end
  object btnOk: TBitBtn
    Left = 24
    Top = 216
    Width = 75
    Height = 25
    TabOrder = 3
    Kind = bkOK
  end
  object btnCancel: TBitBtn
    Left = 112
    Top = 216
    Width = 81
    Height = 25
    TabOrder = 4
    Kind = bkCancel
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Password="";User ID=Admin;Data ' +
      'Source=C:\Documents and Settings\chris.noyes\My Documents\Astro ' +
      'For Windows\astrow.mdb;Mode=Share Deny None;Extended Properties=' +
      '"";Persist Security Info=True;Jet OLEDB:System database="";Jet O' +
      'LEDB:Registry Path="";Jet OLEDB:Database Password="";Jet OLEDB:E' +
      'ngine Type=5;Jet OLEDB:Database Locking Mode=1;Jet OLEDB:Global ' +
      'Partial Bulk Ops=2;Jet OLEDB:Global Bulk Transactions=1;Jet OLED' +
      'B:New Database Password="";Jet OLEDB:Create System Database=Fals' +
      'e;Jet OLEDB:Encrypt Database=False;Jet OLEDB:Don'#39't Copy Locale o' +
      'n Compact=False;Jet OLEDB:Compact Without Replica Repair=False;J' +
      'et OLEDB:SFP=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 88
    Top = 160
  end
  object nameDataSource: TDataSource
    DataSet = ADOTable1
    Left = 40
    Top = 160
  end
  object ADOTable1: TADOTable
    Connection = ADOConnection1
    CursorType = ctStatic
    TableDirect = True
    TableName = 'biorythms'
    Left = 128
    Top = 160
  end
end
