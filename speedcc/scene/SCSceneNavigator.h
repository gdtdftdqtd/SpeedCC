

#ifndef __SPEEDCC__SCSCENENAVIGATOR_H__
#define __SPEEDCC__SCSCENENAVIGATOR_H__

#include "cocos2d.h"
#include "../base/SCBaseDef.h"
#include "SCSceneControllerT.h"

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
		template<typename SceneT, typename TransT = SCClassNull>
		static bool switchScene(const ESceneSwitchType place = SWITCH_REPLACE, SCDictionary dic = SCDictionary())
		{
			SCASSERTCT(!SCIsEmptyClassT<SceneT>::value);

			s_SceneParameterDic = dic;

			SSceneSwitchInfo switchInfo;

			switchInfo.switchType = place;
			switchInfo.pfunSelfTransCreator = &SCTransitionCreator<TransT>::create;
			switchInfo.pfunOppositeTransCreator = &SCTransitionCreator<typename SCTransitionCreator<TransT>::OppositeType>::create;
			switchInfo.pfunCurrentSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SceneT::ControllerBase_t::createScene);
			switchInfo.pfunCurrentLayerCreator = (FUN_SCLayerCreateFunctor_t)(&SceneT::ControllerBase_t::createLayer);

			return SCSceneNavigator::switchScene(switchInfo);
		}

        static SCSceneController::Ptr getCurrentSceneController() {return s_currentSceneControllerPtr;}
		static void back(int nNumber = 1);
        static void reset();
		static void setSceneParameter(const SCDictionary& dic);
//        static SCDictionary getSceneParameter();
        
    private:
        static bool switchScene(const SSceneSwitchInfo& info);

	private:
        static SCSceneController::Ptr           s_currentSceneControllerPtr;
		static SCDictionary                     s_SceneParameterDic;
        static std::list<SStackSceneInfo>       s_sceneStack;
    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
