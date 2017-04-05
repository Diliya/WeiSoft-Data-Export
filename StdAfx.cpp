// stdafx.cpp : source file that includes just the standard includes
//	AddinDemo.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

BOOL WritePrivateProfileInt(
							LPCTSTR lpAppName,
							LPCTSTR lpKeyName,
							int	 nValues,
							LPCTSTR lpFileName
							)
{
	CString str;
	str.Format("%d",nValues);
	
	return WritePrivateProfileString(lpAppName,lpKeyName,str,lpFileName);
}

CString GetPrivateProfileString(
								LPCTSTR lpAppName,
								LPCTSTR lpKeyName,
								LPCTSTR lpDefault,
								LPCTSTR lpFileName
								)
{
	TCHAR szBuffer[MAX_PATH];
	::GetPrivateProfileString(lpAppName,lpKeyName,lpDefault,szBuffer,MAX_PATH,lpFileName);
	
	return CString(szBuffer);
}

float GetPrivateProfileFloat(
							 LPCTSTR lpAppName,
							 LPCTSTR lpKeyName,
							 float fDefault,
							 LPCTSTR lpFileName
							 )
{
	CString strDefault;
	strDefault.Format("%f",fDefault);
	
	CString strValues = GetPrivateProfileString(lpAppName,lpKeyName,strDefault,lpFileName);
	return (float)atof(strValues);
}

void WritePrivateProfileFloat(
							  LPCTSTR lpAppName,
							  LPCTSTR lpKeyName,
							  float fValues,
							  LPCTSTR lpFileName
							  )
{
	CString strValues;
	strValues.Format("%f",fValues);
	
	WritePrivateProfileString(lpAppName,lpKeyName,strValues,lpFileName);
}