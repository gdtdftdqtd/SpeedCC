
#include "SCSceneNavigator.h"


namespace SpeedCC
{
	SCDictionary    SCSceneNavigator::s_SceneParameterDic;

	void SCSceneNavigator::setSceneParameter(const SCDictionary& dic)
	{
		s_SceneParameterDic = dic;
	}

	SCDictionary SCSceneNavigator::getSceneParameter()
	{
		return s_SceneParameterDic;
	}

}


