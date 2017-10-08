


#ifndef __SPEEDCC__SCOBJPTRT_H__
#define __SPEEDCC__SCOBJPTRT_H__

#include "SCObjRefT.h"
#include "SCMacroDef.h"

namespace SPEEDCC
{
    class SCComponent;
    
    template<typename TargetT,bool IsStrong=true>
    class SCObjPtrT : public SCObjRefT<TargetT>
    {
        template<typename T,bool s> friend class SCObjPtrT;
        friend class SCComponent;
    public:
        typedef TargetT type;
        
        SCObjPtrT(){}
        SCObjPtrT(std::nullptr_t){}
        
        SCObjPtrT(const SCObjPtrT& ptr)
        {
            *this = ptr;
        }
        
        template<typename T2>
        SCObjPtrT(const SCObjPtrT<T2,true>& ptr)
        {
            *this = ptr;
        }
        
        TargetT& operator*()
        {
            SCASSERT(this->_pData!=NULL);
            return (*this->getStub());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pData!=NULL);
            return (*this->getStub());
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
        
        inline bool operator==(const SCObjPtrT<TargetT,true>& data) const
        {
            return (this->isNull() && data.isNull()) ? true : ((this->_pData)==(data._pData));
        }
        
        inline bool operator==(const SCObjPtrT<TargetT,false>& data) const
        {
            return (this->isNull() && data.isNull()) ? true : (data.isNull() ? false : ((TargetT*)(this->_pData)==((TargetT*)&(*data))));
        }
        
        template<typename T2>
        typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
        operator=(const SCObjPtrT<T2,true>& ptr)
        {
            if(ptr.getStub()!=this->_pData)
            {
                this->decreaseRef();
                this->_pData = (void*)ptr.getStub();
                this->increaseRef();
            }
            
            return *this;
        }
        
        template<typename T2>
        SCObjPtrT<T2> cast() const
        {
            SC_RETURN_IF(this->_pData==NULL,NULL);
            
            TargetT* p1 = (TargetT*)this->_pData;
            SCObjPtrT<T2> retPtr;
            if(dynamic_cast<T2*>(p1))
            {
                this->increaseRef();
                retPtr._pData = this->_pData;
            }
            
            return retPtr;
        }
        
        inline bool isWeak() const { return false;}
    };
    
    template<typename TargetT>
    class SCObjPtrT<TargetT,false> : public SCObjRefT<void*>
    {
        template<typename T,bool s> friend class SCObjPtrT;
    public:
        typedef TargetT type;
        
        SCObjPtrT(void){}
        
        SCObjPtrT(void* p)
        {
            if(p!=NULL)
            {
                this->SCObjRefT<void*>::createInstance();
                *(this->getStub()) = p;
            }
        }
        
        template<typename T2>
        SCObjPtrT(const SCObjPtrT<T2,false>& ptr)
        {
            *this = ptr;
        }
        
        template<typename T2>
        SCObjPtrT(const SCObjPtrT<T2,true>& ptr)
        {
            *this = ptr;
        }
        
        TargetT& operator*()
        {
            SCASSERT(this->_pData!=NULL);
            return *((TargetT*)this->getTargetPointer());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pData!=NULL);
            return *((TargetT*)this->getTargetPointer());
        }
        
        TargetT* operator->()
        {
            return (TargetT*)(this->getTargetPointer());
        }
        
        const TargetT* operator->() const
        {
            return (TargetT*)this->getTargetPointer();
        }
        
        inline bool isNull() const {return (this->getTargetPointer()==NULL);}
        
        inline bool operator==(const SCObjPtrT& data) const
        {
            return (this->isNull() && data.isNull()) ? true : ((*this->getStub())==(*data.getStub()));
        }
        
        inline bool operator==(const SCObjPtrT<TargetT,true>& data) const
        {
            return (this->isNull() && data.isNull()) ? true : ((this->getTargetPointer())==&(*data));
        }
        
        template<typename T2>
        typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
        operator=(const SCObjPtrT<T2,true>& ptr)
        {
            if(ptr.getStub()!=this->_pData)
            {
                if(this->_pData==NULL)
                {
                    this->SCObjRefT<void*>::createInstance();
                }
                *(this->getStub()) = (void*)ptr.getStub();
            }
            
            return *this;
        }
        
        template<typename T2>
        typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
        operator=(const SCObjPtrT<T2,false>& ptr)
        {
            if(ptr._pData!=this->_pData)
            {
                this->decreaseRef();
                this->_pData = (void*)ptr.getStub();
                this->increaseRef();
            }
            
            return *this;
        }
        
        template<typename T2>
        SCObjPtrT<T2,false> cast() const
        {
            SC_RETURN_IF((SCIsSameTypeT<T2,TargetT>::value),(*this));
            SC_RETURN_IF(_pData==NULL || (*(this->getStub()))==NULL,NULL);
            
            TargetT* p1 = (TargetT*)(*(this->getStub()));
            SCObjPtrT<T2,false> retPtr;
            if(dynamic_cast<T2*>(p1))
            {
                this->increaseRef();
                retPtr._pData = this->_pData;
            }
            
            return retPtr;
        }
        
        inline bool isWeak() const { return true;}
        
    private:
        TargetT* getTargetPointer() const
        {
            return (this->_pData==NULL) ? NULL : ((TargetT*)(*(this->getStub())));
        }
        
//        void createInstance() = delete;
//        
//        template<typename A1>
//        void createInstance(A1 arg1) = delete;
//        
//        template<typename A1,typename A2>
//        void createInstance(A1 arg1,A2 arg2) = delete;
//
//        template<typename A1,typename A2,typename A3>
//        void createInstance(A1 arg1,A2 arg2,A3 arg3) = delete;
        
    };
    
    // strong
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
    
    
    // weak
    template<class T>
    inline bool operator==(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
    { return ptr.isNull(); }
    
    template<class T>
    inline bool operator==(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
    { return ptr.isNull(); }
    
    template<class T>
    inline bool operator!=(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
    { return !ptr.isNull(); }
    
    template<class T>
    inline bool operator!=(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
    { return !ptr.isNull();}
}


#endif //__SPEEDCC__SCOBJPTRT_H__
