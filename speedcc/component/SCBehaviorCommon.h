//
//  SCBehaviorCommon.hpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBEHAVIORCOMMON_H__
#define __SPEEDCC__SCBEHAVIORCOMMON_H__

#include "SCPerformObject.h"
#include "../base/SCWatchNumberT.h"

namespace SpeedCC
{
    ///-------------- SCBehaviorNothing
    class SCBehaviorNothing : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorNothing)
        SC_DEFINE_CLASS_PTR(SCBehaviorNothing)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorNothing)
        
        virtual void execute(const SCDictionary& par) override {}
        
    protected:
        SCBehaviorNothing(){}
    };
    
    ///-------------- SCBehaviroCallFunc
    class SCBehaviorCallFunc : public SCBehavior
    {
    protected:
        SCBehaviorCallFunc()
        {}
        
        SCBehaviorCallFunc(const std::function<void(const SCDictionary& par)>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
        SCBehaviorCallFunc(const std::function<void()>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCallFunc)
        SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorCallFunc)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void(const SCDictionary& par)>&)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void()>&)
        
        virtual void execute(const SCDictionary& par) override;
        
        void setOnStartFunc(const std::function<void(const SCDictionary& par)>& func);
        void setOnStartFunc(const std::function<void()>& func);
        
    private:
        std::function<void(const SCDictionary& par)>  _startFunc;
        std::function<void()>  _startFunc2;
    };
    
    ///-------------- SCBehaviorGroup
    class SCBehaviorGroup : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorGroup)
        SC_DEFINE_CLASS_PTR(SCBehaviorGroup)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorGroup)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorGroup,SCBehavior::Ptr)
        
        template<typename ...Ts>
        static Ptr create(SCBehavior::Ptr ptrBvr1,SCBehavior::Ptr ptrBvr2,Ts... ts)
        {
            SCASSERT(ptrBvr1!=NULL);
            SCASSERT(ptrBvr2!=NULL);
            auto ptr2 = SCBehaviorGroup::create(ptrBvr2,ts...);
            
            auto ptrRet = SCBehaviorGroup::create();
            
            ptrRet->_behaviorList.push_back(ptrBvr1);
            for(auto it : ptr2->_behaviorList)
            {
                ptrRet->_behaviorList.push_back(it);
            }
            
            return ptrRet;
        }
        
        virtual void execute(const SCDictionary& par) override;
        
        void addBehavior(const SCBehavior::Ptr& ptrBvr);
        void removeBehavior(const int nID);
        
    protected:
        SCBehaviorGroup()
        {}
        
        SCBehaviorGroup(SCBehavior::Ptr ptrBvr);
        
    private:
        std::list<SCBehavior::Ptr> _behaviorList;
    };
    
    ///------------- SCBehaviorDelayExecute
    class SCBehaviorDelayExecute :
    public SCBehavior,
    public cocos2d::Ref
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorDelayExecute)
        SC_DEFINE_CLASS_PTR(SCBehaviorDelayExecute)
        
        virtual ~SCBehaviorDelayExecute();
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorDelayExecute)
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorDelayExecute,const float,SCBehavior::Ptr)
        
        virtual void execute(const SCDictionary& par) override;
        bool setBehavior(SCBehavior::Ptr ptrBvr);
        bool setDelayTime(const float fDelay);
        inline bool isRunning() const { return _bPost; }
        
    protected:
        SCBehaviorDelayExecute():
        _fDelay(0),
        _bPost(false)
        {}
        
        SCBehaviorDelayExecute(const float fDelay,SCBehavior::Ptr ptrBvr):
        _fDelay(fDelay),
        _ptrBvr(ptrBvr),
        _bPost(false)
        {}
        
        void onDelayExecute(float fDelta);
        
    private:
        bool                _bPost;
        float               _fDelay;
        SCBehavior::Ptr     _ptrBvr;
    };
    
    ///--------------- SCBehaviorCaseT
    template<typename T,
            typename = typename std::enable_if<SCIsWatchClass<T>::value==1,T>::type >
    class SCBehaviorCaseT : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCaseT)
        SC_DEFINE_CLASS_PTR(SCBehaviorCaseT)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorCaseT)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCaseT,typename T::Ptr)
        
        void setCase(const typename T::type value, SCBehavior::Ptr ptrBvr)
        {
            _watchValue2BvrMap[value] = ptrBvr;
        }
        
        inline typename T::Ptr getWatch() const {return _ptrWatch;}
        inline int getCaseCount() const { return (int)_watchValue2BvrMap.size();}
        
        virtual void execute(const SCDictionary& par) override
        {
            auto it = _watchValue2BvrMap.find((*_ptrWatch));
            if(it!=_watchValue2BvrMap.end())
            {
                (*it).second->execute(par);
            }
        }
        
    protected:
        SCBehaviorCaseT()
        {
            _ptrWatch = T::create();
        }
        
        SCBehaviorCaseT(typename T::Ptr ptrWatch):
        _ptrWatch(ptrWatch)
        {
        }
        
    private:
        typename T::Ptr     _ptrWatch;
        std::map<typename T::type, SCBehavior::Ptr>     _watchValue2BvrMap;
    };
    
    typedef SCBehaviorCaseT<SCWatchInt>         SCBehaviorCaseInt;
    typedef SCBehaviorCaseT<SCWatchBool>        SCBehaviorCaseBool;
    typedef SCBehaviorCaseT<SCWatchString>      SCBehaviorCaseString;
}

#endif // __SPEEDCC__SCBEHAVIORCOMMON_H__
