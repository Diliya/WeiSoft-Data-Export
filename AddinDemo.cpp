// AddinDemo.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "AddinDemo.h"
#include "AddinInterface.h"
#include "MainWindowDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMainWindowDlg * g_pdlgMainWindow = NULL;
IMainFramework * g_pMainFormework = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAddinDemoApp

BEGIN_MESSAGE_MAP(CAddinDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CAddinDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAddinDemoApp construction

CAddinDemoApp::CAddinDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAddinDemoApp object

CAddinDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAddinDemoApp initialization

BOOL CAddinDemoApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	return TRUE;
}

//通知插件主程序初始化完毕
void WINAPI InitFinishedEx2(HWND hMainFrame, IMainFramework * pApp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
	g_pMainFormework= pApp;
	int nAutoShow = GetPrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini"); 
	
	//如果上次系统退出时没有关闭该插件窗口则本次启动时继续显示
	if(nAutoShow && g_pdlgMainWindow == NULL)
	{
		CWnd * pParent = CWnd::FromHandle(pApp->GetMainWindow());
		
		g_pdlgMainWindow = new CMainWindowDlg;
		g_pdlgMainWindow->Create(CMainWindowDlg::IDD,pParent);
		
		//在原来位置显示
		int nXPos = GetPrivateProfileInt("AddinDemo","X",0,"C:\\StockCfg.ini"); 
		int nYPos = GetPrivateProfileInt("AddinDemo","Y",0,"C:\\StockCfg.ini"); 
		
		CRect rc;
		g_pdlgMainWindow->GetWindowRect(rc);

		g_pdlgMainWindow->MoveWindow(nXPos,nYPos,rc.Width(),rc.Height());
		g_pdlgMainWindow->m_bInit = FALSE;
		g_pdlgMainWindow->ShowWindow(SW_SHOW);
		g_pdlgMainWindow->Invalidate();

		//注册窗口消息
		pApp->RegisterMsg(g_pdlgMainWindow->m_hWnd, WM_NOTIFY_UPDATE);
	}
}

//主程序需要显示/关闭窗口时调用
void WINAPI ShowAddinWindow(BOOL bShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(bShow)
	{
		//显示窗体
		if(g_pdlgMainWindow == NULL)
		{			
			CWnd * pParent = CWnd::FromHandle(g_pMainFormework->GetMainWindow());
			
			g_pdlgMainWindow = new CMainWindowDlg;
			g_pdlgMainWindow->Create(CMainWindowDlg::IDD,pParent);
			g_pdlgMainWindow->ShowWindow(SW_SHOW);
		}
		else
		{
			//用户再次脱出此插件时只做一次显示处理，将已创建窗口移动到鼠标位置
			g_pdlgMainWindow->ShowWindow(SW_SHOW);
		}

		//注册窗口消息
		g_pMainFormework->RegisterMsg(g_pdlgMainWindow->m_hWnd, WM_NOTIFY_UPDATE);
		
		WritePrivateProfileInt("AddinDemo","AutoShow",   
			1,"C:\\StockCfg.ini");
		
		//上一次显示位置显示
		int nXPos = GetPrivateProfileInt("AddinDemo","X",0,"C:\\StockCfg.ini"); 
		int nYPos = GetPrivateProfileInt("AddinDemo","Y",0,"C:\\StockCfg.ini"); 
		
		CRect rc;
		g_pdlgMainWindow->GetWindowRect(rc);
		
		g_pdlgMainWindow->MoveWindow(nXPos,nYPos,rc.Width(),rc.Height());
		g_pdlgMainWindow->m_bInit = FALSE;		
	}
	else
	{
		//关闭窗体显示
		if(g_pdlgMainWindow)
		{				
			g_pdlgMainWindow->DestroyWindow();
			delete g_pdlgMainWindow;
			g_pdlgMainWindow = NULL;
		}
		WritePrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini");  
	}
}

//返回给主程序插件的主窗体句柄
HWND WINAPI GetMainWindow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(g_pdlgMainWindow)
		return g_pdlgMainWindow->m_hWnd;
	return NULL;
}

//主程序退出之前调用
void WINAPI AddinUninitialize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(g_pdlgMainWindow)
	{
		delete g_pdlgMainWindow;
	}
}

//返回给主程序插件的名字
void WINAPI GetAddinName(char * pszName, int nSize /*=MAX_PATH*/)
{
	//插件名字拷贝缓冲区 nSize 字节之内 

	//strcpy(pszName,"IF00_1分钟线");
	//strcpy(pszName,"SBMFC");
	strcpy(pszName,"金字塔数据落盘");

}
