//
//  SCBinder.hpp
//  libspeedcc
//
//  Created by Kevin on 17/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBINDER_H__
#define __SPEEDCC__SCBINDER_H__

#include "SCObject.h"
#include "SCMacroDef.h"
#include "SCWatchNumberT.h"

namespace SpeedCC
{
    ///------------- SCBinder
    class SCBinder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinder)
        SC_DEFINE_CLASS_PTR(SCBinder)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinder)
        
        virtual ~SCBinder();
        
        void setActive(const bool bActive);
        inline bool getActive() const {return _bActive;}
        
        virtual void reset();
        
        void removeUpdateFunc();
        
    protected:
        SCBinder():
        _bActive(true),
        _nFuncID(0)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) {}
        
    protected:
        SCObject::Ptr       _ptrWatch;
        std::function<void(SCObject::Ptr ptr,const int nID)>   _removeUpdateFunc;
        int                     _nFuncID;
        
    private:
        bool    _bActive;
    };
    
    ///-------------- SCBinderWatchNumberT
    template<typename T1, typename T2,
    typename = typename std::enable_if<SCIsWatchNumberIntegerT<T1>::value==1 &&
    SCIsWatchNumberIntegerT<T2>::value==1,T1>::type>
    class SCBinderWatchNumberT : public SCBinder
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinderWatchNumberT)
        SC_DEFINE_CLASS_PTR(SCBinderWatchNumberT)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinderWatchNumberT)
        
        void setWatch(typename T1::Ptr ptrWatch)
        {
            this->removeUpdateFunc();
            const int nID = ptrWatch->addUpdateFunc([this](typename T1::Ptr ptrNum,
                                                           typename T1::type newNum,
                                                           typename T1::type oldNum)
                                               {
                                                   if(this->getActive() && _ptrDst!=NULL)
                                                   {
                                                       (*_ptrDst) = (typename T2::type)newNum;
                                                   }
                                               });
            
            if(_ptrDst!=NULL && this->getActive())
            {
                (*_ptrDst) = (typename T2::type)(*ptrWatch);
            }
            
            _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
            {
                SC_RETURN_V_IF(ptr==NULL || nID<=0);
                
                auto p = ptr.cast<typename T1::Ptr>();
                p->removeUpdateFunc(nID);
            };
            
            _ptrWatch = ptrWatch;
            _nFuncID = nID;
        }
        
        inline typename T1::Ptr getSourceWatch() const
        {
            return _ptrWatch==NULL ? NULL : _ptrWatch.cast<typename T1::Ptr>();
        }
        
        inline typename T2::Ptr getDestWatch() const
        {
            return _ptrDst;
        }
        
        void setDestWatch(typename T2::Ptr ptrWatch)
        {
            _ptrDst = ptrWatch;
            
            if(_ptrDst!=NULL && _ptrWatch!=NULL)
            {
                (*_ptrDst) = (typename T2::type)(*(_ptrWatch.cast<typename T1::Ptr>()));
            }
        }
        
        virtual void reset() override
        {
            SCBinder::reset();
            _ptrDst = NULL;
        }
        
    protected:
        SCBinderWatchNumberT(typename T1::Ptr ptrSrc, typename T2::Ptr ptrDst)
        {
            _ptrDst = ptrDst;
            this->setWatch(ptrSrc);
        }
        
    private:
        typename T2::Ptr    _ptrDst;
    };
    
}

#endif //__SPEEDCC__SCBINDER_H__
