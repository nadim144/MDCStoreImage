//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
//Module:  CBlobCallbackEx.cpp
//PURPOSE: Extension of the class CBlobCallback, it 
//         enables saving of data directly file 
//////////////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include ".\blobcallbackex.h"

// Constructor to initilize the object 
CBlobCallbackEx::CBlobCallbackEx( HANDLE file, LONGLONG uTotalSize, LPCSTR pszFileName, UINT uChunkSize /*= DEFAULT_CHUNK_SIZE */) :
    m_file(file), m_uChunkSize(uChunkSize), m_uTotalSize(uTotalSize), m_strFileName(pszFileName)
{
   m_lCurSize = 0;
}

//==============================================================================================
// FUNCTION: NextResult
// PURPOSE:  Next result is retrieved, returns size of the result
//==============================================================================================
BOOL CBlobCallbackEx::NextResult(LONGLONG lResultSize)
{
    return TRUE;
}
//==============================================================================================
// FUNCTION: NextChunk
// PURPOSE: Next chunk of data that will be received from database
// 
// PARAMETERS:
//       pChuck - data
//       uChunkSize - size of data to be retrieved
// RETURN : FALSE - if error occur
//==============================================================================================
BOOL CBlobCallbackEx::NextChunk(const BYTE* pChunk, UINT uChunkSize )   
{      
	DWORD dwByteWritten;
	
	if (!WriteFile(m_file, pChunk, uChunkSize, &dwByteWritten, NULL))
	{
	   char szErrorBuf[256];
	   ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
 					NULL, GetLastError(),
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					szErrorBuf, sizeof(szErrorBuf), NULL);

	   char szError[512] = {0};
	   sprintf(szError, "Cannot write into file '%s'.\r\nReason: %s", m_strFileName, szErrorBuf);
	   Error(szError);
       return FALSE;
   }

   float fPercent = ((float) m_lCurSize /(float)GetTotalSize() * 100);;
   

   m_lCurSize += uChunkSize;      
   return TRUE;
}

//==============================================================================================
// FUNCTION: Error 
// PURPOSE:  Display message box when error occurs 
//==============================================================================================
 
void CBlobCallbackEx::Error(LPCSTR pErrorText)
{                
   _tprintf(pErrorText);
}

//==============================================================================================
//FUNCTION: GetTotalSize
//PURPOSE:  To get total size of data retrieved
//==============================================================================================
LONGLONG CBlobCallbackEx::GetTotalSize() const
{
   return m_uTotalSize;
}

//==============================================================================================
//Function: GetPacketSize
//PURPOSE:  To get data chunk size
//==============================================================================================
UINT CBlobCallbackEx::GetPacketSize() const
{
   return m_uChunkSize;
}

void CBlobCallbackEx::Done()
{
   ;
}
