

#ifndef __SPEEDCC__SCSCENENAVIGATOR_H__
#define __SPEEDCC__SCSCENENAVIGATOR_H__

#include "cocos2d.h"
#include "../base/SCBaseDef.h"
#include "SCCocosDef.h"
#include "SCSceneController.h"

namespace SpeedCC
{
    class SCSceneNavigator final
    {
        friend class SCBehaviorSceneNavigate;
	public:
		enum ESceneSwitchType
		{
			kSceneReplace, // use cocos2d replace scene
			kScenePush, // use cocos2d push scene
			kSceneModal, // push SCSceneLayer as modal layer
		};

    private:
        typedef SCSceneController::Ptr (*FUN_SCSceneCreateFunctor_t)(const SCDictionary& dic);
        typedef SCSceneController::Ptr (*FUN_SCLayerCreateFunctor_t)(const SCDictionary& dic);
        typedef cocos2d::Scene* (*FUN_SCSceneTransitionCreateFunctor_t)(const float fDuration, cocos2d::Scene* pScene);
        
    public:
		struct SSceneSwitchInfo
		{
			ESceneSwitchType						switchType;
			FUN_SCSceneTransitionCreateFunctor_t	pfunSelfTransCreator; 
			FUN_SCSceneTransitionCreateFunctor_t	pfunOppositeTransCreator;
			FUN_SCSceneCreateFunctor_t              pfunCurrentSceneCreator;
			FUN_SCLayerCreateFunctor_t              pfunCurrentLayerCreator;

			SSceneSwitchInfo() :
				switchType(kSceneReplace),
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
            
            template<typename SceneT, typename TransT = SCClassNull>
            void setUp(const ESceneSwitchType place = kSceneReplace)
            {
                static_assert(!SCIsEmptyClassT<SceneT>::value,"target scene should not empty class");
                
                TransT* pTrans = NULL;
                switchType = place;
                pfunSelfTransCreator = &SCTransitionCreator<TransT>::create;
                pfunOppositeTransCreator = &SCTransitionCreator< decltype(SCTraitTransitionSceneOpposite(pTrans)) >::create;
                pfunCurrentSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigator::createScene<SceneT>);
                pfunCurrentLayerCreator = (FUN_SCLayerCreateFunctor_t)(&SCSceneNavigator::createLayer<SceneT>);
            }
		};
        
        struct SStackSceneInfo
        {
            SSceneSwitchInfo                sceneCreatorInfo;
        };

    public:
        static SCSceneNavigator* getInstance();
        
        template<typename SceneT, typename TransT = SCClassNull>
        bool switchScene(const ESceneSwitchType place = kSceneReplace, const SCDictionary& dic = SCDictionary())
		{
            static_assert(!SCIsEmptyClassT<SceneT>::value,"target scene should not empty class");

			s_SceneParameterDic = dic;

			SSceneSwitchInfo switchInfo;

            switchInfo.setUp<SceneT,TransT>(place);
			return SCSceneNavigator::getInstance()->switchScene(switchInfo);
		}

        SCSceneController::Ptr getCurrentController() {return s_ptrCurrentSceneController;}
        void back(int nNumber = 1);
        void reset();
        void setSceneParameter(const SCDictionary& dic);
//        static SCDictionary getSceneParameter();
        
    private:
        bool switchScene(const SSceneSwitchInfo& info);
        
        template<typename TargetCtlrT>
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic)
        {
            SCObjPtrT<TargetCtlrT> ptrSceneCtlr;
            
            do
            {
                ptrSceneCtlr.createInstance();
                
                SC_BREAK_IF(ptrSceneCtlr.isNull());
                
                auto scene = SCScene::create();
                auto pRootLayer = scene->getBedNode();
                pRootLayer->setController(ptrSceneCtlr);
                ptrSceneCtlr->setScene(scene);
                ptrSceneCtlr->setBedNode(pRootLayer);
                ptrSceneCtlr->onCreate(parameterDic);
                
            } while (0);
            
            return ptrSceneCtlr;
        }
        
        template<typename TargetCtlrT>
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic)
        {
            SCObjPtrT<TargetCtlrT> ptrSceneCtlr;
            ptrSceneCtlr.createInstance();
            
            auto rootLayer = SCBedNode::create();
            rootLayer->setController(ptrSceneCtlr);
            ptrSceneCtlr->setBedNode(rootLayer);
            
            ptrSceneCtlr->setScene(NULL);
            ptrSceneCtlr->onCreate(parameterDic);
            
            return ptrSceneCtlr;
        }

	private:
        SCSceneController::Ptr           s_ptrCurrentSceneController;
        SCDictionary                     s_SceneParameterDic;
        std::list<SStackSceneInfo>       s_sceneStack;
        static SCSceneNavigator*         s_pInstance;
    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
