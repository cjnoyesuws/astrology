object DmNumerow: TDmNumerow
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 192
  Top = 166
  Height = 239
  Width = 275
  object ADONumeroConnect: TADOConnection
    Connected = True
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\Documents and Se' +
      'ttings\chris.noyes\My Documents\Astro For Windows\astrow.mdb;Per' +
      'sist Security Info=False'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 40
    Top = 32
  end
  object ADONumOne: TADOQuery
    Connection = ADONumeroConnect
    Parameters = <
      item
        Name = 'name'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      'select * from numerology where ListName=:name')
    Left = 120
    Top = 32
  end
  object ADONumLst: TADOQuery
    Active = True
    Connection = ADONumeroConnect
    CursorType = ctStatic
    Parameters = <>
    SQL.Strings = (
      'select * from numerology order by Listname, BirthDate')
    Left = 32
    Top = 88
  end
  object ADOChartOne: TADOQuery
    Active = True
    Connection = ADONumeroConnect
    CursorType = ctStatic
    Parameters = <
      item
        Name = 'filename'
        Attributes = [paNullable]
        DataType = ftFixedChar
        NumericScale = 255
        Precision = 255
        Size = 510
        Value = Null
      end>
    SQL.Strings = (
      
        'select * from FileList where filename=:filename and ListType='#39'NU' +
        'M'#39)
    Left = 120
    Top = 88
  end
  object ADOChartLst: TADOQuery
    Connection = ADONumeroConnect
    Parameters = <>
    SQL.Strings = (
      'select * from FileList where ListType='#39'NUM'#39)
    Left = 32
    Top = 144
  end
  object SrcNumOne: TDataSource
    DataSet = ADONumOne
    Left = 184
    Top = 40
  end
  object SrcNumLst: TDataSource
    DataSet = ADONumLst
    Left = 192
    Top = 104
  end
  object SrcChartOne: TDataSource
    DataSet = ADOChartOne
    Left = 120
    Top = 152
  end
  object SrcChartLst: TDataSource
    DataSet = ADOChartLst
    Left = 160
    Top = 152
  end
end
