//



#ifndef __SC__OSSYSTEM_H__
#define __SC__OSSYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    // datetime
    int fsosGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    int fsosGetWeekName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort);
    
    void fsxSetupCallbackFunc();
    
#ifdef __cplusplus
}
#endif  // __cplusplus

#endif // __SC__OSSYSTEM_H__
