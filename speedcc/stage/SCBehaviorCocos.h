/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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

#ifndef __SPEEDCC__SCBEHAVIORCOCOS_H__
#define __SPEEDCC__SCBEHAVIORCOCOS_H__

#include "SCPerformObject.h"
#include "../cocos/SCSceneNavigator.h"
#include "SCBehaviorCommon.h"

namespace SpeedCC
{
    ///----------- SCBehaviorSceneGoto
    class SCBehaviorSceneGoto : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorSceneGoto)
        SC_DEFINE_CLASS_PTR(SCBehaviorSceneGoto)
        
        template<typename SceneT, typename TransT = SCClassNull, typename LoadingT = SCClassNull>
        static Ptr create(const SCSceneNavigator::ESceneSwitchType place = SCSceneNavigator::kSceneReplace,
                          const SCDictionary& dic = SCDictionary())
        {
            SCSceneNavigator::SSceneSwitchInfo swi;
            swi.setUp<SceneT,TransT,LoadingT>(place);
            
            SCBehaviorSceneGoto::Ptr ptrRet;
            ptrRet.createInstanceWithCon([swi,dic](void* pData)
                                         {
                                             new(pData)SCBehaviorSceneGoto(swi,dic);
                                         });
            
            return ptrRet;
        }
        
        virtual void execute(const SCDictionary& par = SCDictionary()) override;
        
        void setSceneParameter(const SCDictionary& dic);
        inline void setDirect(const bool bDirect) { _bDirect = bDirect; }
        inline bool getDirect() const { return _bDirect; }
        
    protected:
        SCBehaviorSceneGoto(const SCSceneNavigator::SSceneSwitchInfo& swi,const SCDictionary& dic):
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
