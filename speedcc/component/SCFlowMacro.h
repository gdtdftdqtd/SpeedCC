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
        static SCString purifyString(const int n) {return "";}
        static SCString purifyString(const SCString& str) {return str;}
    };
}

// flow block
#define SC_BEGIN_ROLE(_role_,_init_strategy_) \
{\
    SCASSERT(_createRoleFun!=NULL);\
    SCASSERT(_createStrategyFun!=NULL);\
    auto sc_flow_role = _createRoleFun((_role_));\
    sc_flow_role->setName((_role_));\
    ___SC_FLOW_ADD_STRATEGY_TO_ROLE(_init_strategy_)\
    auto sc_strategy_container = sc_flow_role;



#define SC_END_ROLE \
    this->addRole(sc_flow_role);\
}


// strategy block
#define IN_STRATEGY(_strategy_) \
{\
    SCStrategy::Ptr sc_tem_in_strategy;\
    ___SC_FLOW_CREATE_STRATEGY(sc_tem_in_strategy_strategy_)\
    sc_strategy_container->addStrategy(sc_tem_in_strategy);\
    auto sc_strategy_container = sc_tem_in_strategy;\


#define ENDIN_STRATEGY \
}

//
#define ON_ENTER_STRATEGE(_behavior_) \
{\
    auto bvrPtr = _createStrategyFun((_behavior_));\
    sc_strategy_container->setEnterBehavior(bvrPtr);\
}
    

#define ON_EXIT_STRATEGE(_behavior_) \
{\
    auto bvrPtr = _createStrategyFun((_behavior_));\
    sc_strategy_container->setExitBehavior(bvrPtr);\
}

#define ON_MSG_BEHAVIOR(_msg_,_behavior_) \
{\
    sc_tem_in_strategy->addBehavior(_msg_,_behavior_);\
}

#define ON_MSG_NEXT_STRATEGY(_msg_,_stragegy_) \
{\
    auto bvrPtr = SCBehaviorStrategySwitch::create();\
    ON_MSG_BEHAVIOR(_msg_,bvrPtr)\
}

//#define ON_MSG_SEND_MSG(_msg_,_send_) \



////----------------------
#define ___SC_FLOW_ADD_STRATEGY_TO_ROLE(_strategy_)\
{\
    SCStrategy::Ptr sc_tem_strategy;\
    ___SC_FLOW_CREATE_STRATEGY(sc_tem_strategy,(_strategy_))\
    sc_flow_role->addStrategy(sc_tem_strategy);\
}\

#define ___SC_FLOW_ADD_STRATEGY_TO_STRATEGY(_strategy_parent_,_strategy_)\


#define ___SC_FLOW_CREATE_STRATEGY(_strategy_ptr_,_strategy_name_) \
{\
    auto strSCIniStrategy = SCFlowSetup::purifyString((_strategy_name_));\
    if(strSCIniStrategy==""){\
        (_strategy_ptr_) = SCStrategyEmpty::create();\
    }else{\
        (_strategy_ptr_) = _createStrategyFun(strSCIniStrategy);\
    }\
    (_strategy_ptr_)->setName((_strategy_name_));\
}

#endif // __SPEEDCC__SCFLOWMACRO_H__
