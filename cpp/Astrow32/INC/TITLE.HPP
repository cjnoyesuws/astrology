#ifndef _TITLE____HPP_
#define _TITLE____HPP_

class TitlePane:public zPane {
int reg;
public:
	TitlePane(zWindow *dad);
	virtual int draw(zDrawEvt *);
	virtual int size(zSizeEvt *);
	int kbhnd(zKeyEvt *e);
	virtual int mouseButtonDown( zMouseClickEvt *e );
	int &getReg() { return reg; }
	void wait(int wt);
	};

class TitleFrame:public zPopupFrame {
protected:
	TitlePane* image;
public:
	TitleFrame(zWindow *dad, int h);
	TitleFrame(zWindow *dad);
	~TitleFrame() { delete image;}
	void setFocus() { image->setFocus(); }
	};

#ifdef DEMO

class BegPane : public TitlePane {
int okKill;
public:
	BegPane( zWindow *dad );
	virtual int draw(zDrawEvt *);
	};

class BegFrame : public TitleFrame {
public:
	BegFrame(zWindow *dad);
	int getReg() { return image->getReg(); }
	};
#endif

#endif /* _TITLE____HPP_  */
