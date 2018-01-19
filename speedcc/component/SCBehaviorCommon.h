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

namespace SpeedCC
{
    
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
}

#endif // __SPEEDCC__SCBEHAVIORCOMMON_H__
