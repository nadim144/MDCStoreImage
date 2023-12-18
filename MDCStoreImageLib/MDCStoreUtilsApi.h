//***********************************************************************************************
//
//    Copyright (c) 2004 - 2006 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  MDCSTOREUTILS.h
// PURPOSE: 
// AUTHOR:  MS  July 2004
// prototypes of the functions to work with MDCStore database


#if !defined(AFX_MDCSTOREUTILS_H__4D40DC82_AC4E_404F_A6A2_B014B65A79D1__INCLUDED_)
#define AFX_MDCSTOREUTILS_H__4D40DC82_AC4E_404F_A6A2_B014B65A79D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma pack(8)

#ifndef RC_INVOKED

#include "MDCSStructers.h"
#include "MDCSClasses.h"

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



// #define constants for the API version number.
#define MDCSUTILS_APIVERSION         2,1,8,0
#define MDCSUTILS_APIVERSION_STR     "2.1.08.00\0"

/////////////////////////////////////////////////////////////////////////////////
#define     MDCS_ShapeStructVersion         1

//forward declaration of classes AxStringArray and AxString
//description of class function can be found in AxStringCollection.h file
//in order to work withe these classes in user projects, AxStringCollection.h file
//should be included into projects

class AxStringArray;
class AxString;
class MDCS_CL_BlobLocationCB;
class MDCS_CL_BlobInfoCB;
//////////////////////////////////////////////////////////////////////////////////
//                                                                //
// callbacks and datasources
//          
//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////
//function to initialize MDCStore interface
MDCSUTILS  BOOL WINAPI MDCStoreUtils_Init();

//function to exit MDCStore 
MDCSUTILS  void WINAPI MDCStoreUtils_Finished();

//////////////////////////////////////////////////////////////////////////////
// MDCS_ImportResultset
// datasource to import resultset data (tab-delimited files) into database 
class  MDCSUTILS MDCS_ImportResultset
{
public:
   MDCS_ImportResultset() {};
   virtual ~MDCS_ImportResultset() {};
public:
   //to get nuber of columns in the datasource
   virtual UINT GetColumnCount() const = 0;

   //to get total number of rows in the datasource
   virtual UINT GetRowCount() const = 0;

   //to get column info 
   virtual BOOL GetColumnInfo(UINT uColumnNum, MDCS_ST_COLUMNPROP * pProp) const = 0;

   //to get element to insert
   virtual BOOL GetElement(UINT uRowNum, UINT uColNum, LPSTR pszData, UINT uSize) const = 0;
   
   //to get element to insert
   virtual BOOL GetElement(UINT uRowNum, UINT uColNum, float * pfData) const = 0;
   
   //to get element to insert
   virtual BOOL GetElement(UINT uRowNum, UINT uColNum, INT_PTR * pnData) const = 0;

   //to get name of the ID columns
   virtual LPCSTR GetIDColumnName() const = 0;

   private:
      // hide the default copy constructors
      MDCS_ImportResultset(MDCS_ImportResultset const &);
      const MDCS_ImportResultset &operator=(MDCS_ImportResultset const &);      
};



//strucrure that describes compound 
/*struct MDCS_ST_WellCompoundInfo
{
   float fConcentration;                           //concentration avlue
   char  szCompoundName[MDCS_MAX_COMPOUND_NAME];   //compound name
   char  szUnitName[MDCS_MAX_UNIT_NAME];           //unit name

   MDCS_ST_WellCompoundInfo()
   {
      memset(this, 0, sizeof(*this));     
   };
}; */


//////////////////////////////////////////////////////////////////////////////
// MDCS_ImportPlateLayout
// datasource to import plate layout data
class MDCSUTILS MDCS_ImportPlateLayout
{
public:
   MDCS_ImportPlateLayout() {};
   virtual ~MDCS_ImportPlateLayout() {};
public:

   //to get number of columns in the datasource
   virtual UINT GetNumberWells() const = 0;

   //to get number of groups on a plate
   virtual UINT GetNumberGroups() const = 0;

   //to get number of compound on plate
   virtual UINT GetNumberCompounds() const = 0;

   //to get Well description
   virtual BOOL GetWellInfo(UINT uWellIndex, MDCS_ST_WellInfo& stWellInfo)  const = 0;

   //to get compound description
   virtual BOOL GetCompound(UINT uWellIndex, UINT uCompoundIndex, LPSTR pszData, UINT uSize) const = 0;

   //to get concentration
   virtual BOOL GetConcentration(UINT uWellIndex, UINT uCompoundIndex, float** fConc) const = 0;

   //to get unit
   virtual BOOL GetUnit(UINT uWellIndex, UINT uCompoundIndex, LPSTR pszData, UINT uSize) const = 0;


   //virtual BOOL GetWellCompoundInfo(UINT uWellIndex, UINT uCompoundIndex, MDCS_ST_WellCompoundInfo& stWellInfo)  const = 0;
   
   //to get Well description
   virtual BOOL GetWellGroup(UINT uWellIndex, UINT uGroupIndex, LPSTR pszGroupName, UINT uSize)  const = 0;

   private:
      // hide the default copy constructors
      MDCS_ImportPlateLayout(MDCS_ImportPlateLayout const &);
      const MDCS_ImportPlateLayout &operator=(MDCS_ImportPlateLayout const &);      
};



//////////////////////////////////////////////////////////////////////////////
// MDCS_ImportMeasurementSet
// datasource to import measurement set data into database 
class  MDCSUTILS MDCS_ImportMeasurementSet
{
public:
   MDCS_ImportMeasurementSet() {};
   virtual ~MDCS_ImportMeasurementSet() {};
public:

   //to get number of measuremen attributes that applied to a cell,
   //not including ones that are in MDCS_ST_CellDescription
   virtual UINT GetMeasurementAttributeNumber() const = 0;
   
   //to get total number of rows to be inserted
   virtual UINT GetCellCount() const = 0;

   //to get measurement column info 
   //nAttributeID is an ID of a global measurement attribute
   virtual BOOL GetMeasurementAttributeInfo(UINT uColumnNum, LONGLONG& nAttributeID) = 0;

   //to get cell description for each row that we incert
   virtual BOOL GetCellDescription(UINT uCellIndex, MDCS_ST_CellDescription& stCellDescription) = 0;

   //to get measurement set value to insert
   //use MDCS_MAX_STRING_VALUE for uSize
   virtual BOOL GetMeasurementValue(UINT uCellIndex, UINT uAttrIndex, LPSTR pszData, UINT uSize) const = 0;
   
   //to get measurement set value to insert
   virtual BOOL GetMeasurementValue(UINT uCellIndex, UINT uAttrIndex, float** pfData) const = 0;
   
   //to get measurement set value to insert
   virtual BOOL GetMeasurementValue(UINT uCellIndex, UINT uAttrIndex, INT_PTR** pnData) const = 0;

   //to get max number of rows to be inserted in one step
   virtual UINT GetNumberRowsInStep() const = 0;

   //to set assay status when import done
   virtual MDCS_E_AssayMarkStatus StatusWhenDone()  const { return eMarkNormal;};

   //to set a status of assay while importing
   virtual MDCS_E_AssayMarkStatus StatusWhileProccessing()  const { return eMarkRemove;};

   private:
      // hide the default copy constructors
      MDCS_ImportMeasurementSet(MDCS_ImportMeasurementSet const &);
      const MDCS_ImportMeasurementSet &operator=(MDCS_ImportMeasurementSet const &);      
};

class MDCSUTILS MDCS_CL_ImportDS : public MDCS_ImportMeasurementSet
{
public:
   //to get measurement column database name  
    virtual LPCTSTR GetAttributeDBName(UINT uColumnNum) const = 0;
    virtual LPCTSTR GetTableName() const = 0;
};

//////////////////////////////////////////////////////////////////////////////
// MDCS_QueryResults 
// 
class MDCSUTILS MDCS_QueryResults 
{

public:
   MDCS_QueryResults() {};
	virtual ~MDCS_QueryResults(){};

public:
	//function to get string result value of the field
	virtual LPCSTR GetStringValue(INT_PTR nCol) const = 0;

   //function to get float result value of the field
   virtual float GetFloatValue(INT_PTR nCol) const = 0;

   //function to get integer value of the field 
   virtual LONGLONG GetLongValue(INT_PTR nCol) const = 0;

   //function to get string result value of the field
	virtual LPCSTR GetStringValue(LPCSTR strColumnName) const = 0;

	//function to get float result value of the field
	virtual float  GetFloatValue(LPCSTR strColumnName) const = 0;

   //function to get integer result value of the field
	virtual LONGLONG GetLongValue(LPCSTR strColumnName) const = 0;

	//returns type of column
	virtual MDCS_E_ColumnType GetFieldType(INT_PTR nCol) const = 0;

   //returns type of column
	virtual MDCS_E_ColumnType GetFieldType(LPCSTR strColumnName) const = 0;

	//returns name of the column
	virtual LPCSTR GetColumnName(INT_PTR nCol) const = 0;

	//Returns number of columns
	virtual INT_PTR GetColumnsCount() const = 0;

   //checks if field is empty
   virtual INT_PTR GetFieldLength(INT_PTR nCol) const { nCol = 0;  return 0;} ;

   //returns index of a column
   virtual INT_PTR GetColIndex(LPCSTR strColumnName) const { strColumnName = NULL;  return -1;} ;
};

//////////////////////////////////////////////////////////////////////////////
// MDCS_GetDBResultsCCallback
// 
//
class  MDCSUTILS MDCS_GetDBResultsCCallback
{
public:
   MDCS_GetDBResultsCCallback() {};
   virtual ~MDCS_GetDBResultsCCallback() {};

   //called to get next row of data
   virtual BOOL GetNextResult(MDCS_QueryResults* pQueryRes) = 0;

   //called to get number of results
   virtual void SetResultNumber(LONGLONG nCount) = 0;

   //called when there is an error 
   virtual void Error(LPCSTR pErrorText) = 0;

   // called when completely done
   virtual void Done() = 0;

   //called bby function to check if rerults should be return in their original format
   virtual BOOL ProcessResultsInOriginalFormat() const = 0;

   //called to get info about result structure (field names and types)
   //all field  will be empty
   virtual BOOL GetResultInfo(MDCS_QueryResults* pQueryRes) { if (pQueryRes) return TRUE; else return FALSE;};

private:
   // hide the default copy constructors
   MDCS_GetDBResultsCCallback(MDCS_GetDBResultsCCallback const &);
   const MDCS_GetDBResultsCCallback &operator=(MDCS_GetDBResultsCCallback const &);      
};


//////////////////////////////////////////////////////////////////////////////
// MDCS_GetBlobColumnResults
// 
//
class  MDCSUTILS MDCS_GetBlobColumnResults : public MDCS_GetDBResultsCCallback
{
public:
   MDCS_GetBlobColumnResults() {};
   virtual ~MDCS_GetBlobColumnResults() {};
public:
   //following functions will be always return to client before first GetNextResult call
   //return number of created blob columns to client 
   virtual void NumberBlobColumns(int nColCount) = 0;

   //return max length of a blob column to client 
   virtual void MaxBlobColumnLength(int nMaxLength) = 0;

private:
   // hide the default copy constructors
   MDCS_GetBlobColumnResults (MDCS_GetBlobColumnResults  const &);
   const MDCS_GetBlobColumnResults &operator=(MDCS_GetBlobColumnResults const &);      

};


class MDCSUTILS MDCS_GetProgressStatus
{
public:

enum E_ProgressStatus
{
   //ePSNotStarted,
   ePSInProgress,
   ePSCancelled,
   ePSDone,
   ePSError,
};

public:
   MDCS_GetProgressStatus() {};
   virtual ~MDCS_GetProgressStatus() {};


//to get current progress
   virtual UINT_PTR GetProgress() const = 0;

   //to get current progress
   virtual LPCSTR GetProgressText() const = 0;

   //to get current progress
   virtual LPCSTR GetTitleText() const = 0;

   //to get a status
   virtual E_ProgressStatus GetStatus()  const = 0;

   //to get an error description
   virtual LPCSTR GetError() const  = 0;

private:
   // hide the default copy constructors
   MDCS_GetProgressStatus(MDCS_GetProgressStatus const &);
   const MDCS_GetProgressStatus &operator=(MDCS_GetProgressStatus const &); 

};

///////////////////////////////////////////////////////////////////////////////////////////
//  MDCS_GetBlobCallback - call back for getting data blobs
//  You can instanciate this class since the functionality for getting
//  blobs is pretty consistance.
// 
class MDCSUTILS MDCS_GetBlobCallback 
{
public:
   MDCS_GetBlobCallback () {};
   virtual ~MDCS_GetBlobCallback () {};
 
   //next result is about to be retrived, returns size of the result
   virtual BOOL NextResult(LONGLONG lSizeOfResult) = 0;
   //next chunk of data that will be received from database
   //pChuck - data
   //uChunkSize - size
   virtual BOOL NextChunk( const BYTE* pChuck, UINT uChunkSize ) = 0;   

   //total size of data
   virtual LONGLONG GetTotalSize() const = 0;

   //size of the transfer packet
   virtual UINT GetPacketSize() const = 0;
    
   // called when completely done
   virtual void Done() = 0;
 
   // sent when there is an error
   virtual void Error(LPCSTR pErrorText) = 0;
 
private:
    // hide the default copy constructors
    MDCS_GetBlobCallback (MDCS_GetBlobCallback const &);
    const MDCS_GetBlobCallback &operator=(MDCS_GetBlobCallback const &);      
};

///////////////////////////////////////////////////////////////////////////////////////////
//  MDCS_SaveBlobCallback - call back for saving data blobs
//  You can instanciate this class since the functionality for getting
//  blobs is pretty consistance.
// 
class MDCSUTILS MDCS_SaveBlobCallback
{
public:
   MDCS_SaveBlobCallback () {};
   virtual ~MDCS_SaveBlobCallback() {};

   //to get a next chunk of data
   // pChunk - data
   // uSizeChunk - size that was requested
   // uSizeRead - actual size that was read
   virtual BOOL NextChunk( BYTE* pChunk, const UINT_PTR& uSizeChunk,  UINT_PTR& uSizeRead) = 0;   

   // called when completely done
   virtual void Done() = 0;
 
   virtual UINT GetPacketSize() const = 0;

   virtual LONGLONG GetTotalSize() const = 0;
   // sent when there is an error
   virtual void Error(LPCSTR pErrorText) = 0;
 
private:
    // hide the default copy constructors
    MDCS_SaveBlobCallback(MDCS_SaveBlobCallback &);
    const MDCS_SaveBlobCallback &operator=(MDCS_SaveBlobCallback const &);      
};


///////////////////////////////////////////////////////////////////////////////////////////
//  MDCS_SaveBlobCallback - call back for saving data blobs
//  You can instanciate this class since the functionality for getting
//  blobs is pretty consistance.
// 
class MDCSUTILS MDCS_GroupInfoCallback
{
   public:
      MDCS_GroupInfoCallback () {};
      virtual ~MDCS_GroupInfoCallback() {};

   public:
      //to get a total number of groups
     virtual void ItemCount(LONGLONG lGroupCount) = 0;
     //to get group info 
     virtual BOOL GetNextInfo(const MDCS_ST_GroupInfo& stGroupInfo) = 0; 

   private:
    // hide the default copy constructors
    MDCS_GroupInfoCallback(MDCS_GroupInfoCallback &);
    const MDCS_GroupInfoCallback &operator=(MDCS_GroupInfoCallback const &);      
};

///////////////////////////////////////////////////////////////////
//class is a smart pointer (wrapper aroung HDBHANDLE) to deal with HDBHandles
// can be used only on stack 
class MDCSUTILS MDCS_DBHandleSmartPtr
{
private:
   HDBHANDLE    m_hdbHandle;

private: 
   MDCS_DBHandleSmartPtr() {};
   MDCS_DBHandleSmartPtr&  operator=( const MDCS_DBHandleSmartPtr &stConnection );
   
public:
	
   //constructor 
   //bSilentMode indicates if connection should be in silent mode
   MDCS_DBHandleSmartPtr(const MDCS_ST_UserLogin& stUserLogin, BOOL bSilentMode = FALSE, BOOL bConnectAsAppUser = TRUE);

   MDCS_DBHandleSmartPtr(HDBHANDLE hdbHandle, BOOL bSilentMode = FALSE);
   MDCS_DBHandleSmartPtr(LPCTSTR pszConnectionString, BOOL bSilentMode = FALSE);

   virtual    ~MDCS_DBHandleSmartPtr();

   
   HDBHANDLE GetHandle(BOOL bReconnect = FALSE);
};

///////////////////////////////////////////////////////////////////
//class to create a connection to the database so it can be re-used in functions
/*class MDCSUTILS MDCS_DBConnection
{
private: 
   MDCS_DBConnection() {};
   MDCS_DBConnection&  operator=( const MDCS_DBConnection &stConnection );
   
public:
   virtual    ~MDCS_DBConnection() {};   
   
   HDBHANDLE GetHandle()=0;
};

MDCS_DBConnection * MDCSTOREUTILS_MDCS_CreateDBConnection(const MDCS_ST_UserLogin& stUserLogin); 
void MDCSTOREUTILS_MDCS_DestroyDBConnection(MDCS_DBConnection * pConnection);  */


////////////////////////////////////////////////////////////////////
//                                                                //
//  function to work with connections                             //
//                                                                //
////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to get connection objects
//will call a dialog to obtain login info and return a structure that could be used in all other function calls
//if it been called for Oracle, then structure will contain the selected databsae name
//Input: 
//       pstLoginInfoIn - default settings
//       bCheckSavePassword - default settings for password 
//       pszTitle - dialog title
//       hWnd - application window 
//       bDefaultCheckSavePassword  - to check password by default 
//       bReloginMode - bring up connection dialog in re-login mode
//Output: 
//        pstLoginInfo - selected settings
//        pbSavePasswordChecked - if password save option is checked , if null option will not appear oin the dialog
//Return: FALSE - if dialog canceled

MDCSUTILS BOOL WINAPI MDCS_CONNECTION_GetDetails(MDCS_ST_UserLogin * pstLoginInfo, BOOL* pbSavePasswordChecked = NULL, HWND hWnd = NULL, LPCSTR pszTitle = NULL, const MDCS_ST_UserLogin* pstLoginInfoIn = NULL,  BOOL bDefaultCheckSavePassword = FALSE, BOOL bReloginMode = FALSE, 
                                                 BOOL bValidateVersion = TRUE);

//////////////////////////////////////////////////////////////////////////////////////////
//to test that the user credentials can create a database connection
//Input: 
//       pstLoginInfo - pointer to the strucrure that contains login info
//       nSize - size of pDatabaseName 
//       bConnectAsAppUser - flag indicates that connection should be made using user permissions as application user 
//Output: 
//       pDatabaseName - database name of the connection
//Return: FALSE - if error occured
 MDCSUTILS BOOL WINAPI MDCS_CONNECTION_TestCredentials( const MDCS_ST_UserLogin * pstLoginInfo, LPSTR pDatabaseName, int nSize, BOOL bConnectAsAppUser = TRUE  );

//////////////////////////////////////////////////////////////////////////////////////////
//to generate ODBC connection string from MDCS_ST_UserLogin structure
//Input: 
//       pstLoginInfo - pointer to the strucrure that contains login info
//       nSize - size of connection string 
//Output: 
//       pszConnectionString - generated connection string 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_CreateConnectionString(const MDCS_ST_UserLogin * pstLoginInfo, LPSTR pszConnectionString, int nSize);


//////////////////////////////////////////////////////////////////////////////////////////
//to generate ODBC connection string from MDCS_ST_UserLogin structure
//Input: 
//       pstLoginInfo - pointer to the strucrure that contains login info
//       nSize - size of connection string 
//       bConnectAsAppUser - flag indicates that connection should be made using user permissions as application user 
//Output: 
//       pszConnectionString -  connection string 
//Return: FALSE - if error occured
MDCSUTILS HDBHANDLE WINAPI MDCS_CONNECTION_GetDBHandleFromString(LPCTSTR pszConnectionString, BOOL bSetSilentMode = FALSE);

/////////////////////////////////////////////////////////////////////////////////////
//function to get db handle
//Input: 
//       stLoginInfo - pointer to the strucrure that contains login info
//       bSetSilentMode - flag indicates if silent mode should be set on connection
//Returns: connection handle 
MDCSUTILS HDBHANDLE WINAPI MDCS_CONNECTION_GetDBHandle(const MDCS_ST_UserLogin& stLoginInfo, BOOL bSetSilentMode = FALSE,  BOOL bConnectAsAppUser = TRUE );

//MDCSUTILS BOOL WINAPI MDCS_CONNECTION_GetUserInfoFromHandle(HDBHANDLE hDBHandle, MDCS_ST_UserLogin& stLoginInfo);
/////////////////////////////////////////////////////////////////////////////////////
//function to create a new db handle from existing one
//Input: 
//       hDBHandle - pointer to the strucrure that contains login info
//       bSetSilentMode - flag indicates if silent mode should be set on connection
//Returns: connection handle 
MDCSUTILS HDBHANDLE WINAPI MDCS_CONNECTION_GetNewDBHandle(HDBHANDLE hDBHandle, BOOL bSetSilentMode = FALSE );

/////////////////////////////////////////////////////////////////////////////////////
//function to destroy db handle
//Input: 
//    hHandle        - database connection handle
//Returns: conneciton handle 
MDCSUTILS void WINAPI MDCS_CONNECTION_DestroyDBHandle(HDBHANDLE hHandle);


/////////////////////////////////////////////////////////////////////////////////////
//function to reconnect to the database using existing connection, can be used to make sure that object is connection to the database 
//Input: 
//    hHandle        - database connection handle
//Returns FALSE if fails 
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_Reconnect(HDBHANDLE hHandle);


/////////////////////////////////////////////////////////////////////////////////////
//function to disconnect from the database 
//does not delete handle 
//Input: 
//    hHandle        - database connection handle
MDCSUTILS void WINAPI MDCS_CONNECTION_Disconnect(HDBHANDLE hHandle);

//////////////////////////////////////////////////////////////////////////////////////////
//sets database connection to async mode will affect all the statement
//
//Input: 
//    hHandle        - database connection handle
//Return: FALSE - if error occured
 MDCSUTILS BOOL WINAPI MDCS_CONNECTION_SetAsyncMode( HDBHANDLE hHandle, BOOL bSet = TRUE);


 //////////////////////////////////////////////////////////////////////////////////////////
//will cancel current statement
//
//Input: 
//    hHandle        - database connection handle
//Return: FALSE - if error occured
 MDCSUTILS BOOL WINAPI MDCS_CONNECTION_CancelQueryExecution( HDBHANDLE hHandle);

 //////////////////////////////////////////////////////////////////////////////////////////
//to generate MDCS_ST_UserLogin structure from ODBC connection string 
//Input: 
//       pszConnectionString - generated connection string 
//Output: 
//       pstLoginInfo - pointer to the strucrure that contains login info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_GetDetailsFromString(MDCS_ST_UserLogin * pstLoginInfo, LPCSTR pszConnectionString);


//////////////////////////////////////////////////////////////////////////////////////////
//to start transaction
//Input: 
//    hHandle        - database connection handle
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_BeginTransaction(HDBHANDLE hHandle);


//////////////////////////////////////////////////////////////////////////////////////////
//to commit transaction
//Input: 
//    hHandle        - database connection handle
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_CommitTransaction(HDBHANDLE hHandle);


//////////////////////////////////////////////////////////////////////////////////////////
//to roallback transaction
//Input: 
//    hHandle        - database connection handle
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_RollbackTransaction(HDBHANDLE hHandle);


//////////////////////////////////////////////////////////////////////////////////////////
//to get a type of the database 
//Input: 
//        hHandle        - database connection handle
//Return: FALSE - type of a database server (if server is supported)
MDCSUTILS MDCS_E_SQLServerType WINAPI MDCS_CONNECTION_GetDatabaseType(HDBHANDLE hHandle);


///////////////////////////////////////////////////////
//function: to get information about connection: Server name, type, version,  ODBC name, driver version, etc.
//Input: 
//    hHandle        - database connection handle
//Output:
//    stConnectionInfo  - structure that contains connection information 
//Return: BOOL if fails
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_GetInfo(HDBHANDLE hHandle, MDCS_ST_ConnectionInfo& stConnectionInfo);


///////////////////////////////////////////////////////
//function: to get information about connection attributes: DNS name, User name, database name
//Input: 
//    hHandle        - database connection handle
//Output:
//    stConnectionAttr  - structure that contains connection information 
//Return: BOOL if fails
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_GetAttributes(HDBHANDLE hHandle, MDCS_ST_ConnectionAttr& stConnectionAttr);


///////////////////////////////////////////////////////
//function: to set silent mode on connection - no messages will bbe displayed
//Input: 
//    hHandle        - database connection handle
//    bSilentMode    - silent mode flag
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_SetSilentMode(HDBHANDLE hHandle, BOOL bSilentMode = TRUE);


//////////////////////////////////////////////////////////////////////////////////////////
//to check if connection is active 
//Input: 
//        hHandle        - database connection handle
//        bReconnect     - if true - connection wil be reestablished
//Return: FALSE - type of a database server (if server is supported)
MDCSUTILS BOOL WINAPI MDCS_CONNECTION_CheckIfDead(HDBHANDLE hHandle, BOOL bReconnect = TRUE);

 ///////////////////////////////////////////////////////////////////////////////////////
//  function to work with resultsets
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to import resultset data into database 
// Input:
// pstObjDesc - object description
// pExDataSource -pointer to the datasource that will supply data 
// hHandle        - database connection handle
// pCallBack - progress call back class 
// nSize - size of the pszObjectID 
//Output:
//    pszObjectID  - ID of a new created object
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ImportDataToDB(HDBHANDLE hHandle, const MDCS_ST_ResultSet * pstObjDesc,  const MDCS_ImportResultset * pExDataSource,  LPSTR pszObjectID, int nSize, MDCS_ProgressCallback * pCallBack);



//////////////////////////////////////////////////////////////////////////////////////////
//to get resultset data 
//Input: 
//       hHandle        - database connection handle
//       pszResultsetID - resultset ID that data will be returned for
//       pResultCallback - pointer to a callback function to get data 
// the columns that will be returned: PRINTED_SPOT_ID - feature ID, SUBSTANCE_NAME - feature name 
//Comments: call  MDCS_GetResultsetDataTypes function to find out about additional columns that will be returned in a call back
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetResultsetData(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_GetDBResultsCCallback * pResultCallback);


//////////////////////////////////////////////////////////////////////////////////////////
//to get a description of all resultsets in the database
//Input: 
//       hHandle        - database connection handle
//       pResultCallback - pointer to a callback function to get values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetAllResultsets(HDBHANDLE hHandle,  MDCS_GetDBResultsCCallback * pResultCallback);


//////////////////////////////////////////////////////////////////////////////////////////
//to get a description of individual recordset
//    hHandle        - database connection handle
//
MDCSUTILS BOOL WINAPI MDCS_GetResultsetInfo(HDBHANDLE hHandle,  LONGLONG lAssayID, MDCS_GetDBResultsCCallback * pResultCallback);


///////////////////////////////////////////////////////////////////////////////////////
//  function to work with result set sata types
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to get Resultset data types
//Input:
//       hHandle        - database connection handle
//       pszResultsetID - resultset database ID 
//       pResultCallback - pointer to a call back function to get information from database
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetResultsetDataTypes(HDBHANDLE hHandle,  LONGLONG lAssayID, MDCS_GetDBResultsCCallback * pResultCallback);


//////////////////////////////////////////////////////////////////////////////////////////
//to get all data types for all resultsets
//Input:
//       hHandle        - database connection handle
//       pResultCallback - pointer to a call back function to get information from database
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetAllDataTypes(HDBHANDLE hHandle,   MDCS_GetDBResultsCCallback * pResultCallback);

//////////////////////////////////////////////////////////////////
//Function: MDCS_GetAllDataTypesOfAssays
//Description: To get all data types for all resultsets
//Input:
//       hHandle       - database connection handle
//       arrAssayIDs   - array of assayIDs;
//       pResultCallback - pointer to a call back function to get information from database
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetAllDataTypesOfAssays(HDBHANDLE hHandle, LONGLONG* arrAssayIDs, INT_PTR nSize, MDCS_GetDBResultsCCallback * pResultCallback);

//////////////////////////////////////////////////////////////////////////////////////////
//to get unique data types
//Input:
//       hHandle        - database connection handle
//       pResultCallback - pointer to a call back function to get information from database
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetUniqueDataTypes(HDBHANDLE hHandle,   MDCS_GetDBResultsCCallback * pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to get statistic use of a measurement ( number of assays and dataset use  a measurement) 
//Input: 
//    hHandle           - database connection handle
//    lMeasurementID    - measurement that should be deleted
//Output:    
//    stMeasurementSta - pointer to a statistic structure
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementStatistic(HDBHANDLE hHandle, LONGLONG lMeasurementID, MDCS_ST_MeasurementUseStatistic& stMeasurementSta);

///////////////////////////////////////////////////////////////////////////////////////
//  Error handling                                                                  ///
///////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//to get last error 
//return: error code one of MDCS_ERR_..., see above
MDCSUTILS int WINAPI MDCS_GetLastError();


//////////////////////////////////////////////////////////////////////////////////////////
//to get last error msg
//returns: error code one of MDCS_ERR_..., see above
//pnErrorSize - size of the error not including null terminated symbol
MDCSUTILS int WINAPI MDCS_GetLastErrorMsg(LPSTR pszError, int nErrorSize, int* pnErrorSize = NULL);

//////////////////////////////////////////////////////////////////////////////////////////
//Description: gets default error message for the error code MDCS_ERR_
//Input:
//       nError - error code 
//       nSize  - size of the pszError (use MAX_ERR_SIZE)
//Output:
//       pszError - error
//return: FALSE - if error is not found
MDCSUTILS BOOL WINAPI MDCS_GetDefaultErrorMsg(int nError, LPSTR pszError, int nSize);


///////////////////////////////////////////////////////////////////////////////////////
//  function to work with blob
///////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to insert image info 
//Input:
//       pBlobInfo - pointer to the structure that describes blobs
//       hHandle        - database connection handle
//Output:       
//       lBlobID - creted blob id    
//Return: FALSE - if error occured
//MDCSUTILS BOOL WINAPI MDCS_BLOB_InsertInfo(const MDCS_ST_UserLogin * pstLoginInfo, const MDCS_ST_BlobInfo * pBlobInfo,  MDCS_E_BlobType  eBlobType, LONGLONG* lBlobID);


//////////////////////////////////////////////////////////////////////////////////////////
//to get image info using blob ID
//Input: 
//       hHandle        - database connection handle
//       lBlobID - blob ID
//       hHandle        - database connection handle
//Output:
//       pBlobInfo - blob info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_GetInfo(HDBHANDLE hHandle, MDCS_ST_BlobInfo * pBlobInfo, LONGLONG lBlobID, MDCS_E_BlobType eBlobType );


//////////////////////////////////////////////////////////////////////////////////////////
//to update image id in Plate image table using blob ID (image_id)
//Input: 
//       hHandle        - database connection handle
//       lCurrentImageObjID - is blob ID 
//       lNewImageObjID - updated value of blob id in Plate_Images
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_UpdatePlateObjectImageID(HDBHANDLE hHandle, LONGLONG lCurrentImageObjID, LONGLONG lNewImageObjID );


////////////////////////////////////////////////////////////////////
//Function: MDCS_BLOB_GetBlobInfoEx
//Description: To get attach file info using blob ID
//Input: 
//        hHandle       - database connection handle
//        lBlobID       - blob ID
//Output:
//        pBlobInfo     - blob info
//Return: FALSE - if error occured

MDCSUTILS BOOL WINAPI MDCS_BLOB_GetBlobInfoEx(HDBHANDLE hHandle, MDCS_ST_BlobInfoEx * pBlobInfo, LONGLONG lBlobID, MDCS_E_BlobType eBlobType );

//////////////////////////////////////////////////////////////////////////////////////////
//to get image info using reference ID( dataset id,or assay id, or...)
//Input: 
//       hHandle        - database connection handle
//       lReferenceID   - reference ID which is assayid or dataset id or ...
//       hHandle        - database connection handle
//Output:
//       pBlobInfo - blob info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_GetInfoByReferenceID(HDBHANDLE hHandle, LONGLONG lReferenceID, MDCS_E_BlobType eBlobType, MDCS_GetDBResultsCCallback* pResultCallback );

//////////////////////////////////////////////////////////////////////////////////////////
//to get all attach file info using reference ID( dataset id,or assay id)
//Input: 
//       hHandle        - database connection handle
//       lReferenceID   - reference ID which is assayid or dataset id 
//       hHandle        - database connection handle
//Output:
//       pBlobInfo - blob info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_GetBlobInfoByReferenceIDEx(HDBHANDLE hHandle, LONGLONG lReferenceID, MDCS_E_BlobType eBlobType, MDCS_GetDBResultsCCallback* pResultCallback );

////////////////////////////////////////////////////////////////////
//Function: MDCS_BLOB_GetNumBlobOfObject
//Description: to get number of blob file attached to an object( assay, dataset) using reference ID
//Input: 
//       hHandle - database connection handle
//       lReferenceID - assay id or dataset id, or ...
//
//       pBlobType - blob type 
//Output:
//       lNumBlob - number of blob object of a reference object id
//Return: FALSE - if error occurs
MDCSUTILS BOOL WINAPI MDCS_BLOB_GetNumBlobOfObject(HDBHANDLE hHandle, LONGLONG lReferenceID, MDCS_E_BlobType eBlobType, LONGLONG& lNumBlob);


//////////////////////////////////////////////////////////////////////////////////////////
//to get info for all images in database
//MDCSUTILS BOOL WINAPI MDCS_GetAllImageInfo(const MDCS_ST_UserLogin * pstLoginInfo,  MDCS_GetDBResultsCCallback * pResultCallback);

//////////////////////////////////////////////////////////////////////////////////////////
// to get/create location ID 
// Input:
//		bCreateNew - if TRUE - function will create new record
//		stLocation - pointer to the structure that contains location description (all fields must be filled except for nLocationID )
//    hHandle        - database connection handle
// Output: 
//		nLocationID  - location id, -1 if location is not found 
// Returns: 
//		FALSE -if function fails 
MDCSUTILS BOOL WINAPI MDCS_BLOB_GetLocationID(HDBHANDLE hHandle, const MDCS_ST_BlobLocation *  pstLocation,  LONGLONG* lLocationID, BOOL bCreateNew = FALSE);

//////////////////////////////////////////////////////////////////////////////////////////
// MDCS_BLOB_GetUniqueFileLocationByFilter
// Description: to get unique location info base on filter 
// Input:
//		eFilter - filter to get data//		
//    hHandle - database connection handle
// Output: 
//    Depend on the filter, the output structure will contain all(1-5) follow or one or some of them )
//		1) server name 
//    2) serverRoot 
//    3) Directory 
//    4) Location Type 
//    5) port number
// Returns: 
//		FALSE -if function fails 

MDCSUTILS BOOL WINAPI MDCS_BLOB_GetUniqueLocationNameByFilter(HDBHANDLE hHandle, MDCS_CL_BlobLocationCB* pCallBack, MDCS_E_LocationFilter eFilter = MDCS_eServerName);

//////////////////////////////////////////////////////////////////////////////////////////////
//MDCS_GetAllBlobInfoByFilterAndCriteria
//Get all image info base on criteria, blob type and file location filter( server name or root name, or directory )
//Input:
//    hHandle - db connection handle
//    arrCriteria - all criteria to filter info ex: server name or directory or root name
//    eBlobType - type of blob
//    eFilter - type of filter
//Output:
//    pCallback - call back result
//Return: FALSE if error occur

MDCSUTILS BOOL WINAPI MDCS_BLOB_GetAllBlobInfoByLocationFilterAndLocationInfo(HDBHANDLE hHandle, 
																										MDCS_ST_BlobLocation* arrBlobLocation,
																										INT_PTR nNumLocation, MDCS_E_BlobType eBlobType,
																										MDCS_CL_BlobInfoCB* pCallBack, 
																										MDCS_E_LocationFilter eFilter = MDCS_eServerName);

//////////////////////////////////////////////////////////////////////////////////////////////
//MDCS_GetAllBlobInfoByFilterAndCriteria
//Get all image info base on plate id
//Input:
//    hHandle - db connection handle
//    lPlateID - plate id 
//    eBlobType - type of blob
//   
//Output:
//    pCallback - call back result
//Return: FALSE if error occur

MDCSUTILS BOOL WINAPI MDCS_BLOB_GetAllBlobInfoByPlateID(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_E_BlobType eBlobType, MDCS_CL_BlobInfoCB* pCallBack);

//////////////////////////////////////////////////////////////////////////////////////////
// to get blob location description 
//Input:
//    hHandle        - database connection handle
//		nLocationID    - location ID, 
//Output:
//		pstLocation - pointer to the structure that contains location description 
//Return: FALSE - if error occured


MDCSUTILS BOOL WINAPI MDCS_BLOB_GetLocation (HDBHANDLE hHandle, LONGLONG nLocationID, MDCS_ST_BlobLocation * pstLocation);
//////////////////////////////////////////////////////////////////////////////////////////
//MDCS_BLOB_DeleteUnUsedLocations
//to remove unused locations in File_Location 
//Input:
//    hHandle        - database connection handle
//		pProgressCallback   - progress callback 
//Return: FALSE - if error occured

MDCSUTILS BOOL WINAPI MDCS_BLOB_DeleteUnUsedLocations (HDBHANDLE hHandle,MDCS_ProgressCallback* pProgressCallback);

//////////////////////////////////////////////////////////////////////////////////////////
//MDCS_BLOB_DeleteFileLocation
//to remove a locations 
//Input:
//    hHandle        - database connection handle
//		lLocationID    - progress callback 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_DeleteFileLocation (HDBHANDLE hHandle,const LONGLONG lLocaitonID);

//////////////////////////////////////////////////////////////////////////////////////////
//MDCS_BLOB_LocationIsUsed
//to check if any existing blob are store in location
//Input:
//    hHandle        - database connection handle
//		lLocationID   - location id
//Output:   bIsUse  - TRUE if is used some place, otherwise FALSE
//Return: FALSE - if error occured

MDCSUTILS BOOL WINAPI MDCS_BLOB_LocationIsUsed(HDBHANDLE hHandle,LONGLONG lLocationID, BOOL& bIsUsed);
/////////////////////////////////////////////////////////////////////
//to save blob in database or file server
//Input: 
//    hHandle        - database connection handle
//    pImageInfo     - pointer to the structure that contains image information 
//    pImageLocation - pointer to the structure that contains destination server info 
//    pCallBack      - pointer to callback that will be used to transfer data
//    eStorage       - type of destination where image will be saved (default place is database)
//Output: 
//    nImageIDOut    - database ID of the image 
//Return: FALSE - if error occured
/*MDCSUTILS BOOL WINAPI MDCS_SaveImage( const MDCS_ST_UserLogin * pstLoginInfo,          // structure that contains the user credentials to login into the database server
                                                const MDCS_ST_ImageInfo * pImageInfo,                 // structure that contains info about the image
                                                const MDCS_ST_ImageLocation * pImageLocation,         // structure that contains info about the image location, mainly used when saving on the file server
                                                MDCS_E_BlobType eBlobType,				                  //type of the blob
                                                MDCS_SaveBlobCallback * pCallBack,                 // callback that supplies the file data to the function                                               
                                                LONGLONG* nImageIDOut,                                         // the database ID assigned to the image.
                                                MDCS_E_FileStorage eStorage = MDCS_eDatabaseServer);                   // specify the location to save the image.                                               */


//////////////////////////////////////////////////////////////////////////////////////////
//to get blob from the storage, database or file server 
//Input: 
//    hHandle        - database connection handle
//    lBlobID       - database ID of the bllkob 
//    pCallBack      - pointer to callback that will be used to transfer data
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_Get( HDBHANDLE hHandle, 
                                               LONGLONG lBlobID, 
                                               MDCS_E_BlobType pBlobType,				  //type of the blob
                                               MDCS_GetBlobCallback * pCallBack );


/////////////////////////////////////////////////////////////////////
//to save blob data in database or file server
//Input: 
//    hHandle        - database connection handle
//    pBlobInfo     - pointer to the structure that contains image information 
//    pBlobLocation - pointer to the structure that contains destination server info 
//    pCallBack      - pointer to callback that will be used to transfer data
//    eStorage       - type of destination where image will be saved (default place is database)
//	  pBlobType		 - type of the blob
//    pszDirectoryExtra - if specified, will create directory with pszDirectoryExtra on FileServer
//Output: 
//    lBlobIDOut    - database ID of the blob
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_Save( HDBHANDLE hHandle,          // structure that contains the user credentials to login into the database server
                                            const MDCS_ST_BlobInfo * pImageInfo,                 // structure that contains info about the image
               							        MDCS_E_BlobType pBlobType,				  //type of the blob
                                            MDCS_SaveBlobCallback * pCallBack,                 // callback that supplies the file data to the function                                               
                                            LONGLONG* lBlobIDOut,                                         // the database ID assigned to the image.
                                            const LONGLONG* lRefObjectID /*= NULL */,
                                            MDCS_E_FileStorage eStorage = MDCS_eDatabaseServer,                   // specify the location to save the image.                                              
                                            LPCSTR pszDirectoryExtra = NULL
                                            );


////////////////////////////////////////////////////////////////////////
//Function: RemoveBlobData
//Description: To remove blob data from database server and file server
//Input: 
//    hHandle        - database connection handle
//    lID             - ID of the record that needs to be deleted
//    eBlobType       - type of the blob

MDCSUTILS BOOL WINAPI MDCS_BLOB_RemoveBlobData(HDBHANDLE hHandle, LONGLONG lID, MDCS_E_BlobType eBlobType, BOOL bNotRemoveRecord = FALSE);

////////////////////////////////////////////////////////////////////////
//Function: RemoveFile
//Description: To remove file on file server and UNC 
//Input: 
//    hHandle        - database connection handle
//    stBlobLocation - structure describe location of file need to be deleted
//    eBlobType      - type of the blob

MDCSUTILS BOOL WINAPI MDCS_BLOB_RemoveFile(HDBHANDLE hHandle,const MDCS_ST_BlobLocation& stBlobLocation, LPCSTR szFileName );


////////////////////////////////////////////////////////////////////
//Function: MDCS_BLOB_UpdateBlobDescAndName
//Description: to update desc and name of the blob  
//Input: 
//       hHandle - database connection handle
//       lBlobID - BlobID 
//       pBlobInfo - info to update in database;
//
//Return: FALSE - if error occurs

MDCSUTILS BOOL WINAPI MDCS_BLOB_UpdateBlobDescAndName(HDBHANDLE hHandle, LONGLONG lBlobID, const MDCS_ST_BlobInfo* pBlobInfo, MDCS_E_BlobType eBlobType);
////////////////////////////////////////////////////////////////////
//Function: MDCS_BLOB_UpdateFileAttachDescAndName
//Description: to update desc and display name of the attached file   
//Input: 
//       hHandle - database connection handle
//       lBlobID - BlobID 
//       pBlobInfo - info to update in database;
//
//Return: FALSE - if error occurs

MDCSUTILS BOOL WINAPI MDCS_BLOB_UpdateBlobDescAndNameEx(HDBHANDLE hHandle, LONGLONG lBlobID, const MDCS_ST_BlobInfoEx* pBlobInfo, MDCS_E_BlobType eBlobType);

//==============================================================================================
// FUNCTION: MDCS_BLOB_SaveBlobEx
// PURPOSE:  To save blob into database or file server
//Input: 
//    hHandle       - database connection handle
//    pBlobInfo     - pointer to the structure that contains image information 
//    pCallBack      - pointer to callback that will be used to transfer data
//	  pBlobType	     - type of the blob
//Output: 
//    lBlobIDOut    - database ID of the image 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_SaveBlobEx(HDBHANDLE hHandle,     
                              const MDCS_ST_BlobInfoEx * pBlobInfo,            
							         MDCS_E_BlobType eBlobType,				  
                              MDCS_SaveBlobCallback * pCallBack,            
                              LONGLONG* lBlobIDOut,
                              const LONGLONG* lRefObjectID
                              )    ;

//==============================================================================================
// FUNCTION: MDCS_BLOB_Attach
// PURPOSE:  To attach blob (change blob information)
// comments: before runnong this fnction make sure that location id and blob id exists
//Input: 
//    hHandle       - database connection handle
//    stBlobInfo    - structure that describes blob
//	  eBlobType	    - type of the blob
//Output:
//    plIDOut  -     created image ID
//Return:           
//    FALSE         - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_Attach(HDBHANDLE hHandle,  MDCS_E_BlobType eBlobType, 
                           const MDCS_ST_BlobInfoEx& stBlobInfo, LONGLONG* plIDOut = NULL);
////////////////////////////////////////////////////////////////////
//Function: MDCS_BLOB_UpdateBlobInfo
//Description: to update desc and display name of the attached file   
//Input: 
//       hHandle - database connection handle
//       lBlobID - BlobID 
//       pBlobInfo - info to update in database;
//       eBlobType - type of blob
//Return: FALSE - if error occurs

MDCSUTILS BOOL WINAPI MDCS_BLOB_UpdateBlobInfo(HDBHANDLE hHandle, LONGLONG lBlobID, const MDCS_ST_BlobInfo* pBlobInfo, MDCS_E_BlobType eBlobType);
//class to process object count 
class MDCSUTILS MDCS_CL_BlobLocationCB
{
public:
   MDCS_CL_BlobLocationCB() {};
   virtual  ~MDCS_CL_BlobLocationCB() {};

private:
    // hide the default copy constructors
    MDCS_CL_BlobLocationCB(MDCS_CL_BlobLocationCB const &);
    const MDCS_CL_BlobLocationCB  &operator=(MDCS_CL_BlobLocationCB const &);     
public: 
   virtual void NextResult(const MDCS_ST_BlobLocation& ) = 0;
};

//class to process blob info  
class MDCSUTILS MDCS_CL_BlobInfoCB
{
public:
   MDCS_CL_BlobInfoCB() {};
   virtual  ~MDCS_CL_BlobInfoCB() {};

private:
    // hide the default copy constructors
    MDCS_CL_BlobInfoCB(MDCS_CL_BlobInfoCB const &);
    const MDCS_CL_BlobInfoCB  &operator=(MDCS_CL_BlobInfoCB const &);     
public: 
   virtual void NextResult(const MDCS_ST_BlobInfo& ) = 0;
};

/////////////////////////////////////////////////////////////////////
//function to get available blob locations by blob type 
//Input: 
//    hHandle        - database connection handle
//    eType          - type of blobs
//Output: 
//     pCallBack - callback class will retur results with blob info 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetBlobLocationsByType(HDBHANDLE hHandle, MDCS_E_BlobType eType, MDCS_CL_BlobLocationCB* pCallBack);


/////////////////////////////////////////////////////////////////////
//function to map blob locations
//Input: 
//    hHandle        - database connection handle
//    stSource       -  source 
//    stDest         - destination
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_MapLocations(HDBHANDLE hHandle, const MDCS_ST_BlobLocation& stSource,  const MDCS_ST_BlobLocation& stDest);


//==============================================================================================
// FUNCTION: MDCS_BLOB_CanWriteToLocation
// PURPOSE:  To check if blob can be saved to specified location
//Input: 
//    hHandle        - database connection handle
//    stBlobLocation  - structure that describes location 
//    pszDirectoryExtra - if specified, will create directory with pszDirectoryExtra on FileServer
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_BLOB_CanWriteToLocation(HDBHANDLE hHandle,     
                              const MDCS_ST_BlobLocation& stBlobLocation,            
                              LPCSTR pszDirectoryExtra = NULL
                              );               

/////////////////////////////////////////////////////////////////////
//function will generate new database id 
//Input: 
//    hHandle        - database connection handle
//    nIDSize  - size of ID use MDCS_MAX_DB_ID
//Output: 
//    pszID    - generated id  
//    pnIDSizeOut  - size of the key 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_GetNewDatabaseID(HDBHANDLE hHandle, LPSTR pszID, int nIDSize, int* pnIDSizeOut);


/////////////////////////////////////////////////////////////////////
//function 
//to fill out MDCS_ST_BlobLocation  structure with results of MDCS_QueryResults
//Input: 
//    pResults  - results of the query
//    bNativeFormat - format type of query results, if !native then all results are treated as strings
//Output:
//    stBlobLoc - location structure (if stBlobLoc.lLocationID == 0 - record in DB)
MDCSUTILS BOOL WINAPI MDCS_BLOB_FillOutBlobLocationStruct(const MDCS_QueryResults* pResults, MDCS_ST_BlobLocation& stBlobLoc, BOOL bNativeFormat = TRUE);

////////////////////////////////////////////////////////////////////
//                                                                //
// Functions to work with assays and results of assays            //
//                                                                //
////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to import measurement set data into database 
// Input:
// hHandle - database handle 
// lAssayID = assay id, where data should be saved 
// pDatasource - pointer to a datasource data 
// pCallBack - progress call back class 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_ImportMeasurementSet(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_ImportMeasurementSet* pDatasource,  MDCS_ProgressCallback* pCallback);


//////////////////////////////////////////////////////////////////////////////////////////
//to import measurement set data into database 
// Input:
// hHandle - database handle 
// pDatasource - pointer to a datasource data 
// pCallBack - progress call back class 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_AppendMeasurementSet(HDBHANDLE hHandle, const MDCS_CL_ImportDS* pDatasource,  MDCS_ProgressCallback* pCallback);

/////////////////////////////////////////////////////////////////////
//to insert value of double type to the table that contains results of assay 
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   lAssayID		 -   ID of an assay that was run 
//    lMeasurementID - measurement of an a ssay
//    dValue         - value to insert

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_InsertDValue( HDBHANDLE hHandle,          // pointer to the connection object
                                                const MDCS_ST_ShapeInfo* stShapeInfo,
                                                LONGLONG lAssayID,                                 //assay ID 
                                                LONGLONG lMeasurementID,                           //measurement ID
                                                double   dValue                                    //value
                                                ); 


/////////////////////////////////////////////////////////////////////
//to insert value of double type to the table that contains results of assay 
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pszColumnName -  column name of a measurement
//    dValue         - value to insert

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_InsertNumericValue( HDBHANDLE hHandle,          // pointer to the connection object
                                                LPCSTR pszTableName,                         //table name 
                                                LPCSTR pszColumnName,                        //column name 
                                                const MDCS_ST_ShapeInfo* stShapeInfo,
                                                double   dValue                                    //value
                                                ); 

/////////////////////////////////////////////////////////////////////
//to insert value of string to the table that contains results of assay 
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   lAssayID		 -   ID of an assay that was run 
//    lMeasurementID - measurement of an a ssay
//    pszValue         - value to insert

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_InsertSValue( HDBHANDLE hHandle,          // pointer to the connection object
                                                const MDCS_ST_ShapeInfo* pstShapeInfo,
                                                LONGLONG lAssayID,                                 //assay ID 
                                                LONGLONG lMeasurementID,                           //measurement ID
                                                LPCSTR   pszValue                                    //value
                                                ); 


/////////////////////////////////////////////////////////////////////
//to insert value of string type to the table that contains results of assay 
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pszColumnName -  column name of a measurement
//    pszValue         - value to insert

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_InsertStringValue( HDBHANDLE hHandle,          // pointer to the connection object
                                                LPCSTR pszTableName,                         //table name 
                                                LPCSTR pszColumnName,                        //column name 
                                                const MDCS_ST_ShapeInfo* stShapeInfo,
                                                LPCSTR pszValue                                    //value
                                                ); 
                                                      


/////////////////////////////////////////////////////////////////////
//to insert or update shapes 
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pShapeLines    - pointer to array of structures that describe shape lines
//    nNumShapeLines - number of the shape lines in array
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_InsertShapeLines(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                const MDCS_ST_ShapeInfo* pstShapeInfo,
                                                const MDCS_ST_ShapeLine* pShapeLines, 
                                                UINT nNumShapeLines);

/////////////////////////////////////////////////////////////////////
//to update shape lines
//Input: 
//    hHandle  - database connection handle
//    lShapeID - shape ID to update
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pShapeLines    - pointer to array of structures that describe shape lines
//    nNumShapeLines - number of the shape lines in array
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateShapeLines(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                LONGLONG lShapeID, 
                                                const MDCS_ST_ShapeInfo* pstShapeInfo,
                                                const MDCS_ST_ShapeLine* pShapeLines, 
                                                UINT nNumShapeLines);

/////////////////////////////////////////////////////////////////////
//to get shape lines blob description
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pBlobDesc      - pointer to a structure that describes a blob of shape lines
//Output:
//    bRecordFound   - number of records found
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobDesc(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                const MDCS_ST_ShapeInfo* pstShapeInfo,
                                                MDCS_ST_ShapeLinesBlob *pBlobDesc,
                                                LONGLONG* plRecordsFound
                                                ); 

/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    lSiteID        - site ID where to get blobs from
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    COLOR
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE, COLOR
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobDescBySite(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                LONGLONG lSiteID,
                                                MDCS_GetDBResultsCCallback* pResultCallback); 


/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site and series
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    lSiteID        - site ID where to get blobs from
//    lSeriesID      - series ID
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    COLOR
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE, COLOR
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobDescBySiteAndSeries(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                LONGLONG lSiteID,
                                                LONGLONG lSeriesID,
                                                MDCS_GetDBResultsCCallback* pResultCallback); 

/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site, series and instance
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    lSiteID        - site ID where to get blobs from
//    lSeriesID      - series ID
//    lInstance      - instance ID
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    COLOR
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE, COLOR
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured

MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobDescBySiteSeriesAndInstance( HDBHANDLE hHandle, 
                                                                              LPCSTR pszTableName,                         //table name 
                                                                              LONGLONG lSiteID,
                                                                              LONGLONG lSeriesID,
                                                                              LONGLONG lInstanceID,
                                                                              MDCS_GetDBResultsCCallback* pResultCallback );

/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site and series
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    lPlateID       - plate ID 
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    COLOR
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE, COLOR
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobDescByPlate(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                LONGLONG lPlate,
                                                MDCS_GetDBResultsCCallback* pResultCallback); 


/////////////////////////////////////////////////////////////////////
//to get alll the shapes descriptions per assay
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszShapeName	- table name where shapes are stored
//    lPlateID       - plate ID 
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    COLOR
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLineBlobPerAssay(HDBHANDLE hHandle, 
                                                LPCSTR pszShapeName,                         //table name 
                                                MDCS_GetDBResultsCCallback* pResultCallback); 


/////////////////////////////////////////////////////////////////////
//to get shape lines of a shape
//Input: 
//    hHandle        - database connection handle
//    pstShapeInfo   - pointer to a structure that describes shape
//	   pszTableName	- table name where insert values
//    pBlobDesc      - pointer to a structure that describes a blob of shape lines
//    pShapeLines    - pointer to an array of the shape lines
//    lNumShapeLines - number of the shape lines in pShapeLines
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLines(HDBHANDLE hHandle, 
                                                LPCSTR pszTableName,                         //table name 
                                                const MDCS_ST_ShapeInfo* pstShapeInfo,
                                                MDCS_ST_ShapeLine *pShapeLines, LONGLONG lNumShapeLines);


/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site
//Input: 
//    hHandle        - database connection handle
//	   pszTableName	- table name where insert values
//    lSiteID        - site ID where to get blobs from
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLinesBySite(HDBHANDLE hHandle, 
                                 LPCSTR pszTableName,                         //table name 
                                 LONGLONG  lSiteID, 
                                 MDCS_GetBlobColumnResults * pResultCallback, 
                                 LONGLONG lMaxSize = -1);

/////////////////////////////////////////////////////////////////////
//to get shape lines blob description per site
//Input: 
//    hHandle        - database connection handle
//	   pszTableName	- table name where insert values
//    lSiteID        - site ID
//    lSeriesID      - Series ID  
//Output:
//    SITE_ID  - site id 
//    SERIES_ID 
//    INSTANCE
//    SHAPE_TYPE
//    LINES_TOTAL   - total lines count for the shapes per combination SITE_ID, SERIES_ID, INSTANCE, SHAPE_TYPE
//    RECORD_COUNT  - total records found for the shapes per combination  above
//    BLOB_SIZE     - data size to retireve for the shapes per combination  above
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetShapeLinesBySiteAndSeries(HDBHANDLE hHandle, 
                                 LPCSTR pszTableName,                         //table name 
                                 LONGLONG lSiteID, LONGLONG lSeriesID, 
                                 MDCS_GetBlobColumnResults * pResultCallback, 
                                 LONGLONG lMaxSize = -1);

/////////////////////////////////////////////////////////////////////
//function to get a mesurement description based on assay ID and measurement ID 
//Input: 
//    hHandle        - database connection handle
//    lAssayID - assay ID
//    lMeasurementID - assay ID
//    bInsert - if TRUE, create a new record if does not exists 
//Output: 
//    pAssMeas    - structure that contains results of the query 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementAttributes(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lMeasurementID, MDCS_ST_COLUMNPROP* pAssMeas, BOOL bInsert = FALSE);

/////////////////////////////////////////////////////////////////////
//function to get a mesurements description based on assay ID and measurement ID 
//Input: 
//    hHandle        - database connection handle
//    lAssayID - assay ID
//    lMeasurementID - assay ID
//Output: 
//    pResultCallback   - structure that contains results of the query 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI  MDCS_ASSAY_GetAssayMeasurementRecord(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lMeasurementID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to get deleted assay info using callback
//Input: 
//    hHandle        - database connection handle
//    lAssayID - assay ID
//    lMeasurementID - assay ID
//    bMarkPerm - flag to indicate to get unrestored assay
//    bIncludeSecurity - flag to indicate weather to include security when get assay info.
//Output: 
//    pResultCallback   - structure that contains results of the query 
//Return: FALSE - if error occured

//MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMarkedAssayAndTheirPlateInfo(HDBHANDLE hHandle,MDCS_GetDBResultsCCallback* pResultCallback, BOOL bMarkPerm = TRUE, BOOL bWithSecurity = FALSE);
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMarkedAssaysWithCallback(HDBHANDLE hHandle,MDCS_GetDBResultsCCallback* pResultCallback, BOOL bMarkPerm = TRUE, BOOL bWithSecurity = FALSE);
/////////////////////////////////////////////////////////////////////
//TODO :  to restore an assay from recycle bin
//Input: 
//    hHandle   - database connection handle
//    lAssayID  - id of an assay that needs to be restored
//    
//Return: FALSE - if error occured
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Restore(HDBHANDLE hHandle, LONGLONG lAssayID);
////////////////////////////////////////////////////////////
//to get assay measurement by plate ID and measurement ID
//if plMeasurementID not specified - then get all measurement for plate  
//Input:
//    hHandle        - database connection handle
//    lAssayID       - assay ID
//    plMeasurementID - measurement ID of global measurement
//return columns:
//    TABLE_ID - table name
//    COLUMN_NAME
//    ASSAY_ID
//    COLUMN_TYPE
//    COLUMN_NAME_EXT
MDCSUTILS BOOL WINAPI  MDCS_ASSAY_GetAssayMeasurementsByPlateAndMeasurement(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG* plMeasurementID,  MDCS_GetDBResultsCCallback* pResultCallback);


//////////////////////////////////////////////////////////////////////////
//to get a data type records by site ID
//Input:
//    hHandle        - database connection handle
//    lSiteID       - assay ID
//return columns:
//    TABLE_ID - table name
//    COLUMN_NAME
//    ASSAY_ID
//    COLUMN_TYPE
//    COLUMN_NAME_EXT
MDCSUTILS BOOL WINAPI  MDCS_ASSAY_GetMeasurementsBySiteID(HDBHANDLE hHandle, LONGLONG lSiteID,  MDCS_GetDBResultsCCallback* pResultCallback);



/////////////////////////////////////////////////////////////////////
//function to get a mesurement description based on assay ID and DB column name
//Input: 
//    hHandle        - database connection handle
//    lAssayID - assay ID
//    pszAttrDBColumnName  - name of the attribute column in DB
//    bInsert - if TRUE, create a new record if does not exists 
//Output: 
//    stAssayMeas    - structure that contains results of the query 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementInfoByAssayAndColumnName(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszAttrDBColumnName, MDCS_ST_COLUMNPROP& stAssayMeas);


/////////////////////////////////////////////////////////////////////
//function to get an measurement attribute description based on measurement and functions names 
//Input: 
//    hHandle        - database connection handle
//    pszFunctionName - function name 
//    pszParameterName  - pareameter name
//    eColType - data format 
//Output: 
//    pCallBack    - results that could be converted to MDCS_ST_ColumnProp structure 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementByFunctionAndParameterName(HDBHANDLE hHandle, LPCSTR pszFunctionName, LPCSTR pszParameterName, const MDCS_E_ColumnType& eColType, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to get a data type record by its ID
//Input: 
//    hHandle        - database connection handle
//    lRecordID      - record ID
//    pResultCallback - callback object
//Output: 
//    will return records with columns
//    ID  - measurement ID
//    FUNCTION_NAME - function name
//    PARAMETER_NAME - parameter name 
//    COLUMN_NAME_EXT  - display name of column 
//    COLUMN_NAME      - data type name as in DB
//    COLUMN_DESCRIPTION - data type description
//    COLUMN_TYPE - column type
//    TABLE_ID    - name of the table where can be found
//    ENTITY_ID   - assay ID 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementRecord(HDBHANDLE hHandle, LONGLONG lColumnID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function to create a new assay
//Input: 
//    hHandle        - database connection handle
//    pstAssayIn     - pointer to an assay structure that will be used to create new assay
//    lFolderID      - id of a folder where assay will be created,  if  0 - will create assay 
//                     in user default folder (not used anymore, left for backwasrd compatability)
//Output:
//       stAssayOut - created assay 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Create(HDBHANDLE hHandle, const MDCS_ST_Assay* pAssayIn, MDCS_ST_Assay* pAssayOut, LONGLONG lFolderID);

/////////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_CreateForPlate
//Description: to create a new assay, function will create assay table 
//Input: 
//    hHandle        - database connection handle
//    pstAssayIn     - pointer to an assay structure that will be used to create new assay
//    lPlateID      - id of a plate 
//Output:
//       stAssayOut - created assay 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateForPlate(HDBHANDLE hHandle, const MDCS_ST_Assay* pAssayIn, MDCS_ST_Assay* pAssayOut, LONGLONG lPlateID);

/////////////////////////////////////////////////////////////////////
//function to get assay sibling folders
//Input: 
//    hHandle           - database connection handle
//    lParentFolderID   - ID of parent to retrieve siblings of
//    pResultCallback   - data callback
//Output: result columns will be:  
//                FOLDER_NAME    - folder name
//                FOLDER_ID      - folder ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAssaySiblingFolders(HDBHANDLE hHandle, LONGLONG lParentFolderID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to create a new assay measurement 
//Input: 
//    hHandle        - database connection handle
//    pstMeasurementIn - measurement description
//Output:
//       pstMeasurementOut - measurement description
//comments: either szColumnNameFull or pair szFunctionName and szMeasName is required, column type is required 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateMeasurement(HDBHANDLE hHandle, const MDCS_ST_COLUMNPROP* pstMeasurementIn,  MDCS_ST_COLUMNPROP* pstMeasurementOut);

////////////////////////////////////////////////
//Function to add a new measurement to an assay
//Input: 
//       hHandle        - database connection handle
//       lAssayID       - assay ID where to add measurement
//       lMeasID        - measurement ID to add
//Output:
//       pCreatedMeasurementOut - object that contains created measurement description
//Return: FALSE - if dialog canceled

MDCSUTILS BOOL WINAPI MDCS_ASSAY_AddMeasurement(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lMeasID, MDCS_ST_COLUMNPROP* pCreatedMeasurementOut);

/////////////////////////////////////////////////////////////////////
//function to get a description of an assay measurement
//Input: 
//    hHandle        - database connection handle
//    lMeasuremntID  - measurement ID
//Output:
//       pstMeasurement - measurement description
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementByID(HDBHANDLE hHandle, LONGLONG lMeasuremntID,  MDCS_ST_COLUMNPROP* pstMeasurement);


/////////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetMeasurementByName
//Description: to get a description of an assay measurement
//Input: 
//    hHandle        - database connection handle
//    pszName        - measurement name
//    pszScopeName   - scope name of measurement  (default MDCS_cszMDCSCellMeasurementScope)
//Output:
//       pstMeasurement - measurement description
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementByName(HDBHANDLE hHandle, LPCSTR pszName,  MDCS_ST_COLUMNPROP* pstMeasurement, LPCSTR pszScopeName = MDCS_cszMDCSCellMeasurementScope);


/////////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetMeasurementByName
//Description: to get a description of an assay measurement
//Input: 
//    hHandle        - database connection handle
//    pszColumnDBName - measurement column name in DB
//    pszScopeName   - scope name of measurement  (default MDCS_cszMDCSCellMeasurementScope)
//Output:
//       stMeasurement - measurement description
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementByDBName(HDBHANDLE hHandle, LPCSTR pszColumnDBName,  MDCS_ST_COLUMNPROP& pstMeasurement, LPCSTR pszScopeName = MDCS_cszMDCSCellMeasurementScope);

/////////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetScopeAttributeByName
//Description: to get a description of a scope attribute using display name 
//Input: 
//    hHandle        - database connection handle
//    pszName        - attribute name
//    pszScopeName   - scope name (default is MDCS_cszMDCSCellMeasurementScope)
//
//Output:
//       pstMeasurement - measurement description
//Return: FALSE - if error occured
//Comments: Function only works with the scopes for MDCS_eDSFMeasurementSetParams defined for type
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetScopeAttributeByName(HDBHANDLE hHandle, LPCSTR pszName, MDCS_ST_ScopeAttribute& stAttr, LPCSTR pszScopeName = MDCS_cszMDCSCellMeasurementScope);


/////////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetScopeAttributeByID
//Description: to get a description of a scope attribute using display name 
//Input: 
//    hHandle        - database connection handle
//    pszColumnID    - attribute ID
//    pszScopeName   - scope name (default is MDCS_cszMDCSCellMeasurementScope)
//
//Output:
//       pstMeasurement - measurement description
//Return: FALSE - if error occured
//Comments: Function only works with the scopes for MDCS_eDSFMeasurementSetParams defined for type
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetScopeAttributeByID(HDBHANDLE hHandle, LPCSTR pszColumnID, MDCS_ST_ScopeAttribute& stAttr, LPCSTR pszScopeName = MDCS_cszMDCSCellMeasurementScope);




/////////////////////////////////////////////////////////////////////
//function to delete an assay
//Input: 
//    hHandle        - database connection handle
//    lAssayID  - id of an assay that needs to be deleted
//    bCanRestore - flag if TRUE, indicates that assay can be restored from Recycle bin
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Delete(HDBHANDLE hHandle, LONGLONG lAssayID, BOOL bCanRestore = FALSE );

/////////////////////////////////////////////////////////////////////
//function to delete all assays for a plate
//Input: 
//    hHandle        - database connection handle
//    lPlateID  - id of a plate
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteAllForPlate(HDBHANDLE hHandle, LONGLONG lPlateID);

/////////////////////////////////////////////////////////////////////
//function to delete assay results for a plate
//Input: 
//    hHandle        - database connection handle
//    lPlateID  - id of a plate
//    lAssayID   - assay id 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteDataForPlate(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lPlateID);


/////////////////////////////////////////////////////////////////////
//function to delete assay folder
//Input: 
//    hHandle        - database connection handle
//    lFolderID  - id of a folder in measurement set tree
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteFolder(HDBHANDLE hHandle, LONGLONG lFolderID);

/////////////////////////////////////////////////////////////////////
//function to create assay outlines table
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay id 
//    nSize           
//Output:    
//    pszTableName   - name of a table that contains outlines 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateOutlinesTable(HDBHANDLE hHandle, LONGLONG lAssayID, LPSTR pszTableName, int nSize, INT_PTR* pnSizeOut);


//////////////////////////////////////////////////////////////////////////////////////////
////will call a dialog to manage security access to the assay folders
//Input: 
//       hHandle        - database connection handle
//       lFolderID       - folder ID
//       pszTitle - dialog title
//       hWnd - application window 
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_ASSAY_ManageFolderSecurity(HDBHANDLE hHandle, LONGLONG lFolderID, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL);


//////////////////////////////////////////////////////////////////////////////////////////
////to check if user can modify folder
//Input: 
//       hHandle        - database connection handle
//       lFolderID       - folder ID
//Output:
//       bCanModify - if TRUE - user can modify folder
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CanModifyFolder(HDBHANDLE hHandle, LONGLONG lFolderID, BOOL& bCanModify);

//////////////////////////////////////////////////////////////////////////////////////////
// create a new assay folder in the database
//Input: 
//       hHandle        - database connection handle
//   
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateFolder(HDBHANDLE hHandle, const MDCS_ST_FolderInfo& stInfoIn, MDCS_ST_FolderInfo & stInfoOut); 

//////////////////////////////////////////////////////////////////////////////////////////
// modify a assay folder in the database
//Input: 
//       hHandle        - database connection handle
//   
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_ModifyFolder(HDBHANDLE hHandle, const MDCS_ST_FolderInfo& stInfoIn ); 

//////////////////////////////////////////////////////////////////////////////////////////
// create a new assay folder in the database
//Input: 
//       hHandle        - database connection handle
//Output: 
//       lSubfolderID  - subfolder ID, if 0  subfolder does not exists, otherwise - folder ID
//Return: FALSE - if folder does not exist
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DoesSubFolderExist(HDBHANDLE hHandle, LONGLONG lFolderID, LPCSTR pzName, LONGLONG &lSubfolderID );

//////////////////////////////////////////////////////////////
//Description: to get assays with basic description in folder
//Input: 
//       hHandle     - database connection handle
//       lFolderID   - assay folder ID
//       
//Output:
//       pResultCallback - call back that contains results of a query   
//       fields that always be present
//       ASSAY_ID, ASSAY_NAME, SETTINGS_NAME, TIME_CREATED (as time_t value), TABLE_ID(table name where results are stored), 
//       SHAPE_TABLE_NAME  (name of the table where shape results are stored)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAllInFolder(HDBHANDLE hHandle, LONGLONG lFolderID, MDCS_GetDBResultsCCallback* pResultCallback);

//////////////////////////////////////////////////////////////
//Description: to get the path of a folder
//Input: 
//       hHandle     - database connection handle
//       lFolderID   - assay folder ID
//       
//Output:
//          AxString& strPath - will contain the path
//         
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetFolderPath(HDBHANDLE hHandle, LONGLONG lFolderID, AxString& strPath );

//////////////////////////////////////////////////////////////
//Description: to reindex assay measurements
//Input: 
//       hHandle     - database connection handle
//       lAssayID   -  assay folder ID
//       
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Reindex(HDBHANDLE hHandle, LONGLONG lAssayID);


//////////////////////////////////////////////////////////////
//Description: to reindex assay cell shapes 
//Input: 
//       hHandle     - database connection handle
//       lAssayID   -  assay folder ID
//       
MDCSUTILS BOOL WINAPI MDCS_ASSAY_ReindexShapes(HDBHANDLE hHandle, LONGLONG lAssayID);
//funtion: to optimize all assay tables
//Input: 
//    hHandle        - database connection handle
//    pCallBack      - pointer to a callback class
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_OptimizeAll(HDBHANDLE hHandle,   MDCS_ProgressCallback * pCallBack);

////////////////////////////////////////////////
//Function to copy assay 
//Input: 
//       hHandle         - database connection handle
//       lAssayIDSource  - source assay
//       lAssayIDDestination  - destination assay
//Return: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Copy(HDBHANDLE hHandle, LONGLONG lAssayIDSource, LONGLONG lAssayIDDestination, MDCS_ProgressCallback * pCallBack);

////////////////////////////////////////////////
//Function to merge assay 
//Input: 
//       hHandle         - database connection handle
//       lAssayIDSource  - source assay
//       lAssayIDDestination  - destination assay
//       bCopyObjects  - option indicates that attachments shuld be copied
//Return: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_ASSAY_Merge(HDBHANDLE hHandle, LONGLONG lAssayIDSource, LONGLONG lAssayIDDestination, BOOL bCopyObjects, MDCS_ProgressCallback * pCallBack);

/////////////////////////////////////////////////////////////////////
//function to count site appearence in assay table
//Input: 
//    hHandle        - database connection handle
//    lSiteID       - site id to look for
//    pszTableName   - name of a table that contains outlines 
//Output:    
//    lSiteCount - number of times site appeares in assay table
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetSiteCount(HDBHANDLE hHandle, LPCSTR pszTableName, LONGLONG lSiteID, LONGLONG& lSiteCount);

//////////////////////////////////////////////////////////////////////////////////////////
// get information about the image
//Input: 
//       hHandle        - database connection handle
//       lImageID       - ID of image to retrieve info on.
//   
//Output:
//       
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetSiteInfoImageByID(HDBHANDLE hHandle, LONGLONG lImageID, MDCS_ST_SiteImageInfo& stInfoOut);

//////////////////////////////////////////////////////////////////////////////////////////
// get information about the image
//Input: 
//       hHandle        - database connection handle
//       lImageID       - ID of image to retrieve info on.
//   
//Output:
//       
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetSiteInfoImageBySiteAndSeriesID(HDBHANDLE hHandle, LONGLONG lSiteID, LONGLONG lSeriesID, MDCS_ST_SiteImageInfo& stInfoOut);


//////////////////////////////////////////////////////////////////////////////////////////
//Purpose: to remove shape data for a measurement set
//Input:
//      lAssayID - assay id
//      hHandle  - db handle
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_RemoveShapeData(HDBHANDLE hHandle,  LONGLONG lAssayID);

//==============================================================================================
// FUNCTION: MDCS_GetDataTypesNotInAssaysByDBName
// PURPOSE:  To get all datatype that not belong to assay that have same DBcolname and everagetype, column type
// INPUT:
//    hHandle       - database connection handle
//    pszDBColumn   - DBColumn name of measurement that should be modify( will not modify default datatype)
//    eColType      - format type of column
//    eAvgType      - average type of column
//    arrAssayIDs   - assay ids 
//    nSize         - size of assay id
// OUTPUT: 
//    pResultCallback - result callback
// Return columns:
//    COLUMN_NAME, COLUMN_NAME_EXT, COLUMN_TYPE, AVG_TYPE, COLUMN_ID...
//
MDCSUTILS BOOL WINAPI MDCS_GetDataTypesNotInAssaysByDBName(HDBHANDLE hHandle, LPCSTR pszDBColName, LONGLONG* arrMicIDs,INT_PTR nSize,  const MDCS_E_ColumnType& eColType, const MDCS_E_AverageType& eAvgType, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to count site appearence in a measurement set 
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay ID where to count
//    lSiteID        - site id to look for
//Output:    
//    lSiteCount - number of times site appeares in assay table
MDCSUTILS BOOL WINAPI MDCS_ASSAY_MeasurementGetSiteCount(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lSiteID, LONGLONG& lSiteCount);


/////////////////////////////////////////////////////////////////////
//function to delete a measurement
//Input: 
//    hHandle           - database connection handle
//    lMeasurementID    - measurement that should be deleted

MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteMeasurement(HDBHANDLE hHandle, LONGLONG lMeasurementID);


/////////////////////////////////////////////////////////////////////
//function to delete a measurement from all assay that use it but not the default( default is assay_id = 0)
//Input: 
//    hHandle           - database connection handle
//    pszDBColumnName   - DBColumn name of measurement that should be deleted( will not delete default datatype)
//    arrAssayIDs       - array of assayIds
//    nSize             - size of array of assay ids
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteMeasurementInAssays(HDBHANDLE hHandle, LPCSTR pszDBColumnName, LONGLONG* arrAssayIDs, INT_PTR nSize );

/////////////////////////////////////////////////////////////////////
//function MDCS_ASSAY_UpdateDataType
// Purpose: to update a measurement property 
//Input: 
//    hHandle          - database connection handle
//    lMeasurementID   - measurement id that should be modify
//    stDataTypeNew    - measurement DB column used to replace the original.
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateDataType(HDBHANDLE hHandle, LONGLONG lMeasurementID, const MDCS_ST_COLUMNPROP& stDataTypeNew);



/////////////////////////////////////////////////////////////////////
//MDCS_ASSAY_UpdateDataTypeByAssay
//function to modify a measurement for an assay based on DBcolumn name and assay id, but not the measurement have assay id = 0
//Input: 
//    hHandle           - database connection handle
//    stDataTypeOrig    - structure of a measurement that should be modify( will not modify default datatype)
//    stDataTypeNew     - structure of a measurement used to replace the orig
//    lAssayID          - assay id 
//RETURN :
//    TRUE              - if successful
//    FALSE             - fail
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateDataTypeByAssayIDAndDBName(HDBHANDLE hHandle, LPCSTR stOrigDBCol, MDCS_ST_COLUMNPROP& stDataTypeNew, LONGLONG lAssayID);

/////////////////////////////////////////////////////////////////////
//function to count site appearence in a asssay cell outlines
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay ID where to count
//    lSiteID        - site id to look for
//Output:    
//    lSiteCount - number of times site appeares in assay table
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CellOutlinesGetSiteCount(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lSiteID, LONGLONG& lSiteCount);

/////////////////////////////////////////////////////////////////////
//function to count site appearence in a asssay cell outlines
//Input: 
//    hHandle        - database connection handle
//    lFolderID      - destination folder
//    pszOrigName    - to check availability or create a new assay name in destination folder 
//    strNewName    - to check availability or create a new assay name in destination folder 
//    bCreateAsCopy  - indicates that name should be created using prefix "Copy of <orig name>" if name exists 
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateNewName(HDBHANDLE hHandle, LONGLONG lFolderID, LPCSTR pszOrigName, AxString& strNewName, BOOL bCreateAsCopy);
   
/////////////////////////////////////////////////////////////////////
//function 
//to create a new assay run record
//Input: 
//    hHandle        - database connection handle
//    stAssayRun     - assay run description
//Output: 
//    plAssayRunID -  genereated record ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateRun(HDBHANDLE hHandle, const MDCS_ST_AssayRun& stAssayRun, LONGLONG* plAssayRunID);


/////////////////////////////////////////////////////////////////////
//function 
//to get ID of  the latest run on an assay 
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay ID
//Output: 
//    plRunID     - assay run ID 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetLatestAssayRunID(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG* plRunID);
  

/////////////////////////////////////////////////////////////////////
//function get assay data 
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay ID where to count
//Output:    
//    pstAssay  - assay structure
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetByID(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_ST_Assay* pstAssay );

/////////////////////////////////////////////////////////////////////
//function 
//to create a new asay profile record
//Input: 
//    hHandle         - database connection handle
//    stAssayProfile  - assay profile description
//Output: 
//    plAssayProfileID -  genereated record ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateProfile(HDBHANDLE hHandle, const MDCS_ST_AssayProfile& stAssayProfile, LONGLONG* lAssayProfileID);
   
   
/////////////////////////////////////////////////////////////////////
//function 
//to associate assay with a plate
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay ID
//    lPlateID       - plate ID
//Output: 
//    bRecordExisted -  if TRUE - indicates that record already existed in database
//    plPlateAssayId - assay plate ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_AssociateWithPlate(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lPlateID, BOOL* bRecordExisted, LONGLONG* plPlateAssayId = NULL);

/////////////////////////////////////////////////
//to get the spot id from instance site and series
// Input: 
//       hHandle        - database connection handle
//       lInstance      - instance id
//       lSite          - site id
//       lSeries        - series id
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetSpotID( HDBHANDLE hHandle, LONGLONG lSpot, LONGLONG lInstance, LONGLONG lSeries, LONGLONG lSite, LONGLONG& lSpotID );


/////////////////////////////////////////////////////////////////////
//function to get all assay that are associated with a plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate 
//    pResultCallback   - callback
//Output:
//Callback will return columns:
//       ASSAY_ID          - assay ID
//       ASSAY_NAME        -assay name 
//       ASSAY_DESC        - assay description
//       CREATOR_NAME      - anme of a person who created assay 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAllForPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);

//function to get all available profiles
//Input: 
//    hHandle        - database connection handle
//    pResultCallback - callback class 
//will return columns:
//       ID - unique ID
//       NAME - record name
//       DESCRIPTION - record description
//       SETTINGS_NAME  - name ofd the settings
//       OPERATOR    - name of a person who created settings
//       DATA_STORAGE_TYPE - type of the data storage
//       SETTINGS_STORAGE_TYPE   - type of a storage where setting blob is stored (DB or File Server)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetProfiles(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback * pResultCallback);

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//function to get a profile record
//Input: 
//    hHandle        - database connection handle
//    lProfileID    - profile ID
//    pResultCallback - callback class 

//will return columns:
//       ID - unique ID
//       NAME - record name
//       DESCRIPTION - record description
//       SETTINGS_NAME  - name ofd the settings
//       OPERATOR    - name of a person who created settings
//       DATA_STORAGE_TYPE - type of the data storage
//       SETTINGS_STORAGE_TYPE   - type of a storage where setting blob is stored (DB or File Server)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetProfile(HDBHANDLE hHandle, LONGLONG lProfileID, MDCS_GetDBResultsCCallback * pResultCallback);

//function to get a profile record
//Input: 
//    hHandle        - database connection handle
//    lProfileID    - profile ID
//will return columns:
//       stProfile - structure that containsprofile info
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetProfileInfo(HDBHANDLE hHandle, LONGLONG lProfileID, MDCS_ST_AssayProfile& stProfile);

//function to update profile record
//Input: 
//    hHandle        - database connection handle
//    stProfileToUpdate - profile to update
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateProfile(HDBHANDLE hHandle, const MDCS_ST_AssayProfile& stProfileToUpdate);

//////////////////////////////////////
//to delete assay profile
//Input: 
//    hHandle        - database connection handle
//    lProfileID     - IFD of a profile that needs to be deleted
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteProfile(HDBHANDLE hHandle, LONGLONG lProfileID);


//function to get an assay record
//Input: 
//    hHandle        - database connection handle
//    lProfileID    - profile ID
//    pResultCallback - callback class 
//will return columns:
//       ID - unique ID
//       NAME - record name
//       DESCRIPTION - record description
//       SETTINGS_NAME  - name ofd the settings
//       DATA_STORAGE_TYPE - type of the data storage
//       SETTINGS_STORAGE_TYPE   - type of a storage where setting blob is stored (DB or File Server)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetRecord(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_GetDBResultsCCallback * pResultCallback);


//function to get an assay record using RUN ID
//Input: 
//    hHandle        - database connection handle
//    lRunID      - run ID
//    pResultCallback - callback class 
//will return columns:
//       ID - unique ID
//       NAME - record name
//       DESCRIPTION - record description
//       SETTINGS_NAME  - name ofd the settings
//       DATA_STORAGE_TYPE - type of the data storage
//       SETTINGS_STORAGE_TYPE   - type of a storage where setting blob is stored (DB or File Server)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAssayByRunID(HDBHANDLE hHandle, LONGLONG lRunID, MDCS_GetDBResultsCCallback * pResultCallback);



//////////////////////////////////////////////////////////////////////////////////////////
////to check if assay is used in datasets
//Input: 
//       hHandle        - database connection handle
//       lAssayID       - assay ID
//Output:
//       lDatasets      - number of datasets where assay is used
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UsedInDatasets(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG& lDatasets);


//////////////////////////////////////////////////////////////////////////////////////////
////to check if current user can modify an assay 
//Input: 
//       hHandle        - database connection handle
//       lAssayID       - assay ID
//Output:
//       bCanModify - if TRUE - user can modify assay
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_ASSAY_HavePermissionsToModify(HDBHANDLE hHandle, LONGLONG lAssayID, BOOL& bCanModify);


//////////////////////////////////////////////////////////////////////////////////////////
////to check if current user can modify an assay 
//Input: 
//       hHandle        - database connection handle
//       lAssayID       - assay ID
//Output:
//       bCanModify - if TRUE - user can modify assay
//Return: FALSE - if error occur
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CanModifyAssay(HDBHANDLE hHandle, LONGLONG lAssayID, BOOL& bCanModify);

/////////////////////////////////////////////////////////////////////
//function 
//to get all records from image_source table
//Input: 
//    hHandle        - database connection handle
//    pResultCallback - callback object
//Output: 
//    will return records with columns
//    ID  - image source ID
//    ACQ_INSTANCE_ID - acuisition instance ID
//    ASSAY_INSTANCE_ID - assay ID
//    SOURCE_DESCRIPTION  - source description
//    SOURCE_ILLUMINATION - source illumination
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetImageSourceRecords(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);


////////////////////////////////////////////////////////////////////////////////////
//function: GetStatisticalValuesForPlateAndAssay
//Description: To get ststistical values for selected plate and assay
//Input: pSession - session object
//    hHandle        - database connection handle
//    pResultCallback - callback object
//    lPlateID - ID of a plate
//    lAssayID  ID of an assay where to look
//    lMeasurementID - ID of a measurement for data column
//    eStatistic     - type of statistic to apply to data
//    bGroupSites    - flag, indicated that data should be grouped by sites
//    bAllSites      - flag, indicates that data will be getting for all series for a site
//    nSiteX         - position of a site
//    nSiteY         - position of a site
//    pszSeriesInfoIndex   - series info index
//    pszFilter      - filter that should be applied to data
//Output:
//    will return records with columns
//    Value  - as statistical values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetStatisticalValuesForPlateAndAssay(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG lAssayID, LONGLONG lMeasurementID, const MDCS_E_Statistic& eStatistic, BOOL bGroupSites, BOOL bAllSites,
                                      int nSiteX, int nSiteY, LPCSTR pszSeriesInfoIndex, LPCSTR pszFilter, MDCS_GetDBResultsCCallback * pResultCallback);

////////////////////////////////////////////////////////////////////////////////////
//function: GetStatisticalValuesForPlateAndMeasurement
//Description: To get statistical values for selected plate and measurement 
//Input: pSession - session object
//    hHandle        - database connection handle
//    pResultCallback - callback object
//    lPlateID - ID of a plate
//    lMeasurementID - ID of a measurement for data column
//    eStatistic     - type of statistic to apply to data
//    bGroupSites    - flag, indicated that data should be grouped by sites
//    bAllSites      - flag, indicates that data will be getting for all series for a site
//    nSiteX         - position of a site
//    nSiteY         - position of a site
//    pszSeriesInfoIndex   - series info index
//    pszFilter      - filter that should be applied to data
//Output:
//    will return records with columns
//    Value  - as statistical values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetStatisticalValuesForPlateAndMeasurement(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG lMeasurementID, const MDCS_E_Statistic& eStatistic, BOOL bGroupSites, BOOL bAllSites,
                                      int nSiteX, int nSiteY, LPCSTR pszSeriesInfoIndex, LPCSTR pszFilter, MDCS_GetDBResultsCCallback * pResultCallback);


////////////////////////////////////////////////////////////////////////////////////
//function: 
//Description: To get values for selected plate and assay
//Input: pSession - session object
//    hHandle        - database connection handle
//    pResultCallback - callback object
//    lPlateID - ID of a plate
//    lAssayID  ID of an assay where to look
//    lMeasurementID - ID of a measurement for data column
//    bSingleSites      - flag, indicates that data will be getting for single sites
//    nSiteX         - position of a site
//    nSiteY         - position of a site
//    pszFilter      - filter that should be applied to data
//Output:
//    will return records with columns
//    Value  - as statistical values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetValuesForPlateAndAssay(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG lAssayID, LONGLONG lMeasurementID,  BOOL bSingleSite,
                                      int nSiteX, int nSiteY, LPCSTR pszFilter, MDCS_GetDBResultsCCallback * pResultCallback);

////////////////////////////////////////////////////////////////////////////////////
//function: 
//Description: To get values for selected plate and measurement
//Input: pSession - session object
//    hHandle        - database connection handle
//    pResultCallback - callback object
//    lPlateID - ID of a plate
//    lMeasurementID - ID of a measurement for data column
//    bSingleSites      - flag, indicates that data will be getting for single sites
//    nSiteX         - position of a site
//    nSiteY         - position of a site
//    pszFilter      - filter that should be applied to data
//Output:
//    will return records with columns
//    Value  - as statistical values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetValuesForPlate(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG lMeasurementID,  BOOL bSingleSite,
                                      int nSiteX, int nSiteY, LPCSTR pszFilter, MDCS_GetDBResultsCCallback * pResultCallback);


////////////////////////////////////////////////////////////////////////////////////
//function: 
//Description: To get all values for selected site 
//Input: pSession - session object
//    hHandle        - database connection handle
//    pResultCallback - callback object
//    lAssayID - ID of an assay
//    lSiteID - ID of a site in assay
//    bNumeric - defined type of the measurements to get
//Output:
//    will return records with columns
//    Value  - as statistical values
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAllSiteMeasurements(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lSiteID, BOOL bNumeric, MDCS_GetDBResultsCCallback * pResultCallback);

//////////////////////////////////////////////////////////////////////////
//to get data types records by plate and assay
//return columns:
//    TABLE_ID - table name
//    COLUMN_NAME
//    ASSAY_ID
//    COLUMN_TYPE
//    COLUMN_NAME_EXT
//    T as a column type S for string, N - numeric
//    FUNCTION_NAME,
//    PARAMETER_NAME
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetMeasurementInfoByAssayAndPlate(HDBHANDLE hHandle, LONGLONG lAssayID, LONGLONG lPlateID, MDCS_GetDBResultsCCallback* pResultCallback );

////////////////////////////////////////////////////////////////////////////////////
//function: 
//Description: To get all values for selected site 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate
//    pszAssayName  -  assay name 
//    pszSettingsName -  settings name 
//    lSiteID - ID of a plate
//    bNumeric - defined type of the measurements to get
//Output:
//    stAssayOut - structure that contains assay info
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAssayInfoByNamePlateAndSettings(HDBHANDLE hHandle, LONGLONG lPlateID, LPCSTR pszAssayName, LPCSTR pszSettingsName, MDCS_ST_Assay& stAssayOut);


////////////////////////////////////////////////////////////////////////////////////
//function: 
//description: to get assay IDs that are available for a plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - plate ID
// returns ID column
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAssayIDsOfPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);

/////////////////////////////////////////////////////////////////
//Function: GetAssaySettingsOfPlate
//Description:  To get unique assay-settings of the plate
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - plate ID
//returns recordset with fields:  
///returns columns:
// ASSAY_ID 
// ASSAY_NAME
//SETTINGS_NAME
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAssaySettingsOfPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);




/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_CalculateStatisticResults
//Description:  To get statistic results on array of assay ids
//Input: 
//    hHandle        - database connection handle
//    larrAssayIDs   - array of assay IDs
//    eApplyStatistic - statistic that will be applied to columns in arrStatisticColumns
//    arrStatisticColumns - array of columns that will be used to calculate statistic
//    axarrGroupBy   - array of group by columns
//    axarrOrderBy   - array of order by columns
//    axarrFilters    - array of filters    
//    bGroupByAssay  - if TRUE - identifier of assay will be added
//returns recordset with fields:  
///returns columns:
// statistic data for  arrStatisticColumns columns as STAT_<column name>
// columns specified in axarrGroupBy 
// axarrOrderBy -  columns in axarrOrderBy  should match columns specified  in axarrGroupBy  
MDCSUTILS  BOOL WINAPI MDCS_ASSAY_CalculateStatisticResults(HDBHANDLE hHandle, const LONGLONG* plarrAssayIDs, int nNumElementArray, 
                       const AxStringArray& axarrFilters, 
                       MDCS_E_Statistic* arrApplyStatistic, int nStatCount,  
                       const MDCS_ST_ScopeAttribute* arrStatisticColumns, int nStatColumnCount, 
                       const MDCS_ST_ScopeAttribute* axarrGroupBy, int nGroupByCount, 
                       const MDCS_ST_ScopeAttribute* axarrOrderBy, int nOrderByCount, 
                       MDCS_GetDBResultsCCallback *pResultCallback, BOOL bGroupByAssay = FALSE
                       //, BOOL bImageData = FALSE
                       );


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_CalculateStatisticEx
//Description:  To get statistic results on array of assay ids
//Input: 
//    hHandle        - database connection handle
//    larrAssayIDs   - array of assay IDs
//    eApplyStatistic - statistic that will be applied to columns in arrStatisticColumns
//    arrStatisticColumns - array of columns that will be used to calculate statistic
//    axarrGroupBy   - array of group by columns
//    axarrOrderBy   - array of order by columns
//    axarrFilters    - array of filters    
//    bGroupByAssay  - if TRUE - identifier of assay will be added
//    eInnerStatistic  - statistic operation that will aplied to internal query
//    axarrInnerGroupBy -  array of group by columns for insternal query
//returns recordset with fields:  
///returns columns:
// statistic data for  arrStatisticColumns columns as STAT_<column name>
// columns specified in axarrGroupBy 
// axarrOrderBy -  columns in axarrOrderBy  should match columns specified  in axarrGroupBy  
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CalculateStatisticEx(HDBHANDLE hHandle, const LONGLONG* plarrAssayIDs, int nNumElementArray, const AxStringArray& axarrFilters, 
                                            const MDCS_E_Statistic* arrApplyStatistic, int nStatCount,  
                                            const MDCS_ST_ScopeAttribute* arrStatisticColumns, int nStatColumns,  
                                            const MDCS_ST_ScopeAttribute* axarrGroupBy, int nGroupByColumns,  
                                            const MDCS_ST_ScopeAttribute* axarrOrderBy,  int nOrderByColumns,  
                                            const MDCS_ST_ScopeAttribute* axarrInnerGroupBy,  int nInnerGroupBy, 
                                            const MDCS_E_Statistic* arrInnerStatistic, int nInnerStatCount, 
                                            MDCS_GetDBResultsCCallback *pResultCallback, 
                                            BOOL bGroupByAssay = FALSE 
                                            //, BOOL bImageData = FALSE
                                            );

/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetZPrime
//Description:  To calculate Z' on assay and measurement type
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - target assay 
//    pszFilter      - filter 
//    pszMeasurementType - measurement type to use in calcualtion
//    bImageData     - flag indicates that measurement is image measurement otherwise - cell data
//returns recordset with fields:  
///returns columns:
//    Z_PRIME - calculated Z'
//    PLATE_ID - plate ID 
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetZPrime(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszFilter, LPCSTR pszMeasurementType, MDCS_GetDBResultsCCallback *pResultCallback/*, BOOL bImageData = FALSE*/); 


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetZPrimeScopeAttribute
//Description:  To calculate Z' on assay and scope attribute
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - target assay 
//    pszFilter      - filter 
//    stMeasurement -  measurement to use in calcualtion
//    bImageData     - flag indicates that measurement is image measurement 
//returns recordset with fields:  
///returns columns:
//    Z_PRIME - calculated Z'
//    PLATE_ID - plate ID 
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetZPrimeScopeAttribute(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszFilter, MDCS_ST_ScopeAttribute stMeasurement, MDCS_GetDBResultsCCallback *pResultCallback/*, BOOL bImageData = FALSE*/) ;


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetUniqueMeasurementValues
//Description:  to get unique values of measurement type for array of assays
//Input: 
//    hHandle        - database connection handle
//    larrAssayIDs  - array of assays 
//    sarrFilters    - array of assay fileters
//    stMeasurement -  measurement to use in calcualtion
//returns recordset with fields:  
///returns columns:
//    first column contains results, name is equal DNBColumn name of measurement
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetUniqueMeasurementValues(HDBHANDLE hHandle,  LONGLONG* larrAssayIDs, const AxStringArray& sarrFilters, const MDCS_ST_ScopeAttribute& stMeasurement, MDCS_GetDBResultsCCallback *pResultCallback);


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_FindMeasurementValues
//Description:  finds values from provided array in measurement set 
//Input: 
//    hHandle        - database connection handle
//    lAssayIDs      - measurement set where to search
//    pszFilter      - measurement filter
//    stMeasurement -  measurement column to search on 
//    parrValues      - array of values to be searched
//    nArraySize      - number of elements in array
//    parrResultsColumns - array of result columns
//returns recordset with fields:  
///returns columns:
//    first column contains results for the columns from parrResultsColumns
MDCSUTILS BOOL WINAPI MDCS_ASSAY_FindMeasurementValues(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszFilter, const MDCS_ST_ScopeAttribute* pstMeasurement, const AxStringArray& arrValues, MDCS_ST_ScopeAttribute *paarResultsColumns, int nArrSize, MDCS_GetDBResultsCCallback *pResultCallback);


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_UpdateMeasurementData
//Description:  to update measurement data based on transformation criteria
//Input: 
//    hHandle        - database connection handle
//    lAssayIDs      - measurement set ID
//    stColumnToUpdate  - column to update
//    pszTransformCrit - transformation criteria (i.e. ((MDCS15 - 15)  * 10))  measurement column to search on 
//    pszWhereCrit     - filtering criteria (i.e. MDCS15 <> 0)
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateMeasurementData(HDBHANDLE hHandle, LONGLONG lAssayID, const MDCS_ST_Attribute& stColumnToUpdate, LPCSTR pszTransformCrit, LPCSTR pszWhereCrit = NULL);


/////////////////////////////////////////**************************/VY ADDED To work with MSet annotaiton*****************
//Function: MDCS_ASSAY_GetAllMSetUniqueAnnotation
//Description:  to update measurement data based on transformation criteria
//Input: 
//    hHandle        - database connection handle
//    pResultCallback     - result callback class 
//Return Columns:
//    COLUMN_ID - Database column name 
//    COLUMN_NAME - Display name
//    COLUMN_TYPE - column datatype

MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAllMSetUniqueAnnotation(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to create a Assay attribute
//Input: 
//    hHandle        - database connection handle
//    stAttributeIn  - attribute description
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_CreateAttribute(HDBHANDLE hHandle, const MDCS_ST_Attribute& stAttributeIn, MDCS_ST_Attribute& stAttributeOut);

/////////////////////////////////////////////////////////////////////
//function to get attribute info
//Input: 
//    hHandle        - database connection handle
//    pszDisplayName - display name of attribute
//Output:
//    stAttributeOut - attribute created
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAttributeInfoByDisplayName(HDBHANDLE hHandle, LPCSTR pszDisplayName, MDCS_ST_Attribute& stAttributeOut);

/////////////////////////////////////////////////////////////////////
//function to get attribute info
//Input: 
//    hHandle        - database connection handle
//    pszDBName      - internal name of attribute
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAttributeInfoByDBName(HDBHANDLE hHandle, LPCSTR pszDBName, MDCS_ST_Attribute& stAttributeOut);

/////////////////////////////////////////////////////////////////////
//function to get assay attribute value by DB column name
//Input: 
//    hHandle        - database connection handle
//    pszDBName      - internal name of attribute
//    lAssayID       - assay id
//Output:
//    strValue    - attribute value

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAttributeValueByDBName(HDBHANDLE hHandle, LPCSTR pszDBName, LONGLONG lAssayID, AxString& strValue);

/////////////////////////////////////////////////////////////////////
//function to get assay attribute value by Display name
//Input: 
//    hHandle        - database connection handle
//    pszDisplayName - internal name of attribute
//    lAssayID       - assay id
//Output:
//    strValue -      attribute value
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetAttributeValueByDisplayName(HDBHANDLE hHandle, LPCSTR pszDisplayName, LONGLONG lAssayID, AxString& strValue);

/////////////////////////////////////////////////////////////////////
//function to assign Assay attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    pszValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_AssignAttributeValueString(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszDBName, LPCSTR pszValue);

/////////////////////////////////////////////////////////////////////
//function to assign assay attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    plValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_AssignAttributeValueLong(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszDBName, LONGLONG* plValue);

/////////////////////////////////////////////////////////////////////
//function to assign assay attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    pfValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_AssignAttributeValueFloat(HDBHANDLE hHandle, LONGLONG lAssayID, LPCSTR pszDBName, float* pfValue);

/////////////////////////////////////////////////////////////////////
//function to rename Assay attribute 
//Input: 
//    hHandle        - database connection handle
//    stAttrribute  - attribute to modify 
//    pszDBName      - pszNewName - new name of attribute 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAY_RenameAttribute(HDBHANDLE hHandle, const MDCS_ST_Attribute& stAttrribute, LPCSTR pszNewName);

/////////////////////////////////////////////////////////////////////
//function to delete a Assay attribute
//Input: 
//    hHandle    - database connection handle
//    pszDBname  - DB Name of attribute to delete
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_DeleteAttribute(HDBHANDLE hHandle, LPCSTR pszDBName);
//MDCS_ASSAY_GetHeaderAndFileInfo
//to get header info and file import location of a measuremetn set
//Input:
//      lAssayID - assay id
//      hHandle  - db handle
//      
//Return columns:
//      FILE_PATH - file path
//      FILE_COMPUTER_NAME - computer name where the file imported from
//      FILE_NAME - file name 
//      HEADER_INFO  - info of the header file
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetHeaderAndFileInfo(HDBHANDLE hHandle , LONGLONG lAssayID, MDCS_GetDBResultsCCallback* pCallback );

//MDCS_ASSAY_UpdateMeasurementSetDescAndName
//Purpose: to update measurement set des and name 
//Input:
//      lAssayID - assay id
//      hHandle  - db handle
//      psz      - New Name
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateMeasurementSetName(HDBHANDLE hHandle , LONGLONG lAssayID,LPCSTR pszNewName );

//MDCS_ASSAY_UpdateMeasurementSetDescAndName
//Purpose: to update measurement set des and name 
//Input:
//      lAssayID - assay id
//      hHandle  - db handle
//      psz      - New Desc
//
MDCSUTILS BOOL WINAPI MDCS_ASSAY_UpdateMeasurementSetDescription(HDBHANDLE hHandle , LONGLONG lAssayID, LPCSTR pszNewDesc );


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAY_GetUniqueMeasurementValuesByPlate
//Descruiption: Will return unique values of measurement types for a plate
//Note: works only on cell attributes
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - unique ID of a plate
//    arrMeasurements   - array of measurement data types
//    nArraySize        -  array size 
//returns recordset with fields:   - column correspond measurement types in array ordered by first column
MDCSUTILS BOOL WINAPI MDCS_ASSAY_GetUniqueMeasurementValuesByPlate(HDBHANDLE hHandle,  LONGLONG lPlateID, MDCS_ST_ScopeAttribute* arrMeasurements, int nArraySize,  MDCS_GetDBResultsCCallback *pResultCallback);

/////////////////////////////////////////////////////////////////////
//                                                                 //
//             functions to work with plates                       // 
//                                                                 //
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
//function will create a new plate and set default access permissions
//permissions will be granted to administrators and current user only
//Input: 
//    hHandle        - database connection handle
//    stPlateInfoIn  - plate description to insert 
//    plDefaultGroupID - ID of a group that will also have a Lab Head permissions for the plate  a plate, if NULL - this will be ignored
//Output: 
//    pstPlateInfoOut -  plate descripion as created in DB
//Return: FALSE - if error occured
MDCSUTILS BOOL  WINAPI MDCS_PLATE_CreatePlate(HDBHANDLE hHandle, const MDCS_ST_PlateInfo& stPlateInfoIn, MDCS_ST_PlateInfo* pstPlateInfoOut, LONGLONG* plDefaultGroupID  = NULL);



/////////////////////////////////////////////////////////////////////
//function to get plate info
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate
//Output: 
//    pstPlateInfoOut -  plate descripion as created in DB
//Return: FALSE - if error occured
MDCSUTILS BOOL  WINAPI MDCS_PLATE_GetInfo(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_ST_PlateInfo& stPlateInfoOut);

/////////////////////////////////////////////////////////////////////
//function will return description of columns for the plate attributes 
//Input: 
//    hHandle        - database connection handle
//    pResultCallback - pointer to the callback function that will contain results
//Output: result columns will be:  
//                ATTR_DB_NAME   - name of the column that contains data for the attribute in the database, string
//                ATTR_NAME      - display name of the attribute, string
//                ATTR_FORMAT    - format of the data, integer cast to MDCS_E_ColumnType
//                ATTR_TYPE     -  type of the property, integer cast to MDCS_E_AttributeType
//                
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAllPropertyAttributes(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function will return all plates ordered by attributes how they follow in array 
//Input: 
//    hHandle        - database connection handle
//    pAXStringArray - pointer to string array of property column names
//    pResultCallback - pointer to the callback function that will contain results
//Output: result columns will be:  
//                PLATE_ID       - id of a plate, (LONGLONG)
//                PLATE_NAME     - name of the plate, (string)
//                ACQ_ID         - ID of acquisition when plate was acquired, (longlong)
//                GLOBAL_ID      - plate global ID, (string)
//                CREATOR_ID     - id of a person who created a plate (longlong)
//                CREATOR_NAME   - name of a person who created a plate (string)
//                BARCODE        - barcode of the plate (string)
//                TIME_CREATED   - time when plate was created in seconds from 01/01/1970 00:00:00, (LONGLONG)
//                ACQ_NAME       - name of an acquisition that was used to acquire plate
//             and columns specified in pAXStringArray 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAllOrderedByAttributes(HDBHANDLE hHandle, const AxStringArray* pAXStringArray, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to get plate info for an assay 
//comments: plate info may not exist for an assay 
//Input: 
//    hHandle        - database connection handle
//    lAssayID      - id of an assay for which plate info will be retrieved
//Output: 
//    stPlateInfoOut  - plate info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetInfoBasedOnAssay(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_ST_PlateInfo& stPlateInfoOut);


/////////////////////////////////////////////////////////////////////
//function to get plate info for an assay 
//comments: plate info may not exist for an assay 
//Input: 
//    hHandle        - database connection handle
//    larrAssayID    - array of assay IDs
//    nElementInArray - elements in array 
//    pResultCallback - result callback 
//Output: result columns will be:  
//                ASSAY_ID       - id of an assay, (LONGLONG) (ordered asc)
//                PLATE_ID       - id of a plate, (LONGLONG)
//                PLATE_NAME     - name of the plate, (string)
//                ACQ_ID         - ID of acquisition when plate was acquired, (longlong)
//                GLOBAL_ID      - plate global ID, (string)
//                CREATOR_ID     - id of a person who created a plate (longlong)
//                CREATOR_NAME   - name of a person who created a plate (string)
//                BARCODE        - barcode of the plate (string)
//                TIME_CREATED   - time when plate was created in seconds from 01/01/1970 00:00:00, (LONGLONG)
//                ACQ_NAME       - name of an acquisition that was used to acquire plate
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetInfoBasedOnAssaySet(HDBHANDLE hHandle, const LONGLONG* larrAssayID, int nElementInArray,  MDCS_GetDBResultsCCallback * pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to delete plate 
//comment: will not delete actual data, will only mark data as deleted
//Input: 
//    hHandle        - database connection handle
//    lPlateID  - id of a plate that needs to be deleted
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_Delete(HDBHANDLE hHandle, LONGLONG lPlateID);


/////////////////////////////////////////////////////////////////////
//function to delete plate images
//comment: will not delete actual data, will only mark data as deleted
//Input: 
//    hHandle        - database connection handle
//    lPlateID  - id of a plate that needs to be deleted
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_DeleteImages(HDBHANDLE hHandle, LONGLONG lPlateID);


//////////////////////////////////////////////////////////////////////////
//function to get unique values for a plate attribute 
//Input:
//         hHandle        - database connection handle
//         pszAttrColumnName - column that will contain unique values
//         pAXAttrColumnNames - attribute column names to query on
//         pAXAttrValues      - values of that attrubutes are equal to
//Output:
//       pAXValuesOut - array of unique values 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetUniqueAttributeValues(HDBHANDLE hHandle, LPCSTR pszAttrColumnName, const AxStringArray* pAXAttrColumnNames, const AxStringArray* pAXAttrValues, AxStringArray* pAXValuesOut);

//////////////////////////////////////////////////////////////////////////
//function to get plates based specified attributes values 
//Input:
//         hHandle        - database connection handle
//         pAXDisplayColumns - columns to retrieve 
//         pAXAttrColumn     - columns to query on
//         pAXAttrValues      - of the column to query on
//Output: result columns will be:  
//                PLATE_ID       - id of a plate, (LONGLONG)
//                PLATE_NAME     - name of the plate, (string)
//                ACQ_ID         - ID of acquisition when plate was acquired, (longlong)
//                GLOBAL_ID      - plate global ID, (string)
//                CREATOR_ID     - id of a person who created a plate (longlong)
//                CREATOR_NAME   - name of a person who created a plate (string)
//                BARCODE        - barcode of the plate (string)
//                TIME_CREATED   - time when plate was created in seconds from 01/01/1970 00:00:00, (LONGLONG)
//                ACQ_NAME       - name of an acquisition that was used to acquire plate
//             and columns specified in pAXDisplayColumns
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAllByAttributes(HDBHANDLE hHandle, const AxStringArray* pAXDisplayColumns, const AxStringArray* pAXAttrColumn,  const AxStringArray* pAXAttrValues, MDCS_GetDBResultsCCallback* pResultCallback);

//////////////////////////////////////////////////////////////////////////////////////////
////will call a dialog to manage security access to the plate 
//Input: 
//       hHandle        - database connection handle
//       LPlateID       - plate ID
//       pszTitle - dialog title
//       hWnd - application window 
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_PLATE_ManageSecurity(HDBHANDLE hHandle, LONGLONG lPlateID, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL);


//////////////////////////////////////////////////////////////////////////////////////////
////will call a dialog to manage security access for plates in dynamic folder
//Input: 
//       hHandle        - database connection handle
//       arrAttributes   - array attributes
//       arrValues       - array attribute vlaues
//       pszTitle - dialog title
//       hWnd - application window 
//Return: FALSE - if dialog canceled
//////////////////////////////////////////////////////////////////////////////////////////
MDCSUTILS BOOL WINAPI MDCS_PLATE_FolderManageSecurity(HDBHANDLE hHandle, const AxStringArray& arrAttributes, const AxStringArray& arrValues, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL);

//to share images by site, timepoint and z index 
//Input: 
//    hHandle           - database connection handle
//    lSiteID           - site id to share
//    nTIndexIn         - time index that should be copied 
//    nZIndexIn         - Z Index that should be copied 
//    lSelectBySourceID - source ID, if needed to be part of selection (0 - ignored)
//    lSiteIDNew         - destination site ID
//    nTIndexNew         - destionation time index 
//    nZIndexNew         - destination Z Index
//Output: 
//    lCountUpdated     -  number of record copied
//Return: FALSE, if fails
MDCSUTILS BOOL WINAPI MDCS_PLATE_ShareSiteImagesByTimeAndZIndex(HDBHANDLE hHandle, LONGLONG lSiteID, int nTIndexIn, int nZIndexIn, LONGLONG lSiteIDNew, int nTIndexNew, int nZIndexNew, LONGLONG& lCountUpdated,  LONGLONG lSelectBySourceID = 0);


/////////////////////////////////////////////////////////////////////
//function to create a new site
//Input: 
//    hHandle        - database connection handle
//    stSite         - site description
//Output: 
//    plSiteID -  ID of a new site 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateSite(HDBHANDLE hHandle, const MDCS_ST_Site& stSite, LONGLONG* plSiteID);


/////////////////////////////////////////////////////////////////////
//function to create a new series
//Input: 
//    hHandle        - database connection handle
//    stSeries        - series description
//Output: 
//    plSeriesID -  ID of a new site 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateSeries(HDBHANDLE hHandle, const MDCS_ST_SeriesInfo& stSeries, LONGLONG* plSeriesID);

/////////////////////////////////////////////////////////////////////
//function to create image source
//Input: 
//    hHandle        - database connection handle
//    stImageSource   - image source description
//Output: 
//    plImageSourceID -  ID of a new image source
//Return: FALSE - if error occured
 MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateImageSource(HDBHANDLE hHandle, const MDCS_ST_ImageSource& stImageSource, LONGLONG* lImageSourceID);


/////////////////////////////////////////////////////////////////////
//function to create image record
//Input: 
//    hHandle        - database connection handle
//    stImageDesc   - image description
//Output: 
//    plRecordID -  created ID 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateImageRecord(HDBHANDLE hHandle, const MDCS_ST_SiteImageInfo& stImageDesc, LONGLONG* plRecordID);


/////////////////////////////////////////////////////////////////////
//function to create a plate layout 
//Input: 
//    hHandle        - database connection handle
//    stPlateLayout  - structure that describes plate layout
//Output: 
//    pstPlateLayouteOut -  created layout
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateLayout(HDBHANDLE hHandle, const MDCS_ST_PlateTemplate& stPlateTemplate, MDCS_ST_PlateTemplate* pstPlateTemplateOut);

/////////////////////////////////////////////////////////////////////
//function to create a plate layout 
//Input: 
//    hHandle        - database connection handle
//    pDatasource    - datasource that contains layout data 
//    stPlateLayout  - structure that describes plate layout
//    pCallback      - callback
//Output: 
//    plLayoutID -    created layout
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_ImportLayoutData(HDBHANDLE hHandle, const MDCS_ST_PlateTemplate& stPlateTemplate, MDCS_ImportPlateLayout* pDatasource,  LONGLONG* plLayoutID, MDCS_ProgressCallback* pCallback);

/////////////////////////////////////////////////////////////////////
//function to apply layout to a plate 
//Input: 
//    hHandle        - database connection handle
//    lLayoutID      - id of a layout
//    lAssayID       - id of an assay
//    pCallback      - callback
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_ApplyLayoutToAssay(HDBHANDLE hHandle, LONGLONG lLayoutID, LONGLONG lAssayID, MDCS_ProgressCallback * pCallBack);

/////////////////////////////////////////////////////////////////////
//function to delete plate layout
//Input: 
//    hHandle        - database connection handle
//    lLayoutID      - id of a layout
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_DeleteLayout(HDBHANDLE hHandle, LONGLONG lLayoutID);

/////////////////////////////////////////////////////////////////////
//function to apply layout to a plate 
//Input: 
//    hHandle        - database connection handle
//    lLayoutID      - id of a layout
//    lPlateID       - id of a plate
//    pCallback      - callback
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_ApplyLayoutToPlate(HDBHANDLE hHandle, LONGLONG lLayoutID, LONGLONG lPlateID);


/////////////////////////////////////////////////////////////////////
//function to get plate annotion template 
//Input: 
//    hHandle        - database connection handle
//    lTemplID      - id of a template 
//Output:
//    stPlateTemplate   - plate template 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetTemplate(HDBHANDLE hHandle, LONGLONG lTemplID, MDCS_ST_PlateTemplate& stPlateTemplate);


/////////////////////////////////////////////////////////////////////
//function to get plate annotation template 
//Input: 
//    hHandle        - database connection handle
//    pszTemplName        - name of the template 
//Output:
//    stPlateTemplate  - plate template 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetTemplateByName(HDBHANDLE hHandle, LPCSTR pszTemplName, MDCS_ST_PlateTemplate& stPlateTemplate);

/////////////////////////////////////////////////////////////////////
//function: to get all plate annotation teplates 
//Input: 
//    hHandle        - database connection handle
//Output:
//    callback will returned columns described in MDCS_ST_PlateLayout structure
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetTemplates(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback * pResultCallback);

/////////////////////////////////////////////////////////////////////
//function to update plate layout template 
//Input: 
//    hHandle        - database connection handle
//    stPlateTemplateIn        - template in 
//Output:
//    stPlateTemplate  - plate template updated
//Return: FALSE - if error occured
MDCSUTILS  BOOL WINAPI MDCS_PLATE_UpdatePlateTemplate(HDBHANDLE hHandle, const MDCS_ST_PlateTemplate& stPlateTemplateIn, MDCS_ST_PlateTemplate* pstPlateTemplate);



/////////////////////////////////////////////////////////////////////
//function 
//to get all plate records
//Input: 
//    hHandle        - database connection handle
//Output: 
//    will return records with columns
//    ID  as plate id
//    BATCH_ID  as batch ID
//    X_WELLS, Y_WELLS number of wells
//    BARCODE  - barcxcode
//    GLOBAL_ID - plate global ID
//    STORAGE_LOCATION - storage location
//    STORAGE_TYPE - storage type
//    PLATE_NAME - plate name 
//    PLATE_DESCRIPTION - plate description
//    CREATOR - name of user who create batch
//    TIME_CREATED - time when plate was created
//    NAME     - plate name 
//Return: FALSE - if error occured
//comment: storage location will alwasy set to "db". dll will decide where images are located
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAllRecords(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get a single plate record
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - plate ID
//Output: 
//    will return records with columns
//    ID  as plate id
//    BATCH_ID  as batch ID
//    X_WELLS, Y_WELLS number of wells
//    BARCODE  - barcxcode
//    GLOBAL_ID - plate global ID
//    STORAGE_LOCATION - storage location
//    STORAGE_TYPE - storage type
//    PLATE_NAME - plate name 
//    PLATE_DESCRIPTION - plate description
//    CREATOR - name of user who create batch
//    TIME_CREATED - time when plate was created
//    NAME     - plate name 
//Return: FALSE - if error occured
//comment: storage location will alwasy set to "db". dll will decide where images are located
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetRecord(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get a site record
//Input: 
//    pSession        - session object
//    lSiteID        - site ID
//Output: 
//    will return records with columns
//    ID  as plate id
//    BATCH_ID  as batch ID
//    X_WELLS, Y_WELLS number of wells
//    X_POSITION, Y_POSITION  - position within a well
//    TO_DELETE - flag of deletion
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetSiteRecord(HDBHANDLE hHandle, LONGLONG lSiteID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to get all sites for a plate 
//Input: 
//    pSession        - session object
//    lPlateID        - plate ID
//Output: 
//    will return records with columns
//    ID  as plate id
//    BATCH_ID  as batch ID
//    X_WELLS, Y_WELLS number of wells
//    X_POSITION, Y_POSITION  - position within a well
//    TO_DELETE - flag of deletion
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetSitesByPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get complete image information a plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    will return records with columns
//    SITE_ID, SERIES_ID, IMAGE_SOURCE_ID, 
//    OBJ_ID, IMAGE_ID, OBJ_SIZE, OBJ_SERVER_NAME, OBJ_EXT, THUMB_SIZE, THUMB_SERVER_NAME, "
//    LOCATION_ID, "
//    THUMB_LOCATION_ID, "
//    WELL_X, WELL_Y, X_POSITION, Y_POSITION, "
//    Z_INDEX, Z_POSITION, T_INDEX, "
//    SOURCE_DESCRIPTION, SOURCE_ILLUMINATION "
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetCompleteImageInfo(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get an image record 
//Input: 
//    hHandle        - database connection handle
//    lImageID        - image ID
//Output: 
//    will return records with columns
//    ID  as record ID
//    IMAGE_DATA_ID
//    SITE_ID
//    IMAGE_SOURCE_ID
//    ACQUIRE_DATE
//    TIMEPOINT
//    Z_POSITION
//    Z_STEP
//    SERIES_INFO_ID
//    SOURCE_DESCRIPTION
//    STORAGE_LOCATION_NAME will return location ID
//    STORAGE_TYPE_NAME      - always "DB"

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetImageRecord(HDBHANDLE hHandle, LONGLONG lImageID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get all image record for a plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    will return records with columns
//    ID  as record ID
//    IMAGE_DATA_ID
//    SITE_ID
//    IMAGE_SOURCE_ID
//    ACQUIRE_DATE
//    TIMEPOINT
//    Z_POSITION
//    Z_STEP
//    SERIES_INFO_ID
//    SOURCE_DESCRIPTION
//    STORAGE_LOCATION_NAME will return location ID
//    STORAGE_TYPE_NAME      - always "DB"

//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetImageRecordPerPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to assign image object ID to the plate image
//Input: 
//    hHandle        - database connection handle
//    lPlateImageID      - plate image ID
//    lImageObjectID    - image object ID
MDCSUTILS BOOL WINAPI MDCS_PLATE_UpdateImageObjectID(HDBHANDLE hHandle, LONGLONG lPlateImageID, LONGLONG lImageObjectID);

/////////////////////////////////////////////////////////////////
//to get ID of object record where image is stored for the plate image
//Input: 
//    hHandle        - database connection handle
//    lPlateImageID      - plate image ID
//Output
//    lImageObjectID    - image object ID
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetImageObjectIDForImage(HDBHANDLE hHandle, LONGLONG lPlateImageID, LONGLONG& lImageObjectID);

/////////////////////////////////////////////////////////////////////
//function 
//to get a series record by ID
//Input: 
//    hHandle        - database connection handle
//    lSeriesID        - series ID
//Output: 
//    will return records with columns
//    ID  as series ID
// all othe columns from series_info table
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetSeriesRecord(HDBHANDLE hHandle, LONGLONG lSeriesID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get all sites positions for a plate
//Input: 
//    hHandle        - database connection handle
//    lSeriesID        - series ID
//Output: 
//    will return records with columns
//    X_POSITION, Y_OSITION values
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetSiteLocationsForPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);

////////////////////////////////////////////////////////////////////
//Function: 
//Input: 
//    hHandle        - database connection handle
//    lPlateID - plate ID
//to get image source records of a plate
//return columns:
// ID as image source ID 
// SOURCE_DESCRIPTION as source description 
// SOURCE_ILLUMINATION	as source illumination
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetImageSourcesOfPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);

////////////////////////////////////////////////////////////////////
//Function: GetImageSourcesOfPlate
//to get max value for a timepoint for a plate 
//Input: 
//       lPlateID - plate ID
//Output:
//       lMaxTimepoint - max time point value
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetMaxTimePointForPlate(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lMaxTimepoint);

////////////////////////////////////////////////////////////////////
//Function: 
//to retrieve series ID based on site, Z index and T index
//Input: 
//       lSiteID - site ID
//       lZIndex  - Z Index
//       lTIndex  - Time Index
//Output:
//       lSeriesID - found series ID
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetSeriesIDAtZAndT(HDBHANDLE hHandle, LONGLONG lSiteID, LONG lZIndex, LONG lTIndex, LONGLONG& lSeriesID);

////////////////////////////////////////////////////////////////////
//Function: 
//to get plates info by date range
//Input: 
//       pszStartDate - start date
//       pszEndDate  - end date
//Output: result columns will be:  
//                PLATE_ID       - id of a plate, LONGLONG
//                PLATE_NAME     - name of the plate, string
//                ACQ_ID         - ID of acquisition when plate was acquired, longlong
//                GLOBAL_ID      - plate global ID
//                CREATOR_ID     - id of a person who created a plate
//                CREATOR_NAME   - name of a person who created a plate
//                BARCODE        - barcode of the plate
//                TIME_CREATED   - time when plate was created in seconds from 01/01/1970 00:00:00

MDCSUTILS BOOL WINAPI MDCS_PLATE_GetPlatesByDate(HDBHANDLE hHandle, LPCSTR pszStartDate, LPCSTR pszEndDate, MDCS_GetDBResultsCCallback * pResultCallback);

///////////////////////////////////////////////////
//to update acquisition
//Input: 
//    hHandle        - database connection handle
//    stAcq          - acquisition description
MDCSUTILS BOOL WINAPI MDCS_PLATE_UpdateAcquisition(HDBHANDLE hHandle, const MDCS_ST_Acquisition& stAcq);


/////////////////////////////////////////////////////////////////////
//function to create a plate attribute
//Input: 
//    hHandle        - database connection handle
//    stAttributeIn  - attribute description
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CreateAttribute(HDBHANDLE hHandle, const MDCS_ST_Attribute& stAttributeIn, MDCS_ST_Attribute& stAttributeOut);


/////////////////////////////////////////////////////////////////////
//function to get attribute info
//Input: 
//    hHandle        - database connection handle
//    pszDisplayName - display name of attribute
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAttributeInfoByDisplayName(HDBHANDLE hHandle, LPCSTR pszDisplayName, MDCS_ST_Attribute& stAttributeOut);


/////////////////////////////////////////////////////////////////////
//function to get attribute info
//Input: 
//    hHandle        - database connection handle
//    pszDBName      - internal name of attribute
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAttributeInfoByDBName(HDBHANDLE hHandle, LPCSTR pszDBName, MDCS_ST_Attribute& stAttributeOut);


/////////////////////////////////////////////////////////////////////
//function to assign plate attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    pszValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_AssignAttributeValueString(HDBHANDLE hHandle, LONGLONG lPlateID, LPCSTR pszDBName, LPCSTR pszValue);

/////////////////////////////////////////////////////////////////////
//function to assign plate attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    plValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_AssignAttributeValueLong(HDBHANDLE hHandle, LONGLONG lPlateID, LPCSTR pszDBName, LONGLONG* plValue);

/////////////////////////////////////////////////////////////////////
//function to assign plate attribute value 
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - id of a plate that needs to change attribute value
//    pszDBName      - internal name of attribute, MDCS_ST_Attribute::szDBcolumnName
//    pfValue       - value
//Output:
//    stAttributeOut - attribute created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_AssignAttributeValueFloat(HDBHANDLE hHandle, LONGLONG lPlateID, LPCSTR pszDBName, float* pfValue);


/////////////////////////////////////////////////////////////////////
//function to rename plate attribute 
//Input: 
//    hHandle        - database connection handle
//    stAttrribute  - attribute to modify 
//    pszDBName      - pszNewName - new name of attribute 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_RenameAttribute(HDBHANDLE hHandle, const MDCS_ST_Attribute& stAttrribute, LPCSTR pszNewName);

/////////////////////////////////////////////////////////////////////
//function to update plate info 
//Input: 
//    hHandle        - database connection handle
//    stInfoIn       - new information about plate (plate ID must be specified)
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_UpdateInfo(HDBHANDLE hHandle, const MDCS_ST_PlateInfo& stInfoIn);

/////////////////////////////////////////////////////////////////////
//function to get a number of the datasets where plate assays are used
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - plate ID
//output 
//    lNumDataset    - number of the datasets where plate assays are used
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_CountPlateDatasets(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lNumDataset);


/////////////////////////////////////////////////////////////////////
//function to get a count of all acquired sites per plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    lCount - count of sites per plate 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAcqSiteCount(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lCount);


/////////////////////////////////////////////////////////////////////
//function to get count of all acquired wells per plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    lCount         - count of sites per plate 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAcqWellCount(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lCount);



/////////////////////////////////////////////////////////////////////
//function to get count of all acquired series per plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    lCount         - count of objects per plate 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetAcqSeriesCount(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lCount);


/////////////////////////////////////////////////////////////////////
//function to get count of compounds per plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    lCount         - count of objects per plate 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetCompoundCount(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lCount);

/////////////////////////////////////////////////////////////////////
//function to get count of compounds per plate 
//Input: 
//    hHandle        - database connection handle
//    lPlateID        - plate ID
//Output: 
//    lCount         - count of objects per plate 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetControlsCount(HDBHANDLE hHandle, LONGLONG lPlateID, LONGLONG& lCount);


////////////////////////////////////////////////////////////////////
//Function: GetControlStatistic
//to get a count of all controls in plate 
//Input: 
//       hHandle        - database connection handle
//       lPlateID - plate ID
//Output:
//       arrControlNames  - array that contains control names 
//       arrControlCount  - array that contains count of corresponding control 
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetControlStatistic(HDBHANDLE hHandle, LONGLONG lPlateID, AxStringArray& arrControlNames, AxStringArray& arrControlCount);

////////////////////////////////////////////////////////////////////
//to check if plate can be modified 
//Input: 
//       hHandle        - database connection handle
//       lPlateID - plate ID
//Output:
//       pbCan  - shows if plate can be modified if defined, if not  - if plate cannot be modified retruns 
// bad permissions error code 
MDCSUTILS BOOL WINAPI MDCS_PLATE_CanModify(HDBHANDLE hHandle, LONGLONG lPlateID, BOOL* pbCan);



////////////////////////////////////////////////////////////////////
//to get IDs of plate images
//Input: 
//       hHandle        - database connection handle
//       lPlateID - plate ID
//Output:
//       arrIDs  - ids of image objects that found for a plate 
// bad permissions error code 
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetImageIDs(HDBHANDLE hHandle, LONGLONG lPlateID, AxStringArray& arrIDs);

////////////////////////////////////////////////////////////////////
//to get IDs of plate thumbnails
//Input: 
//       hHandle        - database connection handle
//       lPlateID - plate ID
//Output:
//       arrIDs  - ids of image objects that found for a plate 
// bad permissions error code 
MDCSUTILS BOOL WINAPI MDCS_PLATE_GetThumbImageIDs(HDBHANDLE hHandle, LONGLONG lPlateID, AxStringArray& arrIDs);


////////////////////////////////////////////////////////////////////
//to mark plate as archived
//Input: 
//       hHandle        - database connection handle
//       lPlateID - plate ID
MDCSUTILS BOOL WINAPI MDCS_PLATE_ChangeStatus(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_E_MarkStatus eStatus); 


////////////////////////////////////////////////////////////////////
//                                                                //
// functions to work with acquisitions                            //
//                                                                //
////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//function to delete an acquisition
//Input: 
//    hHandle        - database connection handle
//    lAcqID  - id of an acquisition that needs to be deleted
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_Delete(HDBHANDLE hHandle, LONGLONG lAcqID);

/////////////////////////////////////////////////////////////////////
//function 
//to create a new acquisition
//Input: 
//    hHandle        - database connection handle
//    stAcq          - acquisition description
//Output: 
//    plAcqID -  ID of a new acquisition 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_Create(HDBHANDLE hHandle, const MDCS_ST_Acquisition& stAcq, LONGLONG* plAcqID);

/////////////////////////////////////////////////////////////////////
//function 
//to create acquisition profile
//Input: 
//    hHandle        - database connection handle
//    stAcqProf      - profile description
//Output: 
//    plAcqProfID -  ID of a new profile 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_CreateProfile(HDBHANDLE hHandle, const MDCS_ST_AcquisitionProfile& stAcqProf, LONGLONG* plAcqProfID); 


/////////////////////////////////////////////////////////////////////
//function 
//to get all records from acquisition profile table
//Input: 
//    hHandle        - database connection handle
//Output: 
//    will return records with columns
//    ID  as ACQUISITION ID
//    NAME as acquistion name
//    DESCRIPTION as acquisition decsription 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_GetProfileRecords(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback); 



/////////////////////////////////////////////////////////////////////
//function 
//to get a records from acquisition profile 
//Input: 
//    hHandle        - database connection handle
//    lProfileID     - profile ID
//Output: 
//    will return records with columns
//    ID  as ACQUISITION ID
//    NAME as acquistion name
//    DESCRIPTION as acquisition decsription 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_GetProfile(HDBHANDLE hHandle, LONGLONG lProfileID, MDCS_GetDBResultsCCallback* pResultCallback); 


/////////////////////////////////////////////////////////////////////
//function 
//to get an acquisition instance record
//Input: 
//    hHandle        - database connection handle
//    lProfileID     - profile ID
//Output: 
//    will return records with columns
//    ID  as ACQUISITION ID
//    NAME as acquistion name
//    DESCRIPTION as acquisition decsription 
//    START_DATE  - start data 
//    END_DATE - end date
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_GetInstanceRecord(HDBHANDLE hHandle, LONGLONG lInstanceID, MDCS_GetDBResultsCCallback* pResultCallback); 


/////////////////////////////////////////////////////////////////////
//function 
//to get all batch records
//Input: 
//    hHandle        - database connection handle
//Output: 
//    will return records with columns
//    ID  as ACQUISITION ID
//    ACQ_INSTANCE_ID  as ACQUISITION ID
//    NAME as acquisition name 
//    START_DATE  - start data 
//    END_DATE - end date
//    OPERATOR - name of user who create batch
//    DESCRIPTION - buthc decsription
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_GetBatchRecords(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to get a batch record
//Input: 
//    hHandle        - database connection handle
//    lBatchId       - batch ID
//Output: 
//    will return records with columns
//    ID  as ACQUISITION ID
//    ACQ_INSTANCE_ID  as ACQUISITION ID
//    NAME as acquisition name 
//    START_DATE  - start data 
//    END_DATE - end date
//    OPERATOR - name of user who create batch
//    DESCRIPTION - buthc decsription
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ACQUISITION_GetBatchRecord(HDBHANDLE hHandle, LONGLONG lBatchID, MDCS_GetDBResultsCCallback* pResultCallback);

//////////////////////////////////////////////////////////////////////////////////
// SECURITY                                                                   ///
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////
//to get connection objects
//will call a dialog to manage users
//Input: 
//       hHandle  - database connection handle
//       pszTitle - dialog title
//       hWnd     - application window 
//       eDlgType - type of the dialog, if MDCS_eDlgUsersWithStorage will show storage assigned to each user
//       hIcon    - dialog's icon
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_SECURITY_ManageUsersDlg(HDBHANDLE hHandle, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL, MDCS_ST_DlgUsersType eDlgType = MDCS_eDlgUsersSimple, HICON hIcon  = 0);


//////////////////////////////////////////////////////////////////////////////////////////
//will call a dialog to manage groups
//Input: 
//       hHandle        - database connection handle
//       pszTitle - dialog title
//       hWnd - application window 
//       pbHideUserGroupsDefault (in\out) - if true - will not show user-defined groups
//       bHideUserGroupsControl  - will show\hide check box for user-defined groups
//       hIcon    - dialog's icon
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_SECURITY_ManageGroupsDlg(HDBHANDLE hHandle, HWND hWnd, LPCSTR pszDlgTitle, BOOL bHideUserGroupsControl = TRUE, BOOL* pbHideUserGroupsDefault = NULL, HICON hIcon  = 0);


//////////////////////////////////////////////////////////////////////////////////////////
//will get a list of groups that user has access to 
//Input: 
//       hHandle        - database connection handle
//       lUserID        - id of a user, if 0 - function will return all groups for current user
//Output:
//       arrGroupIDs - group ids
//       arrGroupNames - group names
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_GetUserGroups(HDBHANDLE hHandle, LONGLONG lUserID, AxStringArray& arrGroupIDs, AxStringArray& arrGroupNames);


//////////////////////////////////////////////////////////////////////////////////////////
//will display a selection dilog to choose groups 
//Input: 
//       hHandle        - database connection handle
//       lUserID        - id of a user, if 0 - function will return all groups for current user
//       hWnd - application window 
//Output:
//       pCallback - will get groups info 
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_GetUserGroupsDlg(HDBHANDLE hHandle, HWND hWnd, MDCS_GroupInfoCallback* pCallback);


//////////////////////////////////////////////////////////////////////////////////////////
//will return information about user
//Input: 
//       hHandle        - database connection handle
//       lUserID        - id of a user, if 0 - function will return all groups for current user
//Output:
//       stUserInfo     - user info 
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_GetUserInfo(HDBHANDLE hHandle, LONGLONG lUserID, MDCS_ST_UserInfo& stUserInfo);

//////////////////////////////////////////////////////////////////////////////////////////
//to check if user is in Administrators group
//Input: 
//       hHandle        - database connection handle
//       lUserID        - id of a user, if 0 - function will return all groups for current user
//Output:
//       bAdmin        - if true - user in admin group 
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_IsUserInAdminGroup(HDBHANDLE hHandle, LONGLONG lUserID,  BOOL& bAdmin);

//////////////////////////////////////////////////////////////////////////////////////////
//to get info of group Everyone
//Input: 
//       hHandle        - database connection handle
//Output:
//       stGroupInfo     - group  info
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_GetEveryoneGroupInfo(HDBHANDLE hHandle, MDCS_ST_GroupInfo& stGroupInfo);


//////////////////////////////////////////////////////////////////////////////////////////
//to change a password of a current user 
//Input: 
//       hHandle        - database connection handle
//Return: FALSE - if function fails 
MDCSUTILS BOOL WINAPI MDCS_SECURITY_ChangePassword(HDBHANDLE hHandle);

/////////////////////////////////////////////////////////
// functions to work with datasets

/////////////////////////////////////////////////////////
// to create/insert a new dataset analysis attributes
// Input: 
//       hHandle        - database connection handle
//       pDsetAnalysis - description of analysis
//       pAttributes  - pointer to the attributes array
//       uNumberAttr - number of attributes in array
// Output: 
//       plAnalysisID   - new analysis id
MDCSUTILS BOOL WINAPI MDCS_DATASET_InsertAnalysisAttributes(HDBHANDLE hHandle,   
                                                         const MDCS_ST_DsetAnalysis* pDsetAnalysis,   //analysis description      
                                                         const MDCS_ST_DsetAnalysisAttr* pAttributes, //pointer to the attributes array
                                                         UINT  uNumberAttr,                            //number of attributes in array'
                                                         LONGLONG* plAnalysisID         
                                                         );


//////////////////////////////////////////////////////////
//to get all analysis attributes for a dataset
// Input: 
//       hHandle        - database connection handle
//       lDatasetID     - dataset ID
//Output:
//       callback will return following fields
//       ATTR_ID - unique ID;
//       CALC_METHOD - calculation method
//       ATTR_TYPE - attribute type (pivot, data type)
//       ANALYSIS_ID - analysis ID (pointer to a description of analysis)
//       ORDER_NUM - order number 
//       COLLAPSE_COLUMN -column that is used to collapse data
//       ATTR_COLUMN - name of the attribute column
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAnalysisAttributesByDataset(HDBHANDLE hHandle,   
                                                         LONGLONG   lDatasetID,                       //dataset id
                                                         MDCS_GetDBResultsCCallback  * pCallBack
                                                         );

/////////////////////////////////////////////////////////
//to get dataset analysis attributes per analysis
// Input: 
//       hHandle        - database connection handle
//       lAnalsysisID     - analysis ID
//Output:
//       callback will return following fields
//       ATTR_ID - unique ID;
//       CALC_METHOD - calculation method
//       ATTR_TYPE - attribute type (pivot, data type)
//       ANALYSIS_ID - analysis ID (pointer to a description of analysis)
//       ORDER_NUM - order number 
//       COLLAPSE_COLUMN -column that is used to collapse data
//       ATTR_COLUMN - name of the attribute column
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAnalysisAttributes(HDBHANDLE hHandle,   
                                                         LONGLONG   lAnalysisID,                       //dataset id
                                                         MDCS_GetDBResultsCCallback  * pCallBack
                                                         );


/////////////////////////////////////////////////////////
//to get all analysis descriptions per dataset
// Input: 
//       hHandle        - database connection handle
//       lDatasetID    - dataset ID 
//Output:
//       callback will return following fields
//       ANALYSIS_ID  - unique id
//       DATASET_ID -  id of a dataset where it belongs
//       NAME - ananlysis description name
//       DESCRIPTION - description
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAnalysisDescriptions(HDBHANDLE hHandle,   
                                                         LONGLONG   lDatasetID,                       //dataset id
                                                         MDCS_GetDBResultsCCallback  * pCallBack
                                                         );


/////////////////////////////////////////////////////////
//to get dataset analysis configuration description
// Input: 
//       hHandle        - database connection handle
//       lAnalysisID    - configuration ID
//Output:
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAnalysisDescription(HDBHANDLE hHandle,   
                                                         LONGLONG   lAnalyisisID, 
                                                         MDCS_ST_DsetAnalysis& stDsetAttributes
                                                         );


/////////////////////////////////////////////////////////
//to find a record by attributes
// Input: 
//       hHandle        - database connection handle
//       lDatasetID    - dataset ID 
//       pointer to the attributes array
//       uNumberAttr - number of attributes in array
//Output:
//       pDsetAttributes        - record that corresponds with attributes      
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_FindAnalysisAttributesRecord(HDBHANDLE hHandle,   
                                                         LONGLONG lDatasetID,                         //dataset ID            
                                                         const MDCS_ST_DsetAnalysisAttr* pAttributes, //pointer to the attributes array
                                                         UINT  uNumberAttr,                           //number of attributes in array
                                                         MDCS_ST_DsetAnalysis* pDsetAttributes        //record that corresponds with attributes
                                                         );
/////////////////////////////////////////////////
//to delete analysis attributes
// Input: 
//       hHandle        - database connection handle
//       lDatasetID    - dataset ID 
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_DeleteAnalysisAttributes(HDBHANDLE hHandle,   
                                                         LONGLONG lAttributesID                      //attributes ID            
                                                         );

/////////////////////////////////////////////////
//to update analysis attributes
// Input: 
//       hHandle        - database connection handle
//       pDsetAnalysis  - structure that contains attributes to update
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_UpdateAnalysisAttributes(HDBHANDLE hHandle, const MDCS_ST_DsetAnalysis* pDsetAnalysis );


//////////////////////////////////////////////////////////////////////////////////////////
////will call a dialog to manage security access to the dataset folders
//Input: 
//       hHandle        - database connection handle
//       lFolderID       - folder ID
//       pszTitle - dialog title
//       hWnd - application window 
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_ManageFolderSecurity(HDBHANDLE hHandle, LONGLONG lFolderID, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL);

/////////////////////////////////////////////////////////////////////
//function to delete dataset folder
//Input: 
//    hHandle        - database connection handle
//    lFolderID  - id of a folder in dataset tree
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_DeleteFolder(HDBHANDLE hHandle, LONGLONG lFolderID);

/////////////////////////////////////////////////////////////////////
//function to update the link to folder of a dataset 
//Input: 
//    hHandle        - database connection handle
//    lFolderID    - id of a folder
//    lDatasetID  - id of a dataset
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_UpdateFolderItem(HDBHANDLE hHandle, LONGLONG lFolderID, LONGLONG lDatasetID);

/////////////////////////////////////////////////////////////////////
//function to delete a dataset 
//Input: 
//    hHandle        - database connection handle
//    lDatasetID  - id of a dataset 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_Delete(HDBHANDLE hHandle, LONGLONG lDatasetID);


/////////////////////////////////////////////////////////////////////////////////////////
//to get a number of analysis per dataset 
//Input: 
//       hHandle        - database connection handle
//       lDatasetID     - dataset id
//Output:
//       lCount        - number of analysis
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAnalysisCount(HDBHANDLE hHandle, LONGLONG lDatasetID, LONGLONG& lCount);

/////////////////////////////////////////////////////////////////////
//function to copy a dataset 
//Input: 
//    hHandle        - database connection handle
//    lDatasetSourceID - ID of a dataset that should be copied
//    lDestinationFolderID  - id of a folder where dataset should be copied
//    wCopyDependants - option to copy dataset dependants such as results, objects, scriptlets (use MDC_E_DatasetObjectType)
//    bCopySpots -   if true will copy all spots that were used in dataset 
//    bCopyAssays  - if true will copy all assays associated with dataset
//Output:
//    stDataSetOut   - dataset that was created
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_Copy(HDBHANDLE hHandle, LONGLONG lDatasetSourceID, LONGLONG lDestinationFolderID, MDCS_ST_Dataset& stDataSetOut, WORD wCopyDependants, BOOL bCopySpots = TRUE, BOOL bCopyAssays = TRUE);

/////////////////////////////////////////////////////////////////////
//function to update dataset
//Input: 
//    hHandle        - database connection handle
//    stDataSetIn -  dataset info that will be updated, should contain valid dataset ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_Update(HDBHANDLE hHandle, const MDCS_ST_Dataset& stDataSetIn);


/////////////////////////////////////////////////////////////////////
//function to get a dataset info 
//Input: 
//    hHandle        - database connection handle
//    lDatasetID      - dataset ID 
//Output:
//    stDataSetOut -  dataset info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_Get(HDBHANDLE hHandle, LONGLONG lDatasetID, MDCS_ST_Dataset& stDataSetOut);


/////////////////////////////////////////////////////////////////////
//function to create a new dataset
//Input: 
//    hHandle        - database connection handle
//    lDestFolderID  - folder ID where dataset should be created 
//    stDataSetIn    - dataset description
//Output:
//    stDataSetOut -  dataset info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_Create(HDBHANDLE hHandle, LONGLONG lDestFolderID, const MDCS_ST_Dataset& stDataSetIn, MDCS_ST_Dataset& stDataSetOut);


/////////////////////////////////////////////////////////////////////
//function to create a new dataset
//Input: 
//    hHandle        - database connection handle
//    lDatasetID     - destination dataset ID
//    lAssayID       - assay ID
//Output:
//    stDataSetOut -  dataset info
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_AddAssay(HDBHANDLE hHandle, LONGLONG lDatasetID, LONGLONG lAssayID);


//////////////////////////////////////////////////////////////////////////////////////////
////to check if current user can modify a dataset 
//Input: 
//       hHandle        - database connection handle
//       lDatasetID       - dataset ID
//Output:
//       bCanModify - if TRUE - user can modify dataset
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_HavePermissionsToModify(HDBHANDLE hHandle, LONGLONG lDatasetID, BOOL& bCanModify);


//////////////////////////////////////////////////////////////////////////////////////////
//to get assays that were used to create a dataset
//will not return assays that were created by scripts
//Input: 
//       hHandle        - database connection handle
//       lDatasetID       - dataset ID
//Output:
//       pCallBack - callback returns assay info
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllAssays(HDBHANDLE hHandle, LONGLONG lDatasetID, MDCS_GetDBResultsCCallback  * pCallBack);


//////////////////////////////////////////////////////////////////////////////////////////
//to get assays and filters that were used to create a dataset
//will return arrays of dataset assays and  filters 
//Input: 
//       hHandle        - database connection handle
//       lDatasetID       - dataset ID
//Output:
//       arrAssayIDs - IDs need to be converted to LONGLONG
//       arrAssayFilters - filters
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAssayAndFilters(HDBHANDLE hHandle, LONGLONG lDatasetID, AxStringArray& arrAssayIDs, AxStringArray& arrAssayFilters);


//////////////////////////////////////////////////////////////
//Description: to get assays with basic description in folder
//Input: 
//       hHandle     - database connection handle
//       lFolderID   - assay folder ID
//       
//Output:
//       pResultCallback - call back that contains results of a query   
//       fields that always be present
//       DATASET_ID, DATASET_NAME, TIME_CREATED (as time_t value), DATASET_DESCRIPTION( dataset description), 
//       DATASET_TYPE  (type of the dataset),
//       DATASET_DTYPE
//       ENGLISH_DESCR
//       TO_DELETE 
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllInFolder(HDBHANDLE hHandle, LONGLONG lFolderID, MDCS_GetDBResultsCCallback* pResultCallback);


//////////////////////////////////////////////////////////////
//Description: to get item's folder 
//Input: 
//       hHandle     - database connection handle
//       lItemID    - item ID
//       
//Output:
//       lFolderID      - id of the item's folder 
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetItemFolder(HDBHANDLE hHandle, LONGLONG lItemID, LONGLONG& lFolderID);

/////////////////////////////////////////////////////////////////////
//function to get assay sibling folders
//Input: 
//    hHandle           - database connection handle
//    lParentFolderID   - ID of parent to retrieve siblings of
//    pResultCallback   - data callback
//Output: result columns will be:  
//                FOLDER_NAME    - folder name
//                FOLDER_ID      - folder ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAssaySiblingFolders(HDBHANDLE hHandle, LONGLONG lParentFolderID, MDCS_GetDBResultsCCallback* pResultCallback);


//////////////////////////////////////////////////////////////////////////////////////////
// to check if subfolder exists in the database
//Input: 
//       hHandle        - database connection handle
//Output: 
//       lSubfolderID  - subfolder ID, if 0  subfolder does not exists, otherwise - folder ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_DoesSubFolderExist(HDBHANDLE hHandle, LONGLONG lFolderID, LPCSTR pzName, LONGLONG &lSubfolderID );

//////////////////////////////////////////////////////////////////////////////////////////
// create a new dataset folder in the database
//Input: 
//       hHandle        - database connection handle
//   
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_CreateFolder(HDBHANDLE hHandle, const MDCS_ST_FolderInfo& stInfoIn, MDCS_ST_FolderInfo & stInfoOut);

//////////////////////////////////////////////////////////////////////////////////////////
// modify a dataset folder in the database
//Input: 
//       hHandle        - database connection handle
//   
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_ModifyFolder(HDBHANDLE hHandle, const MDCS_ST_FolderInfo& stInfoIn );

/////////////////////////////////////////////////////////////////////
//function to get dataset sibling folders
//Input: 
//    hHandle           - database connection handle
//    lParentFolderID   - ID of parent to retrieve siblings of
//    pResultCallback   - data callback
//Output: result columns will be:  
//                FOLDER_NAME    - folder name
//                FOLDER_ID      - folder ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetSiblingFolders(HDBHANDLE hHandle, LONGLONG lParentFolderID, MDCS_GetDBResultsCCallback* pResultCallback);


//////////////////////////////////////////////////////////////////////////
//to get data types records dataset
//return columns:
//    TABLE_ID - table name
//    COLUMN_NAME
//    COLUMN_TYPE
//    COLUMN_NAME_EXT
//    FUNCTION_NAME,
//    PARAMETER_NAME
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllMeasurements(HDBHANDLE hHandle, LONGLONG lDatasetID,  MDCS_GetDBResultsCCallback* pResultCallback );


/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_AddScriptletAssay
//Description:  to create and add scriptlet to dataset
//Input: 
//    hHandle        - database connection handle
//    lDatasetID     - target dataset
///returns columns:
//    lAssayIDOut - created assay ID 
MDCSUTILS BOOL WINAPI MDCS_DATASET_AddScriptletAssay(HDBHANDLE hHandle, LONGLONG lDatasetID, LONGLONG lScriptletID, LPCSTR  pszAssayName, LONGLONG& lAssayIDOut);

/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_GetScriptletAssays
//Description:  to get all scriptlets column for sciptlet in dataset 
//Input: 
//    hHandle        - database connection handle
//    lDatasetID     - target dataset
//    lScriptletID    - target scriptlet
///returns:
//    arrAssayIDs - list of sciptlet assay IDs
//    arrAssayNames  - list of scriptlet assay names
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetScriptletAssays(HDBHANDLE hHandle, LONGLONG lDatasetID, LONGLONG lScriptletID, AxStringArray& arrAssayIDs, AxStringArray& arrAssayNames);

/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_GetScriptletAssays
//Description:  to find a sciptlet column with name in dataset
//Input: 
//    hHandle        - database connection handle
//    lDatasetID     - target dataset
//    lScriptletID    - target scriptlet
//    pszName        - assay name 
///returns:
//    lAssayID       - assay ID found
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetScriptletAssayIDByName(HDBHANDLE hHandle, LONGLONG lDatasetID,  LPCSTR pszName, LONGLONG& lAssayID);


/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_GetAllForPlate
//Description:  to get available datasets for a plate
//Input: 
//    hHandle        - database connection handle
//    lPlateID       - plate id 
//Output: callback with dataset columns
///returns: FALSE if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllForPlate(HDBHANDLE hHandle, LONGLONG lPlateID, MDCS_GetDBResultsCCallback * pResultCallback);

/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_GetAllForAssay
//Description:  to get available datasets for a plate
//Input: 
//    hHandle        - database connection handle
//    lAssayID       - assay id 
//
//Output:            -callback with dataset columns
///returns:     FALSE if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllForAssay(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_GetDBResultsCCallback * pResultCallback);


/////////////////////////////////////////////////////////////////
//Function: MDCS_DATASET_GetAllMSetParamValues
//Description:  to get values ofr attributes in a dataset
//Input: 
//    hHandle        - database connection handle
//    lDatasetID       - dataset id 
//Output: callback with dataset columns
///returns: FALSE if fails
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetAllMSetParamValues(HDBHANDLE hdbHandle, LONGLONG lDatasetID,  const MDCS_ST_ScopeAttribute* arrAttributes, INT_PTR nElemCount, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////////////////////////
//to get description of results on dataset for specified configuration
//Input: 
//       hHandle        - database connection handle
//       lDatasetID       - dataset ID
//       lConfigID      - configuration ID
//Output:
//       pCallBack - callback returns assay info
//Return: FALSE - if dialog canceled
//comment: use MDCS_DATASET_CallbackToAnalysisInfo to process results
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetResultsInfoByConfig(HDBHANDLE hHandle, LONGLONG lDatasetID, LONGLONG lConfigID,  MDCS_GetDBResultsCCallback  * pCallBack);

/////////////////////////////////////////////////////////////////////////////////////////
//to get description of result on a dataset 
//Input: 
//       hHandle        - database connection handle
//       lResultID      - result ID
//Output:
//       pCallBack - callback returns assay info
//Return: FALSE - if dialog canceled
//comment: use MDCS_DATASET_CallbackToAnalysisInfo to process results
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetResultInfo(HDBHANDLE hHandle, LONGLONG lResultID, MDCS_GetDBResultsCCallback  * pCallBack);


/////////////////////////////////////////////////////////////////////////////////////////
//to get description of result on a dataset 
//Input: 
//       hHandle        - database connection handle
//       lResultID      - result ID
//Output:
//       pCallBack - callback returns assay info
//Return: FALSE - if dialog canceled
//comment: use MDCS_DATASET_CallbackToAnalysisInfo to process results
MDCSUTILS BOOL WINAPI MDCS_DATASET_GetScriptletInfo(HDBHANDLE hHandle, LONGLONG lScriptletID, MDCS_GetDBResultsCCallback  * pCallBack);

/////////////////////////////////////////////////////////////////////////////////////////
//to convert result of callback to MDCS_ST_DatasetResultInfo structure
//Input: 
//       hHandle        - database connection handle
//       pQueryResults  - call back results
//       stOut          - destination structure
//       bResultsInOrigForm - results are in original form
//Output:
//       pCallBack - callback returns assay info

//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_CallbackToAnalysisInfo(const MDCS_QueryResults* pQueryResults, MDCS_ST_DatasetResultInfo& stOut, BOOL bResultsInOrigForm = FALSE );

/////////////////////////////////////////////////////////////////////////////////////////
//to check if dataset with specified name already exist in folder 
//Input: 
//       hHandle        - database connection handle
//       pszName       -  dataset name 
//       lFolderID      - folder ID  
//Output:
//       bExists - TRUE if exists 
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_DATASET_DoesNameExist(HDBHANDLE hHandle, LPCSTR pszName, LONGLONG lFolderID, BOOL& bExists);


////////////////////////////////////////////////////////////////////
//                                                                //
// Functions to work with images in assays                        //
//                                                                //
////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////
//to get the attributes that assay images can be queried on
// Input: 
//       hHandle        - database connection handle
//       arrayColumnIDs - array to hold column ID
//       arrayColumnNames - array to hold column names
//Returns: FALSE - if fails
MDCSUTILS BOOL WINAPI MDCS_ASSAYIMAGES_GetAllPropertyAttributes(HDBHANDLE hHandle, AxStringArray &arrayColumnIDs, AxStringArray &arrayColumnNames );

//////////////////////////////////////////////////////////////////////////
//function to get assay images based on specified attributes values 
//Input:
//         hHandle        - database connection handle
//         pAXDisplayColumns - columns to retrieve 
//         pAXAttrColumn     - columns to query on
//         pAXAttrValues      - of the column to query on
//Output: result columns will be:  
//                OBJ_ID     - object id
//                PLATE_ID   -plate id
//                IMAGE_ID   -plate id
//                SITE_ID    - site id
//                SERIES_ID   - series id 
//                WELL_X     - well X
//                WELL_Y      - well Y
//                X_POSITION  - x position
//                Y_POSITION  - y position
//                Z_INDEX     - z-index
//                Z_POSITION  - z- position
//                T_INDEX
//                T_POSITION     - T position in seconds
//                T_MICROSECONDS  
MDCSUTILS BOOL WINAPI MDCS_ASSAYIMAGES_GetAllByAttributes( HDBHANDLE hHandle, const AxStringArray& arrayAssayIDs, const AxStringArray* pAXDisplayColumns, const AxStringArray* pAXAttrColumn,  const AxStringArray* pAXAttrValues, MDCS_GetDBResultsCCallback* pResultCallback);

//////////////////////////////////////////////////////////////////////////
//function to get unique values for a assay images attribute 
//Input:
//         hHandle        - database connection handle
//         lAssayID      - assay ID
//         pszAttrColumnName - column that will contain unique values
//         pAXAttrColumnNames - attribute column names to query on
//         pAXAttrValues      - values of that attrubutes are equal to
//Output:
//       pAXValuesOut - array of unique values 
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYIMAGES_GetUniqueAttributeValues(HDBHANDLE hHandle, const AxStringArray& arrayAssayIDs, LPCSTR pszAttrColumnName, const AxStringArray* pAXAttrColumnNames, const AxStringArray* pAXAttrValues, AxStringArray* pAXValuesOut);


//////////////////////////////////////////////////////
//functions to work with quicklist 
//////////////////////////////////////////////////////////////////////////////////////////
////will call a dialog to manage security access to the quicklist folders
//Input: 
//       hHandle        - database connection handle
//       lFolderID       - folder ID
//       pszTitle - dialog title
//       hWnd - application window 
//Return: FALSE - if dialog canceled
MDCSUTILS BOOL WINAPI MDCS_QUICKLIST_ManageFolderSecurity(HDBHANDLE hHandle, LONGLONG lFolderID, HWND hWnd = NULL, LPCSTR pszDlgTitle = NULL);


//////////////////////////////////////////////////////////////////////
//common database functions
//////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
//funtion: to optimize current database
//Input: 
//    hHandle        - database connection handle
//    pCallBack      - pointer to a callbak function
//    bQuickOpt      - for quick optimization that does not include dynamic tables
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_Optimize(HDBHANDLE hHandle,   MDCS_ProgressCallback * pCallBack, BOOL bQuickOpt = FALSE);


///////////////////////////////////////////////////////

//funtion: to compact a database. Available only for SQL server 
//Input: 
//    hHandle           - database connection handle
//    pszDatabaseName   - name of the database to compact 
//    uPrecentLeave     - percentage of a free space that should be left after compacting
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_Compact(HDBHANDLE hHandle,  LPCSTR pszDatabaseName, UINT uPrecentLeave, MDCS_ProgressCallback * pCallBack = NULL);


///////////////////////////////////////////////////////
//funtion: to get a size in bytes of the database. Available only for SQL server 
//Input: 
//    hHandle           - database connection handle
//    pszDatabaseName   - name of the database to compact 
//Output:
//    lSize - size of the database
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_GetSize(HDBHANDLE hHandle,  LPCSTR pszDatabaseName, LONGLONG& lSize);


///////////////////////////////////////////////////////
//funtion: to get database version
//Input: 
//    hHandle        - database connection handle
//Output:
//    stDBVersion     - database version
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_GetVersion(HDBHANDLE hHandle, MDCS_ST_DBVersion& stDBVersion);


///////////////////////////////////////////////////////
//function: to get avalable databases
//Input: 
//    hHandle        - database connection handle
//    arrFilterTables   - tables that should exists on database
//Output:
//    arrDBs         - list of databases found on server
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_GetAvailableDatabases(HDBHANDLE hHandle, AxStringArray& arrDBs, AxStringArray* parrFilterTables = NULL);


///////////////////////////////////////////////////////
//function: to get count active Connections
//Input: 
//    hHandle        - database connection handle
//    strDatabaseName   - name of the database
//Output:
//    lConnectionFound         - number of connections found
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_DATABASE_CountActiveConnections(HDBHANDLE hHandle, LONGLONG& lConnectionFound, LPCSTR pszDatabaseName = NULL);


//////////////////////////////////////////////////////////////////////////////////////////
//function to remove all data that was marked as deleted
//only memebers of admin group cav run this functions
//Input: 
//       hHandle        - database connection handle
//       pCallBack      - pointer to a callback class
//Output:
//       
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_RemoveMarkedData(HDBHANDLE hHandle, MDCS_ProgressCallback * pCallBack);

//////////////////////////////////////////////////////////////////////////////////////////
//function to remove all data that was marked as deleted
//only memebers of admin group cav run this functions. This function will delete marked plates plate by plate not table by table as old one. 
//to prevent confusion for user and user can cancel while delete plates. However there is a draw back that this will run slower compare to old method.
//Input: 
//       hHandle        - database connection handle
//       pCallBack      - pointer to a callback class
//Output:
//       
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_RemoveMarkedDataEx(HDBHANDLE hHandle, MDCS_ProgressCallback * pCallBack, BOOL bRemovePlateByPlate = TRUE);

//////////////////////////////////////////////////////////////////////////////////////////
//function to drop table 
//Input: 
//       hHandle        - database connection handle
//       pszTableName    - table name 
//       bTempSpace     - indicates that table should be dropped from temp sapce
//Output:
//       
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_DropTable(HDBHANDLE hHandle, LPCSTR pszTableName, BOOL bTempSpace = FALSE);


//funtion: to check if object exists in database
//Input: 
//    hHandle        - database connection handle
//    pszObjName     - name of the object(table, view)
//    pCallBack      - pointer to a callbak function
//    bObjTemp       - indicates if objects is temporary
//output:
//    bExists        - true, if object exists
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_DoesObjectExist(HDBHANDLE hHandle, LPCSTR pszObjName, BOOL& bExists, BOOL bObjTemp = FALSE);


//function to convert results to MDCS_ST_COLUMNPROP structure
//Input: 
//    pQueryResults     - query results
//    bOriginalFormat   - flag indicates that fresults are expected to be in original format
// Output
//    stAssayMeasOut     - structure
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_ResultsToCOLUMNPROP(const MDCS_QueryResults* pQueryResults, MDCS_ST_COLUMNPROP& stAssayMeasOut, BOOL bOriginalFormat = FALSE);


//////////////////////////////////////////////////////////////////////////////////////////
//to execute a statement that does not return any value
//Input: 
//    hHandle        - database connection handle
//    pszQuery       - query string
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_Execute(HDBHANDLE hHandle, LPCTSTR pszQuery);


//////////////////////////////////////////////////////////////////////////////////////////
//to create a add a column to a table
//Input: 
//    hHandle        - database connection handle
//    bExists
//    strTableName   - table name
//    strColumnName  - column name
//    eColumnType    - column type
//    nColumnLength  - column length
//    bNull          - NULL allowed?
//    bTemptable     - temp table ?
//Return: FALSE - if error occured
MDCSUTILS  BOOL WINAPI MDCS_UTILS_AddColumnToTable(HDBHANDLE hHandle, BOOL& bExists,  LPCSTR pszTableName, LPCSTR pszColumnName, const MDCS_E_ColumnType& eColumnType, int nColumnLength = 0,  BOOL bNull = TRUE, BOOL bTempTable = FALSE);


/////////////////////////////////////////////////////////////////////
//function: to create a table
//Input: 
//    hHandle        - database connection handle
//    pszTableName   - table name
//    arrColumns     - array of columns
//    nArraySize     - size or array of columns
//    pszPrefix      - table prefix
//Output: 
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UTILS_CreateTable(HDBHANDLE hHandle, LPCTSTR pszTableName, const MDCS_ST_DBColumn* arrColumns, int nArraySize, LPCTSTR pszPrefix = NULL);

//////////////////////////////////////////////////////////////////////////////////////////
//to create a foerign key
//Input: 
//    hHandle        - database connection handle
//    bExists
//    pszTableName   - table name
//    pszColumnName  - column name
//    eColumnType    - column type
//    nColumnLength  - column length
//    bNull          - NULL allowed?
//    bTemptable     - Temp table?
//Return: FALSE - if error occured
MDCSUTILS  BOOL WINAPI MDCS_UTILS_CreateForeignKey(HDBHANDLE hHandle, LPCTSTR pszTableName, LPCTSTR pszColumnName, LPCTSTR pszIndexName, LPCTSTR pszForeignKey, LPCTSTR pszForeignKeyTable,BOOL bTempTable=FALSE);


//////////////////////////////////////////////////////////////////////////////////////////
//to create a stored procedure
//Input: 
//    hHandle        - database connection handle
//    pszeName       - stored proc name
//    pszSQL         - SQL string that efines the stored proc
//Return: FALSE - if error occured
MDCSUTILS  BOOL WINAPI MDCS_UTILS_CreateStoredProc(HDBHANDLE hHandle,LPCTSTR pszName, LPCTSTR pszSQL);

/////////////////////////////////////////////////////////////////////
//function 
//to create a new history record
//Input: 
//    hHandle        - database connection handle
//    stUpdate       - MDCS_ST_Update  struct
//    lUpdateID      - update ID
//Output: 
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UPD_CreateHistoryRecord(HDBHANDLE hHandle, const MDCS_ST_Update& stUpdate, LONGLONG& lUpdateID);

/////////////////////////////////////////////////////////////////////
//function 
//to update status field for a history record
//Input: 
//    hHandle        - database connection handle
//    eStatus        - status
//    lUHID          - update history ID
//Output: 
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UPD_UpdateHistoryRecordStatus(HDBHANDLE hHandle, MDCS_ST_Update::MDCS_E_UpdateStatus eStatus, LONGLONG lUHID);

/////////////////////////////////////////////////////////////////////
//function 
//to get a history record for an update history ID (UH_ID)
//Input: 
//    hHandle        - database connection handle
//    lUHID          - update history 
//    pCallback      - callback
//Output: 
//   
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UPD_GetHistoryRecord(HDBHANDLE hHandle, LONGLONG lUHID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to find a finished update that matches the input update ID and type.
//Input: 
//    hHandle        - database connection handle
//    lUHID          - update id
//    eSType         - System type
//    pCallback      - callback
//Output: 
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UPD_FindFinishedUpdates(HDBHANDLE hHandle, LONGLONG lUHID, MDCS_ST_Update::MDCS_E_SystemType eSType, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to update the DB_Versions table
//Input: 
//    hHandle        - database connection handle
//    lDBVerID       -  DB version ID
//    lDBVerPara1    -  DB version leading number
//    lDBVerPara2    -  DB version middle number
//    lDBVerPara3    -  DB version trailing number//Output: 
//    
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_UPD_UpdateDatabaseVersion(HDBHANDLE hHandle, LONGLONG lDBVerID, LONGLONG lDBVerPara1,LONGLONG lDBVerPara2, LONGLONG lDBVerPara3);


//////////////////////////////////////////////////////////////
//function to work with application data tables       ///////
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//function 
//calls dialog that allows user editing of location options
//Input: 
//    hHandle        - database connection handle
//    hWnd           - parent window
//    plDefaultSelectionID - optional ID if the record that should be selected by default in dialog. 
//    pszDlgTitle    - dialog title
//    hIcon    - dialog's icon
//Output: 
//    pstLocationOption -  selected location option (if pstLocationOption->LocationID == 0, save to db  )
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_ManageLocationOptions(HDBHANDLE hHandle, MDCS_ST_LocationOption* pstLocationOption, HWND hWnd = NULL, const LONGLONG* plDefaultSelectionID = NULL, LPCSTR pszDlgTitle = NULL, HICON hIcon  = 0, BOOL bSelectionMode = TRUE );

/////////////////////////////////////////////////////////////////////
//function 
//to create a new record that describes location option
//Input: 
//    hHandle        - database connection handle
//    stLocation     - location description 
//Output: 
//    plLocationID -  generated record ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_CreateLocationOption(HDBHANDLE hHandle, const MDCS_ST_LocationOption& stLocation, LONGLONG* plLocationID);

/////////////////////////////////////////////////////////////////////
//MDCS_APP_GetFreeSpaceFromFileLocation
//PURPOSE: to get free disk space in file location 
//Input: 
//    hHandle        - database connection handle
//    stLocation     - location description 
//Output: 
//    lFreeSpace -  free disk space in KB
//Return: FALSE - if error occured

MDCSUTILS BOOL WINAPI MDCS_APP_GetFreeSpaceFromFileLocation(/*HDBHANDLE hHandle,*/ const MDCS_ST_LocationOption& stLocation, LONGLONG* lFreeSpace);
/////////////////////////////////////////////////////////////////////
//function 
//to create a new job
//Input: 
//    hHandle        - database connection handle
//    stJob         - job description
//Output: 
//    plJobID -  generated record ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_CreateJobRecord(HDBHANDLE hHandle, const MDCS_ST_Job& stJob, LONGLONG* plJobID);

   

/////////////////////////////////////////////////////////////////////
//function 
//to create a new app parameter
//Input: 
//    hHandle        - database connection handle
//    stParam        - application parameter
//Output: 
//    plParamID -  generated record ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_CreateParameter(HDBHANDLE hHandle, const MDCS_ST_AppParameter& stParam, LONGLONG* plParamID);


/////////////////////////////////////////////////////////////////////
//function 
//to get application param 
//Input: 
//    hHandle        - database connection handle
//    pszParamName   - application parameter name
//Output: 
//    stParam     -  application parameter info structure
//Return: FALSE - if error occured
MDCSUTILS  BOOL WINAPI MDCS_APP_GetParameterByName(HDBHANDLE hHandle, LPCSTR pszParamName, MDCS_ST_AppParameter& stParam);

/////////////////////////////////////////////////////////////////////
//function 
//to get application param using its ID
//Input: 
//    hHandle        - database connection handle
//    lParamID       - application parameter ID
//Output: 
//    stParam     -  application parameter info structure
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetParameterByID(HDBHANDLE hHandle, LONGLONG lParamID, MDCS_ST_AppParameter& stParam);

/////////////////////////////////////////////////////////////////////
//function 
//to update  application param using its ID
//Input: 
//    hHandle        - database connection handle
//    lParamID       - application parameter ID
//    stParam     -  application parameter info structure
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_UpdateParameter(HDBHANDLE hHandle, LONGLONG lParamID, const MDCS_ST_AppParameter& stParam);



/////////////////////////////////////////////////////////////////////
//function 
//to get all records from location options table 
//Input: 
//    hHandle        - database connection handle
//    pResultCallback   - callback 
//Output: 
//    columns from LOCATION_OPTIONS table
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetLocationOptions(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to get a single record from LOCATION_OPTIONS table
//Input: 
//    hHandle        - database connection handle
//    pResultCallback   - callback
//    lLocationID       - location option ID
//Output: 
//    columns from LOCATION_OPTIONS table
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetLocationOptionRecord(HDBHANDLE hHandle, LONGLONG lLocationID, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////////
//function 
//to get a single record from LOCATION_OPTIONS table
//Input: 
//    hHandle        - database connection handle
//    lLocationID       - location option ID
//Output: 
//    stLocationOption - location option structure
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetLocationOptionByID(HDBHANDLE hHandle, LONGLONG lLocationID, MDCS_ST_LocationOption& stLocationOption);

/////////////////////////////////////////////////////////////////////
//function 
//to get all records from location table filtered by Label value
//Input: 
//    hHandle        - database connection handle
//    pszLabel       - LABEL
//    pResultCallback   - callback 
//Output: 
//    columns from LOCATION_OPTIONS table
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetLocationRecordsByLabel(HDBHANDLE hHandle, LPCSTR pszLabel, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////////////////////////////
//function 
//to delete location option by its ID
//Input: 
//    hHandle        - database connection handle
//    lOptionID      - location option ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_DeleteLocationOption(HDBHANDLE hHandle, LONGLONG lOptionID);



/////////////////////////////////////////////////////////////////////
//function 
//to delete user location options by user login 
//Input: 
//    hHandle        - database connection handle
//    lUserID        - user  ID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_DeleteUserLocationOptions(HDBHANDLE hHandle, LONGLONG lUserID);

/////////////////////////////////////////////////////////////////////
//function 
//to assign user location option
//Input: 
//    hHandle          - database connection handle
//    lOptionID        - option  ID
//    lUserID          - user  ID
//    eType            - type of the option (MDCS_eUserDataOptionDefault - by defaul) flag indicated that option is default for user
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_SetUserLocationOptions(HDBHANDLE hHandle, LONGLONG lOptionID, LONGLONG lUserID, MDCS_E_UserDataLocationOptions eType = MDCS_eUserDataOptionDefault);


/////////////////////////////////////////////////////////////////////
//function 
//to get default location option
//Input: 
//    hHandle          - database connection handle
//    lOptionID        - option  ID
//    lUserID        - user  ID
//    eType            - type of the option (MDCS_eUserDataOptionDefault - by defaul) flag indicated that option is default for user
//Output:
//    stLocationOption - location option (if stLocationOption.lLocationID == 0 - record not in DB)
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_APP_GetUserLocationOption(HDBHANDLE hHandle, LONGLONG lUserID, MDCS_ST_LocationOption &stLocationOption, MDCS_E_UserDataLocationOptions eType = MDCS_eUserDataOptionDefault);

/////////////////////////////////////////////
//to get all records from job_queue table
//function will return columns:
// ID,
// TIMESTAMP -as time updated
//all other columns from JOB_QUEUE table
MDCSUTILS BOOL WINAPI MDCS_APP_GetJobQueueRecords(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////
//to get all records from job_queue table
//function will return MDCS_ST_Job structure or of object is NULL columns:
// ID,
// TIMESTAMP -as time updated
//all other columns from JOB_QUEUE table
MDCSUTILS BOOL WINAPI MDCS_APP_GetJobQueueRecord(HDBHANDLE hHandle, LONGLONG lJobID, MDCS_GetDBResultsCCallback* pResultCallback);


/////////////////////////////////////////////
//to get from job_queue info using job ID
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
//Output: 
//    stJob - structure that contains job info 
//all other columns from JOB_QUEUE table
MDCSUTILS BOOL WINAPI MDCS_APP_GetJobQueue(HDBHANDLE hHandle, LONGLONG lJobID, MDCS_ST_Job& stJob);


/////////////////////////////////////////////
//to update job status 
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
//    pszStatus      - status
MDCSUTILS BOOL WINAPI MDCS_APP_UpdateJobStatus(HDBHANDLE hHandle, LONGLONG lJobID, LPCSTR pszStatus);


/////////////////////////////////////////////
//to update job progress
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
//    pszProgress      - pszProgress
MDCSUTILS BOOL WINAPI MDCS_APP_UpdateJobProgress(HDBHANDLE hHandle, LONGLONG lJobID, LPCSTR pszProgress);

/////////////////////////////////////////////
//to update job_queue info using job ID
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
//    stUpdateJob    - info to be updated
MDCSUTILS BOOL WINAPI MDCS_APP_UpdateJobQueueRecord(HDBHANDLE hHandle, LONGLONG lJobID, const MDCS_ST_Job& stUpdateJob);

/////////////////////////////////////////////
//to cancel job 
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
MDCSUTILS BOOL WINAPI MDCS_APP_CancelJobProgress(HDBHANDLE hHandle, LONGLONG lJobID);

/////////////////////////////////////////////
//to claim a new job 
//Input: 
//    hHandle        - database connection handle
//    bDistributed  - flag indicated type of analysis enviroment(c-pod (TRUE)) 
//Output:
//    lJobID         - job ID
MDCSUTILS BOOL WINAPI MDCS_APP_ClaimJob(HDBHANDLE hHandle, LONGLONG& lJobID, BOOL bDistributed = FALSE);

/////////////////////////////////////////////
//to reset job ststus and progress
//Input: 
//    hHandle        - database connection handle
//    lJobID         - job ID
MDCSUTILS BOOL WINAPI MDCS_APP_ResetJob(HDBHANDLE hHandle, LONGLONG lJobID);


/////////////////////////////////////////////
//to reset job ststus and progress
//Input: 
//    hHandle        - database connection handle
//    pszNetworkId   - network ID
MDCSUTILS BOOL WINAPI MDCS_APP_ResetCrashedJobs(HDBHANDLE hHandle, LPCSTR pszNetWorkID);


/////////////////////////////////////////////
///to refresh status of all jobs 
//Input: 
//    hHandle        - database connection handle
MDCSUTILS BOOL WINAPI MDCS_APP_RefreshAllJobs(HDBHANDLE hHandle);


//////////////////////////////////////////////////////////////
//Functions to work with files data 

///////////////////////////////////////////////////////////////
//function to find record ID by GUID 
//Input: 
//    hHandle        - database connection handle
//    lID            - record ID 
//Output:
//    pstFileData    - file data  
MDCSUTILS BOOL WINAPI MDCS_FILEDATA_GetRecordByID(HDBHANDLE hHandle, LONGLONG lID, MDCS_ST_FileDataInfo* pstFileData);


//////////////////////////////////////////////////////////////
//function to find file data record ID by GUID 
//Input: 
//    hHandle        - database connection handle
//    pszGUID        - GUID 
//Output:
//    pstFileData    - file data 
MDCSUTILS BOOL WINAPI MDCS_FILEDATA_GetRecordByGUID(HDBHANDLE hHandle, LPCSTR pszGUID, MDCS_ST_FileDataInfo* pstFileData);


//////////////////////////////////////////////////////////////
//function to update a file data record 
//Input: 
//    hHandle        - database connection handle
//    lID            - record ID 
//    pstFileData    - file data 
MDCSUTILS BOOL WINAPI MDCS_FILEDATA_UpdateRecord(HDBHANDLE hHandle, LONGLONG lID, const MDCS_ST_FileDataInfo& stFileData);


//////////////////////////////////////////////////////////////
//Functions to work with macros


//////////////////////////////////////////////////////////////
//function to get macros info by macros ID 
//Input: 
//    hHandle        - database connection handle
//    lMacrosID      - macros ID
//Output:
//    stMacrosData    - macros data 
MDCSUTILS BOOL WINAPI MDCS_MACROS_GetRecord(HDBHANDLE hHandle, LONGLONG lMacrosID, MDCS_ST_GroupMacros& stMacrosData);

//////////////////////////////////////////////////////////////
//function to get all macros by group 
//Input: 
//    hHandle        - database connection handle
//    lGroupID       - group ID 
//Output: 
//    pResultCallback - callback with data of all macros 
MDCSUTILS BOOL WINAPI MDCS_MACROS_GetAllByGroup(HDBHANDLE hHandle, LONGLONG lGroupID, MDCS_GetDBResultsCCallback* pResultCallback);

//////////////////////////////////////////////////////////////
//function to update macros record 
//Input: 
//    hHandle        - database connection handle
//    lMacrosID      - macros ID 
//    stMacrosData    - new macros data 
MDCSUTILS BOOL WINAPI MDCS_MACROS_UpdateRecord(HDBHANDLE hHandle, LONGLONG lMacrosID, const MDCS_ST_GroupMacros& stMacrosData);

//////////////////////////////////////////////////////////////
//function to update macros record 
//Input: 
//    hHandle        - database connection handle
//    lMacrosID      - macros ID 
MDCSUTILS BOOL WINAPI MDCS_MACROS_DeleteRecord(HDBHANDLE hHandle, LONGLONG lMacrosID);

//////////////////////////////////////////////////////////////
//function to create a new macros 
//Input: 
//    hHandle        - database connection handle
//    lGroupID       - group ID 
//    stObjIn        - macros data to insert
//Output: 
//    stObjOut - created macros 
MDCSUTILS BOOL WINAPI MDCS_MACROS_Create(HDBHANDLE hHandle, const MDCS_ST_GroupMacros& stObjIn,  MDCS_ST_GroupMacros& stObjOut);


//////////////////////////////////////////////////////////////
//function to convert results of query callback to macros structure
//Input: 
//    pResults          - pointer to query results object
//    bInNativeFormat   - flag indiactes that query results should be treated in their original format
//                        otherwise they will be treaded as strings
//Output: 
//    stMacros - converted data
MDCSUTILS BOOL WINAPI MDCS_MACROS_ConvertQueryResultsToMacrosStructure(MDCS_QueryResults* pResults, MDCS_ST_GroupMacros& stMacros, BOOL bInNativeFormat = FALSE);


//////////////////////////////////////////////////////////////////////
//  functions to work with assay normalization                      
//////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_CreateConfig
//Description: to create new normalization configuration
//Input: 
//       hHandle        - database connection handle
//       stConfigIn     - configuration to create 
//Output:
//       pstConfigOut   - created configuration
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_CreateConfig(HDBHANDLE hHandle, const MDCS_ST_NormConfig& stConfigIn, MDCS_ST_NormConfig* pstConfigOut);

/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_UpdateConfig
//Description: to update existing configuration 
//Input: 
//       hHandle        - database connection handle
//       stConfigIn     - configuration that will be updated (lID must exists)
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_UpdateConfig(HDBHANDLE hHandle, const MDCS_ST_NormConfig& stConfigIn);


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_GetConfig
//Description: to get configuration using its ID
//Input: 
//       hHandle        - database connection handle
//       lConfigID      - ID of configuration to retrieve
//Output:
//       stConfigOut     - configuration for ID lConfigID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_GetConfig(HDBHANDLE hHandle, LONGLONG lConfigID, MDCS_ST_NormConfig& stConfigOut);


/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_GetConfig
//Description: to get configuration using its ID
//Input: 
//       hHandle        - database connection handle
//       pszConfigName  - name of the configuration
//Output:
//       stConfigOut     - configuration for ID lConfigID
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_GetConfigByName(HDBHANDLE hHandle, LPCSTR pszConfigName, MDCS_ST_NormConfig& stConfigOut);

/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_GetConfigAll
//Description: to get all configurations
//Input: 
//       hHandle           - database connection handle
//Output:
//       pResultCallback   - callback function, return columns that could be mapped to 
//                           MDCS_ST_NormConfig structure (see its description)
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_GetConfigAll(HDBHANDLE hHandle, MDCS_GetDBResultsCCallback* pResultCallback);

/////////////////////////////////////////////////////////////////
//Function: MDCS_ASSAYNORM_GetConfigForAssay
//Description: to get all configurations that exist for assay 
//Input: 
//       hHandle           - database connection handle
//       lAssayID          - id of the assay 
//Output:
//       pResultCallback   - callback function, return columns that could be mapped to 
//                           MDCS_ST_NormConfig structure (see its description)
//Return: FALSE - if error occured
MDCSUTILS BOOL WINAPI MDCS_ASSAYNORM_GetConfigForAssay(HDBHANDLE hHandle, LONGLONG lAssayID, MDCS_GetDBResultsCCallback* pResultCallback);


MDCSUTILS HDBHANDLE WINAPI MDCS_GETDB_Handle(const MDCS_ST_UserLogin &strConnectString);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //RC_INVOKED

#pragma pack()

#endif // !defined(AFX_MDCSTOREUTILS_H__4D40DC82_AC4E_404F_A6A2_B014B65A79D1__INCLUDED_)

