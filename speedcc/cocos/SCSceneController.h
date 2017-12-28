

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCLayerRoot.h"
#include "SCRefHolder.h"

#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../component/SCMessageDispatch.h"
#include "../component/SCBehavior.h"


namespace SpeedCC
{

    class SCSceneController :
    public SCObject,
    public SCMessageListener,
    public cocos2d::Ref
    {
    public:
        SC_DEFINE_CLASS_PTR(SCSceneController)
        SC_AVOID_CLASS_COPY(SCSceneController)
        
        friend class SCSceneNavigator;
        
        virtual void onCreate(SCDictionary parameters){}
        
        inline bool isNoTouch() const  {return (_pNoTouchLayer==NULL);}
        void setNoTouch(const bool bNoTouch) ;
        void showBlackMask(const bool bShow) ;
        bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        cocos2d::Layer* getRootLayer()  {return _pRootLayer;}
        SCScene* getScene()  {return _pScene;}

        void pushModalController(SCSceneController::Ptr controllerPtr) ;
        SCSceneController::Ptr popModalFromParent();
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
    protected:
        SCSceneController();
        virtual void onSCMessageProcess(SCMessageInfo& mi) override {}
        
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
        SCLayerNoTouch*                         _pNoTouchLayer;
        cocos2d::Layer*                         _pBlackMaskLayer;
        bool                                    _bBlackMaskForModal;
        std::list<SCObject::Ptr>                _ownLifecycleList;
    };
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
