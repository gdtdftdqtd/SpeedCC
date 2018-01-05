

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCLayerRoot.h"
#include "SCRefHolder.h"

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
        
        inline bool isDisableTouch() const  {return (_pDisableTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Layer* getRootLayer()  {return _pRootLayer;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setDisableTouch(const bool bDisableTouch) ;
        void showBlackMask(const bool bShow) ;

        void pushModalController(SCSceneController::Ptr controllerPtr) ;
        SCSceneController::Ptr popModalFromParent();
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        
//        void mapMessage2Func();
        
    protected:
        SCSceneController();
        virtual void onSCMessageProcess(SCMessageInfo& mi) override;
        
    private:
        inline void setSceneRootLayer(SCLayerRoot* pLayer) { _pRootLayer = pLayer;}
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)  { _parentModalControllerPtr = controllerPtr;}
        
    protected:
        std::map<cocos2d::Ref*,SCBehavior::Ptr>         _buttonItem2InfoMap;
        
    private:
        SCLayerRoot*			                _pRootLayer;
        SCScene*                                _pScene;
        SCSceneController::WeakPtr              _parentModalControllerPtr;
        SCLayerDisableTouch*                         _pDisableTouchLayer;
        cocos2d::Layer*                         _pBlackMaskLayer;
        bool                                    _bBlackMaskForModal;
        std::list<SCObject::Ptr>                _ownLifecycleList;
    };
    
    

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
