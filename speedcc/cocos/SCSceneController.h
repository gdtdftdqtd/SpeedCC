

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
#include "../component/SCStage.h"


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
        
        virtual ~SCSceneController();
        
        virtual void onCreate(SCDictionary parameters){}
        virtual void onSetupStage() {}
        virtual SCRole::Ptr onCreateRole(const SCString& strName) { return NULL;}
        virtual SCStrategy::Ptr onCreateStrategy(const SCString& strName) { return NULL;}
        
        inline bool isNoTouch() const  {return (_pNoTouchLayer==NULL);}
        inline bool isBlackMaskForModal() const  {return _bBlackMaskForModal;}
        inline cocos2d::Layer* getRootLayer()  {return _pRootLayer;}
        inline SCScene* getScene()  {return _pScene;}
        
        void setNoTouch(const bool bNoTouch) ;
        void showBlackMask(const bool bShow) ;

        void pushModalController(SCSceneController::Ptr controllerPtr) ;
        SCSceneController::Ptr popModalFromParent();
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
        inline void ownLifecycle(SCObject::Ptr ptr) { _ownLifecycleList.push_back(ptr);}
        void ownLifecycle(cocos2d::Ref* pObject);
        
        void delayExecute(float fDelay,const std::function<void ()>& fun);
        
        void addRole(SCRole::Ptr rolePtr);
    protected:
        SCSceneController();
        virtual void onSCMessageProcess(SCMessageInfo& mi) override {}
        
    private:
        inline void setSceneRootLayer(SCLayerRoot* pLayer) { _pRootLayer = pLayer;}
        inline void setScene(SCScene* pScene)  {_pScene = pScene;}
        inline void setModalParentController(SCSceneController::WeakPtr controllerPtr)  { _parentModalControllerPtr = controllerPtr;}
        
    protected:
        std::map<cocos2d::Ref*,SCBehavior::Ptr>         _buttonItem2InfoMap;
        
        SCStage::Ptr                            _stagePtr;
        
    private:
        SCLayerRoot*			                _pRootLayer;
        SCScene*                                _pScene;
        SCSceneController::WeakPtr              _parentModalControllerPtr;
        SCLayerNoTouch*                         _pNoTouchLayer;
        cocos2d::Layer*                         _pBlackMaskLayer;
        bool                                    _bBlackMaskForModal;
        std::list<SCObject::Ptr>                _ownLifecycleList;
    };
    
    
    ////----------------------
#define ASequence               cocos2d::Sequence::create
#define AMoveTo                 cocos2d::MoveTo::create
#define AMoveBy                 cocos2d::MoveBy::create
#define AScaleTo                cocos2d::ScaleTo::create
#define AScaleBy                cocos2d::ScaleBy::create
#define ARotateTo               cocos2d::RotateTo::create
#define ARotateBy               cocos2d::RotateBy::create
#define APlace                  cocos2d::Place::create
#define ASpawn                  cocos2d::Spawn::create
#define AFadeIn                 cocos2d::FadeIn::create
#define AFadeOut                cocos2d::FadeOut::create
#define AProgressTo             cocos2d::ProgressTo::create
#define AProgressFromTo         cocos2d::ProgressFromTo::create
#define ADelayTime              cocos2d::DelayTime::create
#define ATintBy                 cocos2d::TintBy::create
#define AShow                   cocos2d::Show::create
#define AHide                   cocos2d::Hide::create
#define ABlink                  cocos2d::Blink::create
#define ABezierTo               cocos2d::BezierTo::create
#define ABezierBy               cocos2d::BezierBy::create
#define AJumpBy                 cocos2d::JumpBy::create
#define AJumpTo                 cocos2d::JumpTo::create
#define ASkewTo                 cocos2d::SkewTo::create
#define ASkewBy                 cocos2d::SkewBy::create
#define AFlipY                  cocos2d::FlipY::create
#define AFlipX                  cocos2d::FlipX::create
#define ARemoveSelf             cocos2d::RemoveSelf::create
#define ARepeat                 cocos2d::Repeat::create
#define ARepeatForever          cocos2d::RepeatForever::create
#define ACallFunc               cocos2d::CallFunc::create
#define ACallFuncN              cocos2d::CallFuncN::create
#define ACallFuncND             cocos2d::CallFuncND::create
    
#define AEaseIn                 cocos2d::EaseIn::create
#define AEaseOut                cocos2d::EaseOut::create
#define AEaseInOut              cocos2d::EaseInOut::create
    
#define AEaseSineIn             cocos2d::EaseSineIn::create
#define AEaseSineOut            cocos2d::EaseSineOut::create
#define AEaseSineInOut          cocos2d::EaseSineInOut::create
    
#define AEaseExponentialIn      cocos2d::EaseExponentialIn::create
#define AEaseExponentialOut     cocos2d::EaseExponentialOut::create
#define AEaseExponentialInOut   cocos2d::EaseExponentialInOut::create
    
#define AEaseElasticIn          cocos2d::EaseElasticIn::create
#define AEaseElasticOut         cocos2d::EaseElasticOut::create
#define AEaseElasticInOut       cocos2d::EaseElasticInOut::create
    
#define AWaves3D                cocos2d::Waves3D::create
#define AFlipX3D                cocos2d::FlipX3D::create
#define AFlipY3D                cocos2d::FlipY3D::create
#define ALens3D                 cocos2d::Lens3D::create
#define ARipple3D               cocos2d::Ripple3D::create
#define AShaky3D                cocos2d::Shaky3D::create
#define ALiquid                 cocos2d::Liquid::create
#define AWaves                  cocos2d::Waves::create
#define ATwirl                  cocos2d::Twirl::create

}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
