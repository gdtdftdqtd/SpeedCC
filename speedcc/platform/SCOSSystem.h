//



#ifndef __SC__SCOSSYSTEM_H__
#define __SC__SCOSSYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    ///-------- datetime
    int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    int scGetWeekName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    
    ///-------- system
    // 0: unknown; 1: portrait; 2: portrait upside down;
    // 3: landscape right; 4: landscape left
    int scGetDeviceOrientation();
    void scInitSpeedCC(void* pController);
    void scGetScreenSize(float* pWidth, float* pHeight);
    bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal);
    bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix);
    // OS type. 0: unknown; 1: iOS; 2: Android
    // OS distribution. 0: unkown; 1: offical;
    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle;
    // store type. 0:unkown; 1: apple app store; 2: google play; 3: amazon;
    bool scGetDeviceInfo(int* pOSMainType,
                         int* pOSDistributionType,
                         int* pDeviceType,
                         int* pIsSimulator,
                         int* pStoreType,
                         char* pszHwBuffer,
                         const int nHwBufferSize);
    void scSetMultipleTouch(const bool bEnable);
    bool scGetMultipleTouch();
    void scShowSystemAlertBox(const char* pszTitle,
                              const char* pszMessge,
                              const char* pszButton1,
                              const char* pszButton2,
                              const char* pszButton3,
                              const int nAlertBoxID);
    
    ///-------- app
    int scGetProductName(char* pszBuffer, int nBufferSize);
    bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix);
    int scGetBundleID(char* pszBuffer, int nBufferSize);
    
    ///-------- store
    // callback: scbPurchaseItemResult() 
    bool scStorePurchaseItem(const char* pszIAP,const bool bConsumable);
    // callback: scbPurchaseItemInfoResult()
    bool scStoreRequestItemInfo(char** pszIAP,const int nIAPCount);
    // callback: scbPurchaseRestoreResult()
    bool scStoreRestorePurchased();
    
    
    // network
//    bool scIsInternetAvailable(bool bAlert);
//    void scCheckInternetAvailable();
//    void scOpenURL(const char *pszUrl);
//    void scNavigateToApp(const unsigned int uAppID);
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // __SC__SCOSSYSTEM_H__
