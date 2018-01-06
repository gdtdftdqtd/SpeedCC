

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
        friend class SCSceneNode;
        
        virtual ~SCSceneController();
        
        virtual void onCreate(SCDictionary parameters){}
        
        inline bool isDisableTouch() const  {return (_pDisableTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Node* getRootLayer()  {return _pRootLayer;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setDisableTouch(const bool bDisableTouch) ;
        void showBlackMask(const bool bShow) ;

        void pushModalController(SCSceneController::Ptr controllerPtr) ;
        SCSceneController::Ptr popModalFromParent();
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        void delayExecute(float fDelay,FUN_SCDelayExecute_t pfnFunc,const SCDictionary& dic=SCDictionary());
        void listenMessage(const int nMsg,FUN_SCMapMessage_t pfnFunc);
        
        cocos2d::Node* getLayoutNode(const int nID);
        
    protected:
        SCSceneController();
        virtual void onSCMessageProcess(SCMessageInfo& mi) override;
        
        void storeLayoutNode(const int nID,cocos2d::Node* pNode);
        void storeLayoutNode(...){}
    private:
        inline void setSceneRootLayer(SCSceneNode* pLayer) { _pRootLayer = pLayer;}
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)  { _parentModalControllerPtr = controllerPtr;}
        
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
    };
    
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
