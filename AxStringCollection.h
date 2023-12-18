//***********************************************************************************************
//
//    Copyright (c) 1999-2003 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  AxStringCollection.CPP
// PURPOSE: Interface header for AxStringCollection component.
// AUTHOR:  SB Oct 2004
//

#ifndef INC_AXSTRINGCOLLECTION_H
#define INC_AXSTRINGCOLLECTION_H

#pragma once



// The following #ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the AXAS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AXAS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being expo rted.
#ifdef AXCOLLECTION_EXPORTS
   #define AXCOLLECTION_API __declspec(dllexport)
#else
   #define AXCOLLECTION_API __declspec(dllimport)
#endif

class AxStringInterface;
class AxStringArrayInterface;

////////////////////////////////////////////////////////////////////////////////////
// Class AxStringPtr
//
class AXCOLLECTION_API AxString
{
private:
   AxStringInterface* m_pAxString;

public:
   AxString();   
   AxString( LPCSTR pszData );   
   AxString( AxString &strSrc );
   ~AxString();

   operator LPCSTR() const;
   LPCSTR operator[](int nIndex) const;
   AxString&  operator=( const AxString &strSrc );
};

////////////////////////////////////////////////////////////////////////////////////
// Class AxStringPtr
//
class AXCOLLECTION_API AxStringArray
{
private:
   AxStringArrayInterface* m_pAxStringArray;

public:
   AxStringArray();      
   ~AxStringArray();

   LPCSTR operator[](INT_PTR nIndex) const;
   LPCSTR GetAt(INT_PTR nIndex) const;
   INT_PTR GetSize() const;
   INT_PTR Add( LPCSTR pSrc );
   void RemoveAll();
   void Copy( const AxStringArray& arrayString);
 //  void Copy( const CStringArray& arrayString);
};


#endif // INC_AXSTRINGCOLLECTION_H