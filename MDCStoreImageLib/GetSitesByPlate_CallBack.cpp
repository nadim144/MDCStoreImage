
//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
// Module:  GetSitesByPlate_CallBack.cpp
// Purpose: Provide functions to process data and get all Site IDs belonging to a plate
//  
/////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include ".\getsitesbyplate_callback.h"
#include <iostream>
using namespace std;

//==============================================================================================
// FUNCTION: Constructor
// PARAMETER: 
//		m_plarrSieIDs - pointer to array which stores all siteid returned from db.
//==============================================================================================
CGetSitesByPlate_CallBack::CGetSitesByPlate_CallBack(CArray<LONGLONG, LONGLONG>* parrSiteID): m_plarrSiteIDs(parrSiteID)
{   
}

//==============================================================================================
// FUNCTION: GetNextResult
// PURPOSE: Called to get next row of data
//==============================================================================================
BOOL CGetSitesByPlate_CallBack::GetNextResult(MDCS_QueryResults* pQueryRes)
{
   ASSERT(pQueryRes);
   if(!pQueryRes)
      return TRUE;

   //check if data is empty - if it is empty, function will return -LLONG_MAX 
   LONGLONG lValue = pQueryRes->GetLongValue("SITE_ID");
   if (lValue == -LLONG_MAX)
   {
      return TRUE;
   }
   m_plarrSiteIDs->Add(lValue);

   return TRUE;

}

