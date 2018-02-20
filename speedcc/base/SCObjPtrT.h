


#ifndef __SPEEDCC__SCOBJPTRT_H__
#define __SPEEDCC__SCOBJPTRT_H__

#include "SCObjRefT.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    ///----------- strong smart pointer
    template<typename TargetT,bool IsStrong=true>
    class SCObjPtrT : public SCObjRefT<TargetT>
    {
        template<typename,bool> friend class SCObjPtrT;
    protected:
        virtual void onInstanceCreated(void* pData)
        {
            this->getStub()->setObjPtrData(pData);
        }
    public:
        typedef TargetT type;
        
        SCObjPtrT(){}
        SCObjPtrT(std::nullptr_t p){}
        explicit SCObjPtrT(void* p)
        {
            if(p!=nullptr)
            {
                this->_pObjData = p;
                this->increaseRef();
            }
        }
        
        SCObjPtrT(const SCObjPtrT& ptr)
        {
            *this = ptr;
        }
        
        template<typename T2,typename = typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,T2>::type>
        SCObjPtrT(const SCObjPtrT<T2,true>& ptr)
        {
            *this = ptr;
        }
        
        TargetT& operator*()
        {
            SCASSERT(this->_pObjData!=nullptr);
            return (*this->getStub());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pObjData!=nullptr);
            return (*this->getStub());
        }
        
        TargetT* operator->()
        {
            return this->getStub();
        }
        
//        TargetT* operator=(SCObjPtrT<TargetT,true> data)
//        {
//            return (TargetT*)data.getStub();
//        }
        
        TargetT* getRawPointer()
        {
            return this->getStub();
        }
        
        const TargetT* operator->() const
        {
            return this->getStub();
        }
        
        inline bool isNull() const {return (this->_pObjData==nullptr);}
        
        inline bool operator==(const SCObjPtrT<TargetT,true>& data) const
        {
            return (this->isNull() && data.isNull()) ? true : ((this->_pObjData)==(data._pObjData));
        }
        
        inline bool operator==(const SCObjPtrT<TargetT,false>& data) const
        {
            return (this->isNull() && data.isNull()) ? true : (data.isNull() ? false : ((TargetT*)(this->_pObjData)==((TargetT*)&(*data))));
        }
        
        template<typename T2>
        typename std::enable_if<std::is_convertible<T2*,TargetT*>::value,SCObjPtrT&>::type
        operator=(const SCObjPtrT<T2,true>& ptr)
        {
            if(ptr.getStub()!=this->_pObjData)
            {
                this->decreaseRef();
                this->_pObjData = (void*)ptr.getStub();
                this->increaseRef();
            }
            
            return *this;
        }
        
        template<typename T2>
        T2 cast() const
        {
            SC_RETURN_IF(this->_pObjData==nullptr,nullptr);
            
            TargetT* p1 = (TargetT*)this->_pObjData;
            SCObjPtrT<typename T2::type> ptrRet;
            if(dynamic_cast<typename T2::type *>(p1))
            {
                this->increaseRef();
                ptrRet._pObjData = this->_pObjData;
            }
            
            return ptrRet;
        }
        
        inline bool isWeak() const { return false;}
    };
    
    ///----------- weak smart pointer
    template<typename TargetT>
    class SCObjPtrT<TargetT,false> : public SCObjRefT<void*>
    {
        template<typename,bool> friend class SCObjPtrT;
    public:
        typedef TargetT type;
        
        SCObjPtrT(void){}
        
        SCObjPtrT(void* p)
        {
            if(p!=nullptr)
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
            SCASSERT(this->_pObjData!=nullptr);
            return *((TargetT*)this->getTargetPointer());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pObjData!=nullptr);
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
        
        inline bool isNull() const {return (this->getTargetPointer()==nullptr);}
        
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
            if(ptr.getStub()!=this->_pObjData)
            {
                if(this->_pObjData==nullptr)
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
            if(ptr._pObjData!=this->_pObjData)
            {
                this->decreaseRef();
                this->_pObjData = (void*)ptr.getStub();
                this->increaseRef();
            }
            
            return *this;
        }
        
        template<typename T2>
        SCObjPtrT<T2,false> cast() const
        {
            SC_RETURN_IF((std::is_same<T2,TargetT>::value),(*this));
            SC_RETURN_IF(_pObjData==nullptr || (*(this->getStub()))==nullptr,nullptr);
            
            TargetT* p1 = (TargetT*)(*(this->getStub()));
            SCObjPtrT<T2,false> ptrRet;
            if(dynamic_cast<T2*>(p1))
            {
                this->increaseRef();
                ptrRet._pObjData = this->_pObjData;
            }
            
            return ptrRet;
        }
        
        inline bool isWeak() const { return true;}
        
    private:
        TargetT* getTargetPointer() const
        {
            return (this->_pObjData==nullptr) ? nullptr : ((TargetT*)(*(this->getStub())));
        }
    };
    
    // strong
    template<typename T>
    inline bool operator==(const SCObjPtrT<T>& ptr, std::nullptr_t)
    { return ptr.isNull(); }
    
    template<typename T>
    inline bool operator==(std::nullptr_t, const SCObjPtrT<T>& ptr)
    { return ptr.isNull(); }
    
    template<typename T>
    inline bool operator!=(const SCObjPtrT<T>& ptr, std::nullptr_t)
    { return !ptr.isNull(); }
    
    template<typename T>
    inline bool operator!=(std::nullptr_t, const SCObjPtrT<T>& ptr)
    { return !ptr.isNull();}
    
    
    // weak
    template<typename T>
    inline bool operator==(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
    { return ptr.isNull(); }
    
    template<typename T>
    inline bool operator==(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
    { return ptr.isNull(); }
    
    template<typename T>
    inline bool operator!=(const SCObjPtrT<T,false>& ptr, std::nullptr_t)
    { return !ptr.isNull(); }
    
    template<typename T>
    inline bool operator!=(std::nullptr_t, const SCObjPtrT<T,false>& ptr)
    { return !ptr.isNull();}
    
    
    ///---------- check class wheather object smart pointer
    
    template<typename T, bool b = SCHasInternalTypeT<T>::value ? true : false>
    struct SCIsObjPtrClassT
    {
        enum {value = std::is_same<T, SCObjPtrT<typename T::type>>::value};
    };
    
    template<typename T>
    struct SCIsObjPtrClassT<T,false>
    {
        enum {value = 0};
    };
}


#endif //__SPEEDCC__SCOBJPTRT_H__
