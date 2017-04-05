// MainWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddinDemo.h"
#include "MainWindowDlg.h"
#include "math.h"
#include "LogInfo.h"
#include <fstream>
#include <iomanip>
#include <shlwapi.h>
#include "CSVFile.h"
#include "stdlib.h"
#include "io.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg dialog


CMainWindowDlg::CMainWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainWindowDlg::IDD, pParent)
	, m_strPath(_T(""))
	, m_Contract(_T(""))
	, m_TimeLevel(_T(""))
{
	//{{AFX_DATA_INIT(CMainWindowDlg)
	m_iDirection = 0;
	m_iOffSet = 0;
	m_iVolume = 1;
	m_fPrice = 56320;
	m_iPriceType = 0;
	m_bHedge = FALSE;
	m_strInstrumentID = _T("SQCU01");
	m_iOrderActionID = 0;
	//}}AFX_DATA_INIT
	m_bInit = TRUE;
	//  m_save_path = _T("");
}


void CMainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	////{{AFX_DATA_MAP(CMainWindowDlg)
	//DDX_Control(pDX, IDC_EDIT_INFO, m_editMsg);
	//DDX_Radio(pDX, IDC_RADIO1, m_iDirection);
	//DDX_Radio(pDX, IDC_RADIO3, m_iOffSet);
	//DDX_Text(pDX, IDC_EDIT_VOLUME, m_iVolume);
	//DDX_Text(pDX, IDC_EDIT_PRICE, m_fPrice);
	//DDX_CBIndex(pDX, IDC_COMBO1, m_iPriceType);
	//DDX_Check(pDX, IDC_CHECK_HEDGE, m_bHedge);
	//DDX_Text(pDX, IDC_EDIT_INSTRUMENTID, m_strInstrumentID);
	//DDX_Text(pDX, IDC_EDIT_ORDERID, m_iOrderActionID);
	//}}AFX_DATA_MAP
	//  DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_save_path);
	DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_strPath);

	DDX_Control(pDX, IDC_EDIT_SAVE_PATH, m_Path);
	DDX_Control(pDX, IDC_CMBTIME, m_Time);
	DDX_Control(pDX, IDC_CMBCONTRACT, m_Contr);
}


BEGIN_MESSAGE_MAP(CMainWindowDlg, CDialog)
	//{{AFX_MSG_MAP(CMainWindowDlg)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1_GEDATA, OnButton1Gedata)
	ON_BN_CLICKED(IDC_BUTTON_GET2, OnButtonGet2)
	ON_BN_CLICKED(IDC_BUTTON_ORDERIN, OnButtonOrderin)
	ON_BN_CLICKED(IDC_BUTTON_ORDERACTION, OnButtonOrderAction)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_NOTIFY_UPDATE, OnNotifyUpdate)
	//ON_BN_CLICKED(IDC_BTN_GET1MIN, &CMainWindowDlg::OnBnClickedBtnGet1min)
	
	
	ON_BN_CLICKED(IDC_BUTTON_OPATH, &CMainWindowDlg::OnBnClickedButtonOpath)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg message handlers

BOOL CMainWindowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//去除任务栏窗口对应按钮
	ModifyStyleEx (WS_EX_APPWINDOW,WS_EX_TOOLWINDOW );
	//开始时禁用输出按钮
	CWnd *okbtn = GetDlgItem( IDC_BUTTON1_GEDATA );
	if ( okbtn ) {
		okbtn->EnableWindow( FALSE );
	}
	//初始化时间级别选择框
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("Tick"); //为控件添加初始化数据
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("1Min"); //为控件添加初始化数据
	m_Time.SetCurSel(1); //设置第nIndex项为显示的内容
	//记录状态
	WritePrivateProfileInt("AddinDemo","AutoShow",1,"C:\\StockCfg.ini");  

	//注册沪铜行情数据
	g_pMainFormework->RegReportNotify("CU00",'QS');

	//注册上证指数行情数据
	g_pMainFormework->RegReportNotify("000001",'HS');

	//导出数据输出路径初始化赋值
	CString strText;
	strText.Format("C:\\IF00Data\\1M\\");
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(strText);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainWindowDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	g_pdlgMainWindow = NULL;
	delete this;
}

void CMainWindowDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	//防止调用MoveWindow函数时系统发送此消息
	if(m_bInit)
		return;
	
	CRect rc;
	GetWindowRect(rc);
				
	WritePrivateProfileInt("AddinDemo","X",rc.left,"C:\\StockCfg.ini");  
	WritePrivateProfileInt("AddinDemo","Y",rc.top,"C:\\StockCfg.ini");  
}

void CMainWindowDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	//显示出上证指数的及时报价
	REPORT_STRUCT * pReport = g_pMainFormework->GetReportData("000001",'HS');
	if(pReport) 
	{
		CString strText;
		strText.Format("%s    开盘:%.2f  最高:%.2f  最低:%.2f  最新:%.2f", pReport->m_szName, pReport->m_fOpen, pReport->m_fHigh, pReport->m_fLow, pReport->m_fNewPrice);
//		dc.TextOut(20,20,strText);
	}
}

void CMainWindowDlg::OnCancel() 
{
	WritePrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini"); 
	
	DestroyWindow();
}

void CMainWindowDlg::OnClose() 
{
	OnCancel();
}

//接收通知消息
LRESULT CMainWindowDlg::OnNotifyUpdate(WPARAM w,LPARAM l)
{
	if(w == 2)
	{
		//注册品种报价变化通知
		ReportUpdate(l);
	}
	else if(w == 3)
	{
		//订单状态变化通知
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		OrderStatus(pKsi);
	}
	else if(w == 4)
	{
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		if(strcmp(pKsi->m_szStatus,"Connected") == 0)
		{
			//账户已经连接
		}
		else if(strcmp(pKsi->m_szStatus,"Disconnected") == 0)
		{
			//账户断开连接
		}
	}
	return 0;
}

/*
 订单的变化类型，有如下字符串值：

"Cancelled"  表示订单已经撤销

"Submitted"和"PreSubmitted"  表示订单已经提交，当只成交一部分尚未完全成交时也会出现此事件，此时已成交数量在Filled参数中显示

"Filled"    表示本地订单已经全部成交

"Tradeing"  每笔成交回报，此时Filled是本次成交数量，Remaining将始终为0

"Inactive"  表示本次委托无效，比如价格超过允许范围，委托数量超出范围等等

"PendingSubmit" 本次委托已经发送服务器，但是服务器未发出确认消息（仅IB有效）

"PendingCancel" 本次撤单委托已经发送服务器，但是服务器未发出确认消息（仅IB有效）
*/
void CMainWindowDlg::OrderStatus(BARGAIN_NOTIFY_KSI * pKsi)
{
	CString strLog;
	strLog.Format("[回报] 挂单%d, 状态 %s", pKsi->m_nOrderID, pKsi->m_szStatus);
	WriteLog(strLog);

	//记录日志到文件
	//LOG_DEBUG_INFO( "c:\\MyData.txt", "[回报] 挂单%d, 状态 %s", pKsi->m_nOrderID, pKsi->m_szStatus);

	if(strcmp(pKsi->m_szStatus,"Tradeing") == 0)
	{
		//在这里处理订单成交的代码
	}
	else if(strcmp(pKsi->m_szStatus ,"Cancelled")==0)
	{
	}
	else if(strcmp(pKsi->m_szStatus,"Filled")==0)
	{
	}
	else if(strcmp(pKsi->m_szStatus,"Inactive")==0)
	{
		//在这里处理订单被撤销，无效订单
	}
}

void CMainWindowDlg::ReportUpdate(LPARAM l)
{
	//如果需要更多的数据，可以使用这个扩展数据结构
	//REPORT_STRUCT_EX * pData = (REPORT_STRUCT_EX*)l;

	REPORT_STRUCT * pData = (REPORT_STRUCT*)l;
	//显示处理报表 pData->m_fNewPrice ....

	CString strText;
	strText.Format("注册品种: %s 最新价 %.2f", pData->m_szName, pData->m_fNewPrice);

	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(strText);
}

/*
void CMainWindowDlg::OnButton1Gedata() 
{
	//读取上海市场的600000日线数据范例
	PCALCINFO stData = {0};
	stData.m_dataType = MIN1_DATA;//日线
	stData.m_bIsPow = 0; //是否复权
	stData.m_wMarket = 'JZ';
	strcpy(stData.m_szLabel,"IF00"); //读取600000 浦发银行数据
	stData.m_nCustomCyc = 1;
	int startyear = 2010;
	int endyear = 2017;

	if(g_pMainFormework->GetDataInfo(&stData))
	{
		
		//CString filenamecsv = "C:\\IF00Data\\CSV\\Min1\\";
		CString filenamesql = "E:\\IF00Data\\SQL\\Min1\\";
		CString filename;
		int y = 2010;
		int m = 1;
		ofstream ofs;
		for(int y = startyear; y <= endyear; y++)
		{
			CString t;
			t.Format("%d", y);
			CString filename = filenamesql + t +".txt";
			ofs.open(filename);
			ofs << "begin;" << endl;
			ofs.close();
		}
		
		for(int i = 0; i < stData.m_nNumData; i++)
		{
			double dtime = stData.m_pMainData[i].m_timeDate;
			SYSTEMTIME ttime;
			VariantTimeToSystemTime(dtime, &ttime);

			int year = ttime.wYear;
			int month = ttime.wMonth;
			int day = ttime.wDay;
			int hour = ttime.wHour;
			int minute = ttime.wMinute;
			CTime tmp(year, month, day, hour, minute, 0);
			CTimeSpan span(0, 0, 1, 0);
			CTime adj = tmp - span;

			CString syear, smonth, sday, shour, sminute;
			syear.Format("%d", tmp.GetYear());
			if(tmp.GetMonth() < 10)
			{
				smonth.Format("0%d", tmp.GetMonth());
			}
			else
			{
				smonth.Format("%d", tmp.GetMonth());
			}
			if(tmp.GetDay() < 10)
			{
				sday.Format("0%d", tmp.GetDay());
			}
			else
			{
				sday.Format("%d", tmp.GetDay());
			}
			if(tmp.GetHour() < 10)
			{
				shour.Format("0%d", tmp.GetHour());
			}
			else
			{
				shour.Format("%d", tmp.GetHour());
			}
			if(tmp.GetMinute() < 10)
			{
				sminute.Format("0%d", tmp.GetMinute());
			}
			else
			{
				sminute.Format("%d", tmp.GetMinute());
			}

			CString sqltime = syear + "-" + smonth + "-" + sday + " " + shour + ":" + sminute + ":" + "00.000";
			if(i == 0)
			{
				//AfxMessageBox(sqltime);
			}
			//csv
			filename = filenamesql + syear + ".txt";
			ofs.open(filename, ios::app);
			ofs << "insert into Bar(closetime, date, high, low, open, close, volume, adjclose, openint) Values('"
				<< sqltime << "',"
				<< setprecision(20) << dtime << setprecision(6) << ","
				<< stData.m_pMainData[i].m_fHigh << ","
				<< stData.m_pMainData[i].m_fLow << ","
				<< stData.m_pMainData[i].m_fOpen << ","
				<< stData.m_pMainData[i].m_fClose << ","
				<< stData.m_pMainData[i].m_fVolume << ","
				<< stData.m_pMainData[i].m_fClose << ","
				<< stData.m_pMainData[i].m_fOI << ");" << endl;
			ofs.close();
		}
		for(int y = startyear; y <= endyear; y++)
		{
			CString t;
			t.Format("%d", y);
			CString filename = filenamesql + t +".txt";
			ofs.open(filename,ios::app);
			ofs << "end;";
			ofs.close();
		}
	}
}
*/

void CMainWindowDlg::OnButton1Gedata() 
{
	PCALCINFO stData = {0};
	stData.m_dataType = MIN1_DATA;//日线
	stData.m_bIsPow = 0; //是否复权
	stData.m_wMarket = 'JZ';
	strcpy(stData.m_szLabel,"IF00"); //读取600000 浦发银行数据
	stData.m_nCustomCyc = 1;
	int startyear = 2010;
	int endyear = 2017;

	if(g_pMainFormework->GetDataInfo(&stData))
	{
		
		//CString filenamecsv = "C:\\IF00Data\\CSV\\Min1\\";
		//CString filenamesql = "E:\\IF00Data\\CSV\\Min1\\";
		CString filenamesql;
		GetDlgItemText(IDC_EDIT_SAVE_PATH,filenamesql);//获取保存数据的路径

		/*
		if(!DirectoryExist(filenamesql))
		{
			AfxMessageBox("请校验保存路径，未找到路径："+filenamesql);
		}
		*/

		CString filename;
		int y = 2010;
		int m = 1;
		ofstream ofs;
		
		CString ss;
		ss.Format("%d", stData.m_nNumData);
		//AfxMessageBox(filenamesql);
		for(int i = 0; i < stData.m_nNumData; i++)
		{
			double dtime = stData.m_pMainData[i].m_timeDate;
			SYSTEMTIME ttime;
			VariantTimeToSystemTime(dtime, &ttime);

			int year = ttime.wYear;
			CString syear;
			syear.Format("%d", year);
			int month = ttime.wMonth;
			CString smonth;
			if(month < 10)
			{
				smonth.Format("0%d", month);
			}
			else
			{
				smonth.Format("%d", month);
			}
			int day = ttime.wDay;
			CString sday;
			if(day < 10)
			{
				sday.Format("0%d", day);
			}
			else
			{
				sday.Format("%d", day);
			}

			filename = filenamesql + "\\" + syear + "_" + smonth + "_" + sday + ".csv";
			ofs.open(filename, ios::app);
			ofs << setprecision(20) << dtime << setprecision(6) << ","
				<< stData.m_pMainData[i].m_fHigh << ","
				<< stData.m_pMainData[i].m_fLow << ","
				<< stData.m_pMainData[i].m_fOpen << ","
				<< stData.m_pMainData[i].m_fClose << ","
				<< stData.m_pMainData[i].m_fVolume << ","
				<< stData.m_pMainData[i].m_fClose << ","
				<< stData.m_pMainData[i].m_fOI << endl;
			ofs.close();
		}

		AfxMessageBox("数据输出完成!");
	}
}

void CMainWindowDlg::OnButtonGet2() 
{
	// TODO: Add your control notification handler code here
	int ii,icount;
	typedef CArray<BLOCK_STRUCT,BLOCK_STRUCT&> BLOCK_STRUCT_Array;
	BLOCK_STRUCT_Array css_Array;
	
	//取指定分类板块的品种数组
	//szName为分类或者板块名称，如"上海A股"等，nMode为类别，0市场分组，1分类板块，2系统板块（品种栏对应）
	BLOCK_STRUCT pBlock[3000]; //尽可能分配一个大数组用户存放调取的板块数据
	DWORD dwMaxCount = 3000;//数组大小
	DWORD dwResult = g_pMainFormework->GetReportData(pBlock,dwMaxCount,"上海A股", 0);

	if(dwResult > 0)
	{
		css_Array.SetSize(dwResult);
		memcpy(css_Array.GetData(),&pBlock,sizeof(BLOCK_STRUCT)*dwResult);
	}
	
	icount=css_Array.GetUpperBound();
	
	CString cstr;
	cstr.Format("%d",icount);
	
	for (ii=0;ii<=icount-1;ii++)
	{
		char szMarket[3] = {0};
		memcpy(szMarket,&css_Array[ii].m_nMarket,2);

		cstr.Format("%s%s",szMarket, css_Array[ii].m_szLable);
		WriteLog(cstr);
	}
}

void CMainWindowDlg::OnButtonOrderin() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if (m_strInstrumentID.IsEmpty() || (m_fPrice <=0) || (m_iVolume<=0))
	{
		AfxMessageBox("非法参数, 下单失败!");
		return;
	}

	//注意：请不要在SendMessage消息处理函数或者在线程中调用该下单函数。如果有必要在线程中调用下单，请使用PostMessage向主窗口发送下单
	//    指令消息，然后在主线程中下单。
	
	WORD wMarket = m_strInstrumentID[0]|m_strInstrumentID[1]<<8;
	CString strInstrumentID = m_strInstrumentID.Mid(2);
	long orderID = g_pMainFormework->PlaceOrder(m_iPriceType, m_fPrice, 0, m_iVolume, m_iDirection, strInstrumentID, wMarket, 0, "", m_iOffSet, m_bHedge, 0);
	if (orderID == -1)
	{
		AfxMessageBox("下单失败!");
		return;
	}
	else
	{
		CString strFlag;
		if (m_iDirection==0)
		{
			if (m_iOffSet == 0)
			{
				strFlag.Format("买开仓");
			}
			else if (m_iOffSet == 1)
			{
				strFlag.Format("买平今");
			}
			else
			{
				strFlag.Format("买平仓");
			}
		}
		else
		{
			if (m_iOffSet == 0)
			{
				strFlag.Format("卖开仓");
			}
			else if (m_iOffSet == 1)
			{
				strFlag.Format("卖平今");
			}
			else
			{
				strFlag.Format("卖平仓");
			}
		}
		CString strLog;
		strLog.Format("以限价%.3f 的 %s %d 手, 下单ID %d",
			m_fPrice, strFlag, m_iVolume, orderID);
		WriteLog(strLog);
	}
}

void CMainWindowDlg::OnButtonOrderAction() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	/*
	if (m_iOrderActionID <= 0)
	{
		AfxMessageBox("非法参数, 撤单失败!");
		return;
	}
	*/

	g_pMainFormework->OrderCancel(m_iOrderActionID, 0);
	CString strLog;
	strLog.Format("撤销 %d 单子", m_iOrderActionID);
	WriteLog(strLog);
}

void CMainWindowDlg::WriteLog(CString strLog)
{
	COleDateTime timeNow = COleDateTime::GetCurrentTime();
	m_strInfo += timeNow.Format("%Y.%m.%d %H:%M:%S") + " ";
	m_strInfo += strLog;
	m_strInfo += "\r\n";
	
	m_editMsg.SetWindowText(m_strInfo);
	m_editMsg.SetSel(m_strInfo.GetLength(),m_strInfo.GetLength());
}

//判断文件是否存在
bool CMainWindowDlg::FileExist(CString FileName)
{
 CFileFind fFind;
 return fFind.FindFile(FileName);
}

//判断文件夹是否存在
bool CMainWindowDlg::DirectoryExist(CString Path)
{
 WIN32_FIND_DATA fd;
 BOOL ret = FALSE;
    HANDLE hFind = FindFirstFile(Path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
		//目录存在
		ret = TRUE;
    }
    FindClose(hFind);
 return ret;
}

//创建文件夹路径
bool CMainWindowDlg::CreateDirectory(CString path)
{
 SECURITY_ATTRIBUTES attrib;
 attrib.bInheritHandle = FALSE;
 attrib.lpSecurityDescriptor = NULL;
 attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
 
 return ::CreateDirectory( path, &attrib);
}

//void CMainWindowDlg::OnBnClickedBtnGet1min()
//{
//	// TODO: Add your control notification handler code here
//		//读取上海市场的600000日线数据范例
//	PCALCINFO stData = {0};
//	stData.m_dataType = MIN1_DATA;//日线
//	stData.m_bIsPow = 0; //是否复权
//	stData.m_wMarket = 'JZ';
//	strcpy(stData.m_szLabel,"IF00"); //读取600000 浦发银行数据
//	stData.m_nCustomCyc = 1;
//	int startyear = 2010;
//	int endyear = 2017;
//
//	if(g_pMainFormework->GetDataInfo(&stData))
//	{
//		CString filenamesql;
//		GetDlgItemText(IDC_EDIT_SAVE_PATH,filenamesql);//获取保存数据的路径
//
//		CString filename;
//		int y = 2010;
//		int m = 1;
//		ofstream ofs;
//		
//		int lastday = 0;
//		for(int i = 0; i <= stData.m_nNumData; i++)
//		{
//			if(i == stData.m_nNumData)
//			{
//				if(ofs.is_open() == true)
//				{
//					ofs.close();
//				}
//				break;
//			}
//			double dtime = stData.m_pMainData[i].m_timeDate;
//			SYSTEMTIME ttime;
//			VariantTimeToSystemTime(dtime, &ttime);
//
//			int year = ttime.wYear;
//			int month = ttime.wMonth;
//			int day = ttime.wDay;
//			int hour = ttime.wHour;
//			int minute = ttime.wMinute;
//			CTime tmp(year, month, day, hour, minute, 0);
//			CTimeSpan span(0, 0, 1, 0);
//			CTime adj = tmp - span;
//
//			CString syear, smonth, sday, shour, sminute;
//			syear.Format("%d", tmp.GetYear());
//			if(adj.GetMonth() < 10)
//			{
//				smonth.Format("0%d", adj.GetMonth());
//			}
//			else
//			{
//				smonth.Format("%d", adj.GetMonth());
//			}
//			if(adj.GetDay() < 10)
//			{
//				sday.Format("0%d", adj.GetDay());
//			}
//			else
//			{
//				sday.Format("%d", adj.GetDay());
//			}
//			if(adj.GetHour() < 10)
//			{
//				shour.Format("0%d", adj.GetHour());
//			}
//			else
//			{
//				shour.Format("%d", adj.GetHour());
//			}
//			if(adj.GetMinute() < 10)
//			{
//				sminute.Format("0%d", adj.GetMinute());
//			}
//			else
//			{
//				sminute.Format("%d", adj.GetMinute());
//			}
//
//			filename = filenamesql+"\\SQL\\" + syear +"-"+smonth+"-"+sday+ ".txt";
//			if(adj.GetDay() != lastday)
//			{
//				if(ofs.is_open() == true)
//				{
//					ofs.close();
//				}
//				ofs.open(filename);
//				lastday = adj.GetDay();
//			}
//			if(ofs.is_open() == false)
//			{
//				continue;
//			}
//
//			CString sqltime = syear + "-" + smonth + "-" + sday + " " + shour + ":" + sminute + ":" + "59.999";
//
//			ofs << "insert into Bar(closetime, date, high, low, open, close, volume, adjclose, openint) Values('"
//				<< sqltime << "',"
//				<< setprecision(20) << dtime << setprecision(6) << ","
//				<< stData.m_pMainData[i].m_fHigh << ","
//				<< stData.m_pMainData[i].m_fLow << ","
//				<< stData.m_pMainData[i].m_fOpen << ","
//				<< stData.m_pMainData[i].m_fClose << ","
//				<< stData.m_pMainData[i].m_fVolume << ","
//				<< stData.m_pMainData[i].m_fClose << ","
//				<< stData.m_pMainData[i].m_fOI << ");" << endl;
//		}
//
//		AfxMessageBox("数据输出完成!");
//
//		/*
//		for(int y = startyear; y <= endyear; y++)
//		{
//			CString t;
//			t.Format("%d", y);
//			CString filename = filenamesql + t +".txt";
//			ofs.open(filename,ios::app);
//			ofs << "end;";
//			ofs.close();
//		}
//		*/
//	}
//}

//选择文件夹按钮点击事件
void CMainWindowDlg::OnBnClickedButtonOpath()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

       char szDir[MAX_PATH];

       BROWSEINFO bi;

       ITEMIDLIST *pidl;

       bi.hwndOwner = this->m_hWnd;

       bi.pidlRoot = NULL;

       bi.pszDisplayName = szDir;

       bi.lpszTitle = "请选择目录";

       bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

       bi.lpfn = NULL;

       bi.lParam = 0;

       bi.iImage = 0;

       pidl = SHBrowseForFolder(&bi);


       if(pidl == NULL)  return;

       if(!SHGetPathFromIDList(pidl, szDir))   return;

       else  m_strPath = szDir;

       UpdateData(FALSE);
	   //初始化合约选择框
	   
		  CString cstr = m_strPath;
		   cstr += "\\Weisoft\\contract.csv";
		   string str = LPCTSTR(cstr);
		   char * pszFileName = const_cast<char *>(str.c_str());
		   CStdioFile myFile;
		   CFileException fileException;
		   if (_access(pszFileName, 0)== -1)
		   {
			   CString cs(pszFileName);			   
			   cs = "无法打开" + cs ;
			   AfxMessageBox(cs);
			   CWnd *okbtn = GetDlgItem( IDC_BUTTON1_GEDATA );
			   if ( okbtn ) {
				   okbtn->EnableWindow( FALSE );
			   }
			   
		   }
		   else if(myFile.Open(pszFileName,CFile::typeText|CFile::modeRead|CFile::shareExclusive),&fileException)
		   {
			   myFile.SeekToBegin();
			   CString cstrReadLine,cstrRead="";
			   /*CString str1;
			   myFile.ReadString(str1);
			   CString str2;
			   myFile.ReadString(str2);*/
			   ((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->ResetContent();//消除现有所有内容
			   while (myFile.ReadString(cstrReadLine))
			   {
				   //cstrRead +=cstrReadLine + "\n\r";
				   
				   ((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->AddString(cstrReadLine); //为控件添加初始化数据
			   }
			   m_Contr.SetCurSel(0);
			   //AfxMessageBox(cstrRead);
			   myFile.Close();
			   CWnd *okbtn = GetDlgItem( IDC_BUTTON1_GEDATA );
			   if ( okbtn ) {
				   okbtn->EnableWindow( TRUE );
			   }
		   }
		   else
		   {
			   
			  
		   }
		   
	  
}

