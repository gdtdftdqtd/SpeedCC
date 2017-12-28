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
    };
}

// flow block
#define SC_BEGIN_FLOW(_role_,_init_strategy_) \
{\
auto sc_flow_role = (_role_);\


#define SC_END_FLOW \
}


// strategy block
#define IN_STRATEGY(_strategy_) \

#define ENDIN_STRATEGY \

//
#define ON_ENTER_STRATEGE(_behavior_) \


#define ON_EXIT_STRATEGE(_behavior_) \

#define ON_MSG_NEXT_STRATEGY(_msg_,_stragegy_) \

#define ON_MSG_BEHAVIOR(_msg_,_behavior_) \

#define IF_MATCH(_condition_) \

#define ENDIF_MATCH \

#endif // __SPEEDCC__SCFLOWMACRO_H__
