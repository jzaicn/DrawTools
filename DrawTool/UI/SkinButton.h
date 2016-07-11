#pragma once
#include "atltypes.h"
//#include <GdiPlus.h>

//using namespace Gdiplus;
class CSkinButton :	public CRect
{
public:
	enum BUTTON_STATE{bs_Normal=0, bs_Down, bs_Disabled, bs_Hovered};
	CSkinButton(CString szCaption = _T(""), LPCRECT lprc = NULL, UINT nCtrlID = -1, DWORD dwStyle = BS_PUSHBUTTON, CWnd *pParent = NULL,  BUTTON_STATE bs = bs_Normal);
	~CSkinButton(void);

	

public:
	UINT GetCtrlID() {return m_nCtrlID;};
	BUTTON_STATE GetButtonState() { return m_nState; };
	void SetButtonState(BUTTON_STATE nState) ;
	void SetButtonCaption(CString szCaption) { m_szCaption = szCaption;};
	void SetDrawImage(Image *pNormal, Image *pDown = NULL, Image *pDisabled = NULL, Image *pImgHover = NULL);
	// Param OffsetSize, the offset relative to the parent
	void Draw(Graphics &g, CSize OffsetSize = CSize(0,0) ,CSize szOffsetText = CSize(0,0));
	void SetFont(Gdiplus::Font *pfont) {m_pfont = pfont;};
	void SetTextColor(Color *pcolor) { m_pcolor = pcolor;};
	void SetCaption(CString &szCaption ,BOOL bTransParent = FALSE){
		m_szCaption = szCaption;
		m_bTransParent = bTransParent;
	}
	void SetStringAlign(StringAlignment textAlign) { m_txtAlign = textAlign;};
	void SetButtonStyle(DWORD dwStyle) { btStyle = dwStyle;};
	void Invalidate();
protected:
	CString m_szCaption;
	BUTTON_STATE m_nState;
	Image *m_pImgNormal;
	Image *m_pImgDown;
	Image *m_pImgDisable;
	Image *m_pImgHover;
	UINT m_nCtrlID;
	Gdiplus::Font *m_pfont;
	Color *m_pcolor;
	CWnd *m_pParent;
	BOOL m_bTransParent;
	StringFormat format;	
	StringAlignment m_txtAlign;
	DWORD btStyle;
};

class CSkinPicture : public CRect
{
public:
	CSkinPicture(LPCRECT lprc = NULL, UINT nCtrlID = -1);
	~CSkinPicture(void);
public:
	void SetDrawImage(Image *pImage);
	void SetPosition(LPCRECT lprc) {CopyRect(lprc);};
	void Draw(Graphics &g, CSize OffsetSize = CSize(0,0));
protected:
	Image *m_pImage;
	UINT m_nCtrlID;
};

class CSkinPictureNoDraw :public CSkinPicture
{
public:
	void SetDrawImage(Image *pImage){
		m_pImage = NULL;
	};
protected:
private:
};

class CTitleMenu : public CRect
{
public:
	CTitleMenu(CString szTitle, LPCRECT lprc, UINT nCtrlID = -1, CWnd *pParent = NULL);
	~CTitleMenu();
	enum {tm_Normal=0, tm_Enter, tm_Down};
public:
	void Draw(CDC *pDC);
	void SetTitle(CString szTitle) { m_szTitle = szTitle; };
	void OnLButtonDown(UINT nFlags, CPoint point);
	void SetMenuState(UINT nState);
	const CString &GetTitleR(void);
protected:
	CString m_szTitle;
	UINT m_nCtrlID;
	CWnd *m_pParent;
	UINT m_nState;
	CBrush brush;
	BOOL bPopup;
};

class CTranHyperLink : public CRect
{
public:
	CTranHyperLink(CString szTitile, LPCRECT lprc, UINT nCtrlID = -1, CWnd *pParent = NULL);
	CTranHyperLink(UINT nTitleID, LPCRECT lprc, UINT nCtrlID = -1, CWnd *pParent = NULL);
	~CTranHyperLink() {};
public:
	void Draw(Graphics &g, CSize OffsetSize = CSize(0,0));
	void SetTitle(CString szTitle) { m_szTitle = szTitle; };
	void OnLButtonUp(UINT nFlags, CPoint point);
	void SetState(UINT nState);
	UINT GetState() { return m_nState;};
	void SetFont(Gdiplus::Font *pNomalFont, Gdiplus::Font *pUnderlinefont) { m_pFont = pNomalFont; m_pufont = pUnderlinefont;};
	void SetColor(Color *pColor) { m_pColor = pColor;};
	void SetAlignText(StringAlignment textAlign) { m_txtAlign = textAlign; }
	//void Invalidate() ;
protected:

private:
	CString m_szTitle;
	UINT m_nCtrlID;
	CWnd *m_pParent;
	UINT m_nState;
	Gdiplus::Font *m_pFont; // Normal font
	Gdiplus::Font *m_pufont; // font with Underline
	Color *m_pColor;
	//BOOL m_bRfresh;
	RectF m_rcTitle;
	StringAlignment m_txtAlign;
};

