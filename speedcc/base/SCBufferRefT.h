/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/


#ifndef __SPEEDCC__SCBUFFERREFT_H__
#define __SPEEDCC__SCBUFFERREFT_H__

#include "SCObjRefT.h"

namespace SpeedCC
{
    struct SCBufferRefCookie
    {
        int     nUsedSize;
        
        SCBufferRefCookie():
        nUsedSize(0)
        {}
    };
    
    template<typename CookieT=SCBufferRefCookie>
    class SCBufferRefT : public SCObjRefT<SCClassEmpty,CookieT>
    {
    public:
        SCBufferRefT();
        SCBufferRefT(const void* pData,const int nDataSize);
        
        virtual ~SCBufferRefT();
        
        inline int getSize() const { return ( this->_pObjData==nullptr ? 0 : this->getCookie()->nUsedSize);}
        inline bool isEmpty() const {return ( this->_pObjData==nullptr || this->getCookie()->nUsedSize==0);}
        inline const void* getDataPtr() const {return this->_pObjData==nullptr ? "" : this->_pObjData;}
        
        void clear();
        
        int assign(const void* pData,const int nDataSize);
        int assign(const SCBufferRefT& data);
        int append(const SCBufferRefT& data);
        int append(const void* pData,const int nDataSize);
        
        const SCBufferRefT& operator+=(const SCBufferRefT& data);
        
        void createInstance() = delete;
        void createInstanceWithCon(const std::function<void(void*)>& func) = delete;
    protected:
        void adjustBuf4Write(const int nSize);
    };
    
    template<typename CookieT>
    SCBufferRefT<CookieT>::SCBufferRefT()
    {
    }
    
    template<typename CookieT>
    SCBufferRefT<CookieT>::SCBufferRefT(const void* pData,const int nDataSize)
    {
        if(pData!=nullptr && nDataSize>0)
        {
            this->allocBuf(nDataSize);
            ::memcpy(this->_pObjData,pData,nDataSize);
            this->getCookie()->nUsedSize = nDataSize;
        }
    }
    
    template<typename CookieT>
    SCBufferRefT<CookieT>::~SCBufferRefT()
    {
    }
    
    template<typename CookieT>
    int SCBufferRefT<CookieT>::assign(const SCBufferRefT<CookieT>& data)
    {
        this->SCObjRefT<SCClassEmpty,CookieT>::assign(data);
        
        return this->getSize();
    }
    
    template<typename CookieT>
    int SCBufferRefT<CookieT>::assign(const void* pData,const int nDataSize)
    {
        if((pData==nullptr && nDataSize>0) || nDataSize<0)
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
        ::memcpy(this->_pObjData,pData,nDataSize);
        this->getCookie()->nUsedSize = nDataSize;
        
        return nDataSize;
    }
    
    template<typename CookieT>
    int SCBufferRefT<CookieT>::append(const SCBufferRefT<CookieT>& data)
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
                if(this->_pObjData!=nullptr && nSize0>0)
                {
                    ::memcpy(buf,this->_pObjData,nSize0);
                }
                ::memcpy(buf+nSize0,data.getDataPtr(),nSize1);
                SCBufferRefT<CookieT> data2(buf,nTotalSize);
                *this = data2;
            }
            else
            {
                char* buf = (char*)::malloc(nTotalSize);
                if(this->_pObjData!=nullptr && nSize0>0)
                {
                    ::memcpy(buf,this->_pObjData,nSize0);
                }
                ::memcpy(buf+nSize0,data.getDataPtr(),nSize1);
                SCBufferRefT<CookieT> data2(buf,nTotalSize);
                *this = data2;
                ::free(buf);
            }
        }
        
        return this->getSize();
    }
    
    template<typename CookieT>
    int SCBufferRefT<CookieT>::append(const void* pData,const int nDataSize)
    {
        SC_RETURN_IF(nDataSize==0, this->getSize());
        
        SCBufferRefT<CookieT> data(pData,nDataSize);
        
        return this->append(data);
    }
    
    
    template<typename CookieT>
    const SCBufferRefT<CookieT>& SCBufferRefT<CookieT>::operator+=(const SCBufferRefT<CookieT>& data)
    {
        this->append(data);
        return *this;
    }
    
    template<typename CookieT>
    void SCBufferRefT<CookieT>::clear()
    {
        this->decreaseRef();
        this->_pObjData = nullptr;
    }
    
    template<typename CookieT>
    void SCBufferRefT<CookieT>::adjustBuf4Write(const int nSize)
    {
        bool bNew = true;
        
        if(this->_pObjData!=nullptr)
        {
            auto pDesc = this->getCookieDesc();
            if(1==pDesc->nRefs && (pDesc->getBufferSize() > nSize+(int)sizeof(char)))
            {
                ::memset(this->_pObjData,0,pDesc->getBufferSize());
                pDesc->cookie.nUsedSize = 0;
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


#endif //__SPEEDCC__SCBUFFERREFT_H__
