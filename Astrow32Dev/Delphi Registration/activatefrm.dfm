object ActivateForm: TActivateForm
  Left = 192
  Top = 166
  Width = 467
  Height = 494
  Caption = 'Activate Program'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 32
    Top = 96
    Width = 34
    Height = 13
    Caption = 'Name: '
  end
  object Label2: TLabel
    Left = 32
    Top = 136
    Width = 41
    Height = 13
    Caption = 'Address:'
  end
  object Label3: TLabel
    Left = 32
    Top = 208
    Width = 20
    Height = 13
    Caption = 'City:'
  end
  object Label4: TLabel
    Left = 248
    Top = 208
    Width = 28
    Height = 13
    Caption = 'State:'
  end
  object Label5: TLabel
    Left = 32
    Top = 256
    Width = 57
    Height = 13
    Caption = 'PostalCode:'
  end
  object Label6: TLabel
    Left = 248
    Top = 256
    Width = 39
    Height = 13
    Caption = 'Country:'
  end
  object Label7: TLabel
    Left = 32
    Top = 304
    Width = 54
    Height = 13
    Caption = 'Telephone:'
  end
  object Label8: TLabel
    Left = 32
    Top = 344
    Width = 32
    Height = 13
    Caption = 'E-Mail:'
  end
  object lblActivateTitle: TLabel
    Left = 32
    Top = 16
    Width = 136
    Height = 16
    Caption = 'You Are Activating: '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblRegActivate: TLabel
    Left = 32
    Top = 48
    Width = 385
    Height = 13
    AutoSize = False
    Caption = 'lblRegActivate'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    Visible = False
  end
  object ckPrivate: TCheckBox
    Left = 32
    Top = 48
    Width = 385
    Height = 17
    Caption = 'I Do Not Wish to Provide This Information'
    TabOrder = 0
    OnClick = ckPrivateClick
  end
  object edName: TEdit
    Left = 96
    Top = 96
    Width = 321
    Height = 21
    MaxLength = 50
    TabOrder = 1
    OnEnter = edNameEnter
    OnExit = edNameExit
  end
  object edAddress: TEdit
    Left = 96
    Top = 136
    Width = 321
    Height = 21
    MaxLength = 50
    TabOrder = 2
    OnEnter = edNameEnter
    OnExit = edNameExit
  end
  object edAddress2: TEdit
    Left = 96
    Top = 168
    Width = 321
    Height = 21
    MaxLength = 50
    TabOrder = 3
  end
  object edCity: TEdit
    Left = 96
    Top = 208
    Width = 129
    Height = 21
    MaxLength = 25
    TabOrder = 4
    OnEnter = edNameEnter
    OnExit = edNameExit
  end
  object edState: TEdit
    Left = 296
    Top = 208
    Width = 121
    Height = 21
    MaxLength = 15
    TabOrder = 5
  end
  object edZip: TEdit
    Left = 96
    Top = 256
    Width = 121
    Height = 21
    MaxLength = 15
    TabOrder = 6
    OnEnter = edNameEnter
    OnExit = edNameExit
  end
  object edCountry: TEdit
    Left = 296
    Top = 256
    Width = 121
    Height = 21
    MaxLength = 15
    TabOrder = 7
    OnEnter = edNameEnter
    OnExit = edNameExit
  end
  object edTelephone: TEdit
    Left = 96
    Top = 304
    Width = 121
    Height = 21
    MaxLength = 15
    TabOrder = 8
  end
  object edEmail: TEdit
    Left = 96
    Top = 352
    Width = 225
    Height = 21
    MaxLength = 50
    TabOrder = 9
  end
  object btnOk: TBitBtn
    Left = 32
    Top = 400
    Width = 121
    Height = 33
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 10
    OnClick = btnOkClick
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
  object btnClose: TBitBtn
    Left = 184
    Top = 400
    Width = 105
    Height = 33
    TabOrder = 11
    OnClick = btnCloseClick
    Kind = bkCancel
  end
  object Rio1: THTTPRIO
    URL = 'http://localhost/cjnoyessw/RegCheckService.dll/'
    HTTPWebNode.Agent = 'Borland SOAP 1.1'
    HTTPWebNode.UseUTF8InHeader = False
    HTTPWebNode.InvokeOptions = [soIgnoreInvalidCerts]
    Converter.Options = [soSendMultiRefObj, soTryAllSchema, soRootRefNodesToBody]
    Left = 328
    Top = 400
  end
end
