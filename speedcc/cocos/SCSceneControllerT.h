

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"

#include "SCSceneLayer.h"

#include "../component/SCMessageDispatch.h"

#include "../base/SCBaseCommon.h"
#include "../base/SCBaseDef.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
    class SCSceneController : public SCObject
    {
        friend class SCSceneNavigator;
        template<typename T> friend class SCSceneControllerT;
        
    public:
        SC_DEFINE_CLASS_PTR(SCSceneController);
        
//        virtual bool isTouchFreezed() const = 0;
        virtual void setTouchFreezed(const bool bFreeze) = 0;
//        virtual void showBlackMask(const bool bShow) = 0;
//        virtual bool isBlackMaskForModal() const = 0;
        virtual cocos2d::Layer* getRootLayer() = 0;
        virtual SCScene* getScene() = 0;
        
    protected:
//        virtual void setSceneRootLayer(cocos2d::Layer* pLayer) = 0;
//        virtual void setPreviousModalLayer(SCSceneController::Ptr pLayer) = 0;
//        virtual void onSCModalGotFocus()=0;
        virtual void setScene(SCScene* pScene) = 0;
        virtual void pushModalController(SCSceneController::Ptr controllerPtr) = 0;
        
        // return parent controller
        virtual SCSceneController::Ptr popModalFromParent() = 0;
        virtual void setModalParentController(SCSceneController::WeakPtr pControllerPtr) = 0;
//        virtual SCSceneController::WeakPtr getModalParentController() = 0;
    };
    
    typedef SCSceneController::Ptr (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
    typedef SCSceneController::Ptr (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
    
#define FN(_fun_)\
    ((decltype(TargetCtlrT::traitFuncPointerType(&TargetCtlrT::_fun_)))(&TargetCtlrT::_fun_))
    
    template<typename TargetCtlrT>
    class SCSceneControllerT :
    public SCSceneController,
    public SCMessageListener,
    public cocos2d::Ref
    {
    public:
        friend class SCSceneNavigator;
        typedef SCSceneControllerT<TargetCtlrT>   ControllerBase_t;
        
        virtual void onCreate(SCDictionary parameters){}
        
//        virtual bool isTouchFreezed() const;
        virtual void setTouchFreezed(const bool bFreeze) override;
//        virtual void showBlackMask(const bool bShow);
//        virtual bool isBlackMaskForModal() const;
        virtual cocos2d::Layer* getRootLayer() override;
        virtual SCScene* getScene() override {return _pScene;}

        virtual void pushModalController(SCSceneController::Ptr controllerPtr) override;
        virtual SCSceneController::Ptr popModalFromParent() override;
        
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic);
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic);
        
    protected:
//        virtual void onSCMessageProcess(SSCMessageInfo& mi) override {}
        
    private:
        void setSceneRootLayer(SCSceneLayer* pLayer) { _pRootLayer = pLayer;}
        virtual void setScene(SCScene* pScene) override {_pScene = pScene;}
        virtual void setModalParentController(SCSceneController::WeakPtr controllerPtr) override { _parentModalControllerPtr = controllerPtr;}
//        virtual SCSceneController::WeakPtr getModalParentController() override { return _parentModalControllerPtr;}
        
    protected:
        FUN_SCButtonFunctor_t traitFuncPointerType(bool (TargetCtlrT::*)());
        FUN_SCButtonSenderFunctor_t traitFuncPointerType(bool (TargetCtlrT::*)(cocos2d::MenuItem*));
        cocos2d::SEL_MenuHandler traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Ref*));
        cocos2d::SEL_SCHEDULE traitFuncPointerType(void (TargetCtlrT::*)(float));
        cocos2d::SEL_CallFunc traitFuncPointerType(void (TargetCtlrT::*)());
        cocos2d::SEL_CallFuncN traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*));
        cocos2d::SEL_CallFuncND traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*, void*));
        
    private:
        SCSceneLayer*			        _pRootLayer;
        SCScene*                        _pScene;
        SCSceneController::WeakPtr      _parentModalControllerPtr;
    };
    
    ////-------------- member methods
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::pushModalController(SCSceneController::Ptr controllerPtr)
    {
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController>();
        controllerPtr->setModalParentController(controllerPtr2);
        controllerPtr->setScene(_pScene);
        
        _pScene->addChild(controllerPtr->getRootLayer());
        this->setTouchFreezed(true);
        
        // generate modal mssage
        SSCMessageInfo mi;
        
        mi.nMsgID = SCMessage_ModalSceneLostFocus;
        mi.paramters.setValue(MSG_ARG_NAME_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        mi.nMsgID = SCMessage_ModalSceneGotFocus;
        mi.paramters.setValue(MSG_ARG_NAME_CONTROLLER,controllerPtr.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
    }
    
    template<typename TargetCtlrT>
    SCSceneController::Ptr SCSceneControllerT<TargetCtlrT>::popModalFromParent()
    {
        SCASSERT(_parentModalControllerPtr!=NULL);
        auto ret = _parentModalControllerPtr->makeObjPtr<SCSceneController>();
        
        _parentModalControllerPtr->setTouchFreezed(false);
        _parentModalControllerPtr = NULL;
        _pRootLayer->removeFromParent();
        
        // generate modal mssage
        SSCMessageInfo mi;
        mi.nMsgID = SCMessage_ModalSceneGotFocus;
        mi.paramters.setValue(MSG_ARG_NAME_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        return ret;
    }
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::setTouchFreezed(const bool bFreeze)
    {
        
    }
    
    template<typename TargetCtlrT>
    cocos2d::Layer* SCSceneControllerT<TargetCtlrT>::getRootLayer()
    {
        return ((_pRootLayer==NULL) ? _pScene->getRootLayer() : _pRootLayer);
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
//            SC_BREAK_IF(!scene);
            
            sceneCtlrPtr.createInstance();
            
            SC_BREAK_IF(sceneCtlrPtr.isNull());
            
            auto scene = SCScene::create();
            scene->getRootLayer()->setController(sceneCtlrPtr);
            sceneCtlrPtr->setScene(scene);
            sceneCtlrPtr->onCreate(parameterDic);
            
        } while (0);
        
        return sceneCtlrPtr;
    }
    
    template<typename TargetCtlrT>
    SCSceneController::Ptr SCSceneControllerT<TargetCtlrT>::createLayer(const SCDictionary& parameterDic)
    {
        SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
        sceneCtlrPtr.createInstance();
        
        auto rootLayer = SCSceneLayer::create();
        rootLayer->setController(sceneCtlrPtr);
        sceneCtlrPtr->setSceneRootLayer(rootLayer);
        
        sceneCtlrPtr->setScene(NULL);
        sceneCtlrPtr->onCreate(parameterDic);

        return sceneCtlrPtr;
    }
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
