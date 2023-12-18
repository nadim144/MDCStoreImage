//***********************************************************************************************
//
//    Copyright (c) 2005 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  MDCSEnums.h
// PURPOSE: 
// AUTHOR:  MS  Jan 2005
// describe enums that are used in MDCStoreUtils 

#if !defined(AFX_MDCSENUMS_H_INCLUDED)
#define AFX_MDCSENUMS_H_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef RC_INVOKED

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
// common enums
//////////////////////////////////////////////////////////////////////////////////

// Type of database server
enum MDCS_E_SQLServerType
{
    MDCS_eSrvTypeUnknown,    //unknown server 
    MDCS_eSrvTypeSQL,        //Microsoft SQL Server editions
    MDCS_eSrvTypeOracle,     //Oracle database server
    MDCS_eSrvTypePostgre,    //PostgreSQL (not fully supported at this time)
};

// Version of the database server
enum MDCS_E_SQLServerVersion
{
   MDCS_eSrvVerTypeUnknown = 0,    //unknown version
   MDCS_eSrvVerTypeSQL8 = 1,       //MS SQL Server 2000 
   MDCS_eSrvVerTypeSQL9 = 2,       //MS SQL Server 2005 
   MDCS_eSrvVerTypePostg7 = 3,     //postgreSQL version 7
   MDCS_eSrvVerTypePostg8 = 4,     //postgreSQL version 8
   MDCS_eSrvVerTypeOracle = 5,     //oracle
};


// Type of object in the database
enum MDCS_E_DBObjectType
{
    MDCS_eDBObjTypeUnknown,              //unknown object type
    MDCS_eDBObjTypeResultset,            //resultsets 
};

// The location where files should be stored
enum  MDCS_E_FileStorage
{
   MDCS_eDatabaseServer = 0,       // Save the file in the database server
   MDCS_eFileServer     = 1,           // Save the file in the FileServer 
                              // N.B.  Requires a running instance of the file server.
                              //       The database server still contains the information about the file (i.e. Date, time, size etc)
                              //       , it just doesn't contain the binary. 
   MDCS_eUNCServer =2

};

////////////////////////////////
//enums that describes ratio types
enum  MDCS_E_RatioType
{
   MDCS_eRatioTypeUnknown = 0,            //type unknown
   MDCS_eRatioTypeRatioOfMedians = 8,     //ratio of medians
   MDCS_eRatioTypeRatioOfMeans = 9,       //ratio of means
   MDCS_eRatioTypeMedianOfRatios = 10,    //median of ratios
   MDCS_eRatioTypeMeanOfRatios = 11,      //mean of ratios
   MDCS_eRatioTypeRegressionRatio = 12,   //regression ratio
};


////////////////////////////////
//enums that describes ratio types
enum  MDCS_E_Waves
{
   MDCS_eWaveUnknown = 0,
   MDCS_eWave1 = 3,
   MDCS_eWave2 = 4,
   MDCS_eWave3 = 5,
   MDCS_eWave4 = 6,
};


////////////////////////////////
//enums that describes normalization types
enum  MDCS_E_NormalizationType
{  
   MDCS_eNormTypeUnknown = 0,
   MDCS_eNormTypeRatio = 16,
   MDCS_eNormTypeLogRatio = 17,
   MDCS_eNormTypeWavelength = 18,
};

////////////////////////////////
//enums that describes data average types
enum  MDCS_E_AverageType
{
   MDCS_eAverageTypeUnknown = 0,
   MDCS_eAverageTypeMinimum = 0,    //average will be calculated as a minimum of a group 
   MDCS_eAverageTypeLog = 1,        //average will be calcualted as a log 
   MDCS_eAverageTypeSQRT = 2,       //average will be calcualted as a SQRT 
   MDCS_eAverageTypeMean = 3,       //average will be calcualted as a Mean
   
};


// definition of the enum that describes column types
typedef enum  MDCS_E_ColumnType
{
   MDCS_eColumnTypeString = 0,      //column conatins characters
   MDCS_eColumnTypeFloat = 1,       //data is float   
   MDCS_eColumnTypeInt  = 2,        //data is integer
   MDCS_eColumnTypeBinary = 3,      //data is binary
   MDCS_eColumnTypeDateTime = 4,    //data is date\time
   MDCS_eColumnTypeDate = 5,        //data is date
} MDCS_E_ColumnType; 

/////////////////////////////////
//enum that describes image types
enum  MDCS_E_ImageType
{
   MDCS_eImageTypeUnknown = 0,      //unknown
   MDCS_eImageTypeTiff = 1,         //tiff files
   MDCS_eImageTypeJpeg = 2,         //jpeg files
   MDCS_eImageTypeBMP = 3,          //bmp files
};

////////////////////////////////
//enums that describes data average types
enum  MDCS_E_BlobType
{
   MDCS_eBlobMicImage = 0,	    //microarray image
   MDCS_eBlobMicObject = 1,     //microarray object
   MDCS_eBlobDSetObject = 2,    //dataset object
   MDCS_eBlobDSetAnalysis = 3,  //dataset analysis
   MDCS_eBlobAssay = 4,         //assay data
   MDCS_eBlobAssaySettings = 5, //assay settings
   MDCS_eBlobPlateObj = 6,		//plate object
   MDCS_eBlobSiteImage = 7,     //image of a site
   MDCS_eBlobCollectObject = 8, //collection object
   MDCS_eBlobAssayProfile = 9,         //assay profile data
   MDCS_eBlobAssayProfileSettings = 10, //assay profile settings
   MDCS_eBlobSiteImageThumb   = 11,    //site image thumbnail
   MDCS_eBlobPlateImageThumb = 12,       //plate image thumbnail
   MDCS_eBlobAcqProfile = 13,       //acquiszition profile
   MDCS_eBlobAcqInstance = 14,      //acquisition settings
   MDCS_eBlobFilesData = 15,        //files
   MDCS_eBlobGroupMacros = 16,      //group macros
   MDCS_eBlobNormSettings = 17,     // normalization settings
   MDCS_eBlobPlateTempl = 18,     // plate template
   MDCS_eBlobArchive = 19,       // archive description 
};
//Keep track size of enum
const int nBlobTypeEnumSize = 20;
//enum that describe the location source type   
enum MDCS_E_LocationFilter
{
	MDCS_ePlates = 0,     //use when user want to select plates
	MDCS_eServerName = 1, //File location - use server name 
	MDCS_eServerRoot = 2, //File location - use Server root
	MDCS_eDirectory = 3   //File location - use server dir
};

////////////////////////////////
//enums that describes shapes
enum  MDCS_E_ShapeType 
{  
   MDCS_eShape_Undefined = -1, //underfined 
   //All modules
   MDCS_eShape_Cell_Area = 0,   //reserved for the area owned by a cell
   //Angiogenesis
   MDCS_eShape_Angiogenesis_Nodes = 1,
   MDCS_eShape_Angiogenesis_Tubules = 2,
   //Cell Health
   MDCS_eShape_Viable_Nuclei = 3,
   MDCS_eShape_Early_Apoptotic_Nuclei = 4,
   MDCS_eShape_Late_Apoptotic_Nuclei = 5,
   MDCS_eShape_Necrotic_Nuclei = 6,
   //Cell scoring
   MDCS_eShape_Negative_Nuclei = 7,
   MDCS_eShape_Positive_Nuclei = 8,
   MDCS_eShape_Positive_Cytoplasm = 9,
   //Count Nuclei:
   MDCS_eShape_Nuclei = 10,
   //GPCR Cycling:
   //Nuclei - uses earlier def
   MDCS_eShape_Pits = 11,
   MDCS_eShape_Vesicles = 12,
   //Granularity:
   //Nuclei - uses earlier def
   MDCS_eShape_Granules = 13,
   //Live Dead:
   MDCS_eShape_Live = 14,
   MDCS_eShape_Dead = 15,
   //Mitotic Index: 
   MDCS_eShape_Interphase_Nuclei = 16,
   MDCS_eShape_Mitotic_Nuclei = 17,
   //Neurite Outgrowth:
   //Nuclei - uses earlier def
   MDCS_eShape_Cell_Bodies_and_Outgrowths = 18,
   //Translocation and Translocation-Enhanced:
   MDCS_eShape_Negative_Inner_Region = 19,
   MDCS_eShape_Positive_Inner_Region = 20,
   MDCS_eShape_Negative_Outer_Region = 21,
   MDCS_eShape_Positive_Outer_Region = 22,
   //Monopole Detection:
   MDCS_eShape_Interphase_Cells = 23,
   MDCS_eShape_Bipoles = 24,
   MDCS_eShape_Monopoles = 25,
   //Cell Cycle:
   MDCS_eShape_G0G1_Cells = 26,
   MDCS_eShape_S_Phase_Cells = 27,
   MDCS_eShape_G2_Cells = 28,
   MDCS_eShape_Early_M_Cells = 29,
   MDCS_eShape_Late_M_Cells = 30,
   MDCS_eShape_Apoptotic_Cells = 31, 

   // micro nuclei:
   MDCS_eShape_Micro_Nuclei = 32, 
   MDCS_eShape_Cytoplasm = 33, 
   MDCS_eShape_Multinucleated = 34, 
   //MDCS_eShape_Multinucleated_Cyto = 35, 
   //MDCS_eShape_Dead_Nuclei = 36, 
   //MDCS_eShape_Dead_Cyto = 37, 
   MDCS_eShape_Apoptotic_Nuclei = 35, 
   //MDCS_eShape_Necrotic_Nuclei = 36, 
   MDCS_eShape_ProbeAB_Positive = 37,
   MDCS_eShape_Binucleated = 38,
   MDCS_eShape_Mononucleated = 39,
   MDCS_eShape_ProbeA_Positive = 40,
   MDCS_eShape_ProbeB_Positive = 41,
};

/////////////////////////////////////
//enums that describe attribute types
enum  MDCS_E_AttributeType
{
   MDCS_eAttrTypeAppDefined = 0,    // pre-defined type of the attribute, cannot be changed
   MDCS_eAttrTypeUserDefined = 1,    // user-defined type of the attribute
};
/*
//////////////////////////////////
//enums for statistical types
enum  MDSC_E_StatisticType
{
    MDSC_eStatMean = 0,
    MDSC_eStatMedian = 1,
    MDSC_eStatSD = 2,
    MDSC_eStatCD = 3,
    MDSC_eStatReplicates = 4,
    MDSC_eStatMin = 5,
    MDSC_eStatMax = 6,
    MDSC_eStatMaxMinusMin = 7,
    MDSC_eStatSE = 8,
    MDSC_eStatMAD = 9,
};
*/
//////////////////////////////////
//enums for statistical types
enum  MDSC_E_CollapseType
{
   MDCS_eCollapseType = -1,      //collapse column
   MDCS_eDataType = 0,
   MDCS_eDataPivot = 1,
};

/////////////////////////////////////
//enums that describe user status to access data 
enum  MDCS_E_UserStatus
{
   MDCS_eUserStatusReadOnly = 21,      //user has read-only permissions
   MDCS_eUserStatusReadWrite = 22,     //user has read-write permissions
   MDCS_eUserStatusLabHead = 23,       //user is lab head
};
/////////////////////////////////////
//enums that describe types of the groups
enum  MDSC_E_GroupType
{
   MDCS_eGroupTypeNormal = 0,       //normal group
   MDCS_eGroupTypeUser = 1,         //group that was created as user 
};

/////////////////////////////////////
//enums that describe access permissions to data
enum  MDCS_E_AccessPermissions
{
   MDCS_eAccessReadOnly = 21,      //read-only permissions
   MDCS_eAccessReadWrite= 22,     //read-write permissions
};


/////////////////////////////////////
//enums that describe access permissions to plate
enum  MDCS_E_ObjAccessPermissions
{
   MDCS_eObjAccessReadOnly = 21,      //read-only permissions
   MDCS_eObjAccessReadWrite= 22,     //read-write permissions
   MDCS_eObjAccessLabHead = 23,       //lab head permissions, can change plate permissions
};

//////////////////////////////
//enums that describe availble comparission operations
enum  MDCS_E_CompareOperation 
{
   MDCS_eOperEqual = 0,             //operation equal ( = ) 
   MDCS_eOperGreaterOrEqual = 1,    //operation greater or equal ( >= ) 
   MDCS_eOperGreater = 2,           //operation greater (>)
   MDCS_eOperLess =3,               //operation less (<)
   MDCS_eOperLessOrEqual = 4,       //operation less or equal (<=)
   MDCS_eOperNotEqual = 5,          //operation not equal (<> or !=)
};

//////////////////////////////
//enums that describes dataset types
enum  MDCS_E_DatasetType
{
   MDCS_eDSMeasuresets = 0,
   MDCS_eDSMeasuresetsAndSelection = 1,
   MDCS_eDSFile = 4,
   MDCS_eDSFileAndSelection = 5,
   MDCS_eDSWizard = 6,
   MDCS_eDSWizardAndSelection = 7,
   MDCS_eDSQueryBuilder = 8, 
   MDCS_eDSQueryBuilderImage = 9,
}; 

//enums that describe defined statistical methods 
enum  MDCS_E_Statistic
{
   MDCS_eStatisticAvg = 0,
   MDCS_eStatisticMin = 1,
   MDCS_eStatisticMax = 2,
   MDCS_eStatisticSum = 3,
   MDCS_eStatisticCount = 4,
   MDCS_eStatisticStdDev = 5,
   MDCS_eStatisticVariance = 6,
   MDCS_eStatisticNone = 7,
   MDCS_eStatisticCountDistinct = 8, 
   MDCS_eStatisticMaxMinusMin = 9, 
   MDCS_eStatisticMedian = 10,
};

//enums that describe defined statistical methods 
enum  MDCS_E_UserDataLocationOptions
{
   MDCS_eUserDataOptionDefault = 0,
};

//////////////////////////////////
//enum that describes types of the dialog to manage users
enum  MDCS_ST_DlgUsersType
{
   MDCS_eDlgUsersSimple = 0,
   MDCS_eDlgUsersWithStorage = 1,
} ;

//describes enums for group objects
enum MDCS_E_GroupObjects
{
   MDCS_eGroupObjectMacro = 0,
};

//describes enums for group objects
enum MDCS_E_GroupObjectsType
{
   MDCS_eGroupObjectTypeUndefined = 0,
   MDCS_eGroupObjectTypeGlobalMacro = 1,
};

enum MDC_E_DatasetDependantType
{
   MDCS_eDatasetDependantNone = 0x00000000L,
   MDCS_eDatasetDependantScipts = 0x00000001L,
   MDCS_eDatasetDependantResults = 0x0000002L,
   MDCS_eDatasetDependantObjects = 0x0000004L,
   MDCS_eDatasetDependantAll = (0x00000001L | 0x0000002L | 0x0000004L),
};

//type of result data
enum  MDCS_E_DataType
{
   MDCS_eCellData = 0,
   MDCS_eWellData = 1,
};

//types of group of objects that can be used in datasets
enum MDCS_E_DSFilteringGroup
{
   MDCS_eDSFUnknown = 0,                     //used in dataset filtering
   MDCS_eDSFMeasurementDataAnnotation = 1,   //used for filtering measurement set data using compound annotations
   MDCS_eDSFMeasurementSetParams = 2,        //used to create a list of measurement sets
   MDCS_eDSFMeasurementData = 3,             //used  for filtering measurement set data 
   MDCS_ePFPlateInfo = 4,                    //used in plate filtering
};


//mesurement group by variations
enum MDCS_E_MeasurementGroupBy
{
   MDCS_eMGBId = 0,              //unique objects
   MDCS_eMGBWell = 1,            //wells
   MDCS_eMGBSite = 2,            //sites
   MDCS_eMGBCompound = 3,        //compounds
   MDCS_eMGBCellIDs = 4,         //all cells 
}; 

//mesurement group by variations
enum MDCS_E_PlateElements
{
   MDCS_ePElWell = 0,            //wells
   MDCS_ePElSite = 1,            //sites
   MDCS_ePElSeries = 2,          //series
   MDCS_ePElCompound = 3,        //compounds
   MDCS_eMGBControls = 4,        //controls 
}; 

//type of normalization configuration
enum MDCS_E_NormConfigType
{
   MDCS_eNormConfUnknown = 0,    //unknown
};
//type of query builder
enum MDCS_QueryBldType
{
  MDCS_eQBTUnknown = -1,
  MDCS_eQBTDataset = 0, 
  MDCS_eQBTPlate = 1,
  MDCS_eQBTDatasetImage = 2, 
};

//type of assay marks
enum MDCS_E_AssayMarkStatus
{    
   eMarkNormal = 0,
   eMarkCanBeRestored = 1,
   eMarkRemove = 2,
   eAllMarkType = 3
};


//type of assay marks
enum MDCS_E_MarkStatus
{    
   eMSNormal = 0,
   eMSDeletion = 1,
   eMSRemove = 2,
   eMSAll = 3,
   eMSArchive = 4,
   eMSBackup = 5,
};

//type of MDCStoreTools archive type
enum MDCS_E_ArchiveType
{
   MDCS_Unknown = 0,
   MDCS_eArchive = 1,    
   MDCS_eBackup = 2    
};

//type Archive Enum
enum MDCS_E_ArchiveRestoreType
{
   MDCS_eRestore = 0,
   MDCS_eAttach  = 1
};

// enum identifies environment to run jobs
enum  MDCS_E_JobEnvType
{
   MDCS_eJETAll = 0,       // all or unknown
   MDCS_eJETMX  = 1,      // MX only
};

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //RC_INVOKED

#endif 
