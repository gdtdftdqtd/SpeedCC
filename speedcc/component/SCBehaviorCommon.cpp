//
//  SCBehaviorCommon.cpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorCommon.h"

namespace SpeedCC
{
    ///----------- SCBehaviorCallFunc
    
    void SCBehaviorCallFunc::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        if(_startFunc!=NULL)
        {
            _startFunc(par);
        }
        else if(_startFunc2!=NULL)
        {
            _startFunc2();
        }
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
    {
        _startFunc = func;
        _startFunc2 = NULL;
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void()>& func)
    {
        _startFunc2 = func;
        _startFunc = NULL;
    }
    
    
    ///----------- SCBehaviorGroup
    
    SCBehaviorGroup::Ptr SCBehaviorGroup::create(SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(ptrBvr!=NULL);
        auto ptrRet = SCBehaviorGroup::create();
        ptrRet->addBehavior(ptrBvr);
        return ptrRet;
    }
    
    void SCBehaviorGroup::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        for(auto& it : _behaviorList)
        {
            it->execute(par);
        }
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBvr)
    {
        SC_RETURN_IF_V(ptrBvr==NULL);
        _behaviorList.push_back(ptrBvr);
    }
    
    void SCBehaviorGroup::removeBehavior(const int nID)
    {
        SC_RETURN_IF_V(nID==0);
        _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                                {
                                    return (ptrBvr->getID()==nID);
                                });
    }
    
    
}


