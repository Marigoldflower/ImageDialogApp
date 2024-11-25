﻿
// ImageDialogAppDlg.h: 헤더 파일
//

#pragma once


// CImageDialogAppDlg 대화 상자
class CImageDialogAppDlg : public CDialogEx
{
// 생성입니다.
public:
	CImageDialogAppDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

private:
	CImage m_Image;
	bool isMakeUIButtonTapped;
	int actionCount;
	int nCenterX;
	int nCenterY;
	bool isOpenButtonTapped;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEDIALOGAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDraw();
	afx_msg void OnBnClickedButtonAction();
	afx_msg void OnBnClickedButtonMakeui();
	void DrawCircle();
	void UpdateDisplay();
	afx_msg void OnBnClickedButtonOpen();
};