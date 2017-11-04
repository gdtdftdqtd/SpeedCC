

#include "SCVersion.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    SCVersion::SCVersion():
    _nMajor(0),
    _nMinor(0),
    _nFix(0)
    {}
    
    SCVersion::SCVersion(const SCVersion& info)
    {
        memcpy(this,&info,sizeof(*this));
    }
    
    SCVersion::SCVersion(const char* pszVersion)
    {
        SCASSERT(pszVersion!=NULL);
        this->setString(pszVersion);
    }
    
    SCVersion::SCVersion(const SCString& str)
    {
        this->setString(str);
    }
    
    SCVersion::SCVersion(unsigned uVersion)
    {
        _nMajor = (uVersion&0x00ff0000) >> 16;
        _nMinor = (uVersion&0x0000ff00) >> 8;
        _nFix = uVersion&0x000000ff;
    }
    
    SCString SCVersion::SCVersion::getString(int nBit) const
    {
        switch(nBit)
        {
            default:
            case 3: return SCString(0,"%d.%d.%d",_nMajor,_nMinor,_nFix);
            case 2: return SCString(0,"%d.%d",_nMajor,_nMinor);
            case 1: return _nMajor;
        }
    }
    
    unsigned SCVersion::getHexValue(int nBit) const
    {
        switch(nBit)
        {
            default:
            case 3: return ((_nMajor<<16) | (_nMinor<<8) | _nFix);
            case 2: return (_nMajor<<16 | _nMinor<<8);
            case 1: return _nMajor<<16;
        }
    }
    
    int SCVersion::compare(const SCVersion& info) const
    {
        int nRet = 0;
        
        do
        {
            nRet = 1;
            SC_BREAK_IF(_nMajor>info._nMajor);
            nRet = -1;
            SC_BREAK_IF(_nMajor<info._nMajor);
            
            nRet = 1;
            SC_BREAK_IF(_nMinor>info._nMinor);
            nRet = -1;
            SC_BREAK_IF(_nMinor<info._nMinor);
            
            nRet = 1;
            SC_BREAK_IF(_nFix>info._nFix);
            nRet = -1;
            SC_BREAK_IF(_nFix<info._nFix);
            
            nRet = 0;
        }
        while(0);
        
        return nRet;
    }
    
    bool SCVersion::operator<(const SCVersion& info) const
    {
        return this->compare(info)<0;
    }
    
    bool SCVersion::operator<=(const SCVersion& info) const
    {
        return this->compare(info)<=0;
    }
    
    bool SCVersion::operator>(const SCVersion& info) const
    {
        return this->compare(info)>0;
    }
    
    bool SCVersion::operator>=(const SCVersion& info) const
    {
        return this->compare(info)>=0;
    }
    
    bool SCVersion::operator==(const SCVersion& info) const
    {
        return this->compare(info)==0;
    }
    
    void SCVersion::setString(const SCString& strVersion)
    {
        memset(this,0,sizeof(*this));
        
        std::vector<SCString> strVor = strVersion.split(".");
        
        switch(strVor.size())
        {
            case 3:
                _nMajor = strVor[0].asInt(false,0);
                _nMinor = strVor[1].asInt(false,0);
                _nFix = strVor[2].asInt(false,0);
                break;
                
            case 2:
                _nMajor = strVor[0].asInt(false,0);
                _nMinor = strVor[1].asInt(false,0);
                break;
                
            case 1:
                _nMajor = strVor[0].asInt(false,0);
                break;
                
            default: break;
        }
    }
}

