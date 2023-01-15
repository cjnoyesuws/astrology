object RegDm: TRegDm
  OldCreateOrder = False
  OnCreate = DataModuleCreate
  Left = 206
  Top = 246
  Height = 150
  Width = 923
  object dbCjnoyessw: TDatabase
    AliasName = 'testmysql'
    DatabaseName = 'cjnoyesswdb'
    LoginPrompt = False
    Params.Strings = (
      'USER NAME=cjnoyesuser'
      'PASSWORD=astrowwin32')
    SessionName = 'Default'
    Left = 408
    Top = 40
  end
  object qryAnon: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      
        'select counter from anonsharewareusr where computer_name=:co and' +
        ' mac_addr=:mac and program=:prog')
    Left = 488
    Top = 56
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'co'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'mac'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'prog'
        ParamType = ptUnknown
      end>
  end
  object qryAnonInsert: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      
        'insert into anonsharewareusr(computer_name, mac_addr,program,dat' +
        'e_start,days)'
      'values(:cn,:ma,:prog,:dtst,'#39'30'#39')')
    Left = 552
    Top = 72
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cn'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ma'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'prog'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'dtst'
        ParamType = ptUnknown
      end>
  end
  object qryDownload: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      
        'select counter from downloadcontacts where name=:nam and city=:c' +
        'it and'
      
        '   country=:cou and (state is null or state = :sta) and address=' +
        ':ad1 and'
      
        '  (address2 is null or address2 = :ad2) and (telephone is null o' +
        'r telephone=:tel) and'
      '  (email is null or email=:ema) and zip=:zip and program = prog')
    Left = 616
    Top = 72
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'nam'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cit'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cou'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'sta'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad1'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad2'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'tel'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ema'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'zip'
        ParamType = ptUnknown
      end>
  end
  object qryReg: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      
        'select counter from registereduser where name=:nam and city=:cit' +
        ' and'
      
        '   country=:cou and (state is null or state = :sta) and address=' +
        ':ad1 and'
      
        '  (address2 is null or address2 = :ad2) and (telephone is null o' +
        'r telephone=:tel) and'
      '  (email is null or email=:ema) and zip=:zip and program=:prog')
    Left = 680
    Top = 72
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'nam'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cit'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cou'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'sta'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad1'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad2'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'tel'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ema'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'zip'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'prog'
        ParamType = ptUnknown
      end>
  end
  object qryCounterAnon: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      'select * from anonsharewareusr where counter=:cnt')
    Left = 272
    Top = 32
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cnt'
        ParamType = ptUnknown
      end>
  end
  object qryCounterDload: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      'select * from downloadcontacts where counter=:cnt')
    Left = 488
    Top = 24
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cnt'
        ParamType = ptUnknown
      end>
  end
  object qryCounterReg: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      'select * from registereduser where counter=:cnt')
    Left = 576
    Top = 32
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cnt'
        ParamType = ptUnknown
      end>
  end
  object qryDloadInsert: TQuery
    DatabaseName = 'cjnoyesswdb'
    SQL.Strings = (
      
        'insert into downloadcontacts(program,name,address,address2,city,' +
        'state,'
      
        '   zip, country, telephone, email, date_start, days, may_contact' +
        ') '
      
        'values (:prog,:nam,:ad1,:ad2,:cit,:sta,:zip,:cou,:tel,:ema,:dst,' +
        #39'30'#39',:may)')
    Left = 664
    Top = 8
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'prog'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'nam'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad1'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ad2'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cit'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'sta'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'zip'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cou'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'tel'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'ema'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'dst'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'may'
        ParamType = ptUnknown
      end>
  end
end
