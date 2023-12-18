//******************************************************************************
//   
// Copyright (c) 2005 Molecular Devices
// All rights reserved.
//******************************************************************************
// Module:  MDCStoreImageExample.cpp 
// Purpose: This is a console application to demonstrate using the functions in 
//          MDCStoreUtils lib to get images from MDCStore database.
// Author:  Vy , August 05 
// Modified: MNS, Sept 05 
/////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MDCStoreImageExample.h"
#include "GetSitesByPlate_CallBack.h"
#include "GetImageRecord_CallBack.h"
#include "BlobCallbackEx.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MDCStoreUtilsApi.h"     //always include this file to use funcions provided in MDCStoreUtils
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

// The one and only application object
CWinApp theApp;

using namespace std;

#define  DEFAULT_PLATE_ID  18;


//predefine functions that will be described later
//main function
void ExecMain(const MDCS_ST_UserLogin& stUserLogin, LONGLONG lPlate);
//function that will be called when ExecMain is finished
void ExitMain(void);
//function to get images
BOOL GetImages(HDBHANDLE hDBHandle, LONGLONG lPlateID);
//function to show the DB error return to user
BOOL ShowDBDllError(LPCSTR  strErrorExtra );

//////////////////////////////////////////////////////////////////////////////////////
//===========================================================================================================   
//Main program - entry of application
//PURPOSE: To get image of the specific site when you have a plate ID 
//===========================================================================================================
int main(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;  
  
   // initialize MFC and print an error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
 
   //enums to define argument types
   enum E_ArgType
   {
      eUnknown,
      eUser,
      ePassword,
      eDSN,
      eDB,
      ePlate,
   };

   E_ArgType eArgType = eUnknown;

   //we need to fill out MDCS_ST_UserLogin structure with login information
   //to pass it to the functions that create databse connection
   //structure MDCS_ST_UserLogin is used to get DB handle
   //the following members of the structure should be specified:
   //szUserName
   //szPassword
   //szDSN
   //szDatabase is optional and it's used if ODBC datasource was set up without indicating database name
   //Structure can be fill out manually or by calling function MDCS_CONNECTION_GetDetails
   //Function MDCS_CONNECTION_GetDetails will display Login dialog where you can set login information
   //I.e. MDCS_CONNECTION_GetDetails(&stUserLogin,NULL,NULL,"MDCS Example",NULL,FALSE);
   MDCS_ST_UserLogin stUserLogin ;    //hold user login info 
   LONGLONG lPlateID = DEFAULT_PLATE_ID;
   for (int n = 1; n < argc; n++)
   {
      LPCSTR pszSt1 =  (LPCSTR) argv[n];
      switch(eArgType)
      {
      case eUnknown:
         {
            if (stricmp("-u", pszSt1) == 0)
               eArgType = eUser;
            else if (stricmp("-p", pszSt1) == 0)
               eArgType = ePassword;
            else if (stricmp("-dsn", pszSt1) == 0)
               eArgType = eDSN;
            else if (stricmp("-db", pszSt1) == 0)
               eArgType = eDB;
            if (stricmp("-plate", pszSt1) == 0)
               eArgType = ePlate;
            break;
         }
      case eUser:
         strncpy(stUserLogin.szUserName, pszSt1, min(sizeof(stUserLogin.szUserName) - 1, strlen(pszSt1)));
         eArgType = eUnknown;
         break;
      case ePassword:
         strncpy(stUserLogin.szPassword, pszSt1, min(sizeof(stUserLogin.szPassword) - 1, strlen(pszSt1)));
         eArgType = eUnknown;
         break;
      case eDSN:
         strncpy(stUserLogin.szDSN, pszSt1, min(sizeof(stUserLogin.szDSN) - 1, strlen(pszSt1)));
         eArgType = eUnknown;
         break;
      case eDB:
         strncpy(stUserLogin.szDatabase, pszSt1, min(sizeof(stUserLogin.szDatabase) - 1, strlen(pszSt1)));
         eArgType = eUnknown;
         break;
      case ePlate:
         lPlateID = _atoi64(pszSt1);
         eArgType = eUnknown;
         break;
      default:
         break;
      }
   }
  
   //diaplay message if not all parameters are specified 
   if (!(strlen(stUserLogin.szDSN) && strlen(stUserLogin.szPassword) && strlen(stUserLogin.szUserName)))
   {
      _tprintf(_T("Please specify command line parameters:\n"
                  "-u <User name>,\n"
                  "-p <Password>,\n"
                  "-dsn <ODBC datasource name>\n"
                  "-db <database name> - this parameter is optional\n"
                  "-plate <plate ID> - this parameter is optional\n\n"));


      int ch;
      _cputs( "Press any key to exit." );
      ch = _getch();
      _cputs( "\r\n" );
      exit(1);
   }

   cout << "Step 1 main " << endl;
   bool flag = MDCStoreUtils_Init();				   //Initialize the MDCStore interface
   atexit(ExitMain);
   ExecMain(stUserLogin, lPlateID);
	return nRetCode;
}

void ExecMain(const MDCS_ST_UserLogin& stUserLogin, LONGLONG lPlateID)
{
	cout << "Step 2 ExecMain " << endl;   

   //get database handle 
   MDCS_DBHandleSmartPtr ptrDB(stUserLogin);
   
   //check if we got a valid connection
   if (ptrDB.GetHandle())
   {
	   cout << "lUserLoginID ID:\t" << stUserLogin.lUserLoginID << endl;
	   cout << "lUserGroupID ID:\t" << stUserLogin.lUserGroupID << endl;
	   cout << "eUserStatus ID:\t" << stUserLogin.eUserStatus << endl;
	   cout << "szDSN ID:\t" << stUserLogin.szDSN << endl;
	   cout << "szUserName ID:\t" << stUserLogin.szUserName << endl;
	   cout << "szPassword ID:\t" << stUserLogin.szPassword << endl;
	   cout << "bUseTrusted ID:\t" << stUserLogin.bUseTrusted << endl;
	   cout << "bUseServer ID:\t" << stUserLogin.bUseServer << endl;
      //get images for a plate that have ID 18
      BOOL bReturn = GetImages(ptrDB.GetHandle(), lPlateID);
      if (!bReturn )
         ShowDBDllError("Function failed.\nReason:");  
   }
   else
   {
      cout << "Execution canceled." << endl;
   }

   int ch;
   _cputs( "\n\nPress any key to exit." );
   ch = _getch();
   _cputs( "\r\n" );
}

void ExitMain(void)
{
   //call function to detach MDCStoreUtils interface 
   MDCStoreUtils_Finished(); 
}

//========================================================================
//FUNCTION : GetPlateInfo
//PURPOSE:   Get plate info and print out the plate info
//PARAMETERs: 
//    hDBHandle - db handle
//    lPlateID - a plate ID
//========================================================================  
BOOL GetPlateInfo(HDBHANDLE hDBHandle, LONGLONG lPlateID)
{
   cout << "hDBHandle " << hDBHandle << " was not found.\n" << endl;
	MDCS_ST_PlateInfo st_PlateInfo;
   cout << "Retrieve plate info "  << endl;
   if(!MDCS_PLATE_GetInfo(hDBHandle, lPlateID, st_PlateInfo))
      return FALSE;
	else
	{
      if (!st_PlateInfo.lPlateID)
      {
         cout << "Plate with Plate ID " << lPlateID << " was not found.\n"<< endl;
         return FALSE;
      }

      // Print out plate info
      cout << "The plate info " << endl;
      cout << "Plate ID:\t" << lPlateID << endl;
      cout << "Plate name:\t" << st_PlateInfo.szPlateName << endl;
      cout << "Xwells:\t"  << st_PlateInfo.nXWells << endl;
      cout << "Ywells:\t" << st_PlateInfo.nYWells << endl;
      cout << "Aquisition:\t" << st_PlateInfo.szAcqName << endl;
      cout << "Barcode:\t" << st_PlateInfo.szBarcode << endl;
      cout << "Creator:\t" << st_PlateInfo.szCreator << endl;
      cout << "Description:\t" << st_PlateInfo.szDesc << endl;
      cout << "\n\n" ;
	}
   return TRUE;
}

//========================================================================
//FUNCTION : GetImageIDsPerSite
//PURPOSE:   Helper function to get all the image ids that belongs to one site
//PARAMETERs:  
//    lSiteID - a site ID
//    larrSiteIDImages - array of SiteID that have images in a plate
//    larrImageIDs - array of all Image IDs of the plate
//========================================================================
BOOL GetImageIDsPerSite(LONGLONG lSiteID,
						CArray<LONGLONG,LONGLONG>& larrSiteIDImages, 
						CArray<LONGLONG,LONGLONG>& larrImageIDs,
                  CArray<LONGLONG,LONGLONG>& larrImageIDPerSie)

{
	
	cout << "List of image IDs that belong to the specific site ID,\nthis case is site id : " << lSiteID << endl; 
   for(int nCount = 0; nCount < larrSiteIDImages.GetSize(); nCount++)
   {
      if(larrSiteIDImages[nCount]== lSiteID )
      {
         larrImageIDPerSie.Add(larrImageIDs[nCount]);
         cout << "Image ID: " << larrImageIDs[nCount] << endl;
      }
   }
   return TRUE;

}
   
//========================================================================
//FUNCTION : GetImages
//PURPOSE:   Get all image from database using image id and save them in drive C
//PARAMETERs:  
//    hDBHandle - db handle
//    larrImageIDs - array of ImageIDs of the site
//========================================================================
BOOL GetImages(HDBHANDLE hDBHandle, CArray<LONGLONG, LONGLONG>& larrImageIDs)
{
	//Create file handle to write to it 
    MDCS_E_BlobType eBlobType = MDCS_eBlobSiteImage;
    LONGLONG lTotalSize = 0;

    CString strFileNameTemplate = "Image_%d.%s";
    CString strFileNameTemplate2 = "Image_%d.jpg";
    CString strFileName;

    //get each image from database to C drive
    for ( int nCount = 0; nCount < larrImageIDs.GetSize(); nCount++ )
    {
      
      //get image info and use information about original file extension to create files on disk 
      MDCS_ST_BlobInfo stBlobInfo;
      if (!MDCS_BLOB_GetInfo(hDBHandle, &stBlobInfo, larrImageIDs.GetAt(nCount), MDCS_eBlobSiteImage))
         return FALSE;

      if (!stBlobInfo.lBlobID)
      {
         cout << "Image with ID " << larrImageIDs.GetAt(nCount) << " is not found in the database" << endl;
         continue;
      }

      CString strExt;
      if (!strlen(stBlobInfo.szImportExtension))
         strFileName.Format(strFileNameTemplate2,nCount);
      else
         strFileName.Format(strFileNameTemplate,nCount, stBlobInfo.szImportExtension);
      HANDLE hFile;

      //create image file
      hFile = CreateFile(strFileName,
                     FILE_WRITE_DATA,
                     FILE_SHARE_WRITE,
                     NULL,
                     CREATE_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL) ;

      if (hFile == INVALID_HANDLE_VALUE) 
      { 
		   cout << "Could not open file." << endl;   
      }
      CBlobCallbackEx pCallBack( hFile, lTotalSize, strFileName , 1024*16); //1024*16 is default size
      if(!MDCS_BLOB_Get(hDBHandle, larrImageIDs[nCount], eBlobType , &pCallBack))
      {
		   CloseHandle(hFile);
		   return FALSE;
      }
      cout <<  "Image " << nCount + 1 <<  " saved into " << strFileName.GetBuffer() << endl;
      CloseHandle(hFile);
    }  
    return TRUE;
}

//To show the DB error return to user
BOOL ShowDBDllError(LPCSTR  strErrorExtra )
{
   char szError[MDCS_MAX_ERR_SIZE] = "";
   //call function that returns description of the last error that occurred in MDCStoreUtils.dll
   if (MDCS_GetLastErrorMsg(szError, MDCS_MAX_ERR_SIZE) == MDCS_ERR_SUCCESS)
      //exit if error if  there is no error
      return FALSE;

   CString strErr;
   strErr.Format("%s\n%s", strErrorExtra, szError);
   cout << strErr << endl;
   return FALSE;
}

//========================================================================
//FUNCTION : GetImages
//PURPOSE:   Call other functions to get image
//PARAMETERs:  
//    hDBHandle - db handle
//    lPlateID - Plate ID
//RETURN: FALSE - if fails or error occurs
//========================================================================
BOOL GetImages(HDBHANDLE hDBHandle, LONGLONG lPlateID)
{

	cout << "Step 3 GetImages " << endl;
   //Get plate info and print out
	if(!GetPlateInfo(hDBHandle,lPlateID))
      return FALSE;

   //Get all sites belonging to the plate
   CArray<LONGLONG, LONGLONG> larrSiteIDs ;
   CGetSitesByPlate_CallBack pResult(&larrSiteIDs);
   //Call function in MDCStoreutilsapi
   if(!MDCS_PLATE_GetSitesByPlate(hDBHandle, lPlateID, &pResult))
      return FALSE;

   LONGLONG lSiteID = 0;
   //Get first site id return
   if(larrSiteIDs.GetSize())
	   lSiteID = larrSiteIDs[0];   	 
   else
   {
      _tprintf(_T("No sites were found for the selected plate"));
      return FALSE;
   }
   
   CArray<LONGLONG, LONGLONG> larrSiteIDImages;     //store all siteID has image in the plate 
   CArray<LONGLONG, LONGLONG> larrImageIDs;         //store all image id in the plate

   //Call to get all siteIDs and ImageIDs of the plate
	CGetImageRecord_CallBack pResultImage(&larrSiteIDImages,&larrImageIDs);
   if(!MDCS_PLATE_GetImageRecordPerPlate(hDBHandle, lPlateID, &pResultImage))
      return FALSE;

   cout << "Step 4 GetImageIDsPerSite " << endl;

	CArray<LONGLONG, LONGLONG> larrImageIDOneSites ; //hold all the image id of the first site return from Db
	if(!GetImageIDsPerSite(lSiteID,larrSiteIDImages,larrImageIDs, larrImageIDOneSites))
      return FALSE;

   //Get all image belong to the first siteId return from database and save in drive C 
	if(!GetImages(hDBHandle, larrImageIDOneSites))
      return FALSE;

   return TRUE;  
}
