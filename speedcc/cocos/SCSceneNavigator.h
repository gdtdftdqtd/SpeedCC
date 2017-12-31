

#ifndef __SPEEDCC__SCSCENENAVIGATOR_H__
#define __SPEEDCC__SCSCENENAVIGATOR_H__

#include "cocos2d.h"
#include "../base/SCBaseDef.h"
#include "SCSceneController.h"

namespace SpeedCC
{
    class SCSceneNavigator final
    {
	public:
		enum ESceneSwitchType
		{
			SWITCH_REPLACE, // use cocos2d replace scene
			SWITCH_PUSH, // use cocos2d push scene
			SWITCH_MODAL, // push SCSceneLayer as modal layer
		};

    private:
        typedef SCSceneController::Ptr (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
        typedef SCSceneController::Ptr (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
        typedef cocos2d::Scene* (*FUN_SCSceneTransitionCreateFunctor_t)(const float fDuration, cocos2d::Scene* pScene);
        
		struct SSceneSwitchInfo
		{
			ESceneSwitchType						switchType;
			FUN_SCSceneTransitionCreateFunctor_t	pfunSelfTransCreator; 
			FUN_SCSceneTransitionCreateFunctor_t	pfunOppositeTransCreator;
			FUN_SCSceneCreateFunctor_t              pfunCurrentSceneCreator;
			FUN_SCLayerCreateFunctor_t              pfunCurrentLayerCreator;

			SSceneSwitchInfo() :
				switchType(SWITCH_REPLACE),
				pfunSelfTransCreator(NULL),
				pfunOppositeTransCreator(NULL),
				pfunCurrentSceneCreator(NULL),
				pfunCurrentLayerCreator(NULL)
			{}

			SSceneSwitchInfo(ESceneSwitchType type,
				FUN_SCSceneTransitionCreateFunctor_t pfunSelfTrans,
				FUN_SCSceneTransitionCreateFunctor_t pfunOppositeTrans,
				FUN_SCSceneCreateFunctor_t pfunScene,
				FUN_SCLayerCreateFunctor_t pfunLayer) :
				switchType(type),
				pfunSelfTransCreator(pfunSelfTrans),
				pfunOppositeTransCreator(pfunOppositeTrans),
				pfunCurrentSceneCreator(pfunScene),
				pfunCurrentLayerCreator(pfunLayer)
			{}
		};
        
        struct SStackSceneInfo
        {
            SSceneSwitchInfo                sceneCreatorInfo;
        };

    public:
        static SCSceneNavigator* getInstance();
        
		template<typename SceneT, typename TransT = SCClassNull>
        bool switchScene(const ESceneSwitchType place = SWITCH_REPLACE, SCDictionary dic = SCDictionary())
		{
			SCASSERTCT(!SCIsEmptyClassT<SceneT>::value);

			s_SceneParameterDic = dic;

			SSceneSwitchInfo switchInfo;

			switchInfo.switchType = place;
			switchInfo.pfunSelfTransCreator = &SCTransitionCreator<TransT>::create;
			switchInfo.pfunOppositeTransCreator = &SCTransitionCreator<typename SCTransitionCreator<TransT>::OppositeType>::create;
            switchInfo.pfunCurrentSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigator::createScene<SceneT>);
            switchInfo.pfunCurrentLayerCreator = (FUN_SCLayerCreateFunctor_t)(&SCSceneNavigator::createLayer<SceneT>);

			return SCSceneNavigator::getInstance()->switchScene(switchInfo);
		}

        SCSceneController::Ptr getCurrentController() {return s_currentSceneControllerPtr;}
        void back(int nNumber = 1);
        void reset();
        void setSceneParameter(const SCDictionary& dic);
//        static SCDictionary getSceneParameter();
        
    private:
        bool switchScene(const SSceneSwitchInfo& info);
        
        template<typename TargetCtlrT>
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic)
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
                sceneCtlrPtr->onSetupStage();
                
            } while (0);
            
            return sceneCtlrPtr;
        }
        
        template<typename TargetCtlrT>
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic)
        {
            SCObjPtrT<TargetCtlrT> sceneCtlrPtr;
            sceneCtlrPtr.createInstance();
            
            auto rootLayer = SCLayerRoot::create();
            rootLayer->setController(sceneCtlrPtr);
            sceneCtlrPtr->setSceneRootLayer(rootLayer);
            
            sceneCtlrPtr->setScene(NULL);
            sceneCtlrPtr->onCreate(parameterDic);
            sceneCtlrPtr->onSetupStage();
            
            return sceneCtlrPtr;
        }

	private:
        SCSceneController::Ptr           s_currentSceneControllerPtr;
        SCDictionary                     s_SceneParameterDic;
        std::list<SStackSceneInfo>       s_sceneStack;
        static SCSceneNavigator*         s_pInstance;
    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
