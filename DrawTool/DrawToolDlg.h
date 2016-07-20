
// DrawToolDlg.h : ͷ�ļ�
//

#pragma once

#include "stdafx.h"
#include <vector>


#include "DrawItemManagement.h"

// CDrawToolDlg �Ի���
class CDrawToolDlg : public CDialogEx
{
// ����
public:
	CDrawToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DRAWTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	//////////////////////////////////////////////////////////////////////////
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();


	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	//////////////////////////////////////////////////////////////////////////
	//�¼�����
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);


private:
	//////////////////////////////////////////////////////////////////////////
	//���ݽṹ
	RectF m_rcDragArea;
	int m_nSelectedDragRect;
	PointF m_ptDragStartPos;


	DrawItemManagement m_manager;

public:
	//////////////////////////////////////////////////////////////////////////
	//��ť�¼�
	afx_msg void OnBnClickedReload();
	afx_msg void OnBnClickedInputitem();

	void clearDrawMap();
	void CreateOutterFrame( RectF &rcClient );

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedTest();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
