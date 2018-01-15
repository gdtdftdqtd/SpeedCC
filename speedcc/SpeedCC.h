

#ifndef __SPEEDCC__SPEEDCC_H__
#define __SPEEDCC__SPEEDCC_H__

///////////////////////////////////////////////////////////////////////////////
/// SPEEDCC version
// 0x00 HI ME LO
// 00   00 00 00
#define SPEEDCC_VERSION 0x00000100

#include "base/SCMacroDef.h"
#include "base/SCObject.h"
#include "base/SCString.h"
#include "base/SCBufferRefT.h"
#include "base/SCDataBlock.h"
#include "base/SCDateTime.h"
#include "base/SCValue.h"
#include "base/SCObjPtrT.h"
#include "base/SCDictionary.h"
#include "base/SCVersion.h"
#include "base/SCWatchNumberT.h"
#include "base/SCWatchString.h"

#include "system/SCSystem.h"
#include "system/SCFileUtils.h"
#include "system/SCSetting.h"

#include "cocos/SCRefHolder.h"
#include "cocos/SCSceneNavigator.h"
#include "cocos/SCSceneController.h"
#include "cocos/SCNodeProperty.h"
#include "cocos/SCBinder.h"
#include "cocos/SCNodeUtils.h"
#include "cocos/SCUIMacro.h"
#include "cocos/SCEventEmitter.h"

#include "component/SCFlowMacro.h"
#include "component/SCStage.h"
#include "component/SCRole.h"
#include "component/SCStrategy.h"
#include "component/SCBehaviorCommon.h"
#include "component/SCActor.h"
#include "component/SCMessageDispatch.h"
#include "component/SCBehaviorStage.h"
#include "component/SCBehaviorCocos.h"



#endif // __SPEEDCC__SPEEDCC_H__
