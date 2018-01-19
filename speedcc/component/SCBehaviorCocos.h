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
#include "SCBehaviorCommon.h"

namespace SpeedCC
{
    ///----------- SCBehaviorSceneNavigate
    class SCBehaviorSceneNavigate : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorSceneNavigate)
        SC_DEFINE_CLASS_PTR(SCBehaviorSceneNavigate)
        
        template<typename SceneT, typename TransT = SCClassNull>
        static Ptr create(const SCSceneNavigator::ESceneSwitchType place = SCSceneNavigator::kSceneReplace,
                          const SCDictionary& dic = SCDictionary())
        {
            SCSceneNavigator::SSceneSwitchInfo swi;
            swi.setUp<SceneT,TransT>(place);
            
            SCBehaviorSceneNavigate::Ptr ptrRet;
            ptrRet.createInstanceWithCon([swi,dic](void* pData)
                                         {
                                             new(pData)SCBehaviorSceneNavigate(swi,dic);
                                         });
            
            return ptrRet;
        }
        
        virtual void execute(const SCDictionary& par) override;
        
        void setSceneParameter(const SCDictionary& dic);
        
    protected:
        SCBehaviorSceneNavigate(const SCSceneNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic):
        _switch(swi),
        _parameterDic(dic)
        {}
        
        void onBvrFunc();
    private:
        SCBehaviorDelayExecute::Ptr             _ptrDelayBvr;
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
        
        void onBvrFunc();
    private:
        SCBehaviorDelayExecute::Ptr     _ptrDelayBvr;
        int         _nSceneNum;
    };
}

#endif // __SPEEDCC__SCBEHAVIORCOCOS_H__
