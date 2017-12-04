
#include "SCSceneNavigator.h"
#include "../SCConfig.h"

namespace SpeedCC
{
	SCDictionary                                            SCSceneNavigator::s_SceneParameterDic;
    SCSceneControllerInterface::Ptr                         SCSceneNavigator::s_currentSceneInterfacePtr;
    std::list<SCSceneNavigator::SStackSceneInfo>            SCSceneNavigator::s_sceneStack;

	void SCSceneNavigator::setSceneParameter(const SCDictionary& dic)
	{
		s_SceneParameterDic = dic;
	}

//    SCDictionary SCSceneNavigator::getSceneParameter()
//    {
//        return s_SceneParameterDic;
//    }

    
    
    void SCSceneNavigator::back(const int nNumber)
    {
        
    }
}


