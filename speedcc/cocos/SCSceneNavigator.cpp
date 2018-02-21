/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/


#include "SCSceneNavigator.h"
#include "../SCConfig.h"

using namespace cocos2d;

namespace SpeedCC
{
    SCSceneNavigator*           SCSceneNavigator::s_pInstance = nullptr;
    
    SCSceneNavigator* SCSceneNavigator::getInstance()
    {
        if(s_pInstance==nullptr)
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

    bool SCSceneNavigator::gotoScene(const SSceneSwitchInfo& info)
    {
        SStackSceneInfo navigateInfo;
        navigateInfo.sceneCreatorInfo = info;
        
        switch(navigateInfo.sceneCreatorInfo.switchType)
        {
            case kSceneModal: // modal
            {
                SC_RETURN_IF(s_ptrCurrentSceneController==nullptr, false);
                
                auto call = [this,info,navigateInfo]()
                {
                    auto ptrController = (info.pfunLayerCreator)(s_SceneParameterDic);
                    s_SceneParameterDic.removeAllKeys();
                    
                    s_ptrCurrentSceneController->pushModalController(ptrController);
                    s_sceneStack.push_front(navigateInfo);
                    s_ptrCurrentSceneController = ptrController;
                };
                
                if(info.bHasLoading)
                {
                    SCSceneController::FinishFunc_t finishFunc = [this,call](void*)
                    {
                        s_ptrCurrentSceneController = s_ptrCurrentSceneController->popModalFromParent();
                        call();
                    };
                    
                    s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                    auto ptrController = (info.pfunLoadingLayerCreator)(s_SceneParameterDic);
                    s_ptrCurrentSceneController->pushModalController(ptrController);
                    s_sceneStack.push_front(navigateInfo);
                    s_ptrCurrentSceneController = ptrController;
                }
                else
                {
                    call();
                }
            }
                break;
                
            case kSceneReplace: // replace
            case kScenePush: // push
            {
                auto call = [this,info,navigateInfo]()
                {
                    auto ptrController = (info.pfunSceneCreator)(s_SceneParameterDic);
                    s_SceneParameterDic.removeAllKeys();
                    
                    cocos2d::Scene* pScene = ptrController->getScene();
                    
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
                    s_ptrCurrentSceneController = ptrController;
                };
                
                if(info.bHasLoading)
                {
                    SCSceneController::FinishFunc_t finishFunc = [call](void*) { call(); };
                    s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                    auto ptrController = (info.pfunLoadingSceneCreator)(s_SceneParameterDic);
                    cocos2d::Scene* pScene = ptrController->getScene();
                    
                    if(SCCCDirector()->getRunningScene())
                    {
                        if(navigateInfo.sceneCreatorInfo.switchType==kSceneReplace)
                        {
                            SCCCDirector()->replaceScene(pScene);
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
                    
                    s_ptrCurrentSceneController = ptrController;
                }
                else
                {
                    call();
                }
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
        
        FUN_SCSceneTransitionCreateFunctor_t oppositeTrans = nullptr;
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
                SCASSERT(rootLayer!=nullptr);
                s_ptrCurrentSceneController = rootLayer->getController().cast<SCSceneController::Ptr>();
                SCASSERT(s_ptrCurrentSceneController!=nullptr);
            }
                break;
                
            case kSceneReplace: // replace
            {
                SCASSERT(navigateInfo2.sceneCreatorInfo.pfunSceneCreator!=nullptr);
                
                // remove all of kSceneModal layer from navigator stack
                size_t nStackSize = s_sceneStack.size();
                while(nStackSize>2)
                {
                    SC_BREAK_IF(s_sceneStack.front().sceneCreatorInfo.switchType!=kSceneModal)
                    s_sceneStack.pop_front();
                    --nStackSize;
                }
                
                auto call = [navigateInfo2,oppositeTrans,this]()
                {
                    auto ptrController = (*navigateInfo2.sceneCreatorInfo.pfunSceneCreator)(s_SceneParameterDic);
                    cocos2d::Scene* pScene = ptrController->getScene();
                    if(oppositeTrans)
                    {
                        pScene = (*oppositeTrans)(kSCDurationOfSceneTransition,pScene);
                    }
                    
                    SCCCDirector()->replaceScene(pScene);
                    
                    s_ptrCurrentSceneController = ptrController;
                    s_SceneParameterDic.removeAllKeys();
                };
                
                if(navigateInfo2.sceneCreatorInfo.bHasLoading)
                {
                    SCSceneController::FinishFunc_t finishFunc = [call](void*) { call(); };
                    s_SceneParameterDic.setValue(SC_KEY_FINISHFUNC, finishFunc);
                    auto ptrController = (*navigateInfo2.sceneCreatorInfo.pfunLoadingSceneCreator)(s_SceneParameterDic);
                    cocos2d::Scene* pScene = ptrController->getScene();
                    
                    SCCCDirector()->replaceScene(pScene);
                    s_ptrCurrentSceneController = ptrController;
                }
                else
                {
                    call();
                }
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


