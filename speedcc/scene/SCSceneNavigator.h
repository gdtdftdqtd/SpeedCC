

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

	private:
		static void switchScene(const SSceneSwitchInfo& info);

		template<typename SceneT, typename TransT = SCClassNull>
		static void switchScene(const ESceneSwitchType place = SWITCH_REPLACE, SCDictionary dic = SCDictionary())
		{
			SCASSERTCT(!SCIsEmptyClassT<SceneT>::value);

			s_SceneParameterDic = dic;

			SSCSwitchSceneInfo switchInfo;

			switchInfo.scenePlace = place;
			switchInfo.pfunSelfTransCreator = &SCCCTransitionCreator<TransT>::create;
			switchInfo.pfunOppositeTransCreator = &SCCCTransitionCreator<typename SCCCTransitionCreator<TransT>::OppositeType>::create;
			switchInfo.pfunCurrentSceneCreator = SCTraitSceneCreateFunctor<SceneT>::getCreateSceneFunctor();
			switchInfo.pfunCurrentLayerCreator = SCTraitSceneCreateFunctor<SceneT>::getCreateLayerFunctor();

			SCSceneNavigator::switchScene(switchInfo);
		}

	public:
		static void back(const int nNumber = 1);
		static void setSceneParameter(const SCDictionary& dic);
		static SCDictionary getSceneParameter();

	private:
		static SCDictionary     s_SceneParameterDic;

    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
