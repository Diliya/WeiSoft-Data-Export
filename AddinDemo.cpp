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

//֪ͨ����������ʼ�����
void WINAPI InitFinishedEx2(HWND hMainFrame, IMainFramework * pApp)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
	g_pMainFormework= pApp;
	int nAutoShow = GetPrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini"); 
	
	//����ϴ�ϵͳ�˳�ʱû�йرոò�������򱾴�����ʱ������ʾ
	if(nAutoShow && g_pdlgMainWindow == NULL)
	{
		CWnd * pParent = CWnd::FromHandle(pApp->GetMainWindow());
		
		g_pdlgMainWindow = new CMainWindowDlg;
		g_pdlgMainWindow->Create(CMainWindowDlg::IDD,pParent);
		
		//��ԭ��λ����ʾ
		int nXPos = GetPrivateProfileInt("AddinDemo","X",0,"C:\\StockCfg.ini"); 
		int nYPos = GetPrivateProfileInt("AddinDemo","Y",0,"C:\\StockCfg.ini"); 
		
		CRect rc;
		g_pdlgMainWindow->GetWindowRect(rc);

		g_pdlgMainWindow->MoveWindow(nXPos,nYPos,rc.Width(),rc.Height());
		g_pdlgMainWindow->m_bInit = FALSE;
		g_pdlgMainWindow->ShowWindow(SW_SHOW);
		g_pdlgMainWindow->Invalidate();

		//ע�ᴰ����Ϣ
		pApp->RegisterMsg(g_pdlgMainWindow->m_hWnd, WM_NOTIFY_UPDATE);
	}
}

//��������Ҫ��ʾ/�رմ���ʱ����
void WINAPI ShowAddinWindow(BOOL bShow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(bShow)
	{
		//��ʾ����
		if(g_pdlgMainWindow == NULL)
		{			
			CWnd * pParent = CWnd::FromHandle(g_pMainFormework->GetMainWindow());
			
			g_pdlgMainWindow = new CMainWindowDlg;
			g_pdlgMainWindow->Create(CMainWindowDlg::IDD,pParent);
			g_pdlgMainWindow->ShowWindow(SW_SHOW);
		}
		else
		{
			//�û��ٴ��ѳ��˲��ʱֻ��һ����ʾ�������Ѵ��������ƶ������λ��
			g_pdlgMainWindow->ShowWindow(SW_SHOW);
		}

		//ע�ᴰ����Ϣ
		g_pMainFormework->RegisterMsg(g_pdlgMainWindow->m_hWnd, WM_NOTIFY_UPDATE);
		
		WritePrivateProfileInt("AddinDemo","AutoShow",   
			1,"C:\\StockCfg.ini");
		
		//��һ����ʾλ����ʾ
		int nXPos = GetPrivateProfileInt("AddinDemo","X",0,"C:\\StockCfg.ini"); 
		int nYPos = GetPrivateProfileInt("AddinDemo","Y",0,"C:\\StockCfg.ini"); 
		
		CRect rc;
		g_pdlgMainWindow->GetWindowRect(rc);
		
		g_pdlgMainWindow->MoveWindow(nXPos,nYPos,rc.Width(),rc.Height());
		g_pdlgMainWindow->m_bInit = FALSE;		
	}
	else
	{
		//�رմ�����ʾ
		if(g_pdlgMainWindow)
		{				
			g_pdlgMainWindow->DestroyWindow();
			delete g_pdlgMainWindow;
			g_pdlgMainWindow = NULL;
		}
		WritePrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini");  
	}
}

//���ظ�������������������
HWND WINAPI GetMainWindow()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if(g_pdlgMainWindow)
		return g_pdlgMainWindow->m_hWnd;
	return NULL;
}

//�������˳�֮ǰ����
void WINAPI AddinUninitialize()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if(g_pdlgMainWindow)
	{
		delete g_pdlgMainWindow;
	}
}

//���ظ���������������
void WINAPI GetAddinName(char * pszName, int nSize /*=MAX_PATH*/)
{
	//������ֿ��������� nSize �ֽ�֮�� 

	//strcpy(pszName,"IF00_1������");
	//strcpy(pszName,"SBMFC");
	strcpy(pszName,"��������������");

}
