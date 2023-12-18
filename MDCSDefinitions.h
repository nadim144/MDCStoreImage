//***********************************************************************************************
//
//    Copyright (c) 2005 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  MDCSDefinitions.h
// PURPOSE: 
// AUTHOR:  MS  Jan 2005
// file contains definitions that are used in MDCStoreUtils 
#if !defined(AFX_MDCSDEFINITIONS_H_INCLUDED)
#define AFX_MDCSDEFINITIONS_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef RC_INVOKED

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

DECLARE_HANDLE(HDBHANDLE);

/////////////////////////////////////////////////////////////////////
//max object size definitions
#define MDCS_MAX_DB_ID              20      //max size of the unique database ID
#define MDCS_MAX_OBJ_ID             20      //max size of the object ID
#define MDCS_MAX_COL_NAME           20      //max size of the database column name (user defined, i.e. datatypes) 
#define MDCS_MAX_COL_NAMEEXT        128     //max size of the ext field 
#define MDCS_MAX_COL_RATIOTYPE      4       //max size of the ratio type 
#define MDCS_MAX_COL_WAVEDEF        4       //max type of the wavelength field
#define MDCS_MAX_COL_NORMTYPE       4       //max size of the normaliztion type field
#define MDCS_MAX_TABLEID            25      //max size of the table name in the database 
#define MDCS_MAX_RESULTSETID        18      //max size of the resultset ID
#define MDCS_MAX_COL_DESCRCOLUMN    2000    //max size of the decription field
#define MDCS_MAX_COL_ORDERNUM       16      //max size of the order num field
#define MDCS_MAX_COL_TYPE           10      //max size of the type field
#define MDCS_MAX_COL_LENGTH         4       //max length of the column in database (numeric) 
#define MDCS_MAX_COL_AVGTYPE        4       //max size of the column that contains average type description
#define MDCS_MAX_COL_NORMFACTOR     50      //max size of the column that contains normalization factor  
#define MDCS_MAX_COL_DEFAULT        10      //max size of the column that contains defaults
#define MDCS_MAX_DSN                256     //max size of the DSN (ODBC data source name)  
#define MDCS_MAX_USERNAME           50      //max size of the user name   
#define MDCS_MAX_PASSW              256     //max size of the user password
#define MDCS_MAX_DESCRIPTION        256     //max size of the description field 
#define MDCS_MAX_OBJ_NAME           128     //max size of the object name 
#define MDCS_MAX_OBJ_NAME_BIG       255     //max size of the object name 
#define MDCS_MAX_TABLE_NAME         25      //max size of the table name 
#define MDCS_MAX_SERVER             256     //max size of the server name 
#define MDCS_MAX_DBNAME             256     //max size of the database name
#define MDCS_MAX_ERR_SIZE           1024    //max size of error message
#define MDCS_MAX_CONNECTION_STRING  1000    //max size of connection string 
#define MDCS_MAX_BARCODE            256     //max size of a barcode    
#define MDCS_MAX_GLOBAL_ID          256     //max size of  a global ID
#define MDCS_MAX_WELL_NAME          25      //max size of a well name
#define MDCS_MAX_UNIT_NAME          25      //max size of a unit name 
#define MDCS_MAX_COMPOUND_NAME      128     //max size of a compound name
#define MDCS_MAX_CELL_ID            128     //max size of a cell ID
#define MDCS_MAX_STRING_VALUE       255     //max size of a string value
#define MDCS_MAX_DESCRIPTION_LARGE  1024    //max size of a large description
#define MDCS_MAX_STORAGE_TYPE       256     //max size of a storage type
#define MDCS_MAX_LABEL              256     //max size of a label
#define MDCS_MAX_NETWORK_ID         256     //max size of network ID
#define MDCS_MAX_REQUEST            20      //max size of request
#define MDCS_MAX_PARAM_VALUE        255     //max size of parameter value
#define MDCS_MAX_SERVER_VERSION     255     //max size of database server version
#define MDCS_MAX_SERVER_REVISION    255     //max size of database server revision, i.e. service pack
#define MDCS_MAX_SERVER_TYPE        255     //max size of database server type
#define MDCS_MAX_ODBC_DRIVER_NAME   255     //max size of ODBC driver name
#define MDCS_MAX_ODBC_DRIVER_VERSION   255  //max size of ODBC driver version
#define MDCS_MAX_ODBC_VERSION       255     //max size of ODBC version
#define MDCS_MAX_ODBC_SOURCE_NAME   255     //max size of ODBC datasource name 
#define MDCS_MAX_GUID               256     //max size of GUID
#define MDCS_MAX_SCOPE              128     //max size of scope name
#define MDCS_MAX_SIGNATURE          64      //max size of signature

//////////////////////////////////////////////////
//Error codes
#define     MDCS_ERR_CANCEL                 2999   //operation was cancel 
#define     MDCS_ERR_SUCCESS                3000   //operation completed successfully 
#define     MDCS_ERR_ODBC                   3001   //error was reported by ODBC driver
#define     MDCS_ERR_DB_INCORRECT_PARAM     3002   //incorrect parameter was supplied to function
#define     MDCS_ERR_DB_OBJECT_NOT_EXIST    3003   //database object does not exists 
#define     MDCS_ERR_USER_PERMISSIONS       3004   //user does not have sufficient priveleges to access data, permission denied
#define     MDCS_ERR_INCORRECT_OBJ_SIZE     3005   //result does not fit into the object
#define     MDCS_ERR_APPLICATION            3006   //error happened in application function
#define     MDCS_ERR_OBJECT_EXIST           3007   //cannot continue, object exists 
#define     MDCS_ERR_DELETE_APPLICATION_OBJECT    3008   //cannot delete application object
#define     MDCS_ERR_CANNOT_CONVERT_DATA    3009   //cannot perform data conversion
#define     MDCS_ERR_CANNOT_SAVE_DATA       3010   //cannot save data 
#define     MDCS_ERR_EMPTY_QUERY            3011   //cannot execute empty query
#define     MDCS_ERR_INCORRECT_QUERY        3012   //cannot execute query. query is incorrect
#define     MDCS_ERR_DB_ACTIVE_CONNECTIONS   3013  //operation cannot continue, other users connected to the database.

//registered messages 
#define  MDCS_MSG_PWD_CHANGED               "MDCS_MSGPasswordChanged"    //message send when password for current user is changed 

//application constants
#define  MDCS_CONST_MEASUREMENTTYPE        "MEASUREMENTSET"            //definition of measurement set type
#ifdef __cplusplus

//definitaion of scope names

//const strings that uses as a scope names 

//MDCS_eDSFMeasurementSetParams scopes group
const char MDCS_cszPlateScope[] = "PI"; //"Plate Info";                         //plate info
const char MDCS_cszPlateScopeFull[] = "Plate Info";                         //plate info
const char MDCS_cszPlatePropertyScope[] = "PP"; //"Plate Property";             //plate annotations
const char MDCS_cszPlatePropertyScopeFull[] = "Plate Property";             //plate annotations
const char MDCS_cszMeasurementSetScope[] = "MSI"; //"Measurement Set Info";      //measurement set info
const char MDCS_cszMeasurementSetScopeFull[] = "Measurement Set Info";      //measurement set info
const char MDCS_cszMeasurementSetPropertyScope[] = "MSP"; //"Measurement Set Property";  //measurment set annotations   
const char MDCS_cszMeasurementSetPropertyScopeFull[] = "Measurement Set Property";  //measurement set annotations   

//MDCS_eDSFMeasurementSetParams
const char MDCS_cszMDCSCellMeasurementScope[] = "CM"; //"Cell Measurement";          //cell measurements
const char MDCS_cszMDCSCellMeasurementScopeFull[] = "Cell Measurement";          //cell measurements
//const char MDCS_cszMDCSWellMeasurementScope[] = "Well Measurement";          //well measurements 
const char MDCS_cszMDCSImageMeasurementScopeFull[] = "Image Measurement";        //image measurements
const char MDCS_cszMDCSImageMeasurementScope[] = "IM"; //"Image Measurement";        //image measurements
const char MDCS_cszMDCSWellAnnotationScope[] = "WA"; //"Well Annotation";        //compound annotations
const char MDCS_cszMDCSWellAnnotationScopeFull[] = "Well Annotation";        //compound annotations

//MDCS_eDSFMeasurementDataAnnotation
const char MDCS_cszMDCSCompoundAnnotationScope[] = "SUBSTANCE_PROPERTY";        //default comppound annotation scope

//names of the predefined properties
const char MDCS_cszMeasuremenSetUniqueIDName[] = "Unique ID";           //name to display name of measurement set 
const char MDCS_cszMeasuremenSetUniqueID[] = "ASSAY_ID";                //measurement set ID

const char MDCS_cszAttrMeasuremenSetName[] = "Name";                    //name to display name of measurement set name
const char MDCS_cszAttMeasuremenSetNameID[] = "ASSAY_NAME";             //database value of measurement name 

const char MDCS_cszPlateUniqueIDName[] = "Unique ID";                //name to display name of plate id
const char MDCS_cszPlateUniqueID[] = "PLATE_ID";                     //database value of plate ID 

const char MDCS_cszWellGroupName[] = "Group";                        //name to display name of group
const char MDCS_cszWellGroupID[] = "GROUP0";                        //database value of group

const char MDCS_cszWellCompName[] = "Compound";                        //name to display name of compound
const char MDCS_cszWellCompID[] = "SUBSTANCE_NAME";                 //database value of compound

const char MDCS_cszWellConcName[] = "Concentration";                //name to display name of concentration
const char MDCS_cszWellConcID[] = "CONC";                           //database value of concentration


const char MDCS_cszPlateName[] = "Name";                           //name to display name of well
const char MDCS_cszPlateNameID[] = "PLATE_NAME";                         //database value of WELL


const char MDCS_cszMesRowIDName[] = "Unique ID";           //name to display name of a measurement
const char MDCS_cszMesRow[] = "PRINTED_SPOT_ID";         //measurement data ID

const char MDCS_cszWellName[] = "Well";           //name to display name of well
const char MDCS_cszWell[] = "WELL";                //well ID

const char MDCS_cszSiteName[] = "Site";           //name to display name of site
const char MDCS_cszSite[] = "SITE_ID";                //site


const char MDCS_cszCellIDName[] = "Cell";           //name to display name of cell
const char MDCS_csCellID[] = "CELL_ID";                //cell

}
#endif //__cplusplus

#endif //RC_INVOKED


#endif 
