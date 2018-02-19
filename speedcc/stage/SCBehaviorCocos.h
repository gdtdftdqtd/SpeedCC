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
        
        template<typename SceneT, typename TransT = SCClassNull, typename LoadingT = SCClassNull>
        static Ptr create(const SCSceneNavigator::ESceneSwitchType place = SCSceneNavigator::kSceneReplace,
                          const SCDictionary& dic = SCDictionary())
        {
            SCSceneNavigator::SSceneSwitchInfo swi;
            swi.setUp<SceneT,TransT,LoadingT>(place);
            
            SCBehaviorSceneNavigate::Ptr ptrRet;
            ptrRet.createInstanceWithCon([swi,dic](void* pData)
                                         {
                                             new(pData)SCBehaviorSceneNavigate(swi,dic);
                                         });
            
            return ptrRet;
        }
        
        virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
        void setSceneParameter(const SCDictionary& dic);
        inline void setDirect(const bool bDirect) { _bDirect = bDirect; }
        inline bool getDirect() const { return _bDirect; }
        
    protected:
        SCBehaviorSceneNavigate(const SCSceneNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic):
        _switch(swi),
        _parameterDic(dic),
        _bDirect(false)
        {}
        
        void onBvrFunc();
    private:
        SCBehaviorDelayExecute::Ptr             _ptrDelayBvr;
        SCSceneNavigator::SSceneSwitchInfo      _switch;
        SCDictionary                            _parameterDic;
        bool                                    _bDirect;
    };
    
    ///-------------- SCBehaviorSceneBack
    class SCBehaviorSceneBack : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorSceneBack)
        SC_DEFINE_CLASS_PTR(SCBehaviorSceneBack)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorSceneBack)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorSceneBack,const int)
        
        virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
        inline void setDirect(const bool bDirect) { _bDirect = bDirect; }
        inline bool getDirect() const { return _bDirect; }
        
    protected:
        SCBehaviorSceneBack():
        _nSceneNum(1),
        _bDirect(false)
        {
        }
        
        SCBehaviorSceneBack(const int nSceneNum):
        _nSceneNum(nSceneNum),
        _bDirect(false)
        {
        }
        
        void onBvrFunc();
    private:
        SCBehaviorDelayExecute::Ptr     _ptrDelayBvr;
        int                             _nSceneNum;
        bool                            _bDirect;
    };
    
    
    ///------------ SCBehaviorAlertBoxSelected
    class SCSceneController;
    class SCBehaviorAlertBoxSelected : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorAlertBoxSelected)
        SC_DEFINE_CLASS_PTR(SCBehaviorAlertBoxSelected)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorAlertBoxSelected)
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorAlertBoxSelected,SCSceneController*,const int)
        
        void setController(SCSceneController* pController);
        void setSelectedIndex(const int nSelectedIndex);
        
        virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
    protected:
        SCBehaviorAlertBoxSelected();
        SCBehaviorAlertBoxSelected(SCSceneController* pController,const int nSelected);
        
    private:
        SCSceneController*      _pController;
        int                     _nSelected;
    };
}

#endif // __SPEEDCC__SCBEHAVIORCOCOS_H__
