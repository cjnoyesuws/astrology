// GraFont.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraFont dialog

class CGraFont : public CDialog
{
// Construction
public:
	GraphicFonts *pgf;
	void SetGraphicFonts( GraphicFonts *p ) { pgf = p; }
	CGraFont(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraFont)
	enum { IDD = IDD_GRAFONT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraFont)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraFont)
	afx_msg void OnDatafnt();
	afx_msg void OnGlyphfnt();
	virtual void OnOK();
	afx_msg void OnHelp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
