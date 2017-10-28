

#ifndef __SPEEDCC__SCCOMPONENT_H__
#define __SPEEDCC__SCCOMPONENT_H__

#include "../base/SCObjPtrT.h"
#include "../base/SCValue.h"

namespace SpeedCC
{
    ///------------ SCComponent
    class SCComponent
    {   
    protected:
        SC_AVOID_CLASS_COPY(SCComponent);
        
        SCComponent()
        {}
        
        SCComponent(const SCString& strName):
        _strName(strName)
        {}
        
    public:
        SC_DEFINE_CLASS_PTR(SCComponent);
        
        inline SCString getName() const { return _strName; }
        void setName(const SCString& strName);
        
    private:
        SCString    _strName;
    };
    
    ///------------ SCComponentValue
    class SCComponentValue : public SCComponent
    {
    protected:
        SC_AVOID_CLASS_COPY(SCComponentValue);
        
        SCComponentValue()
        {}
        
        SCComponentValue(const SCString& strName):
        SCComponent(strName)
        {}
        
        SCComponentValue(const SCString& strName,const SCValue& value):
        SCComponent(strName),
        _value(value)
        {}
        
    public:
        SC_DEFINE_CLASS_PTR(SCComponentValue);
        
        static Ptr create();
        static Ptr create(const SCString& strName,const SCValue& value);
        
        SCValue getValue() const;
        SCValue& getValue();
        void setValue(const SCValue& value);
        
    private:
        SCValue     _value;
    };
}

#endif // __SPEEDCC__SCCOMPONENT_H__
