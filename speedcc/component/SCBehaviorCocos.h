//
//  SCBehaviorCocos.hpp
//  libspeedcc
//
//  Created by Kevin on 14/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBEHAVIORCOCOS_H__
#define __SPEEDCC__SCBEHAVIORCOCOS_H__

#include "SCPerformObject.h"
#include "../cocos/SCSceneNavigator.h"

namespace SpeedCC
{
    ///----------- SCBehaviorSceneSwitch
    class SCBehaviorSceneSwitch : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorSceneSwitch)
        SC_DEFINE_CLASS_PTR(SCBehaviorSceneSwitch)
        
        template<typename SceneT, typename TransT = SCClassNull>
        static Ptr create(const SCSceneNavigator::ESceneSwitchType place = SCSceneNavigator::kSceneReplace,
                          const SCDictionary& dic = SCDictionary())
        {
            SCSceneNavigator::SSceneSwitchInfo swi;
            swi.setUp<SceneT,TransT>(place);
            
            SCBehaviorSceneSwitch::Ptr ptrRet;
            ptrRet.createInstanceWithCon([swi,dic](void* pData)
                                         {
                                             new(pData)SCBehaviorSceneSwitch(swi,dic);
                                         });
            
            return ptrRet;
        }
        
        virtual void execute(const SCDictionary& par) override;
        
        void setSceneParameter(const SCDictionary& dic);
        
    protected:
        SCBehaviorSceneSwitch(const SCSceneNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic):
        _switch(swi),
        _parameterDic(dic)
        {}
        
    private:
        SCSceneNavigator::SSceneSwitchInfo      _switch;
        SCDictionary                            _parameterDic;
    };
    
    ///-------------- SCBehaviorSceneBack
    class SCBehaviorSceneBack : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorSceneBack)
        SC_DEFINE_CLASS_PTR(SCBehaviorSceneBack)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorSceneBack)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorSceneBack,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorSceneBack():
        _nSceneNum(1)
        {
        }
        
        SCBehaviorSceneBack(const int nSceneNum):
        _nSceneNum(nSceneNum)
        {
        }
        
    private:
        int         _nSceneNum;
    };
}

#endif // __SPEEDCC__SCBEHAVIORCOCOS_H__
