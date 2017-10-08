

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
    
    bool SCValue::getValue(SCValue& value)
    {
        SC_RETURN_IF(this->getType()!=VALUE_TYPE || this->getStub()->data.pObject==NULL, false);
        value = *((SCValue*)this->getStub()->data.pObject);
        return true;
    }
    
    void SCValue::setInt(const int& nValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.nValue = nValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = INT_TYPE;
    }
    
    void SCValue::setLong(const long& lValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.lValue = lValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = LONG_TYPE;
    }
    
    void SCValue::setBool(const bool& bValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.bValue = bValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = BOOL_TYPE;
    }
    
    void SCValue::setFloat(const float& fValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.fValue = fValue;
        this->getCookieDesc()->cookie = FLOAT_TYPE;
    }
    
    void SCValue::setDouble(const double& dValue)
    {
        this->check4Write();
        this->clone4Write();
        this->getStub()->data.dValue = dValue;
        (*(this->getStub())).pfunDestroyFunctor_t = NULL;
        this->getCookieDesc()->cookie = DOUBLE_TYPE;
    }
    
    void SCValue::setLongLong(long long& llValue)
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
    
    void SCValue::setArray(const std::vector<SCValue>& valueVtr)
    {
        SCValue v = SCValue::create(valueVtr);
        *this = v;
    }
    
    void SCValue::setValue(const SCValue& value)
    {
        SCValue v = SCValue::create(value);
        *this = v;
    }
}

