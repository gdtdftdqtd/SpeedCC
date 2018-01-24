
#include "SCSceneNavigator.h"
#include "../SCConfig.h"

using namespace cocos2d;

namespace SpeedCC
{
    SCSceneNavigator*           SCSceneNavigator::s_pInstance = NULL;
    
    SCSceneNavigator* SCSceneNavigator::getInstance()
    {
        if(s_pInstance==NULL)
        {
            s_pInstance = new SCSceneNavigator();
        }
        
        return s_pInstance;
    }
    
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
            case kSceneModal: // modal
            {
                SC_RETURN_IF(s_ptrCurrentSceneController==NULL, false);
                
                auto ptrController = (info.pfunCurrentLayerCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                s_ptrCurrentSceneController->pushModalController(ptrController);
                s_sceneStack.push_front(navigateInfo);
                s_ptrCurrentSceneController = ptrController;
            }
                break;
                
            case kSceneReplace: // replace
            case kScenePush: // push
            {
                auto controllerPtr = (info.pfunCurrentSceneCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                cocos2d::Scene* pScene = controllerPtr->getScene();
            
                if(navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)
                {
                    pScene = (*navigateInfo.sceneCreatorInfo.pfunSelfTransCreator)(kSCDurationOfSceneTransition,pScene);
                }
                
                if(SCCCDirector()->getRunningScene())
                {
                    if(navigateInfo.sceneCreatorInfo.switchType==kSceneReplace)
                    {
                        SCCCDirector()->replaceScene(pScene);
                        
                        // remove previous modal scene
                        bool bRemoved = false;
                        s_sceneStack.remove_if([&bRemoved](const SStackSceneInfo& stackInfo) -> bool
                                               {
                                                   SC_RETURN_IF(bRemoved, false);
                                                   SC_RETURN_IF(!bRemoved && stackInfo.sceneCreatorInfo.switchType==kSceneModal, true);
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
                s_ptrCurrentSceneController = controllerPtr;
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
        SC_RETURN_V_IF(s_sceneStack.empty());
        if(nNumber<1)
        {
            nNumber = 1;
        }
        auto nSize = s_sceneStack.size();
        SC_RETURN_V_IF(nSize<=nNumber);
        
        FUN_SCSceneTransitionCreateFunctor_t oppositeTrans = NULL;
        auto switchType = kSceneReplace;
        
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
            case kSceneModal: // modal
            {
                s_ptrCurrentSceneController = s_ptrCurrentSceneController->popModalFromParent();
            }
                break;
                
            case kScenePush: // push
            {
                SCCCDirector()->popScene();
                SCScene* pScene = (SCScene*)SCCCDirector()->getRunningScene();
                auto rootLayer = pScene->getBedNode();
                SCASSERT(rootLayer!=NULL);
                s_ptrCurrentSceneController = rootLayer->getController().cast<SCSceneController::Ptr>();
                SCASSERT(s_ptrCurrentSceneController!=NULL);
            }
                break;
                
            case kSceneReplace: // replace
            {
                SCASSERT(navigateInfo2.sceneCreatorInfo.pfunCurrentSceneCreator!=NULL);
                
                // remove all of kSceneModal layer from navigator stack
                size_t nStackSize = s_sceneStack.size();
                while(nStackSize>2)
                {
                    SC_BREAK_IF(s_sceneStack.front().sceneCreatorInfo.switchType!=kSceneModal)
                    s_sceneStack.pop_front();
                    --nStackSize;
                }
                
                auto controllerPtr = (*navigateInfo2.sceneCreatorInfo.pfunCurrentSceneCreator)(s_SceneParameterDic);
                s_SceneParameterDic.removeAllKeys();
                
                cocos2d::Scene* pScene = controllerPtr->getScene();
                if(oppositeTrans)
                {
                    pScene = (*oppositeTrans)(kSCDurationOfSceneTransition,pScene);
                }
                
                SCCCDirector()->replaceScene(pScene);
                
                s_ptrCurrentSceneController = controllerPtr;
            }
                break;
                
            default:
                SCASSERT(false);
                break;
        }
    }
    
    void SCSceneNavigator::reset()
    {
        SC_RETURN_V_IF(s_sceneStack.empty());
        auto info = s_sceneStack.front();
        s_sceneStack.clear();
        s_sceneStack.push_back(info);
    }
}


