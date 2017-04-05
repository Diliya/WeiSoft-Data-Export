/**
*  @file LogInfo.h
*  @brief ��¼��־���ͷ�ļ�
*
*      ʹ�ñ�ģ��ġ�LOG_DEBUG_INFO���꣬�������ɼ�ʱ��־�������������£�
*  @n 1.) ��"Debug"����ģʽ�£�����"Release"����ģʽ���ڹ��������ж�����"_LOG"ѡ�
*         ������־�ļ���
*  @n 2.) ֧��UNICODE�������־��Ϣ��
*  @n 3.) ֧��UNICODE������ļ���ʽ��
*  @n 4.) �Զ���Ӳ�����־��Ϣ��ϸ�������뼶��ĵ�ǰʱ����Ϣ��
*  @n 5.) �Զ�����־��Ϣ����ӻس�����;
*  @n 6.) ��C/C++��⺯�������ļ�����������Ŀ���ֲ��;
*  @n 7.) ֧�ֿɱ��������־��Ϣ��
*  @n 8.) ��豹��棬�ָ���TCHAR��SEH��ʹ�á�
*/

#if !defined(AFX_LOGINFO_H__9EABF931_9C07_4EC9_9FF4_CA90E9F59C5D__INCLUDED_)
#define AFX_LOGINFO_H__9EABF931_9C07_4EC9_9FF4_CA90E9F59C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>    // �ļ���ز�����ͷ�ļ�
#include <tchar.h>    // TCHAR��ͷ�ļ�

//! UNICODE��ʽ�ļ�ͷ�ĳ�������
const unsigned short int gc_uUnicodeFileHeader = 0xFEFF;
#define _CRT_SECURE_NO_WARNINGS

/**
*  @brief ��¼��־��
*
*      ʹ�ñ�ģ��ġ�LOG_DEBUG_INFO���꣬�������ɼ�ʱ��־�������������£�
*  @n 1.) ��"Debug"����ģʽ�£�����"Release"����ģʽ���ڹ��������ж�����"_LOG"ѡ�
*         ������־�ļ���
*  @n 2.) ֧��UNICODE�������־��Ϣ��
*  @n 3.) ֧��UNICODE������ļ���ʽ��
*  @n 4.) �Զ���Ӳ�����־��Ϣ��ϸ�������뼶��ĵ�ǰʱ����Ϣ��
*  @n 5.) �Զ�����־��Ϣ����ӻس�����;
*  @n 6.) ��C/C++��⺯�������ļ�����������Ŀ���ֲ��;
*  @n 7.) ֧�ֿɱ��������־��Ϣ��
*  @n 8.) ��豹��棬�ָ���TCHAR��SEH��ʹ�á�
*
*/
class CLogInfo
{
	static BOOL RemoveFiles(LPCTSTR lpszFiles)
	{
		TRY		
		{
			CFile::Remove(lpszFiles);
		}
		CATCH( CFileException, e )
		{
			if( e->m_cause != CFileException::fileNotFound )
			{
				return FALSE;
			}
		}
		END_CATCH
			
			return TRUE;
	}

	//-----------------------------------------------------------------------
	//    �����ĳ�Ա���� :
	//-----------------------------------------------------------------------
	public:
		/**
		*  @brief ��¼��־��Ϣ
		*
		*      �����������ɼ�ʱ��־�������������£�
		*  @n 1.) ��"Debug"����ģʽ�£�����"Release"����ģʽ���ڹ��������ж�����"_LOG"ѡ�
		*         ������־�ļ���
		*  @n 2.) ֧��UNICODE�������־��Ϣ��
		*  @n 3.) ֧��UNICODE������ļ���ʽ��
		*  @n 4.) �Զ���Ӳ�����־��Ϣ��ϸ�������뼶��ĵ�ǰʱ����Ϣ��
		*  @n 5.) �Զ�����־��Ϣ����ӻس�����;
		*  @n 6.) ��C/C++��⺯�������ļ�����������Ŀ���ֲ��;
		*  @n 7.) ֧�ֿɱ��������־��Ϣ��
		*  @n 8.) ��豹��棬�ָ���TCHAR��SEH��ʹ�á�
		*
		*  @param szLogFileName[]    ��־�ļ����ַ���
		*  @param szFormat[]         ��־��Ϣ��ʽ�ַ���
		*  @param ...                �ɱ���־��Ϣ
		*  @return static void
		*/
		static void LogInfo( const TCHAR szLogFileName[], const TCHAR szFormat[], ... )
		{
			//���ļ���С����500K,��ת���ļ�
			CFileStatus status;
			if(CFile::GetStatus(szLogFileName,status))
			{
				if(status.m_size >= 500*1024)
				{
					CTime time = CTime::GetCurrentTime();
					CString strFileName = szLogFileName + time.Format("%Y-%m-%d %H#%M#%S.txt");
					::CopyFile(szLogFileName, strFileName, FALSE);
					
					RemoveFiles(szLogFileName);
				}
			}
			
			// ����¼����־��Ϣ
			TCHAR szLogInfo[1024];

			// ��ʱ��Ϣ
			TCHAR szTemp[1024];

			// ��ǰ����ʱ��Ľṹʵ��
			SYSTEMTIME stuSystemTime;

			// ��־�ļ�ָ��
			FILE * pFile = NULL;

			try
			{
				// ��ȡ��ǰ�ı���ϵͳʱ��
				::GetLocalTime( &stuSystemTime );

				// ���մ���ĸ�ʽ����ʽ����־��Ϣ :
				va_list ap;

				va_start( ap, szFormat );
				::_vsntprintf( szTemp, 1024, szFormat, ap );
				va_end( ap );
				// ���� ( ���մ���ĸ�ʽ����ʽ����־��Ϣ )

				// ����־��Ϣǰ��ӵ�ǰʱ����Ϣ��������Ϣβ��ӻ�����Ϣ :
				::_stprintf( szLogInfo,
							 _T( "%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d    %s\r\n" ),
							 stuSystemTime.wYear,
							 stuSystemTime.wMonth,
							 stuSystemTime.wDay,
							 stuSystemTime.wHour,
							 stuSystemTime.wMinute,
							 stuSystemTime.wSecond,
							 stuSystemTime.wMilliseconds,
							 szTemp );
				// ���� ( ����־��Ϣǰ��ӵ�ǰʱ����Ϣ��������Ϣβ��ӻ�����Ϣ )
			}
			catch (...)
			{
				return;
			}

			// ����־��Ϣ�ļ�
			pFile  = ::_tfopen( szLogFileName, _T( "a+b" ) );

			if ( pFile )
			{
				try
				{
					// ƫ�Ƶ��ļ�β
					::fseek( pFile, 0, SEEK_END );

					#ifdef _UNICODE 

					// �ļ���С
					long lFileSize = 0;

					// ��ȡ�ļ���С
					lFileSize = ::ftell( pFile );

					// ����ǰΪUNICODEģʽ���ҵ�ǰΪ���ļ�����д��UNICODE��ʽ�ļ�ͷ :
					if( lFileSize == 0 )
					{
						::fwrite( &gc_uUnicodeFileHeader,
								  sizeof( unsigned short int ),
								  1,
								  pFile );
					}

					#endif 
					// ���� ( ����ǰΪUNICODEģʽ���ҵ�ǰΪ���ļ�����д��UNICODE��ʽ�ļ�ͷ )

					// ���ļ�д����־��Ϣ����
					::fwrite( szLogInfo,
							  ::_tcslen( szLogInfo ) * sizeof( TCHAR ),
							  1,
							  pFile );

					// �ر��ļ� :
					::fclose( pFile );
					// ���� ��
				}
				catch(...)
				{
				}
			}
		}

		static void LogInfo2( const TCHAR szLogFileName[], const TCHAR szFormat[], ... )
		{
			//���ļ���С����500K,��ת���ļ�
			CFileStatus status;
			if(CFile::GetStatus(szLogFileName,status))
			{
				if(status.m_size >= 500*1024)
				{
					CTime time = CTime::GetCurrentTime();
					CString strFileName = szLogFileName + time.Format("%Y-%m-%d %H#%M#%S");
					::CopyFile(szLogFileName, strFileName, FALSE);
					
					RemoveFiles(szLogFileName);
				}
			}
			
			// ����¼����־��Ϣ
			TCHAR szLogInfo[1024];

			// ��ʱ��Ϣ
			TCHAR szTemp[1024];

			// ��ǰ����ʱ��Ľṹʵ��
			SYSTEMTIME stuSystemTime;

			// ��־�ļ�ָ��
			FILE * pFile = NULL;

			try
			{
				// ��ȡ��ǰ�ı���ϵͳʱ��
				::GetLocalTime( &stuSystemTime );

				// ���մ���ĸ�ʽ����ʽ����־��Ϣ :
				va_list ap;

				va_start( ap, szFormat );
				::_vsntprintf( szTemp, 1024, szFormat, ap );
				va_end( ap );
				// ���� ( ���մ���ĸ�ʽ����ʽ����־��Ϣ )

				// ����־��Ϣǰ��ӵ�ǰʱ����Ϣ��������Ϣβ��ӻ�����Ϣ :
				::_stprintf( szLogInfo,
							 _T( "%s\r\n" ),
							 szTemp );
				// ���� ( ����־��Ϣǰ��ӵ�ǰʱ����Ϣ��������Ϣβ��ӻ�����Ϣ )
			}
			catch (...)
			{
				return;
			}

			// ����־��Ϣ�ļ�
			pFile  = ::_tfopen( szLogFileName, _T( "a+b" ) );

			if ( pFile )
			{
				try
				{
					// ƫ�Ƶ��ļ�β
					::fseek( pFile, 0, SEEK_END );

					#ifdef _UNICODE 

					// �ļ���С
					long lFileSize = 0;

					// ��ȡ�ļ���С
					lFileSize = ::ftell( pFile );

					// ����ǰΪUNICODEģʽ���ҵ�ǰΪ���ļ�����д��UNICODE��ʽ�ļ�ͷ :
					if( lFileSize == 0 )
					{
						::fwrite( &gc_uUnicodeFileHeader,
								  sizeof( unsigned short int ),
								  1,
								  pFile );
					}

					#endif 
					// ���� ( ����ǰΪUNICODEģʽ���ҵ�ǰΪ���ļ�����д��UNICODE��ʽ�ļ�ͷ )

					// ���ļ�д����־��Ϣ����
					::fwrite( szLogInfo,
							  ::_tcslen( szLogInfo ) * sizeof( TCHAR ),
							  1,
							  pFile );

					// �ر��ļ� :
					::fclose( pFile );
					// ���� ��
				}
				catch(...)
				{
				}
			}
		}
};

#define LOG_DEBUG_INFO CLogInfo::LogInfo
#define LOG_DEBUG_INFO2 CLogInfo::LogInfo2

#endif // !defined(AFX_LOGINFO_H__9EABF931_9C07_4EC9_9FF4_CA90E9F59C5D__INCLUDED_)
