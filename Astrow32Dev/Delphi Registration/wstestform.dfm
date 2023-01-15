object Form1: TForm1
  Left = 324
  Top = 242
  Width = 657
  Height = 549
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 32
    Width = 42
    Height = 13
    Caption = 'Program:'
  end
  object Label2: TLabel
    Left = 248
    Top = 336
    Width = 30
    Height = 13
    Caption = 'Status'
  end
  object Label3: TLabel
    Left = 313
    Top = 336
    Width = 32
    Height = 13
    Caption = 'Label3'
  end
  object Label4: TLabel
    Left = 32
    Top = 368
    Width = 22
    Height = 13
    Caption = 'Start'
  end
  object Label5: TLabel
    Left = 88
    Top = 368
    Width = 32
    Height = 13
    Caption = 'Label5'
  end
  object Label6: TLabel
    Left = 248
    Top = 368
    Width = 19
    Height = 13
    Caption = 'End'
  end
  object Label7: TLabel
    Left = 312
    Top = 368
    Width = 32
    Height = 13
    Caption = 'Label7'
  end
  object Label8: TLabel
    Left = 32
    Top = 400
    Width = 30
    Height = 13
    Caption = 'Codes'
  end
  object Label9: TLabel
    Left = 88
    Top = 400
    Width = 32
    Height = 13
    Caption = 'Label9'
  end
  object Label10: TLabel
    Left = 32
    Top = 336
    Width = 12
    Height = 13
    Caption = 'Id '
  end
  object Label11: TLabel
    Left = 88
    Top = 336
    Width = 38
    Height = 13
    Caption = 'Label11'
  end
  object Label12: TLabel
    Left = 24
    Top = 72
    Width = 31
    Height = 13
    Caption = 'Name:'
  end
  object Label13: TLabel
    Left = 24
    Top = 120
    Width = 38
    Height = 13
    Caption = 'Address'
  end
  object Label14: TLabel
    Left = 32
    Top = 160
    Width = 44
    Height = 13
    Caption = 'Address2'
  end
  object Label15: TLabel
    Left = 32
    Top = 208
    Width = 17
    Height = 13
    Caption = 'City'
  end
  object Label16: TLabel
    Left = 240
    Top = 200
    Width = 25
    Height = 13
    Caption = 'State'
  end
  object Label17: TLabel
    Left = 392
    Top = 200
    Width = 15
    Height = 13
    Caption = 'Zip'
  end
  object Label18: TLabel
    Left = 32
    Top = 248
    Width = 36
    Height = 13
    Caption = 'Country'
  end
  object Label19: TLabel
    Left = 240
    Top = 248
    Width = 31
    Height = 13
    Caption = 'Phone'
  end
  object Label20: TLabel
    Left = 32
    Top = 288
    Width = 25
    Height = 13
    Caption = 'Email'
  end
  object edProgram: TEdit
    Left = 88
    Top = 32
    Width = 241
    Height = 21
    TabOrder = 0
    Text = 'edProgram'
  end
  object BitBtn1: TBitBtn
    Left = 16
    Top = 464
    Width = 97
    Height = 25
    Caption = 'Use Mac Addr'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button1: TButton
    Left = 136
    Top = 464
    Width = 75
    Height = 25
    Caption = 'Use Full'
    TabOrder = 2
    OnClick = BitBtn1Click
  end
  object edName: TEdit
    Left = 88
    Top = 72
    Width = 241
    Height = 21
    TabOrder = 3
    Text = 'edName'
  end
  object edAddress: TEdit
    Left = 88
    Top = 120
    Width = 241
    Height = 21
    TabOrder = 4
    Text = 'edAddress'
  end
  object EdAddress2: TEdit
    Left = 88
    Top = 160
    Width = 241
    Height = 21
    TabOrder = 5
    Text = 'EdAddress2'
  end
  object edCity: TEdit
    Left = 88
    Top = 200
    Width = 121
    Height = 21
    TabOrder = 6
    Text = 'edCity'
  end
  object edState: TEdit
    Left = 296
    Top = 200
    Width = 57
    Height = 21
    TabOrder = 7
    Text = 'edState'
  end
  object edZip: TEdit
    Left = 432
    Top = 200
    Width = 81
    Height = 21
    TabOrder = 8
    Text = 'edZip'
  end
  object edCountry: TEdit
    Left = 88
    Top = 248
    Width = 121
    Height = 21
    TabOrder = 9
    Text = 'edCountry'
  end
  object edPhone: TEdit
    Left = 296
    Top = 248
    Width = 121
    Height = 21
    TabOrder = 10
    Text = 'edPhone'
  end
  object edEmail: TEdit
    Left = 88
    Top = 288
    Width = 121
    Height = 21
    TabOrder = 11
    Text = 'edEmail'
  end
  object HTTPRIO1: THTTPRIO
    OnAfterExecute = HTTPRIO1AfterExecute
    OnBeforeExecute = HTTPRIO1BeforeExecute
    URL = 'http://localhost/cjnoyessw/RegCheckService.dll/'
    HTTPWebNode.Agent = 'Borland SOAP 1.1'
    HTTPWebNode.UserName = 'PTPUSA\chris.noyes'
    HTTPWebNode.Password = 'astrology2005'
    HTTPWebNode.UseUTF8InHeader = False
    HTTPWebNode.InvokeOptions = [soIgnoreInvalidCerts]
    Converter.Options = [soSendMultiRefObj, soTryAllSchema, soRootRefNodesToBody]
    Left = 240
    Top = 464
  end
end
