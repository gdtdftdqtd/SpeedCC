

#include "SCValue.h"
#include "SCDataBlock.h"
#include "SCDateTime.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    SCValue::SCValue()
    {
        this->createInstance();
        this->getCookieDesc()->cookie = UNKNOWN_TYPE;
    }
    
    SCValue::SCValue(const int nValue)
    {
        this->createInstance();
        
        this->getStub()->data.nValue = nValue;
        this->getCookieDesc()->cookie = INT_TYPE;
    }
    
    SCValue::SCValue(const bool bValue)
    {
        this->createInstance();
        
        this->getStub()->data.nValue = bValue;
        this->getCookieDesc()->cookie = BOOL_TYPE;
    }
    
    SCValue::SCValue(const float fValue)
    {
        this->createInstance();
        
        this->getStub()->data.fValue = fValue;
        this->getCookieDesc()->cookie = FLOAT_TYPE;
    }
    
    SCValue::SCValue(const double dValue)
    {
        this->createInstance();
        
        this->getStub()->data.dValue = dValue;
        this->getCookieDesc()->cookie = DOUBLE_TYPE;
    }
    
    SCValue::SCValue(const long lValue)
    {
        this->createInstance();
        
        this->getStub()->data.lValue = lValue;
        this->getCookieDesc()->cookie = LONG_TYPE;
    }
    
    SCValue::SCValue(const long long llValue)
    {
        this->createInstance();
        
        this->getStub()->data.llValue = llValue;
        this->getCookieDesc()->cookie = LONGLONG_TYPE;
    }
    
    SCValue::SCValue(void* const pValue)
    {
        this->createInstance();
        
        this->getStub()->data.pValue = pValue;
        this->getCookieDesc()->cookie = POINTER_TYPE;
    }
    
    SCValue::SCValue(const char* pszValue)
    {
        this->setString(pszValue);
    }
    
    SCValue::SCValue(const SCString& strValue)
    {
        this->setString(strValue);
    }
    
    SCValue::SCValue(SCDateTime& dateTime)
    {
        this->setDateTime(dateTime);
    }
    
    SCValue::SCValue(const SCDataBlock& dataBlock)
    {
        this->setDataBlock(dataBlock);
    }
    
    SCValue::SCValue(const std::vector<SCValue>& valueVtr)
    {
        this->setArray(valueVtr);
    }
    
    SCValue::~SCValue()
    {
    }
    
    void SCValue::check4Write()
    {
        SC_RETURN_IF_V(this->getRefCount()!=1);
        
        switch(this->getType())
        {
            case STRING_TYPE:
            case DATETIME_TYPE:
            case DATABLOCK_TYPE:
            case ARRAY_TYPE:
            case OBJECT_TYPE:
            {
                this->decreaseRef(); // cause to free buffer and destroy object
                this->createInstance();
            }
                break;
                
            default:break;
        }
    }
    
    char SCValue::getChar(bool* pResult,const bool bExactMatch) const
    {
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        bool bResult = false;
        char cRet = 0;
        if(!(bExactMatch && type!=CHAR_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: cRet = (char)data.nValue; break;
                case BTYE_TYPE: cRet = (char)data.byValue; break;
                case CHAR_TYPE: cRet = data.cValue; break;
                case UINT_TYPE: cRet = (char)data.uValue; break;
                case LONG_TYPE: cRet = (char)data.lValue; break;
                case LONGLONG_TYPE: cRet = (char)data.llValue; break;
                case FLOAT_TYPE: cRet = (char)data.fValue; break;
                case DOUBLE_TYPE: cRet = (char)data.dValue; break;
                case POINTER_TYPE: cRet = (char)(long)data.pValue; break;
                case BOOL_TYPE: cRet = data.bValue ? 1 : 0; break;
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return cRet;
    }
    
    unsigned char SCValue::getByte(bool* pResult,const bool bExactMatch) const
    {
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        bool bResult = false;
        unsigned char byRet = 0;
        if(!(bExactMatch && type!=BTYE_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: byRet = (unsigned char)data.nValue; break;
                case BTYE_TYPE: byRet = data.byValue; break;
                case CHAR_TYPE: byRet = (unsigned char)data.cValue; break;
                case UINT_TYPE: byRet = (unsigned char)data.uValue; break;
                case LONG_TYPE: byRet = (unsigned char)data.lValue; break;
                case LONGLONG_TYPE: byRet = (unsigned char)data.llValue; break;
                case FLOAT_TYPE: byRet = (unsigned char)data.fValue; break;
                case DOUBLE_TYPE: byRet = (unsigned char)data.dValue; break;
                case POINTER_TYPE: byRet = (unsigned char)(long)data.pValue; break;
                case BOOL_TYPE: byRet = data.bValue ? 1 : 0; break;
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return byRet;
    }
    
    unsigned int SCValue::getUnsignedInt(bool* pResult,const bool bExactMatch) const
    {
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        bool bResult = false;
        unsigned int uRet = 0;
        if(!(bExactMatch && type!=UINT_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: uRet = (unsigned int)data.nValue; break;
                case BTYE_TYPE: uRet = (unsigned int)data.byValue; break;
                case CHAR_TYPE: uRet = (unsigned int)data.cValue; break;
                case UINT_TYPE: uRet = data.uValue; break;
                case LONG_TYPE: uRet = (unsigned int)data.lValue; break;
                case LONGLONG_TYPE: uRet = (unsigned int)data.llValue; break;
                case FLOAT_TYPE: uRet = (unsigned int)data.fValue; break;
                case DOUBLE_TYPE: uRet = (unsigned int)data.dValue; break;
                case POINTER_TYPE: uRet = (unsigned int)(long)data.pValue; break;
                case BOOL_TYPE: uRet = data.bValue ? 1 : 0; break;
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return uRet;
    }
    
    int SCValue::getInt(bool* pResult,const bool bExactMatch) const
    {
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        bool bResult = false;
        int nRet = 0;
        if(!(bExactMatch && type!=INT_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: nRet = data.nValue; break;
                case BTYE_TYPE: nRet = (int)data.byValue; break;
                case CHAR_TYPE: nRet = (int)data.cValue; break;
                case UINT_TYPE: nRet = (int)data.uValue; break;
                case LONG_TYPE: nRet = (int)data.lValue; break;
                case LONGLONG_TYPE: nRet = (int)data.llValue; break;
                case FLOAT_TYPE: nRet = (int)data.fValue; break;
                case DOUBLE_TYPE: nRet = (int)data.dValue; break;
                case POINTER_TYPE: nRet = (int)(long)data.pValue; break;
                case BOOL_TYPE: nRet = data.bValue ? 1 : 0; break;
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return nRet;
    }
    
    long SCValue::getLong(bool* pResult,const bool bExactMatch) const
    {
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        bool bResult = false;
        long lRet = 0;
        if(!(bExactMatch && type!=LONG_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: lRet = (long)data.nValue; break;
                case BTYE_TYPE: lRet = (long)data.byValue; break;
                case CHAR_TYPE: lRet = (long)data.cValue; break;
                case UINT_TYPE: lRet = (long)data.uValue; break;
                case LONG_TYPE: lRet = data.lValue; break;
                case LONGLONG_TYPE: lRet = (long)data.llValue; break;
                case FLOAT_TYPE: lRet = (long)data.fValue; break;
                case DOUBLE_TYPE: lRet = (long)data.dValue; break;
                case POINTER_TYPE: lRet = (long)data.pValue; break;
                case BOOL_TYPE: lRet = data.bValue ? 1 : 0; break;
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return lRet;
    }
    
    bool SCValue::getBool(bool* pResult,const bool bExactMatch) const
    {
        bool bRet = 0;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=BOOL_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: bRet = (data.nValue!=0); break;
                case BTYE_TYPE: bRet = (data.byValue!=0); break;
                case CHAR_TYPE: bRet = (data.cValue!=0); break;
                case UINT_TYPE: bRet = (data.uValue!=0); break;
                case LONG_TYPE: bRet = (data.lValue!=0); break;
                case LONGLONG_TYPE: bRet = (data.llValue!=0); break;
                case FLOAT_TYPE: bRet = (data.fValue!=0.0f); break;
                case DOUBLE_TYPE: bRet = (data.dValue!=0.0); break;
                case POINTER_TYPE: bRet = (data.pValue!=NULL); break;
                case BOOL_TYPE: bRet = data.bValue ; break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return bRet;
    }
    
    float SCValue::getFloat(bool* pResult,const bool bExactMatch) const
    {
        float fRet = 0;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=FLOAT_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: fRet = (float)data.nValue; break;
                case BTYE_TYPE: fRet = (float)data.byValue; break;
                case CHAR_TYPE: fRet = (float)data.cValue; break;
                case UINT_TYPE: fRet = (float)data.uValue; break;
                case LONG_TYPE: fRet = (float)data.lValue; break;
                case LONGLONG_TYPE: fRet = (float)data.llValue; break;
                case FLOAT_TYPE: fRet = data.fValue; break;
                case DOUBLE_TYPE: fRet = (float)data.dValue; break;
                case POINTER_TYPE: fRet = (float)(long)data.pValue; break;
                case BOOL_TYPE: fRet = data.bValue ? 1 : 0; break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return fRet;
    }
    
    double SCValue::getDouble(bool* pResult,const bool bExactMatch) const
    {
        double dRet = 0;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=DOUBLE_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: dRet = (double)data.nValue; break;
                case BTYE_TYPE: dRet = (double)data.byValue; break;
                case CHAR_TYPE: dRet = (double)data.cValue; break;
                case UINT_TYPE: dRet = (double)data.uValue; break;
                case LONG_TYPE: dRet = (double)data.lValue; break;
                case LONGLONG_TYPE: dRet = (double)data.llValue; break;
                case FLOAT_TYPE: dRet = (double)data.fValue; break;
                case DOUBLE_TYPE: dRet = data.dValue; break;
                case POINTER_TYPE: dRet = (double)(long)data.pValue; break;
                case BOOL_TYPE: dRet = data.bValue ? 1 : 0; break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return dRet;
    }
    
    void* SCValue::getPointer(bool* pResult,const bool bExactMatch) const
    {
        void* pRet = 0;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=POINTER_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: pRet = (void*)(long)data.nValue; break;
                case BTYE_TYPE: pRet = (void*)(long)data.byValue; break;
                case CHAR_TYPE: pRet = (void*)(long)data.cValue; break;
                case UINT_TYPE: pRet = (void*)(long)data.uValue; break;
                case LONG_TYPE: pRet = (void*)data.lValue; break;
                case LONGLONG_TYPE: pRet = (void*)data.llValue; break;
                case FLOAT_TYPE: pRet = (void*)(long)data.fValue; break;
                case DOUBLE_TYPE: pRet = (void*)(long)data.dValue; break;
                case POINTER_TYPE: pRet = data.pValue; break;
                case BOOL_TYPE: pRet = (void*)(long)(data.bValue ? 1 : 0); break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return pRet;
    }
    
    long long SCValue::getLongLong(bool* pResult,const bool bExactMatch) const
    {
        long long llRet = 0;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=LONGLONG_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: llRet = (long long)data.nValue; break;
                case BTYE_TYPE: llRet = (long long)data.byValue; break;
                case CHAR_TYPE: llRet = (long long)data.cValue; break;
                case UINT_TYPE: llRet = (long long)data.uValue; break;
                case LONG_TYPE: llRet = (long long)data.lValue; break;
                case LONGLONG_TYPE: llRet = data.llValue; break;
                case FLOAT_TYPE: llRet = (long long)data.fValue; break;
                case DOUBLE_TYPE: llRet = (long long)data.dValue; break;
                case POINTER_TYPE: llRet = (long long)data.pValue; break;
                case BOOL_TYPE: llRet = data.bValue ? 1 : 0; break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return llRet;
    }
    
    SCDataBlock SCValue::getDataBlock(bool* pResult,const bool bExactMatch) const
    {
        SCDataBlock dbRet;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=DATABLOCK_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: dbRet.append(&data.nValue, sizeof(data.nValue)); break;
                case BTYE_TYPE: dbRet.append(&data.byValue, sizeof(data.byValue)); break;
                case CHAR_TYPE: dbRet.append(&data.cValue, sizeof(data.cValue)); break;
                case UINT_TYPE: dbRet.append(&data.uValue, sizeof(data.uValue)); break;
                case LONG_TYPE: dbRet.append(&data.lValue, sizeof(data.lValue)); break;
                case LONGLONG_TYPE: dbRet.append(&data.llValue, sizeof(data.llValue)); break;
                case FLOAT_TYPE: dbRet.append(&data.fValue, sizeof(data.fValue)); break;
                case DOUBLE_TYPE: dbRet.append(&data.dValue, sizeof(data.dValue)); break;
                case POINTER_TYPE: dbRet.append(&data.pValue, sizeof(data.pValue)); break;
                case BOOL_TYPE: dbRet.append(&data.bValue, sizeof(data.bValue)); break;
                case DATABLOCK_TYPE: dbRet = *((SCDataBlock*)data.pObject); break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return dbRet;
    }
    
    SCString SCValue::getString(bool* pResult,const bool bExactMatch) const
    {
        SCString strRet;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=STRING_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case INT_TYPE: strRet.format("%d",data.nValue); break;
                case BTYE_TYPE: strRet.format("%d",data.byValue); break;
                case CHAR_TYPE: strRet.format("%c",data.cValue); break;
                case UINT_TYPE: strRet.format("%u",data.uValue); break;
                case LONG_TYPE: strRet.format("%d",data.lValue); break;
                case LONGLONG_TYPE: strRet.format("%lld",data.llValue); break;
                case FLOAT_TYPE: strRet.format("%f",data.fValue); break;
                case DOUBLE_TYPE: strRet.format("%f",data.dValue); break;
                case POINTER_TYPE: strRet.format("%p",data.pValue); break;
                case BOOL_TYPE: strRet.format("%s",data.bValue ? "true" : "false"); break;
                case STRING_TYPE: strRet = *((SCString*)data.pObject); break;
                    
                default:bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return strRet;
    }
    
    SCDateTime SCValue::getDateTime(bool* pResult,const bool bExactMatch) const
    {
        SCDateTime dtRet;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=DATETIME_TYPE))
        {
            bResult = true;
            switch(type)
            {
                case STRING_TYPE: dtRet = SCDateTime(*((SCString*)data.pObject)); break;
                case INT_TYPE: dtRet = SCDateTime(data.nValue); break;
                case BTYE_TYPE: dtRet = SCDateTime(data.byValue); break;
                case CHAR_TYPE: dtRet = SCDateTime(data.cValue); break;
                case UINT_TYPE: dtRet = SCDateTime(data.uValue); break;
                case LONG_TYPE: dtRet = SCDateTime(data.lValue); break;
                case LONGLONG_TYPE: dtRet = SCDateTime(data.llValue); break;
                    
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return dtRet;
    }
    
    std::vector<SCValue> SCValue::getArray(bool* pResult,const bool bExactMatch) const
    {
        std::vector<SCValue> retVtr;
        bool bResult = false;
        
        const auto& type = this->getType();
        const auto& data = this->getStub()->data;
        
        if(!(bExactMatch && type!=DATETIME_TYPE))
        {
            bResult = true;
            SCValue value;
            switch(type)
            {
                case INT_TYPE: value = data.nValue; break;
                case BTYE_TYPE: value = data.byValue; break;
                case CHAR_TYPE: value = data.cValue; break;
                case UINT_TYPE: value = data.uValue; break;
                case LONG_TYPE: value = data.lValue; break;
                case LONGLONG_TYPE: value = data.llValue; break;
                case BOOL_TYPE: value = data.bValue; break;
                case FLOAT_TYPE: value = data.fValue; break;
                case DOUBLE_TYPE: value = data.dValue; break;
                case POINTER_TYPE: value = data.pValue; break;
                case STRING_TYPE: value = *((SCString*)data.pObject); break;
                case DATETIME_TYPE: value = *((SCDateTime*)data.pObject); break;
                case DATABLOCK_TYPE: value = *((SCDataBlock*)data.pObject); break;
                case ARRAY_TYPE: value = *((std::vector<SCValue>*)data.pObject); break;
                    
                default: bResult = false; break;
            }
        }
        
        if(pResult!=NULL)
        {
            *pResult = bResult;
        }
        
        return retVtr;
    }
    
    /*
    bool SCValue::getInt(int& nValue) const
    {
        SC_RETURN_IF(this->getType()!=INT_TYPE, false);
        nValue = this->getStub()->data.nValue;
        return true;
    }
    
    bool SCValue::getLong(long& lValue) const
    {
        SC_RETURN_IF(this->getType()!=LONG_TYPE, false);
        lValue = this->getStub()->data.lValue;
        return true;
    }
    
    bool SCValue::getBool(bool& bValue) const
    {
        SC_RETURN_IF(this->getType()!=BOOL_TYPE, false);
        bValue = this->getStub()->data.bValue;
        return true;
    }
    
    bool SCValue::getFloat(float& fValue) const
    {
        SC_RETURN_IF(this->getType()!=FLOAT_TYPE, false);
        fValue = this->getStub()->data.fValue;
        return true;
    }
    
    bool SCValue::getDouble(double& dValue) const
    {
        SC_RETURN_IF(this->getType()!=DOUBLE_TYPE, false);
        dValue = this->getStub()->data.dValue;
        return true;
    }
    
    bool SCValue::getLongLong(long long& llValue) const
    {
        SC_RETURN_IF(this->getType()!=LONGLONG_TYPE, false);
        llValue = this->getStub()->data.llValue;
        return true;
    }
    
    bool SCValue::getPointer(void*& pValue) const
    {
        SC_RETURN_IF(this->getType()!=POINTER_TYPE, false);
        pValue = this->getStub()->data.pValue;
        return true;
    }
    
    bool SCValue::getString(SCString& strValue) const
    {
        SC_RETURN_IF(this->getType()!=STRING_TYPE || this->getStub()->data.pObject==NULL, false);
        strValue = *((SCString*)this->getStub()->data.pObject);
        return true;
    }
    
    bool SCValue::getDataBlock(SCDataBlock& db) const
    {
        SC_RETURN_IF(this->getType()!=DATABLOCK_TYPE || this->getStub()->data.pObject==NULL, false);
        db = *((SCDataBlock*)this->getStub()->data.pObject);
        return true;
    }
    
    bool SCValue::getDateTime(SCDateTime& dateTime) const
    {
        SC_RETURN_IF(this->getType()!=DATETIME_TYPE || this->getStub()->data.pObject==NULL, false);
        dateTime = *((SCDateTime*)this->getStub()->data.pObject);
        return true;
    }
    
    bool SCValue::getArray(std::vector<SCValue>& valueVtr) const
    {
        SC_RETURN_IF(this->getType()!=ARRAY_TYPE || this->getStub()->data.pObject==NULL, false);
        valueVtr = *((std::vector<SCValue>*)this->getStub()->data.pObject);
        return true;
    }
    */
     
    void SCValue::setInt(const int nValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.nValue = nValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = INT_TYPE;
    }
    
    SCValue& SCValue::operator=(const unsigned int uValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.uValue = uValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = UINT_TYPE;
    }
    
    void SCValue::setLong(const long lValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.lValue = lValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = LONG_TYPE;
    }
    
    void SCValue::setBool(const bool bValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.bValue = bValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = BOOL_TYPE;
    }
    
    void SCValue::setFloat(const float fValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.fValue = fValue;
        this->getCookieDesc()->cookie = FLOAT_TYPE;
    }
    
    void SCValue::setDouble(const double dValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.dValue = dValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = DOUBLE_TYPE;
    }
    
    void SCValue::setLongLong(long long llValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.llValue = llValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = LONGLONG_TYPE;
    }
    
    void SCValue::setPointer(void* const pValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.pValue = pValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = POINTER_TYPE;
    }
    
    void SCValue::setString(const char* pszValue)
    {
        SCString s(pszValue);
        this->setString(s);
    }
    
    void SCValue::setString(const SCString& strValue)
    {
        SCValue v = SCValue::create(strValue);
        *this = v;
    }
    
    void SCValue::setDataBlock(const SCDataBlock& db)
    {
        SCValue v = SCValue::create(db);
        *this = v;
    }
    
    void SCValue::setDateTime(const SCDateTime& dateTime)
    {
        SCValue v = SCValue::create(dateTime);
        *this = v;
    }
    
    void SCValue::setArray(const std::vector<SCValue>& valueVcr)
    {
        SCValue v = SCValue::create(valueVcr);
        *this = v;
    }
    
    SCValue& SCValue::operator=(const unsigned char byValue)
    {
        this->setByte(byValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const int nValue)
    {
        this->setInt(nValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const long lValue)
    {
        this->setLong(lValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const bool bValue)
    {
        this->setBool(bValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const float fValue)
    {
        this->setFloat(fValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const double dValue)
    {
        this->setDouble(dValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(void* const pValue)
    {
        this->setPointer(pValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const long long llValue)
    {
        this->setLongLong(llValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const SCString& strValue)
    {
        this->setString(strValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const char* pszValue)
    {
        this->setString(pszValue);
        return *this;
    }
    
    SCValue& SCValue::operator=(const SCDataBlock& db)
    {
        this->setDataBlock(db);
        return *this;
    }
    
    SCValue& SCValue::operator=(const SCDateTime& dateTime)
    {
        this->setDateTime(dateTime);
        return *this;
    }
    
    SCValue& SCValue::operator=(const std::vector<SCValue>& valueVcr)
    {
        this->setArray(valueVcr);
        return *this;
    }
}

