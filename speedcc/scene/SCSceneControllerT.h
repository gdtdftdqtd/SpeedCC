

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"
#include "SCSceneLayer.h"
#include "../component/SCMessageDispatch.h"
#include "../base/SCBaseCommon.h"

namespace SpeedCC
{
    struct SCSceneControllerInterface
    {
        virtual bool isTouchFreezed() const = 0;
        virtual void setTouchFreezed(const bool bFreeze) = 0;
        virtual void showBlackMask(const bool bShow) = 0;
        virtual bool isBlackMaskForModal() const = 0;
        virtual cocos2d::Layer* getSceneLayer() = 0;
        
    protected:
        virtual void setSceneRootLayer(cocos2d::Layer* pLayer) = 0;
        virtual void setPreviousModalLayer(SCSceneControllerInterface* pLayer) = 0;
        virtual void onSCModalGotFocus()=0;
        virtual void pushModalLayer(SCSceneControllerInterface* pLayer) = 0;
        virtual void popModalLayer() = 0;
    };
    
#define FN(_fun_)\
    ((decltype(TargetCtlrT::traitFuncPointerType(&TargetCtlrT::_fun_)))(&TargetCtlrT::_fun_))
    
    template<typename TargetCtlrT>
    class SCSceneControllerT :
    public cocos2d::Ref,
    public SCMessageListener,
    public SCSceneControllerInterface
    {
    public:
        virtual void onCreate(SCDictionary parameters);
        
        virtual bool isTouchFreezed() const;
        virtual void setTouchFreezed(const bool bFreeze);
        virtual void showBlackMask(const bool bShow);
        virtual bool isBlackMaskForModal() const;
        virtual cocos2d::Layer* getSceneLayer() { return _pSceneLayer; }
        
        static SSceneControllerInfo createScene();
        static SCSceneControllerInterface* createLayer();
        
        
    protected:
        virtual void onSCMessageProcess(SSCMessageInfo& mi);
        
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
		//SCEntity				_performerEntity;
    };
    


	////-------------- static method
	template<typename TargetCtlrT>
	void SCSceneControllerT<TargetCtlrT>::setSceneParameter(const SCDictionary& dic)
	{
		s_SceneParameterDic = dic;
	}
    
    template<typename TargetCtlrT>
    SSceneControllerInfo SCSceneControllerT<TargetCtlrT>::createScene()
    {
        SSceneControllerInfo ret;
        cocos2d::Scene* scene = cocos2d::Scene::create();
        ret.pScene = scene;
        
        do
        {
            SC_BREAK_IF(!scene);
            
            SCObjPtrT<T> sceneCtlrPtr;
            sceneCtlrPtr.createInstance();
            
            SC_BREAK_IF(sceneCtlrPtr.isNull());
            
            cocos2d::Layer* rootLayer = cocos2d::Layer::create();
            sceneCtlrPtr->setSceneRootLayer(rootLayer);
            
            sceneCtlrPtr->onCreate(s_SceneParameterDic);
            ret.pInterface = sceneCtlrPtr;
            
            rootLayer->addChild((cocos2d::Node *)sceneCtlrPtr->getSceneLayer());
            scene->addChild(rootLayer);

			s_SceneParameterDic.removeAllKeys();
            
        } while (0);
        
        return ret;
    }
    
    template<typename TargetCtlrT>
    SCSceneControllerInterface* SCSceneControllerT<TargetCtlrT>::createLayer()
    {
        auto pRet = cocos2d::Layer::create();
        
        SCASSERT(pRet!=NULL);
        
        sceneCtlrPtr->onCreate(s_SceneParameterDic);
		s_SceneParameterDic.removeAllKeys();

        return pRet ;
    }
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
