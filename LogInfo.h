/**
*  @file LogInfo.h
*  @brief 记录日志类的头文件
*
*      使用本模块的“LOG_DEBUG_INFO”宏，即可生成即时日志。具体特性如下：
*  @n 1.) 在"Debug"编译模式下，或在"Release"编译模式下在工程设置中定义了"_LOG"选项，
*         产生日志文件；
*  @n 2.) 支持UNICODE编码的日志信息；
*  @n 3.) 支持UNICODE编码的文件格式；
*  @n 4.) 自动添加产生日志信息的细化到毫秒级别的当前时间信息；
*  @n 5.) 自动在日志信息后添加回车换行;
*  @n 6.) 用C/C++类库函数操作文件，提升代码的可移植性;
*  @n 7.) 支持可变参数的日志信息；
*  @n 8.) 返璞归真，恢复对TCHAR和SEH的使用。
*/

#if !defined(AFX_LOGINFO_H__9EABF931_9C07_4EC9_9FF4_CA90E9F59C5D__INCLUDED_)
#define AFX_LOGINFO_H__9EABF931_9C07_4EC9_9FF4_CA90E9F59C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>    // 文件相关操作的头文件
#include <tchar.h>    // TCHAR的头文件

//! UNICODE格式文件头的常量定义
const unsigned short int gc_uUnicodeFileHeader = 0xFEFF;
#define _CRT_SECURE_NO_WARNINGS

/**
*  @brief 记录日志类
*
*      使用本模块的“LOG_DEBUG_INFO”宏，即可生成即时日志。具体特性如下：
*  @n 1.) 在"Debug"编译模式下，或在"Release"编译模式下在工程设置中定义了"_LOG"选项，
*         产生日志文件；
*  @n 2.) 支持UNICODE编码的日志信息；
*  @n 3.) 支持UNICODE编码的文件格式；
*  @n 4.) 自动添加产生日志信息的细化到毫秒级别的当前时间信息；
*  @n 5.) 自动在日志信息后添加回车换行;
*  @n 6.) 用C/C++类库函数操作文件，提升代码的可移植性;
*  @n 7.) 支持可变参数的日志信息；
*  @n 8.) 返璞归真，恢复对TCHAR和SEH的使用。
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
	//    公共的成员变量 :
	//-----------------------------------------------------------------------
	public:
		/**
		*  @brief 记录日志信息
		*
		*      本函数可生成即时日志。具体特性如下：
		*  @n 1.) 在"Debug"编译模式下，或在"Release"编译模式下在工程设置中定义了"_LOG"选项，
		*         产生日志文件；
		*  @n 2.) 支持UNICODE编码的日志信息；
		*  @n 3.) 支持UNICODE编码的文件格式；
		*  @n 4.) 自动添加产生日志信息的细化到毫秒级别的当前时间信息；
		*  @n 5.) 自动在日志信息后添加回车换行;
		*  @n 6.) 用C/C++类库函数操作文件，提升代码的可移植性;
		*  @n 7.) 支持可变参数的日志信息；
		*  @n 8.) 返璞归真，恢复对TCHAR和SEH的使用。
		*
		*  @param szLogFileName[]    日志文件名字符串
		*  @param szFormat[]         日志信息格式字符串
		*  @param ...                可变日志信息
		*  @return static void
		*/
		static void LogInfo( const TCHAR szLogFileName[], const TCHAR szFormat[], ... )
		{
			//若文件大小超过500K,则转移文件
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
			
			// 待记录的日志信息
			TCHAR szLogInfo[1024];

			// 临时信息
			TCHAR szTemp[1024];

			// 当前本机时间的结构实例
			SYSTEMTIME stuSystemTime;

			// 日志文件指针
			FILE * pFile = NULL;

			try
			{
				// 获取当前的本机系统时间
				::GetLocalTime( &stuSystemTime );

				// 按照传入的格式，格式化日志信息 :
				va_list ap;

				va_start( ap, szFormat );
				::_vsntprintf( szTemp, 1024, szFormat, ap );
				va_end( ap );
				// 结束 ( 按照传入的格式，格式化日志信息 )

				// 在日志信息前添加当前时间信息，并在信息尾添加换行信息 :
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
				// 结束 ( 在日志信息前添加当前时间信息，并在信息尾添加换行信息 )
			}
			catch (...)
			{
				return;
			}

			// 打开日志信息文件
			pFile  = ::_tfopen( szLogFileName, _T( "a+b" ) );

			if ( pFile )
			{
				try
				{
					// 偏移到文件尾
					::fseek( pFile, 0, SEEK_END );

					#ifdef _UNICODE 

					// 文件大小
					long lFileSize = 0;

					// 获取文件大小
					lFileSize = ::ftell( pFile );

					// 若当前为UNICODE模式，且当前为新文件，则写入UNICODE格式文件头 :
					if( lFileSize == 0 )
					{
						::fwrite( &gc_uUnicodeFileHeader,
								  sizeof( unsigned short int ),
								  1,
								  pFile );
					}

					#endif 
					// 结束 ( 若当前为UNICODE模式，且当前为新文件，则写入UNICODE格式文件头 )

					// 向文件写入日志信息数据
					::fwrite( szLogInfo,
							  ::_tcslen( szLogInfo ) * sizeof( TCHAR ),
							  1,
							  pFile );

					// 关闭文件 :
					::fclose( pFile );
					// 结束 。
				}
				catch(...)
				{
				}
			}
		}

		static void LogInfo2( const TCHAR szLogFileName[], const TCHAR szFormat[], ... )
		{
			//若文件大小超过500K,则转移文件
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
			
			// 待记录的日志信息
			TCHAR szLogInfo[1024];

			// 临时信息
			TCHAR szTemp[1024];

			// 当前本机时间的结构实例
			SYSTEMTIME stuSystemTime;

			// 日志文件指针
			FILE * pFile = NULL;

			try
			{
				// 获取当前的本机系统时间
				::GetLocalTime( &stuSystemTime );

				// 按照传入的格式，格式化日志信息 :
				va_list ap;

				va_start( ap, szFormat );
				::_vsntprintf( szTemp, 1024, szFormat, ap );
				va_end( ap );
				// 结束 ( 按照传入的格式，格式化日志信息 )

				// 在日志信息前添加当前时间信息，并在信息尾添加换行信息 :
				::_stprintf( szLogInfo,
							 _T( "%s\r\n" ),
							 szTemp );
				// 结束 ( 在日志信息前添加当前时间信息，并在信息尾添加换行信息 )
			}
			catch (...)
			{
				return;
			}

			// 打开日志信息文件
			pFile  = ::_tfopen( szLogFileName, _T( "a+b" ) );

			if ( pFile )
			{
				try
				{
					// 偏移到文件尾
					::fseek( pFile, 0, SEEK_END );

					#ifdef _UNICODE 

					// 文件大小
					long lFileSize = 0;

					// 获取文件大小
					lFileSize = ::ftell( pFile );

					// 若当前为UNICODE模式，且当前为新文件，则写入UNICODE格式文件头 :
					if( lFileSize == 0 )
					{
						::fwrite( &gc_uUnicodeFileHeader,
								  sizeof( unsigned short int ),
								  1,
								  pFile );
					}

					#endif 
					// 结束 ( 若当前为UNICODE模式，且当前为新文件，则写入UNICODE格式文件头 )

					// 向文件写入日志信息数据
					::fwrite( szLogInfo,
							  ::_tcslen( szLogInfo ) * sizeof( TCHAR ),
							  1,
							  pFile );

					// 关闭文件 :
					::fclose( pFile );
					// 结束 。
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
