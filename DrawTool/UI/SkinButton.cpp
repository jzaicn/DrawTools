#include "StdAfx.h"
#include "SkinButton.h"

CSkinButton::CSkinButton(CString szCaption, LPCRECT lprc, UINT nCtrlID, DWORD dwStyle, CWnd *pParent, BUTTON_STATE bs)
	: m_pParent(pParent),
	btStyle(-1)
{
	m_szCaption = szCaption;
	m_pImgNormal = m_pImgDown = m_pImgDisable = m_pImgHover = NULL;
	if (lprc)
	{
		CopyRect(lprc);
	}
	m_nCtrlID = nCtrlID;
	m_nState = bs;
	m_pfont = NULL;
	m_pcolor = NULL;
	m_bTransParent = TRUE;
	m_txtAlign = StringAlignmentNear;
	btStyle = dwStyle;
}

CSkinButton::~CSkinButton(void)
{
}

void CSkinButton::Draw( Graphics &g, CSize OffsetSize /*= CSize(0,0)*/ ,CSize szOffsetText /*= CSize(0,0) */)
{
	RectF destRect(left, top, Width(), Height());
	destRect.Offset(OffsetSize.cx, OffsetSize.cy);

	switch (m_nState)
	{
	case bs_Normal:
		g.FillRectangle(&SolidBrush(Color::Blue), destRect);

		break;
	case bs_Down:
		{
			g.FillRectangle(&SolidBrush(Color::Red), destRect);
		}

		break;
	case bs_Disabled:
		g.FillRectangle(&SolidBrush(Color::Blue), destRect);
		break;
	case bs_Hovered:
		{
			g.FillRectangle(&SolidBrush(Color::PowderBlue), destRect);
		}
		break;
	}



	//RectF destRect(left, top, Width(), Height());
	//destRect.Offset(OffsetSize.cx, OffsetSize.cy);
	//if (/*m_nCtrlID == SC_CLOSE*/0)
	//{
	//	Color colorBkLeftTop;
	//	Color colorBkRightBottmp;
	//	ImageAttributes iab;
	//	Bitmap *pImg = (Bitmap *)m_pImgNormal;

	//	INT iW = pImg->GetWidth();
	//	INT iH = pImg->GetHeight();
	//	pImg->GetPixel(1,1,&colorBkLeftTop);
	//	pImg->GetPixel(iW -1,iH -1 ,&colorBkRightBottmp);
	//	iab.SetColorKey(Color(200,200,200) ,Color(222,222,225) ,ColorAdjustTypeBitmap);
	//	switch (m_nState)
	//	{
	//	case bs_Normal:
	//		m_pImgNormal?g.DrawImage(m_pImgNormal,destRect,0,0,iW,iH ,UnitPixel ,&iab):NULL;
	//		break;
	//	case bs_Down:
	//		m_pImgDown?g.DrawImage(m_pImgDown,destRect,0,0,iW,iH ,UnitPixel ,&iab):NULL;
	//		break;
	//	case bs_Disabled:
	//		m_pImgNormal?g.DrawImage(m_pImgDisable ? m_pImgDisable : m_pImgNormal,destRect,0,0,iW,iH ,UnitPixel ,&iab):NULL;
	//		break;
	//	case bs_Hovered:
	//		m_pImgNormal?g.DrawImage(m_pImgHover ? m_pImgHover : m_pImgNormal,destRect,0,0,iW,iH ,UnitPixel ,&iab):NULL;
	//		break;
	//	}


	//}else
	//{
	//	//RectF rfImg(destRect.X+(destRect.Width-m_pImgNormal->GetWidth())/2, destRect.GetTop(), m_pImgNormal->GetWidth(), m_pImgNormal->GetHeight());
	//	RectF rfImg(destRect.X+1, destRect.GetTop(), destRect.Width-2, m_pImgNormal->GetHeight()*(destRect.Width-2)/m_pImgNormal->GetWidth());
	//	switch (m_nState)
	//	{
	//	case bs_Normal:
	//		m_pImgNormal?g.DrawImage(m_pImgNormal, rfImg):NULL;
	//		break;
	//	case bs_Down:
	//		{
	//			g.FillRectangle(&SolidBrush(Color(153,204,255)), destRect);
	//			g.DrawRectangle(&Pen(Color(51,153,255)), destRect.X, destRect.Y, destRect.Width-1, destRect.Height-1);
	//			m_pImgDown?g.DrawImage(m_pImgDown, rfImg):g.DrawImage(m_pImgNormal, rfImg);
	//		}
	//		
	//		break;
	//	case bs_Disabled:
	//		m_pImgNormal?g.DrawImage(m_pImgDisable ? m_pImgDisable : m_pImgNormal, rfImg):NULL;
	//		break;
	//	case bs_Hovered:
	//		{
	//			g.FillRectangle(&SolidBrush(Color(194,224,255)), destRect);
	//			g.DrawRectangle(&Pen(Color(51,153,255)), destRect.X, destRect.Y, destRect.Width-1, destRect.Height-1);
	//			m_pImgNormal?g.DrawImage(m_pImgHover ? m_pImgHover : m_pImgNormal, rfImg):NULL;
	//		}
	//		break;
	//	}
	//}
	//

	//if (m_szCaption.GetLength()){

	//	Gdiplus::Font myFont(_T("Î¢ÈíÑÅºÚ"), 13, FontStyleRegular,UnitPixel);	
	//	//format.SetAlignment(m_txtAlign);	
	//	format.SetAlignment(StringAlignmentCenter);
	//	format.SetTrimming(StringTrimmingWord);
	//	SolidBrush blackBrush(Color(255, 0, 0, 0));
	//	if (m_pcolor)
	//		blackBrush.SetColor(*m_pcolor);
	//	int TextHeight = myFont.GetHeight(&g);
	//	if (m_pfont)
	//		TextHeight = m_pfont->GetHeight(&g);

	//	RectF rcCaption;
	//	g.MeasureString(m_szCaption ,m_szCaption.GetLength() ,(m_pfont ?m_pfont:&myFont) , PointF(destRect.X, destRect.Y) \
	//		,&format ,&rcCaption);

	//	//RectF layoutRect(destRect.X, destRect.Y + (Height()-TextHeight)/2, destRect.Width, TextHeight);
	//	//RectF layoutRect(destRect.X, destRect.Y + m_pImgNormal->GetHeight(), destRect.Width, destRect.Height - m_pImgNormal->GetHeight());
	//	RectF layoutRect(destRect.X, destRect.GetBottom() - rcCaption.Height+3, destRect.Width, rcCaption.Height);

	//	if (BS_CHECKBOX == btStyle)
	//	{
	//		szOffsetText += (CSize(Width() ,0) + OffsetSize);
	//		layoutRect.Width += rcCaption.Width;
	//		layoutRect.Offset(szOffsetText.cx, szOffsetText.cy);
	//		format.SetTrimming(StringTrimmingNone);
	//	}else if (BS_PUSHBUTTON == btStyle && bs_Down == m_nState) // text go down 1 pixel
	//		/*layoutRect.Y += 1*/;

	//	HDC dc = g.GetHDC();
	//	COLORREF colR = ::GetBkColor(g.GetHDC());
	//	Color colorBg;
	//	if (m_nState == bs_Disabled){
	//		blackBrush.SetColor(Color::Gray);
	//	}
	//	SolidBrush brush(colR);
	//	g.ReleaseHDC(dc);
	//	
	//	if (!m_bTransParent)
	//		g.FillRectangle(&brush ,layoutRect);

	//	if (BS_CHECKBOX == btStyle){
	//		g.DrawString(m_szCaption, m_szCaption.GetLength(), (m_pfont ? m_pfont : &myFont), PointF(layoutRect.GetLeft() ,layoutRect.GetTop()), &format,&blackBrush);
	//	}else
	//		g.DrawString(m_szCaption, m_szCaption.GetLength(), (m_pfont ? m_pfont : &myFont), layoutRect, &format,&blackBrush);

	//	
	//}
}

void CSkinButton::SetDrawImage( Image *pNormal, Image *pDown /*= NULL*/, Image *pDisabled /*= NULL*/, Image *pImgHover /*= NULL*/ )
{
	m_pImgNormal = pNormal;
	m_pImgDown = pDown;
	m_pImgDisable = pDisabled;
	m_pImgHover = pImgHover;
}

void CSkinButton::SetButtonState( BUTTON_STATE nState)
{	
	BOOL bErase = FALSE;
	if (m_nState != nState)
		bErase = TRUE;
	m_nState = nState ;
	if (m_pParent && bErase)
		m_pParent->InvalidateRect(this);
}

void CSkinButton::Invalidate()
{
	if (m_pParent)
		m_pParent->InvalidateRect(this, TRUE);
}
// clas CSkinPicture
CSkinPicture::CSkinPicture( LPCRECT lprc /*= NULL*/, UINT nCtrlID /*= -1*/ )
{
	m_pImage = NULL;
	if (lprc)
		CopyRect(lprc);
	m_nCtrlID = nCtrlID;
}

CSkinPicture::~CSkinPicture( void )
{

}

void CSkinPicture::Draw( Graphics &g, CSize OffsetSize /*= CSize(0,0)*/ )
{
	if (!m_pImage) return;
	RectF rc(left, top, Width(), Height());
	rc.Offset(OffsetSize.cx, OffsetSize.cy);
	if (m_pImage)
		g.DrawImage(m_pImage, rc);
}

void CSkinPicture::SetDrawImage( Image *pImage )
{
	m_pImage = pImage;
}

// CMenuTitle
CTitleMenu::CTitleMenu( CString szTitle, LPCRECT lprc, UINT nCtrlID /*= -1*/, CWnd *pParent /*= NULL*/ )
	:m_nCtrlID(nCtrlID),
	m_pParent(pParent),
	m_szTitle(szTitle),
	bPopup(FALSE)
{
	CopyRect(lprc);
	m_nState = tm_Normal;
	brush.CreateSolidBrush(RGB(244,244,244));
}

CTitleMenu::~CTitleMenu()
{
	brush.DeleteObject();
}

void CTitleMenu::Draw( CDC *pDC )
{
	if (!m_pParent)
		return;
	CFont *pfont = m_pParent->GetFont();
	CFont *poldfont = pDC->SelectObject(pfont);

	//CBrush *poldbrush = NULL;

	if (tm_Normal == m_nState)
	{
		//pDC->FillRect(this, &brush);
	}else if (tm_Enter == m_nState)
	{
		pDC->DrawFocusRect(this);
		CRect rc(this);
		rc.InflateRect(-1,-1);
		CBrush br;
		br.CreateSolidBrush(RGB(182,189,210));
		pDC->FillRect(rc, &br);
		br.DeleteObject();
	}else if (tm_Down == m_nState)
	{
		pDC->DrawFocusRect(this);
		CRect rc(this);
		rc.InflateRect(-1,-1);
		CBrush br;
		br.CreateSolidBrush(RGB(241,239,237));
		pDC->FillRect(rc, &br);
		br.DeleteObject();
	}


	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(m_szTitle, m_szTitle.GetLength(), this, DT_CENTER | DT_VCENTER);
	pDC->SelectObject(poldfont);
}

void CTitleMenu::OnLButtonDown( UINT nFlags, CPoint point )
{
	SetMenuState(tm_Down);
	PostMessage(m_pParent->m_hWnd, WM_COMMAND, MAKEWPARAM(m_nCtrlID, 0), 0);
}

void CTitleMenu::SetMenuState( UINT nState )
{
	if (m_nState == nState)
		return;
	m_nState = nState;
	m_pParent->InvalidateRect(this);
}

const CString & CTitleMenu::GetTitleR( void )
{
	return m_szTitle;
}
// class CTranHyperLink
CTranHyperLink::CTranHyperLink( CString szTitile, LPCRECT lprc, UINT nCtrlID /*= -1*/, CWnd *pParent /*= NULL*/ )	
	:m_szTitle(szTitile),
	m_nCtrlID(nCtrlID),
	m_pParent(pParent),	
	m_pFont(NULL),
	m_pufont(NULL),
	m_pColor(NULL),
	//m_bRfresh(FALSE),
	m_nState(CSkinButton::bs_Normal)
{
	CopyRect(lprc);
}

CTranHyperLink::CTranHyperLink( UINT nTitleID, LPCRECT lprc, UINT nCtrlID /*= -1*/, CWnd *pParent /*= NULL*/ )
	:m_nCtrlID(nCtrlID),
	m_pParent(pParent),	
	m_pFont(NULL),
	m_pufont(NULL),
	m_pColor(NULL),
	//m_bRfresh(FALSE),
	m_nState(CSkinButton::bs_Normal),
	m_txtAlign(StringAlignmentNear)
{
	CString szTitle;
	szTitle.LoadString(nTitleID);
	m_szTitle = szTitle;
	CopyRect(lprc);
}


void CTranHyperLink::Draw(Graphics &g, CSize OffsetSize/* = CSize(0,0) */)
{
	Gdiplus::Font font(_T("Verdana"), 9*96.0/72, FontStyleBold ,UnitPixel);
	Gdiplus::Font ufont(_T("Verdana"), 9*96.0/72, FontStyleUnderline | FontStyleBold ,UnitPixel);
	StringFormat format;
	format.SetAlignment(m_txtAlign);
	SolidBrush brush(Color(255, 0,0,255));
	brush.SetColor(m_pColor ? *m_pColor : Color(255, 0,0,255));
	
	OffsetRect(OffsetSize.cx, OffsetSize.cy);
	RectF rc(left, top, Width(), Height());
	g.MeasureString(m_szTitle, m_szTitle.GetLength(), &font, rc, &format, &m_rcTitle);
	//if (CSkinButton::bs_Normal == m_nState)
	//	g.DrawString(m_szTitle, -1, (m_pFont ? m_pFont : &font), rc, &format, &brush);
	//else if (CSkinButton::bs_Hovered == m_nState)
		g.DrawString(m_szTitle, -1, (m_pufont ? m_pufont : &ufont), rc, &format, &brush);
}

//void CTranHyperLink::Invalidate()
//{ 
//	if (m_bRfresh)
//	{
//		CRect rcTitle(m_rcTitle.X, m_rcTitle.Y, m_rcTitle.X + m_rcTitle.Width, m_rcTitle.Y + m_rcTitle.Height);
//
//		//m_pParent->InvalidateRect(rcTitle); 
//	}
//}
void CTranHyperLink::OnLButtonUp( UINT nFlags, CPoint point )
{
	if (m_pParent)
		m_pParent->PostMessage(WM_COMMAND, MAKEWPARAM(m_nCtrlID, 0), 0);
}

void CTranHyperLink::SetState( UINT nState )
{
	//if (m_nState != nState)
	//	m_bRfresh = TRUE;
	//else 
	//	m_bRfresh = FALSE;
	//m_nState = nState;

	BOOL bErase = FALSE;
	if (m_nState != nState)
		bErase = TRUE;
	m_nState = nState ;
	if (m_pParent && bErase)
		m_pParent->InvalidateRect(this);

}