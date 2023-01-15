object ExpImpForm: TExpImpForm
  Left = 707
  Top = 678
  Width = 567
  Height = 334
  Caption = 'Import Expert Databases'
  Color = clSkyBlue
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 32
    Width = 131
    Height = 13
    Caption = 'Expert Astrologer Directory: '
  end
  object Label2: TLabel
    Left = 32
    Top = 128
    Width = 41
    Height = 13
    Caption = 'Progress'
  end
  object edExpertDir: TEdit
    Left = 184
    Top = 32
    Width = 273
    Height = 21
    TabOrder = 0
    Text = 'C:\XASTROL\'
  end
  object btnSelect: TBitBtn
    Left = 472
    Top = 32
    Width = 49
    Height = 25
    Caption = 'Select'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    OnClick = btnSelectClick
  end
  object ckLocations: TCheckBox
    Left = 32
    Top = 80
    Width = 97
    Height = 17
    Caption = 'Import Locations'
    Checked = True
    State = cbChecked
    TabOrder = 2
  end
  object ckPeople: TCheckBox
    Left = 168
    Top = 80
    Width = 153
    Height = 17
    Caption = 'Import Births/People'
    Checked = True
    State = cbChecked
    TabOrder = 3
  end
  object ProgressBar1: TProgressBar
    Left = 32
    Top = 152
    Width = 489
    Height = 41
    Smooth = True
    Step = 1
    TabOrder = 4
  end
  object OkBtn: TBitBtn
    Left = 32
    Top = 224
    Width = 137
    Height = 41
    TabOrder = 5
    OnClick = OkBtnClick
    Kind = bkOK
  end
  object CancelBtn: TBitBtn
    Left = 184
    Top = 224
    Width = 113
    Height = 41
    TabOrder = 6
    OnClick = CancelBtnClick
    Kind = bkCancel
  end
  object OpenDialog1: TOpenDialog
    Left = 536
    Top = 40
  end
  object tblPeople: TTable
    DatabaseName = 'c:\XAstrol'
    TableName = 'PEOPLE.DB'
    TableType = ttParadox
    Left = 344
    Top = 224
  end
  object tblLocations: TTable
    DatabaseName = 'c:\XAstrol'
    TableName = 'LOCATION.DB'
    TableType = ttParadox
    Left = 384
    Top = 224
  end
  object ADOConnection1: TADOConnection
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 424
    Top = 224
  end
  object ADOLocQuery: TADOQuery
    Connection = ADOConnection1
    Parameters = <
      item
        Name = 'co'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'st'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'lo'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      
        'select * from locations where country=:co and State = :st and lo' +
        'cation =  :lo')
    Left = 464
    Top = 224
  end
  object ADOBirthQuery: TADOQuery
    Connection = ADOConnection1
    Parameters = <
      item
        Name = 'nam'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'bdt'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      'select * from births where Name = :nam and BirthDate = :bdt')
    Left = 504
    Top = 224
  end
  object ADOLocInsertQuery: TADOQuery
    Connection = ADOConnection1
    Parameters = <
      item
        Name = 'co'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'st'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'lo'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'lng'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'lat'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'tz'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'sc'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'hro'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end
      item
        Name = 'mno'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      
        'insert into locations (country,state,location,longitude,latitude' +
        ',timezone,specialcode,houroff,minoff)'
      'values(:co,:st,:lo,:lng,:lat,:tz,:sc,:hro,:mno)'
      '')
    Left = 544
    Top = 184
  end
  object ADOBirthInsertQuery: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 544
    Top = 224
  end
end
