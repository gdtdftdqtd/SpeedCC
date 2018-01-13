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
    protected:
        SCBehaviorGroup()
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorGroup)
        SC_DEFINE_CLASS_PTR(SCBehaviorGroup)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorGroup)
        
        template<typename ...Ts>
        static Ptr create(SCBehavior::Ptr ptrBvr1,SCBehavior::Ptr ptrBvr2,Ts... ts)
        {
            SCASSERT(ptrBvr1!=NULL);
            SCASSERT(ptrBvr2!=NULL);
            auto ptr2 = create(ptrBvr2,ts...);
            
            auto ptrRet = SCBehaviorGroup::create();
            
            ptrRet->_behaviorList.push_back(ptrBvr1);
            for(auto it : ptr2->_behaviorList)
            {
                ptrRet->_behaviorList.push_back(it);
            }
            
            return ptrRet;
        }
        
        static Ptr create(SCBehavior::Ptr ptrBvr);
        
        virtual void execute(const SCDictionary& par) override;
        
        void addBehavior(const SCBehavior::Ptr& ptrBvr);
        void removeBehavior(const int nID);
        
    private:
        std::list<SCBehavior::Ptr> _behaviorList;
    };
    
}

#endif // __SPEEDCC__SCBEHAVIORCOMMON_H__
