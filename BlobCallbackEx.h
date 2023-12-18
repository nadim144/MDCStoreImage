//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
//Module:  CBlobCallbackEx.cpp
//PURPOSE: Callback class to get blob data , it 
//         enables saving of data directly file  
//////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "mdcstoreutilsapi.h"
class CBlobCallbackEx : public MDCS_GetBlobCallback 
{
private:
  
   HANDLE            m_file;       //file handle to open file to write to.
   LONGLONG          m_lCurSize;   //curent size of data retrieved
   UINT              m_uChunkSize; //size of data chunk
   LONGLONG          m_uTotalSize; //Total size of data retrieved
   LPCSTR			   m_strFileName;//File name 


public:

   enum {DEFAULT_CHUNK_SIZE = (1024*16) };

   //Constructor
   CBlobCallbackEx( HANDLE file, LONGLONG uDataSize, LPCSTR pszFileName, UINT uChunkSize = DEFAULT_CHUNK_SIZE );
   virtual ~CBlobCallbackEx() {};
 
   // next result is retrieved, returns size of the result
   virtual BOOL NextResult(LONGLONG lResultSize);
   
   // To get the next chunk of data from source( database or file server)
   virtual BOOL NextChunk( const BYTE* pChuck, UINT uChunkSize );   

   // Sent error when there is an error
   virtual void Error(LPCSTR pErrorText);
   
   // Get the total size of data retrieved
   virtual LONGLONG GetTotalSize() const;

   // Get the package size
   virtual UINT GetPacketSize() const;
    
   // called when completely done
   virtual void Done();
 
    
private:
    // hide the default copy constructors
    CBlobCallbackEx(CBlobCallbackEx const &);
    const CBlobCallbackEx &operator=(CBlobCallbackEx const &);      
};
