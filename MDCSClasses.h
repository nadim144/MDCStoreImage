//***********************************************************************************************
//
//    Copyright (c) 2007 Axon Instruments.
//    All rights reserved.
//
//***********************************************************************************************
// MODULE:  MDCSClasses.h
// PURPOSE: 
// AUTHOR:  MS  Mar 2007
// container for virtual classes used in MDCStore space

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

//////////////////////////////////////////////////////////////////////////////
// MDCS_ProgressCallback
// 
class MDCS_ProgressCallback
{
public:
   MDCS_ProgressCallback() {};
   virtual ~MDCS_ProgressCallback() {};

   // Returning FALSE cancels the progress
   // nPercentDone - between 0 and 100
   // pProgressText - string telling what is being done
   // bComplete - TRUE if 100% is really 100%
   virtual BOOL Progress(int nPercentDone, LPCSTR pProgressText, BOOL bComplete)=0;
   
   // called when completely done
   virtual void Done()=0;

   // sent when there is an error
   //if bWithContinue is TRUE, error is not critical and process can be continued
   //if function return FALSE, then exist - true continue
   virtual BOOL Error(LPCSTR pErrorText, BOOL bWithContinue = FALSE)=0;

private:
   // hide the default copy constructors
   MDCS_ProgressCallback(MDCS_ProgressCallback const &);
   const MDCS_ProgressCallback &operator=(MDCS_ProgressCallback const &);      
};

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //RC_INVOKED
