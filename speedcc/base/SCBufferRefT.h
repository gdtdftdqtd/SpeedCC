


#ifndef __SC__BUFFERREFT_H__
#define __SC__BUFFERREFT_H__

#include "SCObjRefT.h"

namespace SpeedCC
{
    template<typename TargetClassT>
    class SCBufferRefT : public SCObjRefT<SCClassEmpty,int>
    {
    public:
        SCBufferRefT();
        SCBufferRefT(const void* pData,const int nDataSize);
        
        virtual ~SCBufferRefT();
        
        inline int getSize() const { return ( _pData==NULL ? 0 : *this->getCookie());}
        inline bool isEmpty() const {return ( _pData==NULL || *this->getCookie()==0);}
        inline const void* getDataPtr() const {return _pData==NULL ? "" : this->_pData;}
        
        void clear();
        
        int assign(const void* pData,const int nDataSize);
        int assign(const SCBufferRefT<TargetClassT>& data);
        int append(const SCBufferRefT<TargetClassT>& data);
        int append(const void* pData,const int nDataSize);
        
        const SCBufferRefT<TargetClassT>& operator+=(const SCBufferRefT<TargetClassT>& data);
        
    protected:
        void reset4Write(const int nSize);
    };
    
    template<typename TargetClassT>
    SCBufferRefT<TargetClassT>::SCBufferRefT()
    {
    }
    
    template<typename TargetClassT>
    SCBufferRefT<TargetClassT>::SCBufferRefT(const void* pData,const int nDataSize)
    {
        if(pData!=NULL && nDataSize>0)
        {
            this->allocBuf(nDataSize);
            ::memcpy(_pData,pData,nDataSize);
            this->getCookieDesc()->cookie = nDataSize;
        }
    }
    
    template<typename TargetClassT>
    SCBufferRefT<TargetClassT>::~SCBufferRefT()
    {
    }
    
    template<typename TargetClassT>
    int SCBufferRefT<TargetClassT>::assign(const SCBufferRefT<TargetClassT>& data)
    {
        this->SCObjRefT::assign(data);
        
        return this->getSize();
    }
    
    template<typename TargetClassT>
    int SCBufferRefT<TargetClassT>::assign(const void* pData,const int nDataSize)
    {
        if((pData==NULL && nDataSize>0) || nDataSize<0)
        {
            return -1;
        }
        
        if(nDataSize==0)
        {
            if(this->getSize()>0)
            {
                this->clear();
            }
            return 0;
        }
        
        this->decreaseRef();
        this->allocBuf(nDataSize);
        ::memcpy(_pData,pData,nDataSize);
        this->getCookieDesc()->cookie = nDataSize;
        
        return nDataSize;
    }
    
    template<typename TargetClassT>
    int SCBufferRefT<TargetClassT>::append(const SCBufferRefT<TargetClassT>& data)
    {
        const int nSize1 = data.getSize();
        const int nSize0 = this->getSize();
        
        if(nSize1==0)
        {
            return nSize0;
        }
        
        if(nSize0==0)
        {
            *this = data;
        }
        else
        {
            const int nTotalSize = nSize0 + nSize1;
            
            if(nTotalSize<512)
            {
                char buf[512];
                if(_pData!=NULL && nSize0>0)
                {
                    ::memcpy(buf,_pData,nSize0);
                }
                ::memcpy(buf+nSize0,data.getDataPtr(),nSize1);
                SCBufferRefT<TargetClassT> data2(buf,nTotalSize);
                *this = data2;
            }
            else
            {
                char* buf = (char*)::malloc(nTotalSize);
                if(_pData!=NULL && nSize0>0)
                {
                    ::memcpy(buf,_pData,nSize0);
                }
                ::memcpy(buf+nSize0,data.getDataPtr(),nSize1);
                SCBufferRefT<TargetClassT> data2(buf,nTotalSize);
                *this = data2;
                ::free(buf);
            }
        }
        
        return this->getSize();
    }
    
    template<typename TargetClassT>
    int SCBufferRefT<TargetClassT>::append(const void* pData,const int nDataSize)
    {
        SC_RETURN_IF(nDataSize==0, this->getSize());
        
        SCBufferRefT<TargetClassT> data(pData,nDataSize);
        
        return this->append(data);
    }
    
    
    template<typename TargetClassT>
    const SCBufferRefT<TargetClassT>& SCBufferRefT<TargetClassT>::operator+=(const SCBufferRefT<TargetClassT>& data)
    {
        this->append(data);
        return *this;
    }
    
    template<typename TargetClassT>
    void SCBufferRefT<TargetClassT>::clear()
    {
        this->decreaseRef();
        _pData = NULL;
    }
    
    template<typename TargetClassT>
    void SCBufferRefT<TargetClassT>::reset4Write(const int nSize)
    {
        bool bNew = true;
        
        if(_pData!=NULL)
        {
            auto pDesc = this->getCookieDesc();
            if(1==pDesc->nRefs && (pDesc->getBufferSize() > nSize+(int)sizeof(char)))
            {
                ::memset(_pData,0,pDesc->getBufferSize());
                pDesc->cookie = 0;
                bNew = false;
            }
        }
        
        if(bNew)
        {
            this->decreaseRef();
            this->allocBuf(nSize);
        }
    }
}


#endif //__SC__BUFFERREFT_H__
