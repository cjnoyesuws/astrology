



class CAstrowCommandLineInfo : public CCommandLineInfo {
public:
	BOOL m_bQdt;
	
	CAstrowCommandLineInfo() { m_bQdt = FALSE; }

	virtual void ParseParam( LPCTSTR lpszParam, BOOL bFlag, BOOL bLast );
};

