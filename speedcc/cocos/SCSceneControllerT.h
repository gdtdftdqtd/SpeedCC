

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCLayerRoot.h"

#include "../component/SCMessageDispatch.h"

#include "../base/SCBaseCommon.h"
#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

#include "../component/SCBehavior.h"

namespace SpeedCC
{
    class SCSceneController : public SCObject
    {
        friend class SCSceneNavigator;
        template<typename T> friend class SCSceneControllerT;
        
    public:
        SC_DEFINE_CLASS_PTR(SCSceneController);
        
        virtual bool isNoTouch() const = 0;
        virtual void setNoTouch(const bool bNoTouch) = 0;
        virtual void showBlackMask(const bool bShow) = 0;
        virtual bool isBlackMaskForModal() const = 0;
        virtual cocos2d::Layer* getRootLayer() = 0;
        virtual SCScene* getScene() = 0;
        
    protected:
//        virtual void setSceneRootLayer(cocos2d::Layer* pLayer) = 0;
//        virtual void setPreviousModalLayer(SCSceneController::Ptr pLayer) = 0;
//        virtual void onSCModalGotFocus()=0;
        virtual void setScene(SCScene* pScene) = 0;
        virtual void pushModalController(SCSceneController::Ptr controllerPtr) = 0;
        
        virtual SCSceneController::Ptr popModalFromParent() = 0;
        virtual void setModalParentController(SCSceneController::WeakPtr pControllerPtr) = 0;
//        virtual SCSceneController::WeakPtr getModalParentController() = 0;
    };
    
    typedef SCSceneController::Ptr (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
    typedef SCSceneController::Ptr (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
    typedef cocos2d::Scene* (*FUN_SCSceneTransitionCreateFunctor_t)(const float fDuration, cocos2d::Scene* pScene);
    typedef void (cocos2d::Ref::*FUN_SCDelayExecuteFunction_t)(void* pData);
    
#define FN(_fun_)\
    ((decltype(TargetCtrlr_t::traitFuncPointerType(&TargetCtrlr_t::_fun_)))(&TargetCtrlr_t::_fun_))
    
    template<typename TargetCtlrT>
    class SCSceneControllerT :
    public SCSceneController,
    public SCMessageListener,
    public cocos2d::Ref
    {
    public:
        friend class SCSceneNavigator;
        typedef SCSceneControllerT<TargetCtlrT>   ControllerBase_t;
        typedef TargetCtlrT                         TargetCtrlr_t;
        
        SCSceneControllerT():
        _pRootLayer(NULL),
        _pScene(NULL),
        _pNoTouchLayer(NULL),
        _pBlackMaskLayer(NULL),
        _bBlackMaskForModal(true)
        {}
        
        virtual void onCreate(SCDictionary parameters){}
        
        virtual bool isNoTouch() const override {return (_pNoTouchLayer==NULL);}
        virtual void setNoTouch(const bool bNoTouch) override;
        virtual void showBlackMask(const bool bShow) override;
        virtual bool isBlackMaskForModal() const override {return _bBlackMaskForModal;}
        virtual cocos2d::Layer* getRootLayer() override {return _pRootLayer;}
        virtual SCScene* getScene() override {return _pScene;}

        virtual void pushModalController(SCSceneController::Ptr controllerPtr) override;
        virtual SCSceneController::Ptr popModalFromParent() override;
        
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic);
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic);
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
    protected:
        virtual void onSCMessageProcess(SSCMessageInfo& mi) override {}
        
    private:
        void setSceneRootLayer(SCLayerRoot* pLayer) { _pRootLayer = pLayer;}
        virtual void setScene(SCScene* pScene) override {_pScene = pScene;}
        virtual void setModalParentController(SCSceneController::WeakPtr controllerPtr) override { _parentModalControllerPtr = controllerPtr;}
        
    protected:
        cocos2d::SEL_MenuHandler traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Ref*));
        cocos2d::SEL_SCHEDULE traitFuncPointerType(void (TargetCtlrT::*)(float));
        cocos2d::SEL_CallFunc traitFuncPointerType(void (TargetCtlrT::*)());
        cocos2d::SEL_CallFuncN traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*));
        cocos2d::SEL_CallFuncND traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*, void*));
        
    protected:
        std::map<cocos2d::Ref*,SCBehavior::Ptr>         _buttonItem2InfoMap;
        
    private:
        SCLayerRoot*			                _pRootLayer;
        SCScene*                                _pScene;
        SCSceneController::WeakPtr              _parentModalControllerPtr;
        SCLayerNoTouch*                         _pNoTouchLayer;
        cocos2d::Layer*                         _pBlackMaskLayer;
        bool                                    _bBlackMaskForModal;
    };
    
    ////-------------- member methods
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::pushModalController(SCSceneController::Ptr controllerPtr)
    {
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController>();
        controllerPtr->setModalParentController(controllerPtr2);
        controllerPtr->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(controllerPtr->getRootLayer());
        this->setNoTouch(true);
        
        // generate modal mssage
        SSCMessageInfo mi;
        
        mi.nMsgID = SCMessage_ModalSceneLostFocus;
        mi.paramters.setValue(MSG_ARG_KEY_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        mi.nMsgID = SCMessage_ModalSceneGotFocus;
        mi.paramters.setValue(MSG_ARG_KEY_CONTROLLER,controllerPtr.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
    }
    
    template<typename TargetCtlrT>
    SCSceneController::Ptr SCSceneControllerT<TargetCtlrT>::popModalFromParent()
    {
        SCASSERT(_parentModalControllerPtr!=NULL);
        auto ret = _parentModalControllerPtr->makeObjPtr<SCSceneController>();
        
        _parentModalControllerPtr->setNoTouch(false);
        if(_parentModalControllerPtr->isBlackMaskForModal())
        {
            _parentModalControllerPtr->showBlackMask(false);
        }
        
        _parentModalControllerPtr = NULL;
        _pRootLayer->removeFromParent();
        
        // generate modal mssage
        SSCMessageInfo mi;
        mi.nMsgID = SCMessage_ModalSceneGotFocus;
        mi.paramters.setValue(MSG_ARG_KEY_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        return ret;
    }
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::setNoTouch(const bool bNoTouch)
    {
        if(_pNoTouchLayer==NULL && bNoTouch)
        {// turn to no touch
            auto pLayer = SCLayerNoTouch::create();
            _pRootLayer->addChild(pLayer);
            pLayer->setPosition(cocos2d::Vec2(0,0));
            
            _pNoTouchLayer = pLayer;
        }
        else if(_pNoTouchLayer!=NULL && !bNoTouch)
        {// turn to touchable
            _pNoTouchLayer->removeFromParentAndCleanup(true);
            _pNoTouchLayer = NULL;
        }
    }
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::showBlackMask(const bool bShow)
    {
        if(bShow)
        {
            if(_pBlackMaskLayer==NULL)
            {
                _pBlackMaskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
                _pRootLayer->addChild(_pBlackMaskLayer);
            }
        }
        else
        {
            if(_pBlackMaskLayer!=NULL)
            {
                _pBlackMaskLayer->removeFromParentAndCleanup(true);
                _pBlackMaskLayer = NULL;
            }
        }
    }
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::onSCMenuItemPressed(cocos2d::Ref* pSender)
    {
        auto it = _buttonItem2InfoMap.find(pSender);
        
        SCASSERT(it!=_buttonItem2InfoMap.end());
        if(it!=_buttonItem2InfoMap.end())
        {
            if((*it).second!=NULL)
            {
                (*it).second->start();
            }
        }
    }
    
//    template<typename TargetCtlrT>
//    void SCSceneControllerT<TargetCtlrT>::onSCMessageProcess(SSCMessageInfo& mi)
//    {
//
//    }
//
//    template<typename TargetCtlrT>
//    void SCSceneControllerT<TargetCtlrT>::onCreate(SCDictionary parameters)
//    {
//
//    }
    
	////-------------- static methods
    
    template<typename TargetCtlrT>
    SCSceneController::Ptr SCSceneControllerT<TargetCtlrT>::createScene(const SCDictionary& parameterDic)
    {
        SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
        
        do
        {
            sceneCtlrPtr.createInstance();
            
            SC_BREAK_IF(sceneCtlrPtr.isNull());
            
            auto scene = SCScene::create();
            auto pRootLayer = scene->getRootLayer();
            pRootLayer->setController(sceneCtlrPtr);
            sceneCtlrPtr->setScene(scene);
            sceneCtlrPtr->setSceneRootLayer(pRootLayer);
            sceneCtlrPtr->onCreate(parameterDic);
            
        } while (0);
        
        return sceneCtlrPtr;
    }
    
    template<typename TargetCtlrT>
    SCSceneController::Ptr SCSceneControllerT<TargetCtlrT>::createLayer(const SCDictionary& parameterDic)
    {
        SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
        sceneCtlrPtr.createInstance();
        
        auto rootLayer = SCLayerRoot::create();
        rootLayer->setController(sceneCtlrPtr);
        sceneCtlrPtr->setSceneRootLayer(rootLayer);
        
        sceneCtlrPtr->setScene(NULL);
        sceneCtlrPtr->onCreate(parameterDic);

        return sceneCtlrPtr;
    }
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
