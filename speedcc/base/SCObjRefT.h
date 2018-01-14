


#ifndef __SPEEDCC__SCOBJREFT_H__
#define __SPEEDCC__SCOBJREFT_H__

#include "SCTemplateUtils.h"
#include "SCMemAllocator.h"

namespace SpeedCC
{
    template<typename StubT=SCClassEmpty,typename CookieT=SCClassEmpty>
    class SCObjRefT
    {
    protected:
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
        inline SCookieDesc* getCookieDesc() const {return _pObjData==NULL ? NULL : (((SCookieDesc*)_pObjData)-1); }
        
    public:
        SCObjRefT(void);
        SCObjRefT(const SCObjRefT<StubT,CookieT>& buf);
        
        virtual ~SCObjRefT();
        
        inline int getRefCount() const {return _pObjData==NULL ? 0 : this->getCookieDesc()->nRefs;}
        
        void assign(const SCObjRefT<StubT,CookieT>& ref);
        const SCObjRefT<StubT,CookieT>& operator=(const SCObjRefT<StubT,CookieT>& data);
        
        inline bool operator==(const SCObjRefT& data) const {return (_pObjData==data._pObjData);}
        
        inline bool isValid() const {return (_pObjData!=NULL);}
        void createInstance();
        void createInstanceWithCon(const std::function<void(void*)>& func);
        
//        template<class ..._Args>
//        void createInstance(_Args&& ...__args);
        
    protected:
        inline CookieT* getCookie() {return SCIsEmptyClassT<CookieT>::value ? NULL : (_pObjData==NULL ? NULL : &this->getCookieDesc()->cookie);}
        inline const CookieT* getCookie() const {return SCIsEmptyClassT<CookieT>::value ? NULL : (_pObjData==NULL ? NULL : &this->getCookieDesc()->cookie);}
        
        inline StubT* getStub() {return (StubT*)_pObjData;}
        inline StubT* getStub() const {return (StubT*)_pObjData;}
        
        void clone4Write();
        int increaseRef() const;
        int decreaseRef();
        void allocBuf(int nSize=sizeof(StubT));
        virtual void onInstanceCreated(void* pData) {}
        
    private:
        void freeBuf();
        
    protected:
        void*                   _pObjData;
    };
    
    template<typename StubT,typename CookieT>
    SCObjRefT<StubT,CookieT>::SCObjRefT(void):
    _pObjData(NULL)
    {
    }
    
    template<typename StubT,typename CookieT>
    SCObjRefT<StubT,CookieT>::SCObjRefT(const SCObjRefT<StubT,CookieT>& buf):
    _pObjData(NULL)
    {
        if(buf._pObjData!=this->_pObjData)
        {
            buf.increaseRef();
            _pObjData = buf.getCookieDesc()->getBufferPtr();
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
        return (_pObjData==NULL) ? 0 : (++this->getCookieDesc()->nRefs);
    }
    
    template<typename StubT,typename CookieT>
    int SCObjRefT<StubT,CookieT>::decreaseRef()
    {
        if(_pObjData==NULL)
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
        SCDataTypeLifeCycleT<StubT>::construct(_pObjData);
        this->onInstanceCreated(_pObjData);
    }
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::createInstanceWithCon(const std::function<void(void*)>& func)
    {
        this->decreaseRef();
        this->allocBuf();
        
        if(func!=NULL)
        {
            func(_pObjData);
        }
        this->onInstanceCreated(_pObjData);
    }
    
    
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
        SCDataTypeLifeCycleT<SCookieDesc>::construct(pDesc);
        pDesc->nMallocBufSize = nBufferSize;
        
        _pObjData = (char*)pDesc->getBufferPtr();
        ::memset(_pObjData,0,pDesc->getBufferSize());
        
        pDesc->nRefs = 1;
    }
    
    
    template<typename StubT,typename CookieT>
    void SCObjRefT<StubT,CookieT>::freeBuf()
    {
        if(_pObjData!=NULL)
        {
            SCDataTypeLifeCycleT<StubT>::destroy(_pObjData);
            // free buffer directly, does not check buffer whether illegal
            auto pDesc = this->getCookieDesc();
            SCDataTypeLifeCycleT<SCookieDesc>::destroy(pDesc);
            SCMemAllocator::deallocate(pDesc, pDesc->nMallocBufSize);
            _pObjData = NULL;
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
        
        if(SCIsEmptyClassT<StubT>::value)
        {
            this->allocBuf(0);
        }
        else
        {
            this->allocBuf();
            SCDataTypeLifeCycleT<StubT>::construct(_pObjData);
            *(StubT*)_pObjData = *(StubT*)sb._pObjData;
        }
    }
    
    template<typename StubT,typename CookieT>
    const SCObjRefT<StubT,CookieT>&
    SCObjRefT<StubT,CookieT>::operator=(const SCObjRefT<StubT,CookieT>& data)
    {
        if(data._pObjData!=this->_pObjData)
        {
            this->decreaseRef();
            this->_pObjData = data._pObjData;
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


#endif //__SPEEDCC__SCOBJREFT_H__
