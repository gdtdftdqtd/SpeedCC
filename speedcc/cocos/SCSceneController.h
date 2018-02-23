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

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCScene.h"
#include "SCRefHolder.h"
#include "SCCocosDef.h"
#include "SCBinderCocos.h"
#include "SCUIBuilder.h"
#include "SCEventEmitter.h"

#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStage.h"


namespace SpeedCC
{

    class SCSceneController :
    public SCStage,
    public cocos2d::Ref
    {
    public:
        SC_DEFINE_CLASS_PTR(SCSceneController)
        SC_AVOID_CLASS_COPY(SCSceneController)
        
        friend class SCSceneNavigator;
        template<typename> friend class SCSceneNavigationCreator;
        
        typedef std::function<void(SCMessage::Ptr ptrMsg)>      MsgFunc_t;
        typedef std::function<void(void*)>                      FinishFunc_t;
        
        virtual ~SCSceneController();
        
        inline bool getAllTouchEnabled() const  {return (_pDisableTouchLayer==nullptr);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Node* getBedNode() const {return _pBedNode;}
        inline SCScene* getScene() const  {return _pScene;}
        
        void setAllTouchEnabled(const bool bEnabled);
        void showBlackMask(const bool bShow);

        void pushModalController(SCSceneController::Ptr controllerPtr);
        SCSceneController::Ptr popModalFromParent();
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        void delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic);
        void listenMessage(const int nMsg,MsgFunc_t func);
        
        void schedule(cocos2d::SEL_SCHEDULE selector);
        void schedule(cocos2d::SEL_SCHEDULE selector, float interval);
        void schedule(cocos2d::SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay);
        void scheduleOnce(cocos2d::SEL_SCHEDULE selector, float delay);
        void unschedule(cocos2d::SEL_SCHEDULE selector);
        
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
        void finish(void* pResult=nullptr);
        
        void setBackButtonSceneEnabled(const bool bEnabled);
        inline bool getBackButtonSceneEnabled() const { return _ptrKeyboardEventEmtr!=nullptr; }
        
    protected:
        SCSceneController();
        
        virtual void onCreate(SCDictionary parameters);
        
    private:
        void setBedNode(SCBedNode* pLayer);
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController* pController)
        { _pParentModalController = pController; }
        
    private:
        SCBedNode*			                        _pBedNode;
        SCScene*                                    _pScene;
        SCSceneController*                          _pParentModalController; // weak pointer
        SCLayerDisableTouch*                        _pDisableTouchLayer;
        cocos2d::Layer*                             _pBlackMaskLayer;
        bool                                        _bBlackMaskForModal;
        std::list<SCObject::Ptr>                    _ownLifecycleList;
        std::map<int,MsgFunc_t>                     _msg2FuncMap;
        FinishFunc_t                                _finishFunc;
        SCEventEmitter::Ptr                         _ptrKeyboardEventEmtr;
    };
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
