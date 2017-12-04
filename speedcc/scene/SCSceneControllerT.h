

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"
//#include "SCSceneNavigator.h"
#include "SCSceneLayer.h"

#include "../component/SCMessageDispatch.h"
#include "../base/SCBaseCommon.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
    class SCSceneLayer;
    class SCScene;
    
    class SCSceneControllerInterface : SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCSceneControllerInterface);
        
//        virtual bool isTouchFreezed() const = 0;
//        virtual void setTouchFreezed(const bool bFreeze) = 0;
//        virtual void showBlackMask(const bool bShow) = 0;
//        virtual bool isBlackMaskForModal() const = 0;
        virtual cocos2d::Layer* getSceneLayer() = 0;
        virtual cocos2d::Scene* getScene() = 0;
        
    protected:
//        virtual void setSceneRootLayer(cocos2d::Layer* pLayer) = 0;
//        virtual void setPreviousModalLayer(SCSceneControllerInterface::Ptr pLayer) = 0;
//        virtual void onSCModalGotFocus()=0;
        virtual void pushModalController(SCSceneControllerInterface::Ptr interfacePtr) = 0;
//        virtual void popModalLayer() = 0;
    };
    
    typedef SCSceneControllerInterface::Ptr (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
    typedef SCSceneControllerInterface::Ptr (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
    
#define FN(_fun_)\
    ((decltype(TargetCtlrT::traitFuncPointerType(&TargetCtlrT::_fun_)))(&TargetCtlrT::_fun_))
    
    template<typename TargetCtlrT>
    class SCSceneControllerT :
    public cocos2d::Ref,
    public SCMessageListener,
    public SCSceneControllerInterface
    {
    public:
        typedef SCSceneControllerT<TargetCtlrT>   BaseType_t;
        
        virtual void onCreate(SCDictionary parameters);
        
//        virtual bool isTouchFreezed() const;
//        virtual void setTouchFreezed(const bool bFreeze);
//        virtual void showBlackMask(const bool bShow);
//        virtual bool isBlackMaskForModal() const;
        virtual cocos2d::Layer* getSceneLayer() { return _pSceneLayer; }
        virtual cocos2d::Scene* getScene() { return _pScene; }

//        virtual void setPreviousModalLayer(SCSceneControllerInterface* pLayer);
        virtual void pushModalController(SCSceneControllerInterface::Ptr interfacePtr);
//        virtual void popModalLayer();
        
        static SCSceneControllerInterface::Ptr createScene(const SCDictionary& parameterDic);
        static SCSceneControllerInterface::Ptr createLayer(const SCDictionary& parameterDic);
        
    protected:
        virtual void onSCMessageProcess(SSCMessageInfo& mi);
        void setSceneRootLayer(SCSceneLayer* pLayer) { _pSceneLayer = pLayer;}
        void setScene(SCScene* pScene) {_pScene = pScene;}
        
    protected:
        FUN_SCButtonFunctor_t traitFuncPointerType(bool (TargetCtlrT::*)());
        FUN_SCButtonSenderFunctor_t traitFuncPointerType(bool (TargetCtlrT::*)(cocos2d::MenuItem*));
        cocos2d::SEL_MenuHandler traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Ref*));
        cocos2d::SEL_SCHEDULE traitFuncPointerType(void (TargetCtlrT::*)(float));
        cocos2d::SEL_CallFunc traitFuncPointerType(void (TargetCtlrT::*)());
        cocos2d::SEL_CallFuncN traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*));
        cocos2d::SEL_CallFuncND traitFuncPointerType(void (TargetCtlrT::*)(cocos2d::Node*, void*));
        
    protected:
        SCSceneLayer*			_pSceneLayer;
        SCScene*                _pScene;
    };
    
    ////-------------- member methods
    
    template<typename TargetCtlrT>
    void SCSceneControllerT<TargetCtlrT>::pushModalController(SCSceneControllerInterface::Ptr interfacePtr)
    {
        
    }
    
	////-------------- static methods
    
    template<typename TargetCtlrT>
    SCSceneControllerInterface::Ptr SCSceneControllerT<TargetCtlrT>::createScene(const SCDictionary& parameterDic)
    {
        SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
        auto scene = SCScene::create();
        
        do
        {
            SC_BREAK_IF(!scene);
            
            sceneCtlrPtr.createInstance();
            
            SC_BREAK_IF(sceneCtlrPtr.isNull());
            
            auto rootLayer = SCSceneLayer::create();
            rootLayer->setControllerInterface(sceneCtlrPtr);
            sceneCtlrPtr->setSceneRootLayer(rootLayer);
            
            scene->addChild(rootLayer);
            sceneCtlrPtr->setScene(scene);
            sceneCtlrPtr->onCreate(parameterDic);
            
        } while (0);
        
        return sceneCtlrPtr;
    }
    
    template<typename TargetCtlrT>
    SCSceneControllerInterface::Ptr SCSceneControllerT<TargetCtlrT>::createLayer(const SCDictionary& parameterDic)
    {
        SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
        sceneCtlrPtr.createInstance();
        
        auto rootLayer = SCSceneLayer::create();
        rootLayer->setControllerInterface(sceneCtlrPtr);
        sceneCtlrPtr->setSceneRootLayer(rootLayer);
        
        sceneCtlrPtr->setScene(NULL);
        sceneCtlrPtr->onCreate(parameterDic);

        return sceneCtlrPtr;
    }
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
