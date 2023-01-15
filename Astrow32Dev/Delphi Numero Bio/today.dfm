object TodayPlanForm: TTodayPlanForm
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  Caption = 'Today'#39's Planets'
  ClientHeight = 279
  ClientWidth = 387
  Color = clGradientActiveCaption
  DefaultMonitor = dmDesktop
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clAqua
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
    Left = 32
    Top = 32
    Width = 61
    Height = 13
    Caption = 'Ascendant'
  end
  object lblAscend: TLabel
    Left = 104
    Top = 30
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 32
    Top = 64
    Width = 23
    Height = 13
    Caption = 'Sun'
  end
  object Label3: TLabel
    Left = 32
    Top = 96
    Width = 32
    Height = 13
    Caption = 'Moon'
  end
  object Label4: TLabel
    Left = 32
    Top = 128
    Width = 46
    Height = 13
    Caption = 'Mercury'
  end
  object Label5: TLabel
    Left = 32
    Top = 160
    Width = 36
    Height = 13
    Caption = 'Venus'
  end
  object Label6: TLabel
    Left = 32
    Top = 192
    Width = 28
    Height = 13
    Caption = 'Mars'
  end
  object Label7: TLabel
    Left = 208
    Top = 32
    Width = 38
    Height = 13
    Caption = 'Saturn'
  end
  object Label8: TLabel
    Left = 208
    Top = 64
    Width = 41
    Height = 13
    Caption = 'Uranus'
  end
  object Label9: TLabel
    Left = 208
    Top = 96
    Width = 49
    Height = 13
    Caption = 'Neptune'
  end
  object Label10: TLabel
    Left = 208
    Top = 128
    Width = 30
    Height = 13
    Caption = 'Pluto'
  end
  object Label11: TLabel
    Left = 208
    Top = 160
    Width = 66
    Height = 13
    Caption = 'North Node'
  end
  object Label12: TLabel
    Left = 208
    Top = 192
    Width = 57
    Height = 13
    Caption = 'Med Coeli'
  end
  object Label13: TLabel
    Left = 32
    Top = 224
    Width = 39
    Height = 13
    Caption = 'Jupiter'
  end
  object Label14: TLabel
    Left = 208
    Top = 224
    Width = 86
    Height = 13
    Caption = 'Part of Fortune'
  end
  object lblSun: TLabel
    Left = 104
    Top = 62
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblMoon: TLabel
    Left = 104
    Top = 94
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblMercury: TLabel
    Left = 104
    Top = 126
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblVenus: TLabel
    Left = 104
    Top = 158
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblMars: TLabel
    Left = 104
    Top = 190
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblJupiter: TLabel
    Left = 104
    Top = 222
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblSaturn: TLabel
    Left = 280
    Top = 30
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblUranus: TLabel
    Left = 280
    Top = 62
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblNeptune: TLabel
    Left = 280
    Top = 94
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblPluto: TLabel
    Left = 280
    Top = 126
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblNode: TLabel
    Left = 280
    Top = 158
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblMedCoeli: TLabel
    Left = 280
    Top = 190
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object lblPartFort: TLabel
    Left = 304
    Top = 222
    Width = 5
    Height = 16
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
end
