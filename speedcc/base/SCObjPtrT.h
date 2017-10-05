


#ifndef __SC__OBJPTRT_H__
#define __SC__OBJPTRT_H__

#include "SCObjRefT.h"
#include "SCMacroDef.h"

namespace SPEEDCC
{
    template<typename TargetT>
    class SCObjPtrT : public SCObjRefT<TargetT>
    {
    public:
        SCObjPtrT(){}
        SCObjPtrT(std::nullptr_t){}
        
        template<typename T2>
        SCObjPtrT(const SCObjPtrT<T2>& ptr)
        {
            *this = ptr;
        }
        
        TargetT& operator*()
        {
            if(this->_pData==NULL)
            {
                SCASSERT(false);
            }
            
            *this->getStub();
        }
        
        const TargetT& operator*() const
        {
            if(this->_pData==NULL)
            {
                SCASSERT(false);
            }
            
            *this->getStub();
        }
        
        TargetT* operator->()
        {
            return this->getStub();
        }
        
        const TargetT* operator->() const
        {
            return this->getStub();
        }
        
        inline bool isNull() const {return (this->_pData==NULL);}
        
        template<typename T2>
        typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
        operator=(const SCObjPtrT<T2>& ptr)
        {
            if(ptr.getStub()!=this->_pData)
            {
                this->decreaseRef();
                this->_pData = (void*)ptr.getStub();
                this->increaseRef();
            }
            
            return *this;
        }
    };
    
    
    template<class T>
    inline bool operator==(const SCObjPtrT<T>& ptr, std::nullptr_t)
    { return ptr.isNull(); }
    
    template<class T>
    inline bool operator==(std::nullptr_t, const SCObjPtrT<T>& ptr)
    { return ptr.isNull(); }
    
    template<class T>
    inline bool operator!=(const SCObjPtrT<T>& ptr, std::nullptr_t)
    { return !ptr.isNull(); }
    
    template<class T>
    inline bool operator!=(std::nullptr_t, const SCObjPtrT<T>& ptr)
    { return !ptr.isNull();}
}


#endif //__SC__OBJPTRT_H__
