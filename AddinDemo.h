// AddinDemo.h : main header file for the ADDINDEMO DLL
//

#if !defined(AFX_ADDINDEMO_H__E6D39031_BD4D_4B9F_A0BF_84D6DF337BD5__INCLUDED_)
#define AFX_ADDINDEMO_H__E6D39031_BD4D_4B9F_A0BF_84D6DF337BD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAddinDemoApp
// See AddinDemo.cpp for the implementation of this class
//

class CAddinDemoApp : public CWinApp
{
public:
	CAddinDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddinDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CAddinDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINDEMO_H__E6D39031_BD4D_4B9F_A0BF_84D6DF337BD5__INCLUDED_)
