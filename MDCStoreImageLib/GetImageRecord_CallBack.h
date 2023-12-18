//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
//Module:  GetImageRecord_CallBack.h
//PURPOSE: Inherit MDCS_GetDBResultsCCallback base class. It provides functions to 
//         process data returned from db. 
//////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "mdcstoreutilsapi.h"
#include <afxtempl.h>

class CGetImageRecord_CallBack :
   public MDCS_GetDBResultsCCallback
{
public:
   //Constructor
   CGetImageRecord_CallBack(CArray<LONGLONG, LONGLONG> *arrSiteIDs, CArray<LONGLONG, LONGLONG> *arrImageDataID );
   virtual ~CGetImageRecord_CallBack(void){}

  //called to get next row of data returned from datasource
   virtual BOOL GetNextResult(MDCS_QueryResults* pQueryRes) ;

   //called to get number of results
   virtual void SetResultNumber(LONGLONG nCount){};

   //called when there is an error 
   virtual void Error(LPCSTR pErrorText) {return;}

   // called when completely done
   virtual void Done() {return;} 

   //called by other functions to check if results should be returned in their original format
   virtual BOOL ProcessResultsInOriginalFormat()const
   {
      return TRUE;
   } 

   //called to get info about results structure (field names and types)
   //all fields  will be empty
   virtual BOOL GetResultInfo(MDCS_QueryResults* pQueryRes) {return TRUE;};

private:
   // hide the default copy constructors
   CGetImageRecord_CallBack(MDCS_GetDBResultsCCallback const &);
   const CGetImageRecord_CallBack &operator=(MDCS_GetDBResultsCCallback const &); 


   //Member data to hold result callback
   CArray<LONGLONG, LONGLONG> *m_larrSiteIDs;      // pointer to array of site IDs 
   CArray<LONGLONG, LONGLONG> *m_larrImageDataIDs; // pointer to array of image(blob)ids

};
