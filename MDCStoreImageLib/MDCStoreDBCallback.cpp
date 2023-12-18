#include "stdafx.h"
#include "MDCStoreUtilsApi.h"

HDBHANDLE WINAPI MDCS_GETDB_Handle(const MDCS_ST_UserLogin &stUserLogin)
{
	//ExecMain(strConnectString, lPlateID);
	 //get database handle 
	MDCS_DBHandleSmartPtr ptrDB(stUserLogin);

	HDBHANDLE _DBHandle = ptrDB.GetHandle();
	//check if we got a valid connection
	/*if (ptrDB.GetHandle())
	{
		_DBHandle = &ptrDB;
	}*/
	return _DBHandle;
}
