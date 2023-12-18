//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
// MODULE:  GetImageRecord_CallBack.cpp
// PURPOSE: Inherit from GetDBREsultsCCallback. It provides function to process and 
//		   retrieved data from db 
//////////////////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include ".\getimagerecord_callback.h"
#include <iostream>

using namespace std;

//==============================================================================================
// FUNCTION: Constructor to initialize object
// PARAMETERS: 
//		arrSiterIDs - array of long to hold the all site id returned from db
//		arrImageDataIDs - array of long to hold all the image(blob)ids returned from db
//==============================================================================================
CGetImageRecord_CallBack::CGetImageRecord_CallBack(CArray<LONGLONG, LONGLONG> *arrSiteIDs, CArray<LONGLONG, LONGLONG> *arrImageDataID): m_larrSiteIDs(arrSiteIDs), m_larrImageDataIDs(arrImageDataID)
{
}


//==============================================================================================
// FUNCTION: GetNextResult
// PURPOSE: Get next row of data returned from datasource
//==============================================================================================
BOOL CGetImageRecord_CallBack::GetNextResult(MDCS_QueryResults* pQueryRes)
{
   ASSERT(pQueryRes);
   if(!pQueryRes)
      return TRUE;

   LONGLONG lSiteValue = pQueryRes->GetLongValue("SITE_ID");
   LONGLONG lImageValue = pQueryRes->GetLongValue("IMAGE_DATA_ID");
   //check if data is empty - if it is empty, function will return -LLONG_MAX  
   if(lSiteValue == -LLONG_MAX || lImageValue == -LLONG_MAX )
   {
      return TRUE;
   }
   m_larrSiteIDs->Add(lSiteValue);
   m_larrImageDataIDs->Add(lImageValue);
  
   return TRUE;
}