#ifndef   _NEWMULTDOCTMPL_
#define  _NEWMULTDOCTMPL_

// upgrade to CMultiDocTemplate. Adding a feature where we can open a document given a
// template and get both the document and the frame to handle it further.


class CNewMultiDocTemplate : public CMultiDocTemplate {
  
public:
	CNewMultiDocTemplate(UINT nIDResource, CRuntimeClass* pDocClass,
		  CRuntimeClass* pFrameClass, CRuntimeClass* pViewClass) : 
	          CMultiDocTemplate(nIDResource, pDocClass,	pFrameClass, pViewClass) {}
	~CNewMultiDocTemplate() {}
	CDocument* OpenDocumentFile(LPCTSTR lpszPathName,
	       BOOL bMakeVisible, CFrameWnd** pFrame);

};


#endif /* _NEWMULTDOCTMPL_ */
