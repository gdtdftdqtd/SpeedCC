

#ifndef __SPEEDCC__SCSCENENAVIGATOR_H__
#define __SPEEDCC__SCSCENENAVIGATOR_H__

#include "cocos2d.h"
#include "SCCocosDef.h"
#include "SCSceneController.h"

#include "../base/SCBaseDef.h"

namespace SpeedCC
{
    
    template<typename T>
    struct SCSceneNavigationCreator
    {
        static cocos2d::Scene* createTransition(float duration,cocos2d::Scene* pScene)
        {
            return T::create(duration, pScene);
        }
        
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic)
        {
            SCObjPtrT<T> ptrSceneCtlr;
            
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
        
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic)
        {
            SCObjPtrT<T> ptrSceneCtlr;
            ptrSceneCtlr.createInstance();
            
            auto rootLayer = SCBedNode::create();
            rootLayer->setController(ptrSceneCtlr);
            ptrSceneCtlr->setBedNode(rootLayer);
            
            ptrSceneCtlr->setScene(NULL);
            ptrSceneCtlr->onCreate(parameterDic);
            
            return ptrSceneCtlr;
        }
    };
    
    template<>
    struct SCSceneNavigationCreator<SCClassNull>
    {
        static cocos2d::Scene* createTransition(float duration,cocos2d::Scene* pScene)
        {return pScene;}
        
        static SCSceneController::Ptr createScene(const SCDictionary& parameterDic)
        { return NULL; }
        
        static SCSceneController::Ptr createLayer(const SCDictionary& parameterDic)
        { return NULL; }
    };
    
    
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
			FUN_SCSceneCreateFunctor_t              pfunSceneCreator;
            FUN_SCLayerCreateFunctor_t              pfunLayerCreator;
            FUN_SCSceneCreateFunctor_t              pfunLoadingSceneCreator;
            FUN_SCLayerCreateFunctor_t              pfunLoadingLayerCreator;
            bool                                    bHasLoading;
            
			SSceneSwitchInfo() :
				switchType(kSceneReplace),
				pfunSelfTransCreator(NULL),
				pfunOppositeTransCreator(NULL),
				pfunSceneCreator(NULL),
                pfunLayerCreator(NULL),
            pfunLoadingSceneCreator(NULL),
            pfunLoadingLayerCreator(NULL),
                bHasLoading(false)
			{}

            SSceneSwitchInfo(ESceneSwitchType type,
                             FUN_SCSceneTransitionCreateFunctor_t pfunSelfTrans,
                             FUN_SCSceneTransitionCreateFunctor_t pfunOppositeTrans,
                             FUN_SCSceneCreateFunctor_t pfunScene,
                             FUN_SCLayerCreateFunctor_t pfunLayer,
                             FUN_SCSceneCreateFunctor_t pfunLoadingScene,
                             FUN_SCLayerCreateFunctor_t pfunLoadingLayer,
                             bool bLoading) :
            switchType(type),
            pfunSelfTransCreator(pfunSelfTrans),
            pfunOppositeTransCreator(pfunOppositeTrans),
            pfunSceneCreator(pfunScene),
            pfunLayerCreator(pfunLoadingScene),
            pfunLoadingSceneCreator(pfunScene),
            pfunLoadingLayerCreator(pfunLoadingScene),
            bHasLoading(bLoading)
            {}
            
            template<typename SceneT, typename TransT = SCClassNull, typename LoadingT=SCClassNull>
            void setUp(const ESceneSwitchType place = kSceneReplace)
            {
                static_assert(!SCIsEmptyClassT<SceneT>::value,"target scene should not empty class");
                
                TransT* pTrans = NULL;
                switchType = place;
                pfunSelfTransCreator = &SCSceneNavigationCreator<TransT>::createTransition;
                pfunOppositeTransCreator = &SCSceneNavigationCreator< decltype(SCTraitsTransitionSceneOpposite(pTrans)) >::createTransition;
                pfunSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigationCreator<SceneT>::createScene);
                pfunLayerCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigationCreator<SceneT>::createLayer);
                
                pfunLoadingSceneCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigationCreator<LoadingT>::createScene);
                pfunLoadingLayerCreator = (FUN_SCSceneCreateFunctor_t)(&SCSceneNavigationCreator<LoadingT>::createLayer);
                
                bHasLoading = std::is_same<LoadingT,SCClassNull>::value ? false : true;
            }
		};
        
        struct SStackSceneInfo
        {
            SSceneSwitchInfo                sceneCreatorInfo;
        };

    public:
        static SCSceneNavigator* getInstance();
        
        template<typename SceneT, typename TransT = SCClassNull, typename LoadingT=SCClassNull>
        bool switchScene(const ESceneSwitchType place = kSceneReplace, const SCDictionary& dic = SCDictionary())
		{
            static_assert(std::is_base_of<SCSceneController,SceneT>::value,
                          "Target Scene Must Derive From SCSceneController");

			s_SceneParameterDic = dic;

			SSceneSwitchInfo switchInfo;

            switchInfo.setUp<SceneT,TransT,LoadingT>(place);
			return SCSceneNavigator::getInstance()->switchScene(switchInfo);
		}

        SCSceneController::Ptr getCurrentController() {return s_ptrCurrentSceneController;}
        void back(int nNumber = 1);
        void reset();
        void setSceneParameter(const SCDictionary& dic);
        
    private:
        bool switchScene(const SSceneSwitchInfo& info);
        
	private:
        SCSceneController::Ptr           s_ptrCurrentSceneController;
        SCDictionary                     s_SceneParameterDic;
        std::list<SStackSceneInfo>       s_sceneStack;
        static SCSceneNavigator*         s_pInstance;
    };
}

#endif // __SPEEDCC__SCSCENENAVIGATOR_H__
