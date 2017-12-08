
#include "SCSceneNavigator.h"
#include "../SCConfig.h"

using namespace cocos2d;

namespace SpeedCC
{
	SCDictionary                                            SCSceneNavigator::s_SceneParameterDic;
    SCSceneController::Ptr                                  SCSceneNavigator::s_currentSceneControllerPtr;
    std::list<SCSceneNavigator::SStackSceneInfo>            SCSceneNavigator::s_sceneStack;

	void SCSceneNavigator::setSceneParameter(const SCDictionary& dic)
	{
		s_SceneParameterDic = dic;
	}

//    SCDictionary SCSceneNavigator::getSceneParameter()
//    {
//        return s_SceneParameterDic;
//    }

    bool SCSceneNavigator::switchScene(const SSceneSwitchInfo& info)
    {
        SStackSceneInfo navigateInfo;
        
        navigateInfo.sceneCreatorInfo = info;
        
        switch(navigateInfo.sceneCreatorInfo.switchType)
        {
            case SWITCH_MODAL: // modal
            {
                SC_RETURN_IF(s_currentSceneControllerPtr==NULL, false);
                
                auto interfacePtr = (info.pfunCurrentLayerCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                s_currentSceneControllerPtr->pushModalController(interfacePtr);
                s_sceneStack.push_front(navigateInfo);
            }
                break;
                
            case SWITCH_REPLACE: // replace
            case SWITCH_PUSH: // push
            {
                auto controllerPtr = (info.pfunCurrentSceneCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                cocos2d::Scene* pScene = controllerPtr->getScene();
            
                if(navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)
                {
                    pScene = (*navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)(SC_DURATION_OF_SCENE_TRANSITION,pScene);
                }
                
                if(SCCCDirector()->getRunningScene())
                {
                    if(navigateInfo.sceneCreatorInfo.switchType==SWITCH_REPLACE)
                    {
                        SCCCDirector()->replaceScene(pScene);
                        
                        // remove previous modal scene
                        bool bRemoved = false;
                        s_sceneStack.remove_if([&bRemoved](const SStackSceneInfo& stackInfo) -> bool
                                               {
                                                   SC_RETURN_IF(bRemoved, false);
                                                   SC_RETURN_IF(!bRemoved && stackInfo.sceneCreatorInfo.switchType==SWITCH_MODAL, true);
                                                   bRemoved = true;
                                                   return false;
                                               });
                    }
                    else
                    {
                        SCCCDirector()->pushScene(pScene);
                    }
                }
                else
                {
                    SCCCDirector()->runWithScene(pScene);
                }
                
                s_sceneStack.push_front(navigateInfo);
                
                s_currentSceneControllerPtr = controllerPtr;
            }
                break;
                
            default:
                SCASSERT(false);
                break;
        }
        
        return true;
    }
    
    void SCSceneNavigator::back(int nNumber)
    {
        SC_RETURN_IF_V(s_sceneStack.empty());
        if(nNumber<1)
        {
            nNumber = 1;
        }
        auto nSize = s_sceneStack.size();
        SC_RETURN_IF_V(nSize<=nNumber);
        
        FUN_SCSceneTransitionCreateFunctor_t oppositeTrans = NULL;
        auto switchType = SWITCH_REPLACE;
        
        SStackSceneInfo navigateInfo1;
        
        do
        {
            navigateInfo1 = s_sceneStack.front();

            oppositeTrans = navigateInfo1.sceneCreatorInfo.pfunOppositeTransCreator;
            switchType = navigateInfo1.sceneCreatorInfo.switchType;
            s_sceneStack.pop_front();
        }
        while(--nNumber>0);
        
        // use below scene as previous scene
        const auto& navigateInfo2 = s_sceneStack.front();
        
        switch(switchType)
        {
            case SWITCH_MODAL: // mmodal
            {
                s_currentSceneControllerPtr = s_currentSceneControllerPtr->popModalFromParent();
            }
                break;
                
            case SWITCH_PUSH: // push
            {
                SCCCDirector()->popScene();
                SCScene* pScene = (SCScene*)SCCCDirector()->getRunningScene();
                auto rootLayer = pScene->getRootLayer();
                SCASSERT(rootLayer!=NULL);
                s_currentSceneControllerPtr = rootLayer->getController().cast<SCSceneController>();
                SCASSERT(s_currentSceneControllerPtr!=NULL);
            }
                break;
                
            case SWITCH_REPLACE: // replace
            {
                SCASSERT(navigateInfo2.sceneCreatorInfo.pfunCurrentSceneCreator!=NULL);
                
                // remove all of SWITCH_MODAL layer from navigator stack
                size_t nStackSize = s_sceneStack.size();
                while(nStackSize>2)
                {
                    if(s_sceneStack.front().sceneCreatorInfo.switchType==SWITCH_MODAL)
                    {
                        s_sceneStack.pop_front();
                        --nStackSize;
                    }
                    else
                    {
                        break;
                    }
                }
                
                auto sceneControllerPtr = (*navigateInfo2.sceneCreatorInfo.pfunCurrentSceneCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                auto call = [oppositeTrans]() -> void
                {
                    cocos2d::Scene* pScene = SCScene::create();
                    if(oppositeTrans)
                    {
                        pScene = (*oppositeTrans)(SC_DURATION_OF_SCENE_TRANSITION,pScene);
                    }
                    
                    SCCCDirector()->replaceScene(pScene);
                };
                
                call();
                s_currentSceneControllerPtr = sceneControllerPtr;
            }
                break;
                
            default:
                SCASSERT(false);
                break;
        }
    }
    
    void SCSceneNavigator::reset()
    {
        SC_RETURN_IF_V(s_sceneStack.empty());
        auto info = s_sceneStack.front();
        s_sceneStack.clear();
        s_sceneStack.push_back(info);
    }
}


