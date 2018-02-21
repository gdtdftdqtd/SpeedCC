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

#ifndef __SPEEDCC__SCFLOWMACRO_H__
#define __SPEEDCC__SCFLOWMACRO_H__

#define SC_BEGIN_ROLE(_role_id_,_strategy_id_,_stage_) \
do{\
    SpeedCC::SCRoleBuilder::Ptr ptrSCRoleBuilder = SpeedCC::SCRoleBuilder::create(); \
    ptrSCRoleBuilder->begin((_role_id_),(_strategy_id_),(_stage_));\


#define SC_END_ROLE \
    ptrSCRoleBuilder->end();\
}while(0);

#define IN_STRATEGY(_strategy_id_) \
do{\
    ptrSCRoleBuilder->beginStragtegy((_strategy_id_));

#define ENDIN_STRATEGY \
    ptrSCRoleBuilder->endStrategy();\
}while(0);

#define ON_MSG_BEHAVIOR(_msg_,_behavior_) \
    ptrSCRoleBuilder->insertBehaviorWithMsg((_msg_),(_behavior_));

#define ON_CMD_BEHAVIOR(_cmd_,_behavior_) \
    ptrSCRoleBuilder->insertBehaviorWithCmd((_cmd_),(_behavior_));

#define ON_ENTER_STRATEGE(_behavior_) \
    ptrSCRoleBuilder->insertEnterBehavior((_behavior_));

#define ON_EXIT_STRATEGE(_behavior_) \
    ptrSCRoleBuilder->insertExitBehavior((_behavior_));

#define ON_MSG_ROLE_ACTIVE(_msg_,_role_id_,_active_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorRoleActive::create((_role_id_),(_active_)); \
    ON_MSG_BEHAVIOR((_msg_),ptrBvr)\
}while(0);

#define ON_CMD_ACTIVE(_cmd_,_role_id_,_active_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorRoleActive::create((_role_id_),(_active_)); \
    ON_CMD_BEHAVIOR((_cmd_),ptrBvr)\
}while(0);

#define ON_MSG_SCENE(_msg_,_scene_class_,_switch_type_,_trans_class_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorSceneSwitch::create<_scene_class_,_trans_class_>((_switch_type_));\
    ON_MSG_BEHAVIOR((_msg_),ptrBvr)\
}while(0);

#define ON_CMD_SCENE(_cmd_,_scene_class_,_switch_type_,_trans_class_) \
do{\
    auto ptrBvr = SpeedCC::SCBehaviorSceneSwitch::create<_scene_class_,_trans_class_>((_switch_type_));\
    ON_CMD_BEHAVIOR((_cmd_),ptrBvr)\
}while(0);

#define ON_MSG(_msg_) \
    ON_MSG_BEHAVIOR((_msg_),nullptr)

#define ON_MSG_NEXT_STRATEGY(_msg_,_stragegy_id_) \
do{\
    auto bvrPtr = SpeedCC::SCBehaviorStrategySwitch::create((_stragegy_id_));\
    ON_MSG_BEHAVIOR(_msg_,bvrPtr)\
}while(0);

#endif // __SPEEDCC__SCFLOWMACRO_H__
