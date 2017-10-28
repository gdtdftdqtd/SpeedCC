

#include "SCComponent.h"

namespace SpeedCC
{
    ///------------ SCComponent
    void SCComponent::setName(const SCString& strName)
    {
        _strName = strName;
    }
    
    
    ///------------ SCComponentValue
    SCComponentValue::Ptr SCComponentValue::create()
    {
        SCComponentValue::Ptr ptrRet;
        ptrRet.createInstanceWithCon([](void* pData)
                                     {
                                         new(pData)SCComponentValue();
                                     });
        
        return ptrRet;
    }
    
    SCComponentValue::Ptr SCComponentValue::create(const SCString& strName,const SCValue& value)
    {
        SCComponentValue::Ptr ptrRet;
        ptrRet.createInstanceWithCon([strName,value](void* pData)
                                     {
                                         new(pData)SCComponentValue(strName,value);
                                     });
        
        return ptrRet;
    }
    
    SCValue SCComponentValue::getValue() const
    {
        return _value;
    }
    
    SCValue& SCComponentValue::getValue()
    {
        return _value;
    }
    
    void SCComponentValue::setValue(const SCValue& value)
    {
        _value = value;
    }
}

