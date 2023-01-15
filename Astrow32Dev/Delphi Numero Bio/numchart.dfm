object NumChartForm: TNumChartForm
  Left = 192
  Top = 166
  Width = 696
  Height = 511
  ActiveControl = PageControl1
  Caption = 'New Numero Chart '
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label5: TLabel
    Left = 32
    Top = 16
    Width = 32
    Height = 13
    Caption = 'Label5'
  end
  object PageControl1: TPageControl
    Left = 0
    Top = 0
    Width = 688
    Height = 416
    ActivePage = tsData
    Align = alClient
    TabIndex = 0
    TabOrder = 0
    object tsData: TTabSheet
      Caption = 'Chart Data'
      object Label6: TLabel
        Left = 16
        Top = 16
        Width = 50
        Height = 13
        Caption = 'List Name:'
      end
      object Label7: TLabel
        Left = 16
        Top = 64
        Width = 50
        Height = 13
        Caption = 'Birth Date:'
      end
      object Label8: TLabel
        Left = 16
        Top = 96
        Width = 73
        Height = 13
        Caption = 'Name at Birth:'
      end
      object Label9: TLabel
        Left = 16
        Top = 120
        Width = 22
        Height = 13
        Caption = 'First:'
      end
      object Label10: TLabel
        Left = 192
        Top = 120
        Width = 34
        Height = 13
        Caption = 'Middle:'
      end
      object Label11: TLabel
        Left = 392
        Top = 120
        Width = 23
        Height = 13
        Caption = 'Last:'
      end
      object Label12: TLabel
        Left = 16
        Top = 160
        Width = 68
        Height = 13
        Caption = 'Current Name:'
      end
      object Label13: TLabel
        Left = 16
        Top = 184
        Width = 22
        Height = 13
        Caption = 'First:'
      end
      object Label14: TLabel
        Left = 192
        Top = 184
        Width = 34
        Height = 13
        Caption = 'Middle:'
      end
      object Label15: TLabel
        Left = 392
        Top = 184
        Width = 23
        Height = 13
        Caption = 'Last:'
      end
      object Label16: TLabel
        Left = 16
        Top = 216
        Width = 82
        Height = 13
        Caption = 'Optional Name 1:'
      end
      object Label17: TLabel
        Left = 16
        Top = 256
        Width = 22
        Height = 13
        Caption = 'First:'
      end
      object Label18: TLabel
        Left = 192
        Top = 256
        Width = 34
        Height = 17
        Caption = 'Middle:'
      end
      object Label19: TLabel
        Left = 392
        Top = 256
        Width = 23
        Height = 13
        Caption = 'Last:'
      end
      object Label20: TLabel
        Left = 16
        Top = 304
        Width = 82
        Height = 13
        Caption = 'Optional Name 2:'
      end
      object Label21: TLabel
        Left = 16
        Top = 328
        Width = 22
        Height = 13
        Caption = 'First:'
      end
      object Label22: TLabel
        Left = 192
        Top = 328
        Width = 34
        Height = 13
        Caption = 'Middle:'
      end
      object Label23: TLabel
        Left = 384
        Top = 328
        Width = 23
        Height = 13
        Caption = 'Last:'
      end
      object DbLuCbListName: TDBLookupComboBox
        Left = 80
        Top = 16
        Width = 225
        Height = 21
        ListField = 'ListName'
        ListSource = DmNumerow.SrcNumLst
        TabOrder = 0
        OnDropDown = DbLuCbListNameDropDown
      end
      object edtListName: TEdit
        Left = 80
        Top = 16
        Width = 206
        Height = 21
        TabOrder = 1
      end
      object dtpBirth: TDateTimePicker
        Left = 80
        Top = 64
        Width = 186
        Height = 21
        CalAlignment = dtaLeft
        Date = 38609.7056909259
        Time = 38609.7056909259
        DateFormat = dfShort
        DateMode = dmComboBox
        Kind = dtkDate
        ParseInput = False
        TabOrder = 2
        OnChange = dtpBirthChange
      end
      object ckBirthInc: TCheckBox
        Left = 288
        Top = 64
        Width = 97
        Height = 17
        Caption = 'Include'
        TabOrder = 3
      end
      object edtBirthFirst: TEdit
        Left = 48
        Top = 120
        Width = 129
        Height = 21
        TabOrder = 4
        OnChange = edtBirthFirstChange
      end
      object edtBirthMiddle: TEdit
        Left = 232
        Top = 120
        Width = 145
        Height = 21
        TabOrder = 5
        OnChange = edtBirthFirstChange
      end
      object edtBirthLast: TEdit
        Left = 424
        Top = 120
        Width = 153
        Height = 21
        TabOrder = 6
        OnChange = edtBirthFirstChange
      end
      object ckBirthNameInclude: TCheckBox
        Left = 584
        Top = 120
        Width = 65
        Height = 17
        Caption = 'Include'
        TabOrder = 7
      end
      object edtCurFirst: TEdit
        Left = 48
        Top = 184
        Width = 129
        Height = 21
        TabOrder = 8
        OnChange = edtCurFirstChange
      end
      object edtCurMiddle: TEdit
        Left = 232
        Top = 184
        Width = 145
        Height = 21
        TabOrder = 9
        OnChange = edtCurFirstChange
      end
      object edtCurLast: TEdit
        Left = 424
        Top = 184
        Width = 153
        Height = 21
        TabOrder = 10
        OnChange = edtCurFirstChange
      end
      object ckCurInclude: TCheckBox
        Left = 584
        Top = 184
        Width = 65
        Height = 17
        Caption = 'Include'
        TabOrder = 11
      end
      object edOpt1First: TEdit
        Left = 48
        Top = 256
        Width = 129
        Height = 21
        TabOrder = 12
        OnChange = edOpt1FirstChange
      end
      object edOpt1Middle: TEdit
        Left = 232
        Top = 256
        Width = 145
        Height = 21
        TabOrder = 13
        OnChange = edOpt1FirstChange
      end
      object edtOpt1Last: TEdit
        Left = 424
        Top = 256
        Width = 153
        Height = 21
        TabOrder = 14
        OnChange = edOpt1FirstChange
      end
      object CheckBox2: TCheckBox
        Left = 584
        Top = 256
        Width = 65
        Height = 17
        Caption = 'Include'
        TabOrder = 15
      end
      object edtOpt2First: TEdit
        Left = 48
        Top = 328
        Width = 129
        Height = 21
        TabOrder = 16
        OnChange = edtOpt2FirstChange
      end
      object edtOpt2Middle: TEdit
        Left = 232
        Top = 328
        Width = 145
        Height = 21
        TabOrder = 17
        OnChange = edtOpt2FirstChange
      end
      object edtOpt2Last: TEdit
        Left = 416
        Top = 328
        Width = 153
        Height = 21
        TabOrder = 18
        OnChange = edtOpt2FirstChange
      end
      object edtOpt2Include: TCheckBox
        Left = 576
        Top = 328
        Width = 65
        Height = 17
        Caption = 'Include'
        TabOrder = 19
      end
    end
    object tsChart: TTabSheet
      Caption = 'Chart File Information'
      ImageIndex = 1
      object Label1: TLabel
        Left = 24
        Top = 24
        Width = 55
        Height = 13
        Caption = 'Chart Type:'
      end
      object Label2: TLabel
        Left = 24
        Top = 72
        Width = 76
        Height = 13
        Caption = 'Name On Chart:'
      end
      object Label3: TLabel
        Left = 24
        Top = 120
        Width = 80
        Height = 13
        Caption = 'Chart Comments:'
      end
      object Label4: TLabel
        Left = 24
        Top = 176
        Width = 50
        Height = 13
        Caption = 'File Name:'
      end
      object sbDialog: TSpeedButton
        Left = 376
        Top = 176
        Width = 23
        Height = 22
        Hint = 'Click Here to Select File Name'
        Caption = '...'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        OnClick = sbDialogClick
      end
      object CbChartType: TComboBox
        Left = 88
        Top = 24
        Width = 225
        Height = 21
        Hint = 'Select Report Type'
        ItemHeight = 13
        ItemIndex = 0
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Text = 'Full Personality Report'
        Items.Strings = (
          'Full Personality Report'
          'Personality Numbers Only'
          'Full Name Transits Report'
          'Name Transits Numbers Only ')
      end
      object edtChartName: TEdit
        Left = 120
        Top = 72
        Width = 249
        Height = 21
        Hint = 'This is the Name that will Appear in The List'
        TabOrder = 1
      end
      object edtChartComments: TEdit
        Left = 120
        Top = 120
        Width = 249
        Height = 21
        Hint = 'This is the Comment for the File'
        TabOrder = 2
      end
      object EdtFileName: TEdit
        Left = 120
        Top = 176
        Width = 249
        Height = 21
        Hint = 'This is the File Name of the Report'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
      end
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 416
    Width = 688
    Height = 61
    Align = alBottom
    TabOrder = 1
    object BtnOk: TBitBtn
      Left = 16
      Top = 8
      Width = 113
      Height = 41
      TabOrder = 0
      Kind = bkOK
    end
    object BitBtn1: TBitBtn
      Left = 144
      Top = 8
      Width = 105
      Height = 41
      TabOrder = 1
      Kind = bkCancel
    end
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.NRP'
    FileName = 'Numero.NRP'
    Filter = 'Numerology Reports|*.NRP'
    Left = 648
    Top = 216
  end
end
