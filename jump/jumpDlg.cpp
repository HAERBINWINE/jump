
// jumpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jump.h"
#include "jumpDlg.h"
#include "afxdialogex.h"
#include <cstdlib>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BOOL ColorFunc(COLORREF color1, COLORREF color2, int diff);
DWORD WINAPI  myThreadFunc(LPVOID lparam);
// CAboutDlg dialog used for App About

HANDLE mH_mutex=NULL;
BOOL SendCmd(CString csCMD);

BOOL SendCmd(CString csCMD)
{
	if (!csCMD)
	{
		return FALSE;
	}
	CString csTemp;
	csTemp.Format("cmd /c %s",csTemp);
	UINT U_ret=WinExec(csTemp,SW_HIDE);
	if (U_ret>31)
	{
		return FALSE;
	}
	return TRUE;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CjumpDlg dialog




CjumpDlg::CjumpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CjumpDlg::IDD, pParent)
{
	is_clicked=false;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CjumpDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	if(!CjumpDlg::PreCreateWindow(cs))
		return FALSE;
	cs.cx=1080/3+100;
	cs.cy=1920/3+100;
	cs.x=0;
	cs.y=0;
	return TRUE;
}

void CjumpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CjumpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CjumpDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CjumpDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CjumpDlg message handlers

BOOL CjumpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->MoveWindow(0,0,1080/2,1920/2);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CjumpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CjumpDlg::OnPaint()
{
	//system(" adb shell screencap //sdcard//screen.png");
	CString cmd;
	cmd.Format(" adb shell screencap //sdcard//screen.png");
	SendCmd(cmd);
	cmd.Format("adb pull //sdcard//screen.png");
	SendCmd(cmd);
	//system("adb pull //sdcard//screen.png");
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);

	CImage* screen=ImageHandle();
	screen->Draw(dc,rect);
	//GetImagePixel(screen);

	//int xxx = m_ps.x1 + 5;
	//int yyy = m_ps.y1 + 50;


	//CPen redpen;
	//redpen.CreatePen(PS_SOLID,5,RGB(255,0,0));
	//dc.SelectObject(redpen);
	//dc.Ellipse((xxx+10)/2,(yyy+10)/2,(xxx-10)/2,(yyy-10)/2);
	//DeleteObject(redpen);

	
	delete screen;
	screen=NULL;


	

	if (IsIconic())
	{
		 // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

void CjumpDlg::Ondraw(CjumpDlg* dlg)
{
	CString cmd;
	cmd.Format(" adb shell screencap -p //sdcard//screen.png");
	if (!SendCmd(cmd))
	{
		return;
	}


	//system(" adb shell screencap -p //sdcard//screen.png");
	//system("adb pull //sdcard//screen.png");
	cmd.Format(" adb pull //sdcard//screen.png");
	if (!SendCmd(cmd))
	{
		return;
	}
	CDC* dc=GetDC();
	CRect rect;
	GetClientRect(&rect);



	CImage* screen=ImageHandle();
	HDC hdc=dc->GetSafeHdc();
	screen->Draw(hdc,rect);
	
	GetImagePixel(screen);

	int xxx = m_ps.x1;
	int yyy = m_ps.y1;


	CPen redpen;
	redpen.CreatePen(PS_SOLID,5,RGB(255,0,0));
	SelectObject(hdc,redpen);
	Ellipse(hdc,(xxx+5)/2,(yyy+5)/2,(xxx-5)/2,(yyy-5)/2);
	DeleteObject(redpen);
	int iran=rand()%30;


	// �������
	int distance = sqrt(double((yyy - m_ps.y2)*(yyy - m_ps.y2) + 
		(xxx - m_ps.x2)*(xxx - m_ps.x2)));

	// ����ʱ��
	int time = 1.32 * distance;

	// ִ����Ծ
	char str[100];
	sprintf(str, "adb shell input swipe %d %d %d %d %d",450+iran*2,1200+iran,475+iran*3,1250+iran,time);
	if (!SendCmd(str))
	{
		return;
	}
	
	//system(str);
	Sleep(time+50);


	delete screen;
	screen=NULL;}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CjumpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CjumpDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

void CjumpDlg::mainloop()
{
	mH_mutex=CreateMutex(NULL,FALSE,NULL);
	//DWORD D_Err=GetLastError();


	m_pThread=CreateThread(NULL,0,myThreadFunc,this,0,NULL);
	if(NULL == m_pThread)
	{
		TRACE("�����µ��̳߳���\n");
		return;
	}
	CloseHandle(m_pThread);
}
void CjumpDlg::GetImagePixel(CImage* screen)
{
	//int bmpwidth=0;
	//int bmpheight=0;
	//ImageColor.empty();

	// 
	// BYTE ** sub_col = new BYTE *[bmpheight];
	// sub_col = new BYTE *[bmpheight];
	// for (int i =0; i<bmpwidth; i++)
	// {
	//	 sub_col[i] = new BYTE[(bmpwidth)*3];
	// }
	// COLORREF col;
	// for(int i=0; i<bmpheight;i++)
	// {
	//	 for(int j=0; j<bmpwidth;j++)
	//	 {
	//		 // ��ȡ��pixel��ɫ
	//		 col = screen->GetPixel(j,i);
	//		 color temcolor;
	//		 temcolor.R=GetRValue(col);
	//		 temcolor.G=GetGValue(col);
	//		 temcolor.B=GetBValue(col);
	//		    //GetPixel�����У���һ��������ʾ�У��ڶ���������ʾ�У�����
	//		 // ��ȡ��subpixel��ɫ����
	//		 ImageColor.push_back(temcolor);


	//	 }
	// }
	m_ps.x1=0;
	m_ps.y1=0;
	m_ps.x2=0;
	m_ps.y2=0;
	int bmp_width = 0;
	int bmp_height = 0;
	bmp_width = screen->GetWidth();  // ͼƬ���
	bmp_height = screen->GetHeight(); // ͼƬ�߶�

	// ������̬��ά����洢�����ַ�
	//BYTE ** sub_col = new BYTE *[bmp_height];
	//sub_col = new BYTE *[bmp_height];
	//for (int i =0; i<bmp_height; i++)
	//{
	//	sub_col[i] = new BYTE[(bmp_width)*3];
	//}

	COLORREF col;
	COLORREF colpre;
	bool isget_point=false;

	for (int i=1750;i>0;i--)
	{
		for (int j=bmp_width-1;j>0;j--)
		{
			col = screen->GetPixel(j,i);
			if (ColorFun(col,RGB(55, 60, 100), 10))
			{
				m_ps.x2=j;
				m_ps.y2=i;

				isget_point=true;
				break;
			}

		}
		if (isget_point)
		{

			isget_point=false;
			break;
		};
	}

	for(int i=410; i<1750;i++)
	{
		for(int j=((m_ps.x2<540)?m_ps.x2+70:10); j<((m_ps.x2<540)?bmp_width-100:m_ps.x2-70);j++)
		{
			// ��ȡ��pixel��ɫ
			col = screen->GetPixel(j,i);   //GetPixel�����У���һ��������ʾ�У��ڶ���������ʾ�У�����
			colpre=screen->GetPixel(j,i-1);
			if(ColorFunc(col,colpre,30))
			{

				m_ps.x1=j;
				m_ps.y1=i;
				isget_point=true;
				break;
			}
			// ��ȡ��subpixel��ɫ��
			
		}
		if (isget_point)
		{
			isget_point=false;
			break;
		}
	}
	for (int i=m_ps.y1+10;i<1750;i+=5)
	{
		if (m_ps.x1+(i+5-m_ps.y1)*1.732>=1080)
		{
			m_ps.y1=i-20;
			break;
		}
		else{
			col = screen->GetPixel(m_ps.x1+(i-m_ps.y1)*1.732,i);   //GetPixel�����У���һ��������ʾ�У��ڶ���������ʾ�У�����
			colpre=screen->GetPixel(m_ps.x1+(i+5-m_ps.y1)*1.732,i+5);
			
		}
		if(ColorFunc(col,colpre,30))
		
		{

			
			//m_ps.y1=(i+m_ps.y1)/2;
			m_ps.y1=i-20;
			break;
		}
	}

	}




CImage* CjumpDlg::ImageHandle()
{
	CImage* Screen=new CImage;
	CString filepath;
	filepath.Empty();
	CString filename;
	filename.Empty();
	filename=_T("screen.png");
	filepath=GetModlePath(filename);
	Screen->Load(filepath);
	//Screen.Draw(dc,ScreenRect);
	filename.Empty();
	filename=_T("screen.bmp");
	filepath=GetModlePath(filename);
	Screen->Save(filepath);
	delete Screen;
	Screen =NULL;
	return Screen;

}
CString CjumpDlg::GetModlePath(CString filename)
{
	CString szPath;
	szPath.Empty();
	char strpath[1024];
	GetModuleFileName(NULL,strpath,sizeof(strpath));
	char drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
	_splitpath_s(strpath, drive, dir, fname, ext);
	szPath.Format(_T("%s%s\\%s"), drive, dir, filename);
	return szPath;
}

void CjumpDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	if (is_clicked)
	{
		OnCancel();
		is_clicked=false;
	}
	else{
		mainloop();
		is_clicked=true;
	}
	
}
BOOL CjumpDlg:: ColorFun(COLORREF color1, COLORREF color2, int diff)
{
	// ȡ������ɫ��R��G��Bֵ
	int r1 = GetRValue(color1);
	int g1 = GetGValue(color1);
	int b1 = GetBValue(color1);

	int r2 = GetRValue(color2);
	int g2 = GetGValue(color2);
	int b2 = GetBValue(color2);

	if (sqrt(double((r2-r1)*(r2-r1) + (g2-g1)*(g2-g1) + (b2-b1)*(b2-b1))) < diff)
	{
		return TRUE;
	}
	return FALSE;
}

 BOOL ColorFunc(COLORREF color1, COLORREF color2, int diff)
{
	// ȡ������ɫ��R��G��Bֵ
	int r1 = GetRValue(color1);
	int g1 = GetGValue(color1);
	int b1 = GetBValue(color1);

	int r2 = GetRValue(color2);
	int g2 = GetGValue(color2);
	int b2 = GetBValue(color2);

	if (sqrt(double((r2-r1)*(r2-r1) + (g2-g1)*(g2-g1) + (b2-b1)*(b2-b1))) >diff)
	{
		return TRUE;
	}
	return FALSE;
}
/*
sqrt(double((r2-r1)*(r2-r1) + (g2-g1)*(g2-g1) + (b2-b1)*(b2-b1))
��ɫ��R��G��B����ɫ��ɣ�������ɫֵԽ�ӽ�������R��G��BֵԽ�ӽ�
���ֻ�ɫ����ɫ���ƽ������ֵ�����������ɫ�����ƶȣ�ֵԽС��Խ����
�ú�����diff������Ϊ���ƶȣ������ֶ�ָ����ȷ����ɫ���Ƶĳ̶�
*/
//BOOL CjumpDlg::GetPixel()
//DWORD* pMem; //�����Դ�
//int x,y;
//int xy[800][700]; // ����img�����е����ص�
//
//pMem = GetImageBuffer(NULL); //��ȡ���ڵ��Դ�
//
//SetWorkingImage(&img);
//for (y = 0; y < 700; y++)
//	for (x = 0; x < 800; x++)
//		xy[x][y] = getpixel(x, y); // ��ȡ���ص�
//
//// ��ͼ... 
//
//cleardevice(); // �����Ļ
//// ������ͼ
//for (x = 0; x < 800; x++)
//{
//	for (y = 0; y < 700; y++)
//	{
//		int b = xy[x][y]&0xff; // ��ȡ��8λ
//		int g = (xy[x][y] >> 8) & 0xff; // ��8λȥ������ȡ��8λ
//		int r = xy[x][y] >> 16; // ȡ��16λ
//		pMem[y * 800 + x] = BGR(xy[x][y]);
//	}
//}
//FlushBatchDraw(); // ˢ�»��棬��ʾͼ��
//}

BOOL CjumpDlg::isNewBlock(int color)
{
	// colorΪ��img��ȡ��������
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (ColorFun(color, RGB(246, 246, 246), 10))//ǳ��ɫ
		{style=0;
	return TRUE;}
	else if (ColorFun(color, RGB(250, 250, 250), 10))
		{style=1;
	return TRUE;}
	else if (ColorFun(color, RGB(255, 255, 255), 0))//����ɫ
		{style=2;
	return TRUE;}
	else if (ColorFun(color, RGB(100, 148, 106), 20))//ī��ɫ
		{style=3;
	return TRUE;}
	else if (ColorFun(color, RGB(113, 113, 113), 10))//���ɫ
		{style=4;
	return TRUE;}
	else if (ColorFun(color, RGB(245, 128, 58), 10))//��ɫ
		{style=5;
	return TRUE;}
	else if (ColorFun(color, RGB(186, 239, 69), 10))//ǳ��ɫ
		{style=6;
	return TRUE;}
	else if (ColorFun(color, RGB(234, 203, 174), 10))//ľ������
		{style=7;
	return TRUE;}
	else if (ColorFun(color, RGB(254, 240, 89), 10))//��ɫ
		{style=8;
	return TRUE;}
	else if (r > 124 && r < 134 && g>111 && g < 121 && b > 219 && b < 229)//��ɫ���
		{style=9;
	return TRUE;}
	else if (r > 75 && r < 85 && g>158 && g < 165 && b > 85 && b < 95)//��Բ������
		{style=10;
	return TRUE;}
	else if (ColorFun(color, RGB(254, 74, 83), 10))//��ɫ
		{style=11;
	return TRUE;}
	else if (ColorFun(color, RGB(152, 114, 111), 10))//����ʯ
		{style=12;
	return TRUE;}
	else if (ColorFun(color, RGB(117, 117, 117), 10))//��Ͱ
		{style=13;
	return TRUE;}
	else if (ColorFun(color, RGB(225, 199, 142), 10))
		{style=14;
	return TRUE;}
	else if (ColorFun(color, RGB(241, 241, 241), 10))//�鱾
		{style=15;
	return TRUE;}
	else if (ColorFun(color, RGB(255, 172, 178), 10))//��ɫ����
		{style=16;
	return TRUE;}
	else if (ColorFun(color, RGB(73, 73, 73), 3))//�̲豭��
		{style=17;
	return TRUE;}
	else if (ColorFun(color, RGB(147, 147, 147), 10))//���Ƴ�Ƭ��
		{style=18;
	return TRUE;}
	return FALSE;
}

DWORD WINAPI myThreadFunc(LPVOID lparam)
{
	CjumpDlg* dlg=(CjumpDlg*)lparam;
	while (1)
	{
		WaitForSingleObject(mH_mutex,INFINITE);
		if (dlg==NULL)
		{
			return 0;
		}
		dlg->Ondraw(dlg);
		ReleaseMutex(mH_mutex);
	}
	return 1;

}