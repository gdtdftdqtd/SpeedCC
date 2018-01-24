

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCScene.h"
#include "SCRefHolder.h"
#include "SCCocosDef.h"
#include "SCBinder.h"
#include "SCUIBuilder.h"

#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../component/SCMessageDispatch.h"
#include "../component/SCStage.h"

#include "../base/SCWatchNumberT.h"


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
        
        inline bool getAllTouchEnabled() const  {return (_pDisableTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Node* getBedNode()  {return _pBedNode;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setAllTouchEnabled(const bool bEnabled);
        void showBlackMask(const bool bShow);

        void pushModalController(SCSceneController::Ptr controllerPtr);
        SCSceneController::Ptr popModalFromParent();
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        void delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic);
        void listenMessage(const int nMsg,FUN_SCMapMessage_t pfnFunc);
        
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
    protected:
        SCSceneController();
        
        virtual void onCreate(const SCDictionary& parameters){}
        
    private:
        void setBedNode(SCBedNode* pLayer);
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)  { _ptrParentModalController = controllerPtr;}
        
    protected:
        SCUIBuilder::Ptr                            _ptrUI;
        
    private:
        SCBedNode*			                        _pBedNode;
        SCScene*                                    _pScene;
        SCSceneController::WeakPtr                  _ptrParentModalController;
        SCLayerDisableTouch*                        _pDisableTouchLayer;
        cocos2d::Layer*                             _pBlackMaskLayer;
        bool                                        _bBlackMaskForModal;
        std::list<SCObject::Ptr>                    _ownLifecycleList;
        std::map<int,FUN_SCMapMessage_t>            _msg2FuncMap;
    };
    
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
