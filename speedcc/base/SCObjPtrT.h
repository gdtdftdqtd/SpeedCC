


#ifndef __SPEEDCC__SCOBJPTRT_H__
#define __SPEEDCC__SCOBJPTRT_H__

#include "SCObjRefT.h"
#include "SCMacroDef.h"

namespace SpeedCC
{   
    template<typename TargetT,bool IsStrong=true>
    class SCObjPtrT : public SCObjRefT<TargetT>
    {
        template<typename T,bool s> friend class SCObjPtrT;
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
            if(p!=NULL)
            {
                this->_pObjData = p;
                this->increaseRef();
            }
        }
        
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
            SCASSERT(this->_pObjData!=NULL);
            return (*this->getStub());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pObjData!=NULL);
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
        
        inline bool isNull() const {return (this->_pObjData==NULL);}
        
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
        SCObjPtrT<T2> cast() const
        {
            SC_RETURN_IF(this->_pObjData==NULL,NULL);
            
            TargetT* p1 = (TargetT*)this->_pObjData;
            SCObjPtrT<T2> retPtr;
            if(dynamic_cast<T2*>(p1))
            {
                this->increaseRef();
                retPtr._pObjData = this->_pObjData;
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
            SCASSERT(this->_pObjData!=NULL);
            return *((TargetT*)this->getTargetPointer());
        }
        
        const TargetT& operator*() const
        {
            SCASSERT(this->_pObjData!=NULL);
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
            if(ptr.getStub()!=this->_pObjData)
            {
                if(this->_pObjData==NULL)
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
            SC_RETURN_IF((SCIsSameTypeT<T2,TargetT>::value),(*this));
            SC_RETURN_IF(_pObjData==NULL || (*(this->getStub()))==NULL,NULL);
            
            TargetT* p1 = (TargetT*)(*(this->getStub()));
            SCObjPtrT<T2,false> retPtr;
            if(dynamic_cast<T2*>(p1))
            {
                this->increaseRef();
                retPtr._pObjData = this->_pObjData;
            }
            
            return retPtr;
        }
        
        inline bool isWeak() const { return true;}
        
    private:
        TargetT* getTargetPointer() const
        {
            return (this->_pObjData==NULL) ? NULL : ((TargetT*)(*(this->getStub())));
        }
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
