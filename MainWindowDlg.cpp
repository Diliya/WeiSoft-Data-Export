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
#include "io.h"
#include <direct.h>  

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
	m_Contract = _T("");
	m_TimeLevel = _T("");
}


void CMainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainWindowDlg)
	DDX_Control(pDX, IDC_EDIT_INFO, m_editMsg);
	DDX_Radio(pDX, IDC_RADIO1, m_iDirection);
	DDX_Radio(pDX, IDC_RADIO3, m_iOffSet);
	DDX_Text(pDX, IDC_EDIT_VOLUME, m_iVolume);
	DDX_Text(pDX, IDC_EDIT_PRICE, m_fPrice);
	DDX_CBIndex(pDX, IDC_COMBO1, m_iPriceType);
	DDX_Check(pDX, IDC_CHECK_HEDGE, m_bHedge);
	DDX_Text(pDX, IDC_EDIT_INSTRUMENTID, m_strInstrumentID);
	DDX_Text(pDX, IDC_EDIT_ORDERID, m_iOrderActionID);
	//}}AFX_DATA_MAP
	//  DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_save_path);
	DDX_CBString(pDX, IDC_CMBCONTRACT, m_Contract);
	DDX_CBString(pDX, IDC_CMBTIME, m_TimeLevel);
	DDX_Control(pDX, IDC_CMBTIME, m_Time);
	DDX_Control(pDX, IDC_CMBCONTRACT, m_Contr);
	DDX_Text(pDX, IDC_EDIT_SAVE_PATH, m_strPath);
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
	ON_BN_CLICKED(IDC_BTN_GET1MIN, &CMainWindowDlg::OnBnClickedBtnGet1min)
	ON_BN_CLICKED(IDC_BUTTON2, &CMainWindowDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg message handlers

BOOL CMainWindowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//ȥ�����������ڶ�Ӧ��ť
	ModifyStyleEx (WS_EX_APPWINDOW,WS_EX_TOOLWINDOW );
	
	//��¼״̬
	WritePrivateProfileInt("AddinDemo","AutoShow",1,"C:\\StockCfg.ini");  

	//ע�Ủͭ��������
	g_pMainFormework->RegReportNotify("CU00",'QS');

	//ע����ָ֤����������
	g_pMainFormework->RegReportNotify("000001",'HS');

	//�����������·����ʼ����ֵ
	CString strText;
	strText.Format("C:\\IF00Data\\1M\\");
	GetDlgItem(IDC_EDIT_SAVE_PATH)->SetWindowText(strText);
	//��ʼʱ���������ť
	CWnd *okbtn = GetDlgItem( IDC_BUTTON1_GEDATA );
	if ( okbtn ) {
		okbtn->EnableWindow( FALSE );
	}
	//��ʼ��ʱ�伶��ѡ���
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("Tick"); //Ϊ�ؼ���ӳ�ʼ������
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("1Min"); //Ϊ�ؼ���ӳ�ʼ������
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("1Day"); //Ϊ�ؼ���ӳ�ʼ������
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("2Day"); //Ϊ�ؼ���ӳ�ʼ������
	((CComboBox*)GetDlgItem(IDC_CMBTIME))->AddString("2Min"); //Ϊ�ؼ���ӳ�ʼ������
	m_Time.SetCurSel(1); //���õ�nIndex��Ϊ��ʾ������
	//����·���ı���༭����
	CWnd *editpath = GetDlgItem( IDC_EDIT_SAVE_PATH );
	if ( editpath ) {
		okbtn->EnableWindow( FALSE );
	}
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
	
	//��ֹ����MoveWindow����ʱϵͳ���ʹ���Ϣ
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
	
	//��ʾ����ָ֤���ļ�ʱ����
	REPORT_STRUCT * pReport = g_pMainFormework->GetReportData("000001",'HS');
	if(pReport) 
	{
		CString strText;
		strText.Format("%s    ����:%.2f  ���:%.2f  ���:%.2f  ����:%.2f", pReport->m_szName, pReport->m_fOpen, pReport->m_fHigh, pReport->m_fLow, pReport->m_fNewPrice);
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

//����֪ͨ��Ϣ
LRESULT CMainWindowDlg::OnNotifyUpdate(WPARAM w,LPARAM l)
{
	if(w == 2)
	{
		//ע��Ʒ�ֱ��۱仯֪ͨ
		ReportUpdate(l);
	}
	else if(w == 3)
	{
		//����״̬�仯֪ͨ
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		OrderStatus(pKsi);
	}
	else if(w == 4)
	{
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		if(strcmp(pKsi->m_szStatus,"Connected") == 0)
		{
			//�˻��Ѿ�����
		}
		else if(strcmp(pKsi->m_szStatus,"Disconnected") == 0)
		{
			//�˻��Ͽ�����
		}
	}
	return 0;
}

/*
 �����ı仯���ͣ��������ַ���ֵ��

"Cancelled"  ��ʾ�����Ѿ�����

"Submitted"��"PreSubmitted"  ��ʾ�����Ѿ��ύ����ֻ�ɽ�һ������δ��ȫ�ɽ�ʱҲ����ִ��¼�����ʱ�ѳɽ�������Filled��������ʾ

"Filled"    ��ʾ���ض����Ѿ�ȫ���ɽ�

"Tradeing"  ÿ�ʳɽ��ر�����ʱFilled�Ǳ��γɽ�������Remaining��ʼ��Ϊ0

"Inactive"  ��ʾ����ί����Ч������۸񳬹�����Χ��ί������������Χ�ȵ�

"PendingSubmit" ����ί���Ѿ����ͷ����������Ƿ�����δ����ȷ����Ϣ����IB��Ч��

"PendingCancel" ���γ���ί���Ѿ����ͷ����������Ƿ�����δ����ȷ����Ϣ����IB��Ч��
*/
void CMainWindowDlg::OrderStatus(BARGAIN_NOTIFY_KSI * pKsi)
{
	CString strLog;
	strLog.Format("[�ر�] �ҵ�%d, ״̬ %s", pKsi->m_nOrderID, pKsi->m_szStatus);
	WriteLog(strLog);

	//��¼��־���ļ�
	//LOG_DEBUG_INFO( "c:\\MyData.txt", "[�ر�] �ҵ�%d, ״̬ %s", pKsi->m_nOrderID, pKsi->m_szStatus);

	if(strcmp(pKsi->m_szStatus,"Tradeing") == 0)
	{
		//�����ﴦ�����ɽ��Ĵ���
	}
	else if(strcmp(pKsi->m_szStatus ,"Cancelled")==0)
	{
	}
	else if(strcmp(pKsi->m_szStatus,"Filled")==0)
	{
	}
	else if(strcmp(pKsi->m_szStatus,"Inactive")==0)
	{
		//�����ﴦ��������������Ч����
	}
}

void CMainWindowDlg::ReportUpdate(LPARAM l)
{
	//�����Ҫ��������ݣ�����ʹ�������չ���ݽṹ
	//REPORT_STRUCT_EX * pData = (REPORT_STRUCT_EX*)l;

	REPORT_STRUCT * pData = (REPORT_STRUCT*)l;
	//��ʾ������ pData->m_fNewPrice ....

	CString strText;
	strText.Format("ע��Ʒ��: %s ���¼� %.2f", pData->m_szName, pData->m_fNewPrice);

	GetDlgItem(IDC_STATIC_TEXT)->SetWindowText(strText);
}

/*
void CMainWindowDlg::OnButton1Gedata() 
{
	//��ȡ�Ϻ��г���600000�������ݷ���
	PCALCINFO stData = {0};
	stData.m_dataType = MIN1_DATA;//����
	stData.m_bIsPow = 0; //�Ƿ�Ȩ
	stData.m_wMarket = 'JZ';
	strcpy(stData.m_szLabel,"IF00"); //��ȡ600000 �ַ���������
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
void OutputTickData()
{
	

}


void CMainWindowDlg::OnButton1Gedata() 
{
	UpdateData(TRUE);
	PCALCINFO stData = {0};
	CYC_DATA_TYPE tmpType;
	CString cstrTmp;

	((CComboBox*)GetDlgItem(IDC_CMBTIME))->GetWindowText(cstrTmp);
	if (cstrTmp == "Tick")
	{	
		tmpType = TICK_DATA;
		PCALCINFO stData = {0};
		stData.m_dataType = TICK_DATA;//����
		stData.m_bIsPow = 0; //�Ƿ�Ȩ
		stData.m_wMarket = 'JZ';
		strcpy(stData.m_szLabel,"IF00");
		//const int sleepperiod = 1000 * 60 * 60 * 24;
		const int sleepperiod = 1000 * 60 * 60 * 24;

		time_t tt = time(NULL);
		tm* t = localtime(&tt);
		int sys_year = t->tm_year + 1900;
		int sys_month = t->tm_mon + 1;
		int sys_day = t->tm_mday;
		//int sys_hour = t->tm_hour;
		//int sys_minute = t->tm_min;
		//int sys_second = t->tm_sec;
		CString filename;
		CString filenamesql;
		GetDlgItemText(IDC_EDIT_SAVE_PATH,filenamesql);//��ȡ�������ݵ�·��
		CString cstsTmp;
		((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->GetWindowText(cstsTmp);
		CString directory = filenamesql+"\\WeiSoft\\"+cstsTmp+"\\Tick";

		if(PathIsDirectory(directory) == false)
		{
			::CreateDirectory(directory, NULL);
		}

		CString tmp;
		tmp.Format("%d", sys_year);
		directory = directory + "\\" + tmp;
		if(PathIsDirectory(directory) == false)
		{
			::CreateDirectory(directory, NULL);
		}

		tmp.Format("%d", sys_month);
		directory = directory + "\\" + tmp;
		if(PathIsDirectory(directory) == false)//�ж��ļ����Ƿ����
		{
			::CreateDirectory(directory, NULL);//�����ļ���
		}

		filename.Format("%d��%d��%d��Tick����.csv", sys_year, sys_month, sys_day);
		//filename.Format("%d��%d��%d��Tick����.csv", sys_year, sys_month, sys_day);
		filename = directory + "\\" + filename;
		if (!PathFileExists(filename))
		{


			if(g_pMainFormework->GetDataInfo(&stData))
			{
				if(stData.m_pSubsection != NULL)
				{
					ofstream ofs(filename);
					ofs << "m_fBuyVolume" << ","
						<< "m_fSellVolume" << ","
						<< "m_bOrder" << ","
						<< "m_timeV2" << ","
						<< "m_fBuyPrice" << ","
						<< "m_fSellPrice" << ","
						<< "m_fNewPrice" << ","
						<< "m_fOI" << ","
						<< "m_fVolume" << ","
						<< "m_fAmount" << endl;
					for(int i = 0; i < stData.m_nNumSubData; i++)
					{
						ofs << stData.m_pSubsection[i].m_fBuyVolume << ","
							<< stData.m_pSubsection[i].m_fSellVolume << ","
							<< stData.m_pSubsection[i].m_bOrder << ","
							<< stData.m_pSubsection[i].m_timeV2 << ","
							<< stData.m_pSubsection[i].m_fBuyPrice << ","
							<< stData.m_pSubsection[i].m_fSellPrice << ","
							<< stData.m_pSubsection[i].m_fNewPrice << ","
							<< stData.m_pSubsection[i].m_fOI << ","
							<< stData.m_pSubsection[i].m_fVolume << ","
							<< stData.m_pSubsection[i].m_fAmount << endl;
					}
					ofs.close();
				}
			}
		}
		//OutputTickData();
		return;
	}
	else if (cstrTmp == "2Day")
	{
		tmpType = MULTIDAY_DATA;
		stData.m_nCustomCyc = 2;
	}
	else if (cstrTmp == "1Day")
	{
		tmpType = DAY_DATA;
	}
	else if (cstrTmp == "2Min")
	{
		tmpType = MULTIMIN_DATA;
		stData.m_nCustomCyc = 2;
	}
	else if (cstrTmp == "1Min")
	{
		tmpType = MIN1_DATA;
	}
	else
	{
		AfxMessageBox("ѡȡƵ����Ч");
		return;
	}
	stData.m_dataType = tmpType;//Ƶ��
	stData.m_bIsPow = 0; //�Ƿ�Ȩ
	stData.m_wMarket = 'JZ';
	CString cstsTmp;
	((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->GetWindowText(cstsTmp);
	strcpy(stData.m_szLabel,cstsTmp); //��Լ
	stData.m_nCustomCyc = 1;
	int startyear = 2010;
	int endyear = 2017;

	if(g_pMainFormework->GetDataInfo(&stData))
	{
		
		//CString filenamecsv = "C:\\IF00Data\\CSV\\Min1\\";
		//CString filenamesql = "E:\\IF00Data\\CSV\\Min1\\";
		CString filenamesql;
		GetDlgItemText(IDC_EDIT_SAVE_PATH,filenamesql);//��ȡ�������ݵ�·��
		CString tmpPath = filenamesql+"\\Weisoft\\"+cstsTmp+"\\"+cstrTmp;
		/*if (PathIsDirectory(tmpPath) == true)
		{*/
			CFileFind finder;
			CString strdel,strdir;
			strdir=tmpPath +"\\*";
			BOOL b_found=finder.FindFile(strdir,0); 
			while(b_found) 
			{
				b_found=finder.FindNextFile(); 
				strdel=finder.GetFileName(); 
				strdel=tmpPath + "\\" + strdel;
				if(finder.IsReadOnly())//���ֻ������
				{    
					SetFileAttributes(strdel,GetFileAttributes(strdel)&(~FILE_ATTRIBUTE_READONLY));
				}
				DeleteFile(strdel); //ɾ���ļ�
			}
			finder.Close();
		/*}*/ 
		filenamesql += ("\\Weisoft\\"+cstsTmp);
		if(PathIsDirectory(filenamesql) == false)//�ж��ļ����Ƿ����
		{
			::CreateDirectory(filenamesql, NULL);//�����ļ���
		}
		filenamesql += ("\\"+cstrTmp);
		if(PathIsDirectory(filenamesql) == false)//�ж��ļ����Ƿ����
		{
			::CreateDirectory(filenamesql, NULL);//�����ļ���
		}
		/*
		if(!DirectoryExist(filenamesql))
		{
			AfxMessageBox("��У�鱣��·����δ�ҵ�·����"+filenamesql);
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
			
			//mkdir(filenamesql);
			filename = filenamesql + "\\CSV\\" + syear + "_" + smonth + "_" + sday + ".csv";
			
			ofs.open(filename,ios::app);
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

		AfxMessageBox("����������!");
	}
}

void CMainWindowDlg::OnButtonGet2() 
{
	// TODO: Add your control notification handler code here
	int ii,icount;
	typedef CArray<BLOCK_STRUCT,BLOCK_STRUCT&> BLOCK_STRUCT_Array;
	BLOCK_STRUCT_Array css_Array;
	
	//ȡָ���������Ʒ������
	//szNameΪ������߰�����ƣ���"�Ϻ�A��"�ȣ�nModeΪ���0�г����飬1�����飬2ϵͳ��飨Ʒ������Ӧ��
	BLOCK_STRUCT pBlock[3000]; //�����ܷ���һ���������û���ŵ�ȡ�İ������
	DWORD dwMaxCount = 3000;//�����С
	DWORD dwResult = g_pMainFormework->GetReportData(pBlock,dwMaxCount,"�Ϻ�A��", 0);

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
		AfxMessageBox("�Ƿ�����, �µ�ʧ��!");
		return;
	}

	//ע�⣺�벻Ҫ��SendMessage��Ϣ�������������߳��е��ø��µ�����������б�Ҫ���߳��е����µ�����ʹ��PostMessage�������ڷ����µ�
	//    ָ����Ϣ��Ȼ�������߳����µ���
	
	WORD wMarket = m_strInstrumentID[0]|m_strInstrumentID[1]<<8;
	CString strInstrumentID = m_strInstrumentID.Mid(2);
	long orderID = g_pMainFormework->PlaceOrder(m_iPriceType, m_fPrice, 0, m_iVolume, m_iDirection, strInstrumentID, wMarket, 0, "", m_iOffSet, m_bHedge, 0);
	if (orderID == -1)
	{
		AfxMessageBox("�µ�ʧ��!");
		return;
	}
	else
	{
		CString strFlag;
		if (m_iDirection==0)
		{
			if (m_iOffSet == 0)
			{
				strFlag.Format("�򿪲�");
			}
			else if (m_iOffSet == 1)
			{
				strFlag.Format("��ƽ��");
			}
			else
			{
				strFlag.Format("��ƽ��");
			}
		}
		else
		{
			if (m_iOffSet == 0)
			{
				strFlag.Format("������");
			}
			else if (m_iOffSet == 1)
			{
				strFlag.Format("��ƽ��");
			}
			else
			{
				strFlag.Format("��ƽ��");
			}
		}
		CString strLog;
		strLog.Format("���޼�%.3f �� %s %d ��, �µ�ID %d",
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
		AfxMessageBox("�Ƿ�����, ����ʧ��!");
		return;
	}
	*/

	g_pMainFormework->OrderCancel(m_iOrderActionID, 0);
	CString strLog;
	strLog.Format("���� %d ����", m_iOrderActionID);
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

//�ж��ļ��Ƿ����
bool CMainWindowDlg::FileExist(CString FileName)
{
 CFileFind fFind;
 return fFind.FindFile(FileName);
}

//�ж��ļ����Ƿ����
bool CMainWindowDlg::DirectoryExist(CString Path)
{
 WIN32_FIND_DATA fd;
 BOOL ret = FALSE;
    HANDLE hFind = FindFirstFile(Path, &fd);
    if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
		//Ŀ¼����
		ret = TRUE;
    }
    FindClose(hFind);
 return ret;
}

//�����ļ���·��
bool CMainWindowDlg::CreateDirectory(CString path)
{
 SECURITY_ATTRIBUTES attrib;
 attrib.bInheritHandle = FALSE;
 attrib.lpSecurityDescriptor = NULL;
 attrib.nLength = sizeof(SECURITY_ATTRIBUTES);
 
 return ::CreateDirectory( path, &attrib);
}

void CMainWindowDlg::OnBnClickedBtnGet1min()
{
	// TODO: Add your control notification handler code here
		//��ȡ�Ϻ��г���600000�������ݷ���
	PCALCINFO stData = {0};
	stData.m_dataType = MIN1_DATA;//����
	stData.m_bIsPow = 0; //�Ƿ�Ȩ
	stData.m_wMarket = 'JZ';
	strcpy(stData.m_szLabel,"IF00"); //��ȡ600000 �ַ���������
	stData.m_nCustomCyc = 1;
	int startyear = 2010;
	int endyear = 2017;

	if(g_pMainFormework->GetDataInfo(&stData))
	{
		CString filenamesql;
		GetDlgItemText(IDC_EDIT_SAVE_PATH,filenamesql);//��ȡ�������ݵ�·��

		CString filename;
		int y = 2010;
		int m = 1;
		ofstream ofs;
		
		int lastday = 0;
		for(int i = 0; i <= stData.m_nNumData; i++)
		{
			if(i == stData.m_nNumData)
			{
				if(ofs.is_open() == true)
				{
					ofs.close();
				}
				break;
			}
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
			if(adj.GetMonth() < 10)
			{
				smonth.Format("0%d", adj.GetMonth());
			}
			else
			{
				smonth.Format("%d", adj.GetMonth());
			}
			if(adj.GetDay() < 10)
			{
				sday.Format("0%d", adj.GetDay());
			}
			else
			{
				sday.Format("%d", adj.GetDay());
			}
			if(adj.GetHour() < 10)
			{
				shour.Format("0%d", adj.GetHour());
			}
			else
			{
				shour.Format("%d", adj.GetHour());
			}
			if(adj.GetMinute() < 10)
			{
				sminute.Format("0%d", adj.GetMinute());
			}
			else
			{
				sminute.Format("%d", adj.GetMinute());
			}

			filename = filenamesql+"\\SQL\\" + syear +"-"+smonth+"-"+sday+ ".txt";
			if(adj.GetDay() != lastday)
			{
				if(ofs.is_open() == true)
				{
					ofs.close();
				}
				ofs.open(filename);
				lastday = adj.GetDay();
			}
			if(ofs.is_open() == false)
			{
				continue;
			}

			CString sqltime = syear + "-" + smonth + "-" + sday + " " + shour + ":" + sminute + ":" + "59.999";

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
		}

		AfxMessageBox("����������!");

		/*
		for(int y = startyear; y <= endyear; y++)
		{
			CString t;
			t.Format("%d", y);
			CString filename = filenamesql + t +".txt";
			ofs.open(filename,ios::app);
			ofs << "end;";
			ofs.close();
		}
		*/
	}
}


void CMainWindowDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

       char szDir[MAX_PATH];

       BROWSEINFO bi;

       ITEMIDLIST *pidl;

       bi.hwndOwner = this->m_hWnd;

       bi.pidlRoot = NULL;

       bi.pszDisplayName = szDir;

       bi.lpszTitle = "��ѡ��Ŀ¼";

       bi.ulFlags = BIF_STATUSTEXT | BIF_USENEWUI | BIF_RETURNONLYFSDIRS;

       bi.lpfn = NULL;

       bi.lParam = 0;

       bi.iImage = 0;

       pidl = SHBrowseForFolder(&bi);


       if(pidl == NULL)  return;

       if(!SHGetPathFromIDList(pidl, szDir))   return;

       else  m_strPath = szDir;

       UpdateData(FALSE);
	   //��ʼ����Լѡ���
	   
		  CString cstr = m_strPath;
		   cstr += "\\Weisoft\\contract.csv";
		   string str = LPCTSTR(cstr);
		   char * pszFileName = const_cast<char *>(str.c_str());
		   CStdioFile myFile;
		   CFileException fileException;
		   if (_access(pszFileName, 0)== -1)
		   {
			   CString cs(pszFileName);			   
			   cs = "�޷���" + cs ;
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
			   ((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->ResetContent();//����������������
			   while (myFile.ReadString(cstrReadLine))
			   {
				   //cstrRead +=cstrReadLine + "\n\r";
				   
				   ((CComboBox*)GetDlgItem(IDC_CMBCONTRACT))->AddString(cstrReadLine); //Ϊ�ؼ���ӳ�ʼ������
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
