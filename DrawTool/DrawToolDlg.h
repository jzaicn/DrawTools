
// DrawToolDlg.h : 头文件
//

#pragma once

#include <vector>
#include "UI/SkinButton.h"

// CDrawToolDlg 对话框
class CDrawToolDlg : public CDialogEx
{
// 构造
public:
	CDrawToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DRAWTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

	//////////////////////////////////////////////////////////////////////////
	//数据结构
private:
	CRect m_rcDragArea;
	std::vector<CSkinButton*> m_vpDragableRect;
	int m_nSelectedDragRect;
	CPoint m_ptDragStartPos;

public:
	afx_msg void OnBnClickedReload();
	afx_msg void OnBnClickedInputitem();
};
