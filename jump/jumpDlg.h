
// jumpDlg.h : header file
//
#include <vector>
#pragma once
using std::vector;
typedef struct color{
	int R;
	int G;
	int B;
}Color;

typedef struct points{
	int x1;
	int x2;
	int y1;
	int y2;
}Points;

// CjumpDlg dialog
class CjumpDlg : public CDialogEx
{
// Construction
public:
	CjumpDlg(CWnd* pParent = NULL);	// standard constructor
	HANDLE m_pThread; 
	void GetImagePixel();
	vector<color>ImageColor;
	points m_ps;
	int style;
// Dialog Data
	enum { IDD = IDD_JUMP_DIALOG };

	protected:
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	CImage* ImageHandle();
	CString GetModlePath(CString filename);
	void mainloop();
public:
	void Ondraw(CjumpDlg* dlg);
	BOOL isNewBlock(int color);
	BOOL ColorFun(COLORREF color1, COLORREF color2, int diff);
	void GetImagePixel(CImage* screen);

// Implementation
protected:
	bool is_clicked;
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
