

#include "SCComponent.h"

namespace SpeedCC
{
    ///------------ SCComponent
    void SCComponent::setName(const SCString& strName)
    {
        _strName = strName;
    }
    
    
    ///------------ SCComponentValue
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

