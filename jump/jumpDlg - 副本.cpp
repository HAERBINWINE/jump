
// jumpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "jump.h"
#include "jumpDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BOOL ColorFunc(COLORREF color1, COLORREF color2, int diff);
UINT myThreadFunc(LPVOID lparam);
// CAboutDlg dialog used for App About

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
	system(" adb shell screencap //sdcard//screen.png");
	system("adb pull //sdcard//screen.png");
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
	system(" adb shell screencap -p //sdcard//screen.png");
	system("adb pull //sdcard//screen.png");
	
	CDC* dc=GetDC();
	CRect rect;
	GetClientRect(&rect);



	CImage* screen=ImageHandle();
	HDC hdc=dc->GetSafeHdc();
	screen->Draw(hdc,rect);
	
	GetImagePixel(screen);

	int xxx = m_ps.x1 + 10;
	int yyy = m_ps.y1 + 95;


	CPen redpen;
	redpen.CreatePen(PS_SOLID,5,RGB(255,0,0));
	SelectObject(hdc,redpen);
	Ellipse(hdc,(xxx+5)/2,(yyy+5)/2,(xxx-5)/2,(yyy-5)/2);
	DeleteObject(redpen);



	// 计算距离
	int distance = sqrt(double((yyy - m_ps.y2)*(yyy - m_ps.y2) + 
		(xxx - m_ps.x2)*(xxx - m_ps.x2)));

	// 计算时间
	int time = 1.35 * distance;

	// 执行跳跃
	char str[100];
	sprintf(str, "adb shell input swipe 200 300 205 305 %d",time);
	system(str);
	Sleep(500);


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
	m_pThread=AfxBeginThread(myThreadFunc,this,0,0,0,NULL);
	if(NULL == m_pThread)
	{
		TRACE("创建新的线程出错！\n");
		return;
	}
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
	//		 // 获取各pixel颜色
	//		 col = screen->GetPixel(j,i);
	//		 color temcolor;
	//		 temcolor.R=GetRValue(col);
	//		 temcolor.G=GetGValue(col);
	//		 temcolor.B=GetBValue(col);
	//		    //GetPixel函数中，第一个参数表示列，第二个参数表示行！！！
	//		 // 获取各subpixel颜色数据
	//		 ImageColor.push_back(temcolor);


	//	 }
	// }
	m_ps.x1=0;
	m_ps.y1=0;
	m_ps.x2=0;
	m_ps.y2=0;
	int bmp_width = 0;
	int bmp_height = 0;
	bmp_width = screen->GetWidth();  // 图片宽度
	bmp_height = screen->GetHeight(); // 图片高度

	// 创建动态二维数组存储各行字符
	BYTE ** sub_col = new BYTE *[bmp_height];
	sub_col = new BYTE *[bmp_height];
	for (int i =0; i<bmp_height; i++)
	{
		sub_col[i] = new BYTE[(bmp_width)*3];
	}

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
		for(int j=((m_ps.x2<500)?m_ps.x2+70:10); j<((m_ps.x2<500)?bmp_width-100:m_ps.x2-70);j++)
		{
			// 获取各pixel颜色
			col = screen->GetPixel(j,i);   //GetPixel函数中，第一个参数表示列，第二个参数表示行！！！
			colpre=screen->GetPixel(j,i-1);
			if(ColorFunc(col,colpre,30))
			{

				m_ps.x1=j;
				m_ps.y1=i;
				isget_point=true;
				break;
			}
			// 获取各subpixel颜色数
			
		}
		if (isget_point)
		{
			isget_point=false;
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
	// 取两种颜色的R、G、B值
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
	// 取两种颜色的R、G、B值
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
颜色由R、G、B三基色组成，两个颜色值越接近，则其R、G、B值越接近
三种基色的颜色差的平方根的值则代表两种颜色的相似度，值越小则越相似
该函数的diff参数即为相似度，可以手动指定来确定颜色相似的程度
*/
//BOOL CjumpDlg::GetPixel()
//DWORD* pMem; //窗口显存
//int x,y;
//int xy[800][700]; // 保存img中所有的像素点
//
//pMem = GetImageBuffer(NULL); //获取窗口的显存
//
//SetWorkingImage(&img);
//for (y = 0; y < 700; y++)
//	for (x = 0; x < 800; x++)
//		xy[x][y] = getpixel(x, y); // 获取像素点
//
//// 贴图... 
//
//cleardevice(); // 清除屏幕
//// 重新贴图
//for (x = 0; x < 800; x++)
//{
//	for (y = 0; y < 700; y++)
//	{
//		int b = xy[x][y]&0xff; // 获取低8位
//		int g = (xy[x][y] >> 8) & 0xff; // 低8位去掉，再取低8位
//		int r = xy[x][y] >> 16; // 取高16位
//		pMem[y * 800 + x] = BGR(xy[x][y]);
//	}
//}
//FlushBatchDraw(); // 刷新缓存，显示图形
//}

BOOL CjumpDlg::isNewBlock(int color)
{
	// color为在img中取到的像素
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (ColorFun(color, RGB(246, 246, 246), 10))//浅白色
		{style=0;
	return TRUE;}
	else if (ColorFun(color, RGB(250, 250, 250), 10))
		{style=1;
	return TRUE;}
	else if (ColorFun(color, RGB(255, 255, 255), 0))//纯白色
		{style=2;
	return TRUE;}
	else if (ColorFun(color, RGB(100, 148, 106), 20))//墨绿色
		{style=3;
	return TRUE;}
	else if (ColorFun(color, RGB(113, 113, 113), 10))//深灰色
		{style=4;
	return TRUE;}
	else if (ColorFun(color, RGB(245, 128, 58), 10))//橙色
		{style=5;
	return TRUE;}
	else if (ColorFun(color, RGB(186, 239, 69), 10))//浅绿色
		{style=6;
	return TRUE;}
	else if (ColorFun(color, RGB(234, 203, 174), 10))//木质桌子
		{style=7;
	return TRUE;}
	else if (ColorFun(color, RGB(254, 240, 89), 10))//黄色
		{style=8;
	return TRUE;}
	else if (r > 124 && r < 134 && g>111 && g < 121 && b > 219 && b < 229)//紫色相间
		{style=9;
	return TRUE;}
	else if (r > 75 && r < 85 && g>158 && g < 165 && b > 85 && b < 95)//大圆绿柱子
		{style=10;
	return TRUE;}
	else if (ColorFun(color, RGB(254, 74, 83), 10))//红色
		{style=11;
	return TRUE;}
	else if (ColorFun(color, RGB(152, 114, 111), 10))//华岩石
		{style=12;
	return TRUE;}
	else if (ColorFun(color, RGB(117, 117, 117), 10))//马桶
		{style=13;
	return TRUE;}
	else if (ColorFun(color, RGB(225, 199, 142), 10))
		{style=14;
	return TRUE;}
	else if (ColorFun(color, RGB(241, 241, 241), 10))//书本
		{style=15;
	return TRUE;}
	else if (ColorFun(color, RGB(255, 172, 178), 10))//粉色盒子
		{style=16;
	return TRUE;}
	else if (ColorFun(color, RGB(73, 73, 73), 3))//奶茶杯子
		{style=17;
	return TRUE;}
	else if (ColorFun(color, RGB(147, 147, 147), 10))//类似唱片机
		{style=18;
	return TRUE;}
	return FALSE;
}

UINT myThreadFunc(LPVOID lparam)
{
	CjumpDlg* dlg=(CjumpDlg*)lparam;
	while (1)
	{
		if (dlg==NULL)
		{
			return 0;
		}
		dlg->Ondraw(dlg);
	}
	return 1;

}