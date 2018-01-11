//
//  Header.h
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCFLOWMACRO_H__
#define __SPEEDCC__SCFLOWMACRO_H__

namespace SpeedCC
{
    class SCFlowSetup
    {
    public:
        static int extractMsgID(const int nMsgID) { return nMsgID;}
        static int extractMsgID(SCMessageMatcher::Ptr matcherPtr) { return matcherPtr->getMessageID();}
        
        static SCMessageMatcher::Ptr extractMsgMatcher(const int nMsgID) { return NULL;}
        static SCMessageMatcher::Ptr extractMsgMatcher(SCMessageMatcher::Ptr matcherPtr) { return matcherPtr;}
        
        static SCBehavior::Ptr extractBehavior(SCBehavior::Ptr bvrPtr) {return bvrPtr;}
        static SCBehavior::Ptr extractBehavior(const std::function<void(const SCDictionary& par)>& func)
        {
            return SCBehaviorCallFunc::create(func);
        }
        static SCBehavior::Ptr extractBehavior(const std::function<void()>& func)
        {
            return SCBehaviorCallFunc::create([func](const SCDictionary& par)
                                              {
                                                  func();
                                              });
        }
        static SCBehavior::Ptr extractBehavior(void*) {return NULL;}
        static SCBehavior::Ptr extractBehavior(...) {return NULL;}
    };
}

// flow block
// _strategy_id_ for initial strategy
#define SC_BEGIN_ROLE(_role_id_,_strategy_id_) \
do{\
    SCStrategy::Ptr sc_flow_in_strategy;\
    auto sc_flow_role = SpeedCC::SCRole::create((_role_id_), this);\
    sc_flow_role->setID((_role_id_));\
    ___SC_FLOW_CREATE_STRATEGY(sc_flow_in_strategy,(_strategy_id_))\
    sc_flow_role->addStrategy(sc_flow_in_strategy,true);\



#define SC_END_ROLE \
    this->addRole(sc_flow_role);\
}while(0);


// strategy block
#define IN_STRATEGY(_strategy_id_) \
{\
    SCStrategy::Ptr sc_flow_in_strategy;\
    ___SC_FLOW_CREATE_STRATEGY(sc_flow_in_strategy,_strategy_id_)\
    sc_flow_role->addStrategy(sc_flow_in_strategy);\


#define ENDIN_STRATEGY \
}

//
#define ON_ENTER_STRATEGE(_behavior_) \
do{\
    SCBehavior::Ptr temBehavior = SCFlowSetup::extractBehavior((_behavior_));\
    sc_flow_in_strategy->setEnterBehavior(temBehavior);\
}while(0);
    

#define ON_EXIT_STRATEGE(_behavior_) \
do{\
    SCBehavior::Ptr temBehavior = SCFlowSetup::extractBehavior((_behavior_));\
    sc_flow_in_strategy->setExitBehavior(temBehavior);\
}while(0);

#define ON_MSG_BEHAVIOR(_msg_,_behavior_) \
do{\
    auto temMsg = (_msg_);\
    SCBehavior::Ptr temBehavior = SCFlowSetup::extractBehavior((_behavior_));\
    const int nMsg = SCFlowSetup::extractMsgID(temMsg);\
    auto matchPtr = SCFlowSetup::extractMsgMatcher(temMsg);\
    sc_flow_role->increaseMsgFilter(nMsg);\
    sc_flow_in_strategy->addBehavior(nMsg,temBehavior,matchPtr);\
}while(0);

#define ON_CMD_BEHAVIOR(_command_,_behavior_) \
do{\
    SCBehavior::Ptr temBehavior = SCFlowSetup::extractBehavior((_behavior_));\
    sc_flow_role->increaseCmdFilter(_command_);\
    sc_flow_in_strategy->addBehavior((_command_),temBehavior);\
}while(0);


#define ON_MSG_ACTIVE(_msg_,_active_) \
do{\
    auto activeRoleBvrPtr = SCBehaviorRoleActive::create((_active_)); \
    ON_MSG_BEHAVIOR((_msg_),activeRoleBvrPtr)\
}while(0);

#define ON_CMD_ACTIVE(_command_,_active_) \
do{\
    auto activeRoleBvrPtr = SCBehaviorRoleActive::create((_active_)); \
    ON_CMD_BEHAVIOR((_command_),activeRoleBvrPtr)\
}while(0);

//#define ON_FRAME_BEHAVIOR(_behavior_) \
//do{\
//    sc_flow_in_strategy->addBehavior(kSCMsgFrame,(_behavior_));\
//}while(0);

#define ON_MSG(_msg_) \
    ON_MSG_BEHAVIOR((_msg_),NULL)

#define ON_MSG_NEXT_STRATEGY(_msg_,_stragegy_id_) \
do{\
    auto bvrPtr = SCBehaviorStrategySwitch::create(sc_flow_role,(_stragegy_id_));\
    ON_MSG_BEHAVIOR(_msg_,bvrPtr)\
}while(0);

//#define ON_MSG_SEND_MSG(_msg_,_send_) \



////----------------------

#define ___SC_FLOW_CREATE_STRATEGY(_strategy_ptr_,_strategy_id_) \
{\
    if(_strategy_id_==SCID::Stg::kSCStgEmpty){\
        (_strategy_ptr_) = SCStrategyEmpty::create();\
    }else{\
        (_strategy_ptr_) = this->onCreateStrategy((_strategy_id_));\
    }\
    (_strategy_ptr_)->setID((_strategy_id_));\
}

#endif // __SPEEDCC__SCFLOWMACRO_H__
