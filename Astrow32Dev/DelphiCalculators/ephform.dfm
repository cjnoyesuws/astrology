object EphemForm: TEphemForm
  Left = 80
  Top = 114
  ActiveControl = dtpStart
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  Caption = 'Instant Ephemeris'
  ClientHeight = 573
  ClientWidth = 865
  Color = clGradientActiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clMenuText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = [fsBold]
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 24
    Width = 59
    Height = 13
    Caption = 'Start Date'
  end
  object Label2: TLabel
    Left = 16
    Top = 56
    Width = 92
    Height = 13
    Caption = 'Planet Positions'
  end
  object dtpStart: TDateTimePicker
    Left = 112
    Top = 24
    Width = 186
    Height = 21
    Date = 38597.537270000000000000
    Time = 38597.537270000000000000
    TabOrder = 0
    OnChange = dtpStartChange
  end
  object ckMidnightEphem: TCheckBox
    Left = 320
    Top = 24
    Width = 121
    Height = 17
    Caption = 'Midnight Ephemeris'
    Checked = True
    State = cbChecked
    TabOrder = 1
    OnClick = ckMidnightEphemClick
  end
  object sgPositions: TStringGrid
    Left = 16
    Top = 72
    Width = 825
    Height = 481
    ColCount = 13
    DefaultColWidth = 72
    FixedColor = clGradientInactiveCaption
    RowCount = 30
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
  object CustomizeDlg1: TCustomizeDlg
    StayOnTop = False
    Left = 768
    Top = 32
  end
end
