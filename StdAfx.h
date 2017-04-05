// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__F553FCD2_F7E1_45D0_B6E9_3679B3C4B5AD__INCLUDED_)
#define AFX_STDAFX_H__F553FCD2_F7E1_45D0_B6E9_3679B3C4B5AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 对于使用VC6等较低版本的编译器，LONG_PTR类型可能尚未指定而出现编译错误，将该类型定义为long即可。
#if   _MSC_VER   <=   1200 
typedef long LONG_PTR;
#endif 

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT


#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>			// MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxsock.h>		// MFC socket extensions
#include <afxtempl.h>

class CMainWindowDlg;
interface IMainFramework;

extern CMainWindowDlg * g_pdlgMainWindow;
extern IMainFramework * g_pMainFormework;

BOOL WritePrivateProfileInt(
							LPCTSTR lpAppName,
							LPCTSTR lpKeyName,
							int	 nValues,
							LPCTSTR lpFileName
							);

CString GetPrivateProfileString(
								LPCTSTR lpAppName,
								LPCTSTR lpKeyName,
								LPCTSTR lpDefault,
								LPCTSTR lpFileName
								);

float GetPrivateProfileFloat(
							 LPCTSTR lpAppName,
							 LPCTSTR lpKeyName,
							 float fDefault,
							 LPCTSTR lpFileName
							 );

void WritePrivateProfileFloat(
							  LPCTSTR lpAppName,
							  LPCTSTR lpKeyName,
							  float fValues,
							  LPCTSTR lpFileName
							  );
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__F553FCD2_F7E1_45D0_B6E9_3679B3C4B5AD__INCLUDED_)
