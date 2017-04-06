#if !defined(AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_)
#define AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainWindowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg dialog
#define	 WM_NOTIFY_UPDATE	WM_APP + 1
#include "AddinInterface.h"
#include "afxwin.h"

class CMainWindowDlg : public CDialog
{
// Construction
public:
	void WriteLog(CString strLog);
	CMainWindowDlg(CWnd* pParent = NULL);   // standard constructor
	bool FileExist(CString strLog);
	bool DirectoryExist(CString Path);
	bool CreateDirectory(CString path);

// Dialog Data
	//{{AFX_DATA(CMainWindowDlg)
	enum { IDD = IDD_DIALOG_MAIN_WINDOW };
	CEdit	m_editMsg;
	int		m_iDirection;
	int		m_iOffSet;
	int		m_iVolume;
	float	m_fPrice;
	int		m_iPriceType;
	BOOL	m_bHedge;
	CString	m_strInstrumentID;
	int		m_iOrderActionID;
	//}}AFX_DATA

	BOOL m_bInit;

	void ReportUpdate(LPARAM l);
	void OrderStatus(BARGAIN_NOTIFY_KSI * pKsi);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnButton1();
	afx_msg void OnCheckRport1();
	afx_msg void OnCheckReport2();
	afx_msg void OnButtonLoad();
	afx_msg void OnButtonPing();
	afx_msg void OnCheckStart();
	afx_msg void OnButton1Gedata();
	afx_msg void OnButtonGet2();
	afx_msg void OnButtonOrderin();
	afx_msg void OnButtonOrderAction();
	//}}AFX_MSG
	afx_msg LRESULT OnNotifyUpdate(WPARAM w,LPARAM l);
	DECLARE_MESSAGE_MAP()


private:
	CString m_strInfo;
public:
//	CString m_save_path;
	afx_msg void OnBnClickedBtnGet1min();
	CString m_Contract;
	CString m_TimeLevel;
	CComboBox m_Time;
	CComboBox m_Contr;
	afx_msg void OnBnClickedButton2();
	CString m_strPath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_)
