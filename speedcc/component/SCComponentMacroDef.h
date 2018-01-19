//
//  SCComponentMacroDef.h
//  libspeedcc
//
//  Created by Kevin on 19/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCCOMPONENTMACRODEF_H__
#define __SPEEDCC__SCCOMPONENTMACRODEF_H__

///----------------------
#define SC_BVR_GROUP(_bvr_,...) \
    SpeedCC::SCBehaviorGroup::create((_bvr_),##__VA_ARGS__)

#define SC_MSG_GROUP(_msg_,...) \
    SpeedCC::SCMessageGroup::create((_msg_),##__VA_ARGS__)

#define SC_MATCHER_GROUP(_mat_,...) \
    SpeedCC::SCMessageMatcherGroup::create((_mat_),##__VA_ARGS__)

#define SCMsgDisp() \
    (SpeedCC::SCMessageDispatch::getInstance())

#endif // __SPEEDCC__SCCOMPONENTMACRODEF_H__
