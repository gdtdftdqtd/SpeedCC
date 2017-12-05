


#ifndef __SC__OBJREFT_H__
#define __SC__OBJREFT_H__

#include "SCTemplateUtils.h"
#include "SCMemAllocator.h"

namespace SpeedCC
{
    template<typename StubT=SCClassEmpty,typename CookieT=SCClassEmpty>
    class SCObjRefT
    {
    private:
        struct SCookieDesc
        {
            unsigned short              nRefs;	// reference counter
            unsigned short              nMallocBufSize;	// size of memory allocated
            CookieT                     cookie;
            
            SCookieDesc():
            nRefs(0),
            nMallocBufSize(0)
            {}
            
            inline void* getBufferPtr() const { return (void*)(this+1); }
            inline int getBufferSize() const { return nMallocBufSize-sizeof(SCookieDesc);}
        };
        
    protected:
        inline SCookieDesc* getCookieDesc() const {return _pData==NULL ? NULL : (((SCookieDesc*)_pData)-1); }
        
    public:
        SCObjRefT(void);
        SCObjRefT(const SCObjRefT<StubT,CookieT>& buf);
        
        virtual ~SCObjRefT();
        
        inline int getRefCount() const {return _pData==NULL ? 0 : this->getCookieDesc()->nRefs;}
        
        void assign(const SCObjRefT<StubT,CookieT>& ref);
        const SCObjRefT<StubT,CookieT>& operator=(const SCObjRefT<StubT,CookieT>& data);
        
        inline bool operator==(const SCObjRefT& data) const {return (_pData==data._pData);}
        
        inline bool isValid() const {return (_pData!=NULL);}
        void createInstance();
        void createInstanceWithCon(const std::function<void(void*)>& func);
        
        template<class ..._Args>
        void createInstance(_Args&& ...__args);
        
    protected:
        inline CookieT* getCookie() {return SCIsEmptyClassT<CookieT>::value ? NULL : (_pData==NULL ? NULL : &this->getCookieDesc()->cookie);}
        inline const CookieT* getCookie() const {return SCIsEmptyClassT<CookieT>::value ? NULL : (_pData==NULL ? NULL : &this->getCookieDesc()->cookie);}
        
        inline StubT* getStub() {return (StubT*)_pData;}
        inline const StubT* getStub() const {return (StubT*)_pData;}
        
        void clone4Write();
        int increaseRef() const;
        int decreaseRef();
        void allocBuf(int nSize=sizeof(StubT));
        virtual void onInstanceCreated(void* pData) {}
        
    private:
        void freeBuf();
        
    protected:
        void*                   _pData;
    };
    
    template<typename StubT,typename CookieT>
    SCObjRefT<StubT,CookieT>::SCObjRefT(void):
    _pData(NULL)
    {
    }
    
    template<typename StubT,typename CookieT>
    SCObjRefT<StubT,CookieT>::SCObjRefT(const SCObjRefT<StubT,CookieT>& buf):
    _pData(NULL)
    {
        if(buf._pData!=this->_pData)
        {
            buf.increaseRef();
            _pData = buf.getCookieDesc()->getBufferPtr();
        }
    }
    
    template<typename StubT,typename CookieT>
    SCObjRefT<StubT,CookieT>::~SCObjRefT()
    {
        this->decreaseRef();
    }
    
    template<typename StubT,typename CookieT>
    int SCObjRefT<StubT,CookieT>::increaseRef() const
    {
        return (_pData==NULL) ? 0 : (++this->getCookieDesc()->nRefs);
    }
    
    template<typename StubT,typename CookieT>
    int SCObjRefT<StubT,CookieT>::decreaseRef()
    {
        if(_pData==NULL)
        {
            return 0;
        }
        
        const int nNewRef = --(this->getCookieDesc()->nRefs);
        
        if(nNewRef==0)
        {
            this->freeBuf();
        }
        
        return nNewRef;
    }
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::createInstance()
    {
        this->decreaseRef();
        this->allocBuf();
        SCDataTypeLifeCycle<StubT>::construct(_pData);
        this->onInstanceCreated(_pData);
    }
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::createInstanceWithCon(const std::function<void(void*)>& func)
    {
        this->decreaseRef();
        this->allocBuf();
        
        if(func!=NULL)
        {
            func(_pData);
        }
        this->onInstanceCreated(_pData);
    }
    
    template<typename StubT,typename CookieT>
    template<class ..._Args>
    void SCObjRefT<StubT,CookieT>::createInstance(_Args&& ...__args)
    {
        this->decreaseRef();
        this->allocBuf();
        SCDataTypeLifeCycle<StubT>::construct(_pData, _VSTD::forward<_Args>(__args)...);
        this->onInstanceCreated(_pData);
    }
    
    /*
    template<typename StubT,typename CookieT>
    template<typename A1>
    void SCObjRefT<StubT,CookieT>::createInstance(A1 arg1)
    {
        this->decreaseRef();
        this->allocBuf();
        SCDataTypeLifeCycle<StubT>::construct(_pData,arg1);
    }
    
    template<typename StubT,typename CookieT>
    template<typename A1,typename A2>
    void SCObjRefT<StubT,CookieT>::createInstance(A1 arg1,A2 arg2)
    {
        this->decreaseRef();
        this->allocBuf();
        SCDataTypeLifeCycle<StubT>::construct(_pData,arg1,arg2);
    }
    
    
    template<typename StubT,typename CookieT>
    template<typename A1,typename A2,typename A3>
    void SCObjRefT<StubT,CookieT>::createInstance(A1 arg1,A2 arg2,A3 arg3)
    {
        this->decreaseRef();
        this->allocBuf();
        SCDataTypeLifeCycle<StubT>::construct(_pData,arg1,arg2,arg3);
    }
     */
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::allocBuf(int nSize)
    {
        if(nSize<0)
        {
            nSize = 0;
        }
        
        // alloc buffer directly, does not check old buffer
        const int nBufferSize = nSize+sizeof(SCookieDesc);
        
        auto pDesc = (SCookieDesc*)SCMemAllocator::allocate(nBufferSize);
        SCDataTypeLifeCycle<SCookieDesc>::construct(pDesc);
        pDesc->nMallocBufSize = nBufferSize;
        
        _pData = (char*)pDesc->getBufferPtr();
        ::memset(_pData,0,pDesc->getBufferSize());
        
        pDesc->nRefs = 1;
    }
    
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::freeBuf()
    {
        if(_pData!=NULL)
        {
            SCDataTypeLifeCycle<StubT>::destroy(_pData);
            // free buffer directly, does not check buffer whether illegal
            auto pDesc = this->getCookieDesc();
            SCDataTypeLifeCycle<SCookieDesc>::destroy(pDesc);
            SCMemAllocator::deallocate(pDesc, pDesc->nMallocBufSize);
            _pData = NULL ;
        }
    }
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::clone4Write()
    {
        if(this->getRefCount()<2)
        {
            return;
        }
        
        const auto sb = *this;
        
        this->decreaseRef();
        
        if(!SCIsEmptyClassT<StubT>::value)
        {
            this->allocBuf();
            SCDataTypeLifeCycle<StubT>::construct(_pData);
            *(StubT*)_pData = *(StubT*)sb._pData;
        }
        else
        {
            this->allocBuf(0);
        }
    }
    
    template<typename StubT,typename CookieT>
    const SCObjRefT<StubT,CookieT>&
    SCObjRefT<StubT,CookieT>::operator=(const SCObjRefT<StubT,CookieT>& data)
    {
        if(data._pData!=this->_pData)
        {
            this->decreaseRef();
            this->_pData = data._pData;
            this->increaseRef();
        }
        return *this;
    }
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::assign(const SCObjRefT<StubT,CookieT>& data)
    {
        *this = data;
    }
}


#endif //__SC__OBJREFT_H__
