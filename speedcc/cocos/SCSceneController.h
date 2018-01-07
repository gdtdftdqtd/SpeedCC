

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCScene.h"
#include "SCRefHolder.h"
#include "SCCocosDef.h"

#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../component/SCMessageDispatch.h"
#include "../component/SCStage.h"


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
        
        virtual ~SCSceneController();
        
        virtual void onCreate(SCDictionary parameters){}
        
        inline bool getAllTouchEnabled() const  {return (_pDisableTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Node* getSceneNode()  {return _pRootLayer;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setAllTouchEnabled(const bool bEnabled);
        void showBlackMask(const bool bShow);

        void pushModalController(SCSceneController::Ptr controllerPtr);
        SCSceneController::Ptr popModalFromParent();
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        void delayExecute(float fDelay,FUN_SCDelayExecute_t pfnFunc,const SCDictionary& dic=SCDictionary());
        void listenMessage(const int nMsg,FUN_SCMapMessage_t pfnFunc);
        
        cocos2d::Node* getLayoutNode(const int nID);
        
        void setTouchMode(const ETouchMode touch);
        inline ETouchMode getTouchMode() const { return _touchMode;}
        
        cocos2d::EventListener* getEventListener(cocos2d::EventListener::Type type) const;
        
        virtual void onSCMessageProcess(SCMessageInfo& mi) override;
        
    protected:
        SCSceneController();
        
        void storeLayoutNode(const int nID,cocos2d::Node* pNode);
        void storeLayoutNode(...){}
    private:
        inline void setSceneRootLayer(SCSceneNode* pLayer) { _pRootLayer = pLayer;}
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)  { _parentModalControllerPtr = controllerPtr;}
        
        bool onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        
        void onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        
        void onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent);
        
        template<typename T>
        void sendTouchMessage(const int nMsg, T touch)
        {
            SCDictionary::SPair pair = {std::is_same<T,cocos2d::Touch*>::value ? MSG_KEY_TOUCH : MSG_KEY_TOUCHES,touch};
            
            SCDictionary dic(pair);
            
            SCMessageInfo mi;
            mi.nMsgID = nMsg;
            mi.paramters = dic;
            this->onSCMessageProcess(mi);
        }
    protected:
        std::map<cocos2d::Ref*,SCBehavior::Ptr>         _buttonItem2InfoMap;
        
    private:
        SCSceneNode*			                _pRootLayer;
        SCScene*                                _pScene;
        SCSceneController::WeakPtr              _parentModalControllerPtr;
        SCLayerDisableTouch*                    _pDisableTouchLayer;
        cocos2d::Layer*                         _pBlackMaskLayer;
        bool                                    _bBlackMaskForModal;
        std::list<SCObject::Ptr>                _ownLifecycleList;
        std::map<int,FUN_SCMapMessage_t>        _msg2FuncMap;
        std::map<int,cocos2d::Node*>            _id2NodeMap;
        
        ETouchMode                              _touchMode;
        cocos2d::EventListener*                 _pTouchListener; // no need to remove from event dispatch
    };
    
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
