
#include "SCBaseCommon.h"
#include "SCMacroDef.h"
//#include "SCBufferRefT.h"

namespace SpeedCC
{
    ///------------ SCBufferRefT
    
    //template<typename TargetClassT>
    //unsigned char	SCBufferRefT<TargetClassT>::_emptyBuf[] = {0};
    
    ///------------ SCVersionInfo
    
    SCVersionInfo::SCVersionInfo():
    nMajor(0),
    nMinor(0),
    nFix(0)
    {}
    
    SCVersionInfo::SCVersionInfo(const SCVersionInfo& info)
    {
        memcpy(this,&info,sizeof(*this));
    }
    
    SCVersionInfo::SCVersionInfo(const char* pszVersion)
    {
        SCASSERT(pszVersion!=NULL);
        this->setString(pszVersion);
    }
    
    SCVersionInfo::SCVersionInfo(const SCString& str)
    {
        this->setString(str);
    }
    
    SCVersionInfo::SCVersionInfo(unsigned uVersion)
    {
        nMajor = (uVersion&0x00ff0000) >> 16;
        nMinor = (uVersion&0x0000ff00) >> 8;
        nFix = uVersion&0x000000ff;
    }
    
    SCString SCVersionInfo::SCVersionInfo::getString(int nBit) const
    {
        switch(nBit)
        {
            default:
            case 3: return SCString(0,"%d.%d.%d",nMajor,nMinor,nFix);
            case 2: return SCString(0,"%d.%d",nMajor,nMinor);
            case 1: return nMajor;
        }
    }
    
    unsigned SCVersionInfo::getHexValue(int nBit) const
    {
        switch(nBit)
        {
            default:
            case 3: return ((nMajor<<16) | (nMinor<<8) | nFix);
            case 2: return (nMajor<<16 | nMinor<<8);
            case 1: return nMajor<<16;
        }
    }
    
    int SCVersionInfo::compare(const SCVersionInfo& info) const
    {
        int nRet = 0;
        
        do
        {
            nRet = 1;
            SC_BREAK_IF(nMajor>info.nMajor);
            nRet = -1;
            SC_BREAK_IF(nMajor<info.nMajor);
            
            nRet = 1;
            SC_BREAK_IF(nMinor>info.nMinor);
            nRet = -1;
            SC_BREAK_IF(nMinor<info.nMinor);
            
            nRet = 1;
            SC_BREAK_IF(nFix>info.nFix);
            nRet = -1;
            SC_BREAK_IF(nFix<info.nFix);
            
            nRet = 0;
        }
        while(0);
        
        return nRet;
    }
    
    bool SCVersionInfo::operator<(const SCVersionInfo& info) const
    {
        return this->compare(info)<0;
    }
    
    bool SCVersionInfo::operator<=(const SCVersionInfo& info) const
    {
        return this->compare(info)<=0;
    }
    
    bool SCVersionInfo::operator>(const SCVersionInfo& info) const
    {
        return this->compare(info)>0;
    }
    
    bool SCVersionInfo::operator>=(const SCVersionInfo& info) const
    {
        return this->compare(info)>=0;
    }
    
    bool SCVersionInfo::operator==(const SCVersionInfo& info) const
    {
        return this->compare(info)==0;
    }
    
    void SCVersionInfo::setString(const SCString& strVersion)
    {
        memset(this,0,sizeof(*this));
        
        std::vector<SCString> strVor = strVersion.split(".");
        
        switch(strVor.size())
        {
            case 3:
                nMajor = strVor[0].asInt(false,0);
                nMinor = strVor[1].asInt(false,0);
                nFix = strVor[2].asInt(false,0);
                break;
                
            case 2:
                nMajor = strVor[0].asInt(false,0);
                nMinor = strVor[1].asInt(false,0);
                break;
                
            case 1:
                nMajor = strVor[0].asInt(false,0);
                break;
                
            default: break;
        }
    }
    
    ///------------- SCParameters
    SCValue& SCParameters::operator[](const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    SCValue SCParameters::operator[](SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    void SCParameters::setValue(const SCString& strKey,const SCValue& value)
    {
        SCASSERT(!strKey.isEmpty());
        (*this->getStub())[strKey] = value;
    }
    
    SCValue SCParameters::getValue(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    bool SCParameters::hasKey(const SCString& strKey) const
    {
        SCASSERT(!strKey.isEmpty());
        const auto& it = this->getStub()->find(strKey);
        return (this->getStub()->end()!=it);
    }
    
    void SCParameters::removeKey(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        this->getStub()->erase(strKey);
    }
    
    void SCParameters::removeAllKey()
    {
        this->getStub()->clear();
    }
    
    bool SCParameters::isEmpty()
    {
        return this->getStub()->empty();
    }
}



