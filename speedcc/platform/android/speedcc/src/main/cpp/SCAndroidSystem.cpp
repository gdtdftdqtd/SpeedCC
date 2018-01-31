#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "../../../../../../../cocos2dx/v3/cocos/platform/android/jni/JniHelper.h"
#include <android/log.h>

#define CLASS_NAME "org/speedcc/lib"

using namespace cocos2d;

#ifdef __cplusplus
extern "C"
{
#endif  // __cplusplus


///--------- C => Java

	void scInitSpeedCC(void* pController)
	{

	}

bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix)
{
    return false;
}

bool scGetDeviceInfo(int* pOSMainType,int* pOSDistributionType,int* pDeviceType,int* pIsSimulator,char* pszHwIdenti,const int nHwIdentiSize)
{
    return false;
}

bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
{
    return false;
}

void scSetMultipleTouch(bool bEnable)
{

}

bool scGetMultipleTouch()
{
    return false;
}

void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID)
{

}

bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable)
{
	return false;
}
    // callback: scbPurchaseItemInfoResult()
    bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount)
    {
    	return false;
    }

    // callback: scbPurchaseRestoreResult()
    bool scStoreRestorePurchased()
    {
    	return false;
    }


#ifdef __cplusplus
}
#endif // __cplusplus
