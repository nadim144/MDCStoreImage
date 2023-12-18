//***********************************************************************************************
//
//    Copyright (c) 2005 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  MDCSStructers.h
// PURPOSE: 
// AUTHOR:  MS  Jan 2005
// structures that are used in MDCStoreUtils 

#if !defined(AFX_MDCSTRUCTURES_H_INCLUDED)
#define AFX_MDCSTRUCTURES_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#pragma pack(push, 4)

#ifndef RC_INVOKED

#include "MDCSDefinitions.h"
#include "MDCSEnums.h"
#include <stdlib.h>  
#include <time.h>   

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
// The following #ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the _MDCSTOREUTILS_DLL
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// AXCB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef  _MDCSTOREUTILS_DLL
   #define MDCSUTILS   __declspec(dllexport)
#else
   #define MDCSUTILS   __declspec(dllimport)
#endif


   //////////////////////////////////////////////////////////////////////////////////
// common structures
//////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////
//structure of the column from table_columns table
//represents MDCStore data type info
struct  MDCS_ST_COLUMNPROP
{
   LONGLONG                   lColID;                                       //database ID
   LONGLONG                   lAssayID;                                     //assay ID - ID of an assay where it is used 
   float                      fNormalizationFactor;                         // normalization factor
   int                        nOrderNumber;                                 //order number of a data type on the resultset
   BOOL                       bAppColumn;                                   //indicates that column is an application column (get only)
   MDCS_E_RatioType           eRatioType;                                   //ratio type that will be applied to data
   MDCS_E_Waves               eWaveNum;                                     //wavelength numerator   
   MDCS_E_Waves               eWaveDenom;                                   //wave denominator
   //MDCS_E_NormalizationType   eNormalizationType;                           //normalization type of data
   int                        nNormalSettingsID;                            //normalization settings ID
   MDCS_E_AverageType         eAverageType;                                 //average method for the data 
   MDCS_E_ColumnType          eColumnType;                                  //type of data
   char                       szColName[MDCS_MAX_COL_NAME];                 //name of the column as in database 
   char                       szColNameFull[MDCS_MAX_COL_NAMEEXT];          //name of the column as display name
	char                       szColDescr[MDCS_MAX_COL_DESCRCOLUMN];         //description of the data type
	char                       szTableName[MDCS_MAX_RESULTSETID];            //database resultset ID (foreign key for the row)
   char                       szMeasurementName[MDCS_MAX_OBJ_NAME];         //name of the measurement
   char                       szFunctionName[MDCS_MAX_OBJ_NAME];            // name of the function
   
   MDCS_ST_COLUMNPROP() { memset(this, 0, sizeof(*this)); }	
};

/////////////////////////////////
//structure of the column from table_columns table
//represents MDCStore data type info
/*struct  MDCS_ST_ScopeDatatypeProp
{
  char                       szScopeName[MDCS_MAX_SCOPE];                  //name of the scope
  MDCS_ST_COLUMNPROP         stColumnAttr;                                 //description of column propery

  MDCS_ST_ScopeDatatypeProp() { memset(this, 0, sizeof(*this)); }	
}*/
//////////////////////////////////////////////
//structure that describes blob location on server
struct  MDCS_ST_BlobLocation
{
	LONGLONG  nLocationID;                 // database ID
   int 	nPort;                           // server port
   MDCS_E_FileStorage   eStorageType;     //storage type - file server or UNC
   char	szServerName[MDCS_MAX_SERVER];   // file server name, e.g. fileserver.moldev.com
   char 	szServerRoot[_MAX_DIR];          // server root, e.g. c:\files
   char  szServerDirectory[_MAX_DIR];     // directory where file is located
  
   MDCS_ST_BlobLocation()
   {
      memset(this, 0, sizeof(*this));     
      eStorageType = MDCS_eUNCServer;
   }
};
/////////////////////////////////
//structure that describes basic blob info
struct  MDCS_ST_BlobInfo
{
   LONGLONG                lBlobID;                               // blob id
   LONGLONG                lBlobSize;                             // size of the blob, in bytes
   MDCS_E_ImageType        eType;                                 // type of the image file see MDCS_E_ImageType for options description
   MDCS_E_FileStorage      eStorageType;                          // where blob is stored see MDCS_E_FileStorage for option
   //int                     nLocationID;                         // location id
   char                    szServerFileName[_MAX_FNAME];          // blob name on server
   char                    szBlobDesc[MDCS_MAX_DESCRIPTION];      // image description
   char                    szImportFileName[_MAX_FNAME];          // file name of the original blob
   char                    szImportComputerName[MDCS_MAX_SERVER]; // computer name where image was created 
   char                    szImportDirectory[_MAX_PATH];          // name of a directory on PC where blob came from 
   char                    szImportExtension[_MAX_EXT];           // file extension 
   
   MDCS_ST_BlobLocation    stBlobLocation;                        // blob location 
   
   MDCS_ST_BlobInfo()
   {
      memset(this, 0, sizeof(*this));            
   }
};

/////////////////////////////////
//structure that describes info of attached files( save by blob) to MSet, dataset, and plate  
struct  MDCS_ST_BlobInfoEx
{
   LONGLONG                lBlobID;                               // blob id
   LONGLONG                lBlobSize;                             // size of the blob, in bytes
   LONGLONG                lLocationID;                           //location ID
   MDCS_E_ImageType        eType;                                 // type of the image file see MDCS_E_ImageType for options description
   MDCS_E_FileStorage      eStorageType;                          // where blob is stored see MDCS_E_FileStorage for option
   char                    szServerFileName[_MAX_FNAME];          // blob name on server
   char                    szBlobDisplayName[_MAX_FNAME];         // blob display name
   char                    szBlobDesc[MDCS_MAX_DESCRIPTION];      // image description
   char                    szImportFileName[_MAX_FNAME];          // file name of the original blob
   char                    szImportComputerName[MDCS_MAX_SERVER]; // computer name where image was created 
   char                    szImportDirectory[_MAX_PATH];          // name of a directory on PC where blob came from 
   char                    szImportExtension[_MAX_EXT];           // file extension 
   time_t                  tTimeCreated;                          // time when the file is attached( auto fill by system when insert)
     
   MDCS_ST_BlobInfoEx()

   {
      memset(this, 0, sizeof(*this));            
   }
};

/////////////////////////////////
//structure that describes assay result value
struct  MDCS_ST_ShapeInfo
{
   LONGLONG          lSiteID;                //site ID   
   LONGLONG          lSeriesID;              //series ID
   LONGLONG          lRunID;                 //assay run ID
   int               nInstance;              //instance
   MDCS_E_ShapeType  eShapeType;             //type of a shape (i.e. image, cell, nucleus)
   int               nParentInstance;        //instance of a parent where shape belongs
   MDCS_E_ShapeType  eParentShapeType;       //type of a parent shape (i.e. image, cell, nucleus)
   int               nColor;                 //shape color 
   char              szCellID[MDCS_MAX_CELL_ID];   //cell ID

   //constructor
   MDCS_ST_ShapeInfo()
   {
      memset(this, 0, sizeof(*this));            
   }
 };


////////////////////////////
//structure to describe user credentials to connect to the database
struct  MDCS_ST_UserLogin
{
   LONGLONG          lUserLoginID;           //user login ID
   LONGLONG          lUserGroupID;           //user group ID
   MDCS_E_UserStatus eUserStatus;            //user status in database
   BOOL              bUseServer;             //to use server name instead of datasource name (SQL only)
   BOOL              bUseTrusted;            //to use trusted connection (SQL only)

   //char    szUserName[MDCS_MAX_USERNAME] = "MDCadmin";    //user name
  // char    szPassword[MDCS_MAX_PASSW] = "Software1!";      //user password
  // char    szDSN[MDCS_MAX_DSN] = "OPCITSEUW00AA";             //datasource name 
   //char    szDatabase[MDCS_MAX_DBNAME] = "MDCStore";
   char    szUserName[MDCS_MAX_USERNAME];    //user name
   char    szPassword[MDCS_MAX_PASSW];       //user password
   char    szDSN[MDCS_MAX_DSN];              //datasource name 
   char    szDatabase[MDCS_MAX_DBNAME];      //database name (is not required for ODBC datasources 
                                             //that uses database name (i.e. SQL Server). 
                                          //However, you may want to specify database name for ORACLE datasource)
                                             //if there are more than one database running on server   
  

   //operator ==
 /*  BOOL operator == (const MDCS_ST_UserLogin &) const
   {
     if ((_stricmp(this->szDSN, stUserCred.szDSN) == 0) &&
        (_stricmp(this->szUserName, stUserCred.szUserName) == 0) &&
        (strcmp(this->szPassword, stUserCred.szPassword) == 0) &&
        (strcmp(this->szDatabase, stUserCred.szDatabase) == 0))
        return TRUE;
   
      return FALSE;
   };

   //operator !=
   BOOL operator != (const MDCS_ST_UserLogin &) const
   {
      MDCS_ST_UserLogin stThis = *this;
      return !(stThis  == stUserCred);
   }
*/
   MDCS_ST_UserLogin()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//////////////////////////////////
//structure that describes user 
struct  MDCS_ST_UserInfo
{
   LONGLONG          lUserLoginID;                       //user login ID
   LONGLONG          lUserGroupID;                       //user group ID
   LONGLONG          lCreatorID;                         //id of the user who created user [out only] 
   time_t            tTimeCreated;                       //time when user was created [out only] 
   MDCS_E_UserStatus eUserStatus;                        //user status in database

   char              szCreator[MDCS_MAX_OBJ_NAME];       //name of the user who created record [out only] 
   char              szUserName[MDCS_MAX_USERNAME];      //user name
   char              szDesc[MDCS_MAX_DESCRIPTION];       //user description
   char              szFullName[MDCS_MAX_OBJ_NAME];      //user's full name

   MDCS_ST_UserInfo()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//////////////////////////////////
//structure that describes a group
struct  MDCS_ST_GroupInfo
{
   LONGLONG          lGroupID;                           //group id
   LONGLONG          lCreatorID;                         //id of the user who created group [out only] 
   time_t            tTimeCreated;                       //time when group was created [out only] 
   MDSC_E_GroupType  eGroupType;                         //type of group               [in for insert only]
   char              szName[MDCS_MAX_USERNAME];          //group name
   char              szDesc[MDCS_MAX_DESCRIPTION];       //user description
   char              szCreator[MDCS_MAX_OBJ_NAME];       //name of the user who created record [out only] 
   

   MDCS_ST_GroupInfo()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//////////////////////////////////
//structure that describes group access to the folder
struct MDCS_ST_FolderGroups
{
   LONGLONG                   lEntityID;        //entity ID (folder or plate)
   LONGLONG                   lGroupID;         //group ID
   LONGLONG                   lShareOwnerID;    //ID of the person who assigned permissions
   MDCS_E_AccessPermissions   eAccess;          //type of permissions

   char                       szGroupName[MDCS_MAX_OBJ_NAME];  //group name
   char                       szFolderName[MDCS_MAX_OBJ_NAME]; //folder name 

   MDCS_ST_FolderGroups()
   {
      memset(this, 0, sizeof(*this));
   };
};

//////////////////////////////////
//structure that describes group access to a plate 
struct MDCS_ST_ObjGroups
{
   LONGLONG                   lUniqueID;        //unique ID (folder or plate)
   LONGLONG                   lEntityID;        //entity ID (folder or plate)
   LONGLONG                   lGroupID;         //group ID
   LONGLONG                   lShareOwnerID;    //ID of the person who assigned permissions
   MDCS_E_ObjAccessPermissions   eAccess;          //type of permissions

   char                       szGroupName[MDCS_MAX_OBJ_NAME];  //group name
   char                       szPlateName[MDCS_MAX_OBJ_NAME]; //plate name 

   MDCS_ST_ObjGroups()
   {
      memset(this, 0, sizeof(*this));
   };
};

////////////////////////////
//common structure to describe objects (resultset) in the database 
struct  MDCS_ST_ResultSet
{
   char    szID[MDCS_MAX_OBJ_ID];                 //object database ID
   char    szName[MDCS_MAX_OBJ_NAME];             //object name  
   char    szDescription[MDCS_MAX_DESCRIPTION];   //object description
   char    szImportDirectory[_MAX_DIR];           //directory where object was originally located
   char    szImportComputer[MDCS_MAX_SERVER];     //PC name where object was originally located
   char    szImportFileName[_MAX_FNAME];          //name of the original file 
   
   MDCS_ST_ResultSet()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//describes current database version
struct MDCS_ST_DBVersion 
{
   int nLead;
   int nMid;  
   int nTrail;

   MDCS_ST_DBVersion()
   {
      memset(this, 0, sizeof(*this));
   }
};
//structure that describes column in dynamic cell or image table
/*struct  MDCS_ST_AssayMeasurementAttr
{
  // LONGLONG lColAssayID;                     //collection-assay unique identifier   
  // LONGLONG lCollectionID;                   //colleciton ID
   LONGLONG lAssayMeasID;                     //assay measurement ID
   LONGLONG lAssayID;                        //assay ID
   LONGLONG lMeasurementID;                  //measurement ID
   char szColumnName[MDCS_MAX_COL_NAME];     //name of the column
   char szTableName[MDCS_MAX_TABLE_NAME];    //table name 


   MDCS_ST_AssayMeasurementAttr()
   {
      memset(this, 0, sizeof(*this));      
   }
};*/

//structure that describes assay measurement
/*struct  MDCS_ST_AssayMeasurement
{
   LONGLONG lMeasID;                         //measurement ID
   char szName[MDCS_MAX_OBJ_NAME];           //measurement name
   char szDescription[MDCS_MAX_DESCRIPTION]; //description
   zchar szFunctionName[MDCS_MAX_OBJ_NAME];   //function name
   char szDBColumnName[MDCS_MAX_COL_NAME];   //column name as in DB
   MDCS_E_ColumnType eColumnType;            //column type

   MDCS_ST_AssayMeasurement()
   {
      memset(this, 0, sizeof(*this));      
   }

};
*/
//structer that describes measurement 
struct   MDCS_ST_Measurements 
{
   LONGLONG lMeasurementID;
   MDCS_E_ColumnType eFormat;                   //measurement format (integer, string)

   char     szName[MDCS_MAX_OBJ_NAME];          //measurement name 
   char     szColumnName[MDCS_MAX_COL_NAME];    //measurement name 
   char     szDesc[MDCS_MAX_DESCRIPTION];       //measurement description
   char     szFunctionName[MDCS_MAX_OBJ_NAME];  //function name
   
   
   MDCS_ST_Measurements()
   {
	   memset(this, 0, sizeof(*this));
   }
};


//structure that describes assay 
struct  MDCS_ST_Assay
{
   LONGLONG lAssayID;                        //assay ID (do not required to create new assay)
   LONGLONG lCreatorID;                      //id of a person who created assay (not used to create new assay)
   LONGLONG lModifierID;                     //id of a person who modofied assay (not used to create new assay)
   LONGLONG lRowCount;                       //number of rows in assay (read-only)
   LONGLONG lShapeRowCount;                  //number of shapes in assay (read-only)
   time_t tTimeCreated;                      //time when assay was created
   time_t tTimeModified;                     //time when assay was modified  
   BOOL   bNormalized;                       //flag indicates that assay was normalized
   char szName[MDCS_MAX_OBJ_NAME];           //assay name (required to create new assay)
   char szSettingName[MDCS_MAX_OBJ_NAME];    //assay settings name (required to create new assay)
   char szDesc[MDCS_MAX_DESCRIPTION];        //assay description (optional)
   char szAssayTable[MDCS_MAX_TABLE_NAME];   //name of assay table (not used to create new assay)
   char szAssayShapeTable[MDCS_MAX_TABLE_NAME];   //name of an assay table that contains shapes (not used to create new assay)
   char szCreatorName[MDCS_MAX_USERNAME];    //user who created assay

   MDCS_ST_Assay()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//structure that describe plate image
struct  MDCS_ST_PlateImages
{
   LONGLONG lPlateImageID;         //plate image id
   LONGLONG lSiteID;               //site ID of the image
   LONGLONG lSeriesID;             //series ID

   MDCS_ST_PlateImages()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//////////////////////////////////////////////////////
//structure that describes shape lines
struct  MDCS_ST_ShapeLine
{
   int xStart;          // the horizontal pixel position of the scanline
   int yStart;          // the vertical pixel position of the scanline
   int nLength;         // the length in pixels of the scanline
   int nReserved;       // reserved for future use
   
   MDCS_ST_ShapeLine()
   {
      memset(this, 0, sizeof(*this));      
   }
};

//structure that describes blob that contains shape line
struct  MDCS_ST_ShapeLinesBlob
{
   LONGLONG lBlobSize;           //total blob size
   LONGLONG lStructureNumber;    //number of structures 
   LONGLONG lReserved;

   MDCS_ST_ShapeLinesBlob()
   {
      memset(this, 0, sizeof(*this));
   };
 
};
//structure that describes blob that contains shape line
struct  MDCS_ST_DsetAnalysis
{
   LONGLONG   lID;
   LONGLONG   lDatasetID;
   char       szName[MDCS_MAX_OBJ_NAME];
   char       szDesc[MDCS_MAX_DESCRIPTION];

   MDCS_ST_DsetAnalysis()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes blob that contains shape line
struct  MDCS_ST_DsetAnalysisAttr
{
   LONGLONG                lAttrID;
   LONGLONG                lDsetAnalysisID;                     //data set analysis ID
   MDSC_E_CollapseType     eAttrType;
   MDCS_E_Statistic        eStatisticType;
   UINT                    uOrderNum;

   char                    szName[MDCS_MAX_COL_NAME];           //attribute name 
   char                    szCollapseName[MDCS_MAX_COL_NAME];    //collapse column name
   char                    szNameScope[MDCS_MAX_SCOPE];         //attribute scope name
   char                    szCollapseScope[MDCS_MAX_SCOPE];     //collapse column scope name

   MDCS_ST_DsetAnalysisAttr()
   {
      memset(this, 0, sizeof(*this));
   };
};

////////////////////////////////
//structure that describes folder
struct  MDCS_ST_FolderInfo
{
   LONGLONG          lID;                       //id of a folder
   LONGLONG          lParentID;                 //id of the parent folder (if  0 - root folder)        
   LONGLONG          lCreatorID;                //id of the person who created folder (out only)
   time_t            timeCreated;               //time when folder was created (out only)
   
   char              szName[MDCS_MAX_OBJ_NAME];
   char              szDesc[MDCS_MAX_DESCRIPTION];
   char              szCreator[MDCS_MAX_OBJ_NAME];    //name of a person who created folder  (out only)


   MDCS_ST_FolderInfo()
   {
      memset(this, 0, sizeof(*this));
   };
};

///////////////////////////////
//structure that describes plate
struct  MDCS_ST_PlateInfo
{
   LONGLONG          lPlateID;                              //plate ID
   LONGLONG          lAcqID;                                //ID of acquisition when plate was acquired
   LONGLONG          lCreatorID;                            //id of the user who created user [out only] 
   time_t            tTimeCreated;                          //time when plate was created [out only] 
   time_t            tTimeAnnotated;                        //time when plate was annotated [out only] 
   time_t            tTimeModified;                         //time when plate was modified[out only] 
   LONGLONG          lAnnotatedBy;                          //id of the user who annotated plate [out only] 
   LONGLONG          lModifierID;                              //id of the user who annotated plate [out only] 
   int               nXWells;                               //number of X wells in plate
   int               nYWells;                               //number of Y wells in plate
   
   char              szPlateName[MDCS_MAX_OBJ_NAME];        //plate name 
   char              szCreator[MDCS_MAX_OBJ_NAME];          //name of the user who created record [out only] 
   char              szBarcode[MDCS_MAX_BARCODE];           //barcode
   char              szAcqName[MDCS_MAX_OBJ_NAME];          //name of an acquisition that was used to acquire plate
   char              szGlobalID[MDCS_MAX_GLOBAL_ID];        //plate's global ID
   char              szDesc[MDCS_MAX_DESCRIPTION];          //plate description

   MDCS_ST_PlateInfo()
   {
      memset(this, 0, sizeof(*this));
   };
};

///////////////////////////////
//structure that describes site images plate
struct  MDCS_ST_SiteImageInfo
{
   LONGLONG    lID;              //unique ID of the site image [out only]
   LONGLONG    lSiteID;          //site ID of the site image   [in/out]
   LONGLONG    lSeriesID;        //series ID of the site image [in/out]
   LONGLONG    lImageSourceID;   //reference to the record that contains source description
   LONGLONG    lImageID;         //reference to the record where image is stored [int/out]
   double      dZPositions;      //calibrated posiztion the image was acquired from along the z-axis [in/out]
   time_t      tTimeCreated;     //time when plate was created [out only] 
   int         nZIndex;          //z index of the image  [in/out]
   int         nTIndex;          //timepoint  [in/out]

   MDCS_ST_SiteImageInfo()
   {
      memset(this, 0, sizeof(*this));
   };

};
///////////////////////////////
//structure that describes series info
struct  MDCS_ST_SeriesInfo 
{
   LONGLONG lSeriesID;     //series id [out]
   LONGLONG lSiteID;       //site id
   time_t   tTPosition;    //time position  
   LONGLONG lMicSeconds;   //microseconds added to thge t_position values for this series
   float    dZPosition;    //z position  [in\out]
   int      nZIndex;       //Z index [in\out]
   int      nTIndex;       //t index [in\out]
   MDCS_ST_SeriesInfo()
   {
      memset(this, 0, sizeof(*this));
   };
};


///////////////////////////////
//structure that describes series info
struct  MDCS_ST_Dataset
{
   LONGLONG lDatasetID;
   LONGLONG lCreatorID; 
   time_t   tTimeCreated;                                //time when dataset was created [out only] 
   MDCS_E_DatasetType   eDatasetType;                    // type of the dataset
   char     szName[MDCS_MAX_OBJ_NAME];                   //dataset  name (required to create new dataset)
   char     szDesc[MDCS_MAX_DESCRIPTION_LARGE];          //assay description (optional)
   char     szDatasetTable[MDCS_MAX_TABLE_NAME];         //name of a dataset table that was created when dataset was imported (not used to create new )
   char     szCreatorName[MDCS_MAX_USERNAME];            //user who created assay
   char     szDataType[MDCS_MAX_COL_NAME];               //datatype of the data in dataset 
   char     szStaticDecs[MDCS_MAX_DESCRIPTION_LARGE];    //description that is given to a dataset at time of creation
   char     szDataTypeScope[MDCS_MAX_SCOPE];             //scope of the datatype 
   
   MDCS_ST_Dataset()
   {
      memset(this, 0, sizeof(*this));
   };
};

///////////////////////////////
//structure that describes site 
struct  MDCS_ST_Site
{
   LONGLONG lSiteID;          //ID of a site, ignored for insert
   LONGLONG lPlateID;         //id of a plate where site is found
   float    fXPosition;       //X position within a well
   float    fYPosition;       //Y position within a well
   UINT     uWellXPosition;   //well X position 
   UINT     uWellYPosition;   //well Y position 
   

   MDCS_ST_Site()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes image source
struct  MDCS_ST_ImageSource
{
   LONGLONG    lSourceID;                       //unique identifier of a record
   LONGLONG    lAcqID;                          //acquizition ID
   LONGLONG    lAssayID;                        //assay ID
   char szSource[MDCS_MAX_DESCRIPTION_LARGE];  //source description
   char szIllum[MDCS_MAX_DESCRIPTION_LARGE];    //illumination description

   MDCS_ST_ImageSource()
   {
      memset(this, 0, sizeof(*this));
   };
};

//stucture that describes acquisition
struct  MDCS_ST_Acquisition
{
   LONGLONG lAcqID;                       //unique identified
   time_t   tTimeStart;                   //time when acquisition strats
   time_t   tTimeEnd;                     //time when acquisition ends

   char szName[MDCS_MAX_OBJ_NAME];        //acuisition name
   char szDesc[MDCS_MAX_DESCRIPTION];     //acquisition description
   MDCS_ST_Acquisition()
   {
      memset(this, 0, sizeof(*this));
   };
};
//stucture that describes acquisition profile
struct  MDCS_ST_AcquisitionProfile
{
   LONGLONG lProfID;                      //unique identified
   char szName[MDCS_MAX_OBJ_NAME];        //profile name
   char szDesc[MDCS_MAX_DESCRIPTION];     //profile  description

   MDCS_ST_AcquisitionProfile()
   {
      memset(this, 0, sizeof(*this));
   };
};


//stucture that describes assay runs
struct  MDCS_ST_AssayRun
{
   LONGLONG lRunID;
   LONGLONG lAssayID;
   
   char szSettingsName[MDCS_MAX_OBJ_NAME];      //settings name
   MDCS_ST_AssayRun()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes assay profile
struct   MDCS_ST_AssayProfile
{
   LONGLONG    lProfileID;                         //identifier
   LONGLONG    lCreatorID;                         //id of the user who created profile [out only]
   time_t      tTimeCreated;                       //time when profile was created [out only] 

   char szAssayName[MDCS_MAX_OBJ_NAME];            //assay name
   char szAssayDesc[MDCS_MAX_DESCRIPTION_LARGE ];  //assay description
   char szSettingsName[MDCS_MAX_OBJ_NAME];         //settings name
   
   char              szCreator[MDCS_MAX_OBJ_NAME];       //name of the user who created record [out only] 
  
   MDCS_ST_AssayProfile()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes location option
struct  MDCS_ST_LocationOption
{
   LONGLONG lLocationID;                        //identifier
   int  nPort;                                  //server port number 
   MDCS_E_FileStorage   eStorageType;           //storage type - file server or UNC

   char szStorageType[MDCS_MAX_STORAGE_TYPE];   //storage type - obsolete, not used
   char szLabel[MDCS_MAX_LABEL];                //label
   char szServerName[MDCS_MAX_OBJ_NAME];        //server name


   MDCS_ST_LocationOption()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes job
struct  MDCS_ST_Job
{
   LONGLONG lJobId;                          //identifier
   LONGLONG lProfID;                         //assay profile ID
   LONGLONG lFolderID;                       //folder ID that associated with job
   time_t   tTimeUpdated;                    //time when was last update, (ignored on create)
   time_t   tTimeCreated;                    //time when was created, (ignored on create)
   MDCS_E_JobEnvType eEnvType;               //environment type (c-pod or MX)
   
   
   char szSourceDataDesc[MDCS_MAX_DESCRIPTION_LARGE ];   //description of source data
   char szNetworkID[MDCS_MAX_NETWORK_ID];    //network ID
   char szStatus[MDCS_MAX_DESCRIPTION];      //status description
   char szProgress[MDCS_MAX_DESCRIPTION];    //progress description
   char szRequest[MDCS_MAX_REQUEST];         //request

   MDCS_ST_Job()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes application parameter
struct  MDCS_ST_AppParameter
{
   LONGLONG lParamID;                        //identifier
   char szParamName[MDCS_MAX_OBJ_NAME];      //parameter
   char szParamValue[MDCS_MAX_PARAM_VALUE];  //parameter value

   MDCS_ST_AppParameter()
   {
      memset(this, 0, sizeof(*this));
   };
};


//structure that describes plate layote templates
struct  MDCS_ST_PlateTemplate
{
   LONGLONG lTemplID;                           //identifier  [TEMPL_ID]                         
   LONGLONG lCreatorID;                         //creator ID [out]            [CREATOR_ID]
   LONGLONG lModifierID;                        //modifier ID [out]           [MODIFIER_ID]
   time_t   tCreated;                           //time when plate template was created [out]    [DATE_CREATED]
   time_t   tModified;                          //time when plate templete was modified [out]   [TIME_MODIFIED]

   int  nWellX;                                 //number of wells in X axis   [WELL_X]
   int  nWellY;                                 //number of wells in Y axis   [WELL_Y]   
   int  nWellAnnotated;                         //number of well annotated    [WELL_ANNOTATED]
   int  nNumCoumpounds;                         //number compounds in plate   [NUM_COMPOUNDS]
   int  nNumGroups;                             //number of groups in plate   [NUM_GROUPS]

   char szName[MDCS_MAX_OBJ_NAME];              //plate layout name [TEMPL_NAME]
   char szDesc[MDCS_MAX_DESCRIPTION_LARGE];     //plate layout description [TEMPL_DESC]
   char szTableName[MDCS_MAX_TABLE_NAME];       //name of the table for the plate layout, if empty will be generated by app [TEMPL_TABLE]
   

   MDCS_ST_PlateTemplate()
   {
      memset(this, 0, sizeof(*this));
   };
};


//structure that describes database server information
struct MDCS_ST_ConnectionInfo
{
   char szServerName[MDCS_MAX_SERVER];                      //server name 
   char szServerVersion[MDCS_MAX_SERVER_VERSION];           //server version
   char szServerType[MDCS_MAX_SERVER_TYPE];                 //server type
   char szRevision[MDCS_MAX_SERVER_REVISION];               //server revision
   char szDatabaseName[MDCS_MAX_DBNAME];                    //database name
   char szDriverName[MDCS_MAX_ODBC_DRIVER_NAME];            //ODBC driver name
   char szDriverVersion[MDCS_MAX_ODBC_DRIVER_VERSION];      //ODBC driver version
   char szODBCVersion[MDCS_MAX_ODBC_VERSION];               //ODBC version (different from driver)
   char szODBCSourceName[MDCS_MAX_ODBC_SOURCE_NAME];        //ODBC data source name
   
   MDCS_ST_ConnectionInfo()
   {
      memset(this, 0, sizeof(*this));
   };
};

//structure that describes connection attributes
struct MDCS_ST_ConnectionAttr
{
   char szDSN[MDCS_MAX_ODBC_SOURCE_NAME];    //ODBC data source name
   char szUserName[MDCS_MAX_USERNAME];       //user name 
   char szDatabase[MDCS_MAX_DBNAME];         //database name 

   MDCS_ST_ConnectionAttr()
   {
      memset(this, 0, sizeof(*this));
   };
};
////////////////////////////////
//structure that describes attribute of the plate, dataset, measurement set 
struct  MDCS_ST_Attribute
{
   MDCS_E_ColumnType    eColumnType;         //column type
   MDCS_E_AttributeType eAttributeType;      //type of the attribute, used only in select statement 

   char szDisplayName[MDCS_MAX_OBJ_NAME];    //display name of the attribute
   char szDBColumnName[MDCS_MAX_COL_NAME];   //column name as in DB, not available in create function
   
   MDCS_ST_Attribute()
   {
      memset(this, 0, sizeof(*this));      
   }
};

////////////////////////////////
//structure that describes scope attribute of the plate, dataset, measurement set 
struct MDCS_ST_ScopeAttribute
{
   char szScopeName[MDCS_MAX_OBJ_NAME]; //scope name
   MDCS_ST_Attribute stAttribute;       //attribute;  

   MDCS_ST_ScopeAttribute() 
   {
      memset(this, 0, sizeof(*this));
   }
};

////////////////////////////////
//structure that describes file data records
struct  MDCS_ST_FileDataInfo
{
    LONGLONG          lID;                                //record ID [out]
    LONGLONG          lLocationID;                        //location of the data ID [out]
    LONGLONG          lDataSize;                          //data size [out]
    time_t            tTimeCreated;                       //time when record was created [out]
    
    char              szGUID[MDCS_MAX_GUID];              //guid that used for data [in]

    MDCS_ST_FileDataInfo()
    {
         memset(this, 0, sizeof(*this));
    }
};


//strucrure that describes well
struct MDCS_ST_WellInfo
{  
   int nXPos;                             // x position of a well 
   int nYPos;                             // y position of a well 
   
   char szWellName[MDCS_MAX_WELL_NAME];   // readable well name

   MDCS_ST_WellInfo()
   {
      memset(this, 0, sizeof(*this));     
   };
};


//strucrure that describes measurement
struct MDCS_ST_CellDescription
{
   LONGLONG          lSiteID;                      //measurement site id
   LONGLONG          lSeriesID;                    //measurement plate ID
   LONGLONG          lPlateID;                     //plate ID 
   LONGLONG          lRunID;                       //RUN ID 
   int               nInstance;                    //instance
   
   char              szCellID[MDCS_MAX_CELL_ID];   //cell ID
   MDCS_ST_WellInfo  stWellInfo;

   MDCS_ST_CellDescription()
   {
      memset(this, 0, sizeof(*this));     
   };
};

////////////////////////////////
//structure that describes group macros
struct  MDCS_ST_GroupMacros
{
    LONGLONG               lID;                                //record ID [out]
    LONGLONG               lLocationID;                        //location of the data ID [out]
    LONGLONG               lDataSize;                          //data size [out]
    LONGLONG               lGroupID;                            //group id 
    time_t                 tTimeCreated;                       //time when record was created [out]

    MDCS_E_GroupObjectsType eMacroType;                        //type of the macro

    char              szName[MDCS_MAX_OBJ_NAME];               //object name 
    char              szDesc[MDCS_MAX_DESCRIPTION];            //object description
    char              szCategory[MDCS_MAX_DESCRIPTION_LARGE];  //object category

    MDCS_ST_GroupMacros()
    {
         memset(this, 0, sizeof(*this));
    }
};

////////////////////////////////
//structure that describes annotation warehouse
struct  MDCS_ST_Warehouse
{
   LONGLONG               lID;                                 //record ID [out]
   LONGLONG               lOwnerID;                            //ID of user who owns it
   time_t                 tTimeCreated;                        //time when was created   [out]
   time_t                 tTimeModified;                       //time when was modified last time [out]
   
   char                   szInternalName[MDCS_MAX_TABLE_NAME]; //internal name 
   char                   szName[MDCS_MAX_OBJ_NAME];           //name of warehouse
   char                   szDesc[MDCS_MAX_DESCRIPTION];        //description

   MDCS_ST_Warehouse()
   {
      memset(this, 0, sizeof(*this));
   };
};

////////////////////////////////
//structure that describes normalization configuration
struct  MDCS_ST_NormConfig
{
   LONGLONG                   lID;         //unique identifier [out\ in(reference only)]     [CONF_ID]
   LONGLONG                   lCreatorID;  //id of person who created config [out]           [CREATOR_ID]
   LONGLONG                   lModifierID; //id of person who modofied config [out]          [MODIFIER_ID]
   time_t                     tCreated;    //time created  [out]                             [TIME_CREATED_UTC]
   time_t                     tModified;   //time modified [out]                             [TIME_UPDATED_UTC]
   LONGLONG                   lDataSize;  //size of data of configuration blob object[out]  [OBJ_SIZE]

   MDCS_E_NormConfigType      eType;      //configuration type [in\pot]                     [CONF_TYPE]
   MDCS_E_DataType            eDataType;  //type of data

   char  szName[MDCS_MAX_OBJ_NAME];     //name of configuration [in\out]                  [CONF_NAME]
   char  szDesc[MDCS_MAX_DESCRIPTION];  //description       [in\out]                      [CONF_DESC]

   MDCS_ST_NormConfig()
   {
      memset(this, 0, sizeof(*this));
   };
};

struct MDCS_ST_MeasurementUseStatistic
{
   LONGLONG lAssayCount;
   LONGLONG lDatasetCount;

   MDCS_ST_MeasurementUseStatistic() { memset(this, 0, sizeof(*this)); }	
};
////////////////////////////////
//structure that describes dataset analysis results
struct  MDCS_ST_DatasetResultInfo
{
   LONGLONG                   lID;         //unique identifier [out\ in(reference only)]     [RESULT_ID]
   LONGLONG                   lDatasetID;  //id of a dataset   [out\in]                      [DATASET_ID]
   LONGLONG                   lConfigID;   //id of dataset configuration  [out\in]           [ANALYSIS_ID]
   LONGLONG                   lDataSize;   //size of results data
  
   int                        nResultType; //type of result analysys                         [RESULT_TYPE]


   char  szName[MDCS_MAX_OBJ_NAME_BIG];     //name of result [in\out]                        [RESULT_NAME]
   char  szDesc[MDCS_MAX_DESCRIPTION_LARGE];//description       [in\out]                     [RESULT_DESCR]

   MDCS_ST_DatasetResultInfo()
   {
      memset(this, 0, sizeof(*this));
   };
};

const int c_nDlgRegSectionSize = 128;
const int c_nDlgTitleSize = 128;
const int c_nDlgAppNameSize = 128;
//structure to describe dlg params
struct MDCS_ST_DlgParams
{
   char szRegSection[c_nDlgRegSectionSize];     //registry section
   char szTitle[c_nDlgTitleSize];               //dlg title
   char szAppName[c_nDlgAppNameSize];           //app name

   MDCS_ST_DlgParams()
   {
      memset(this, 0, sizeof(this));
   };
};

//structer that describes database columns
struct   MDCS_ST_DBColumn
{
   // definition of the enum that describes column types
   /*enum  MDCS_E_DBColumnType
   {
      MDCS_eDBColumnTypeString = 0,       //column conatins characters
      MDCS_eDBColumnTypeFloat = 1,        //data is float   
      MDCS_eDBColumnTypeInt  = 2,         //data is integer
      MDCS_eDBColumnTypeBinary = 3,       //data is binary
      MDCS_eDBColumnTypeDateTime = 4      //data is date\time
      //MDCS_eDBColumnTypeShort = 6       //data short 
                                          // removed short int to be consistent with MDCS_E_ColumnType
   }; */ 

   //MDCS_E_DBColumnType  eDataType;   
   MDCS_E_ColumnType  eDataType;                          //column data type
   UINT                 uColumnSize;                      //column size for char columns or size specification for numeric columns
   BOOL                 bNullable;                        //nullable
   BOOL                 bUnique;                          //unique 
   UINT                 nPrimary;                         //primary key
   INT_PTR              nIdentity;                        //identity column, increment by
   INT_PTR              nSeed;                            //identity seed, starts with
   char                 szName[MDCS_MAX_COL_NAME];        //db column name
   char                 szDefValue[MDCS_MAX_STRING_VALUE];//default value for the column                       
   
   MDCS_ST_DBColumn()
   {
	   memset(this, 0, sizeof(*this));
   }
};


//structer that describes archive info 
struct   MDCS_ST_ArchiveInfo
{
   MDCS_E_ArchiveType   eType;                              //archive type
   LONGLONG             lID;                                //archive ID
   LONGLONG             lCreatorID;                         //creator ID 
   time_t               tTimeCreated;                       // time when archive was created (auto fill by system when insert)
   char                 szName[MDCS_MAX_OBJ_NAME];          // archive name
   char                 szGUID[MDCS_MAX_GUID];              //guid that was assigned for archive (auto fill by system when insert)
   char                 szDesc[MDCS_MAX_DESCRIPTION_LARGE]; //user description
   char                 szArchFileName[_MAX_FNAME];         //user description
   char                 szArchPCName[MDCS_MAX_SERVER]; // computer name where archive is located
   char                 szArchDir[_MAX_PATH];          // directory where is located
   char                 szArchExt[_MAX_EXT];           // file extension 

   MDCS_ST_ArchiveInfo()
   {
	   memset(this, 0, sizeof(*this));
   }
};

struct   MDCS_ST_Update
{
   // definition of the enum that describes column types
   enum MDCS_E_UpdateStatus
   {
      MDCS_eUPSUnknown = 0,
      MDCS_eUPSStarted = 1,
      MDCS_eUPSFinished = 2,
      MDCS_eUPSFailed = 3,
   };

   // definition of the enum that describes column types
   enum MDCS_E_SystemType
   {
      MDCS_eSTypeAll = 0,
      MDCS_eSTypeAX = 1,
      MDCS_eSTypeMX = 2
      
   };

   // definition of the enum that describes column types
   enum MDCS_E_UpdateType
   {
      MDCS_eUpTypeSchema = 0,   //schema 
      MDCS_eUpTypeData   = 1,   // data
   };

   LONGLONG             nID;
   LONGLONG             nUpdateID;
   MDCS_E_UpdateStatus  eStatus;
   MDCS_E_SystemType    eSystemType;
   MDCS_E_UpdateType    eType;
   time_t               timeStarted;
   time_t               timeFinished;
   char                 szUser[MDCS_MAX_OBJ_NAME];

   MDCS_ST_Update()
   {
	   memset(this, 0, sizeof(*this));
   }
};

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //RC_INVOKED

#pragma pack(pop)

#endif 
