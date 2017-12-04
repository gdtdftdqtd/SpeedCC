

#ifndef __SPEEDCC__SCSCENENAVIGATOR_H__
#define __SPEEDCC__SCSCENENAVIGATOR_H__

#include "cocos2d.h"
#include "../base/SCBaseDef.h"
#include "SCSceneControllerT.h"

namespace SpeedCC
{
    /*
    template<typename T>
    struct SCTraitSceneCreateFunctor
    {
        static inline FUN_SCSceneCreateFunctor_t getCreateSceneFunctor()
        {
            return (FUN_SCSceneCreateFunctor_t)(&T::BaseType_t::createScene);
        };
        
        static inline FUN_SCLayerCreateFunctor_t getCreateLayerFunctor()
        {
            return (FUN_SCLayerCreateFunctor_t)(&T::BaseType_t::createLayer);
        };
    };
    
    template<>
    struct SCTraitSceneCreateFunctor<SCClassEmpty>
    {
        static inline FUN_SCSceneCreateFunctor_t getCreateSceneFunctor()
        {
            SCASSERT(false);
            return NULL;
        };
        
        static inline FUN_SCLayerCreateFunctor_t getCreateLayerFunctor()
        {
            SCASSERT(false);
            return NULL;
        };
    };
    */
    
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
        
        struct SStackSceneInfo
        {
            SSceneSwitchInfo                sceneCreatorInfo;
        };

	private:
		static bool switchScene(const SSceneSwitchInfo& info);

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
			switchInfo.pfunCurrentSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SceneT::BaseType_t::createScene);
			switchInfo.pfunCurrentLayerCreator = (FUN_SCLayerCreateFunctor_t)(&SceneT::BaseType_t::createLayer);

			return SCSceneNavigator::switchScene(switchInfo);
		}

		static void back(const int nNumber = 1);
		static void setSceneParameter(const SCDictionary& dic);
//        static SCDictionary getSceneParameter();

	private:
        static SCSceneControllerInterface::Ptr  s_currentSceneInterfacePtr;
		static SCDictionary                     s_SceneParameterDic;
        static std::list<SStackSceneInfo>       s_sceneStack;
    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
