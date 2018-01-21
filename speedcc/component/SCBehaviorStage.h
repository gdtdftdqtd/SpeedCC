//
//  SCBehaviorStage.hpp
//  libspeedcc
//
//  Created by Kevin on 13/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBEHAVIORSTAGE_H__
#define __SPEEDCC__SCBEHAVIORSTAGE_H__

#include "SCActor.h"

namespace SpeedCC
{
    ///---------------- SCBehaviorStrategySwitch
    class SCBehaviorStrategySwitch : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorStrategySwitch)
        SC_DEFINE_CLASS_PTR(SCBehaviorStrategySwitch)
        
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorStrategySwitch,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorStrategySwitch(const int nStragtegyID):
        _nStragtegyID(nStragtegyID)
        {}
        
    private:
        int                         _nStragtegyID;
    };
    
    ///-------------- SCBehaviorStrategyParent
    class SCBehaviorStrategyParent : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorStrategyParent)
        SC_DEFINE_CLASS_PTR(SCBehaviorStrategyParent)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorStrategyParent)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorStrategyParent()
        {}
    };
    
    ///----------- SCBehaviorRemoveActor
    class SCBehaviorRemoveActor : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorRemoveActor)
        SC_DEFINE_CLASS_PTR(SCBehaviorRemoveActor)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorRemoveActor)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorRemoveActor,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        // by default, remove all actors from role
        SCBehaviorRemoveActor():
        _nActorID(0)
        {}
        
        SCBehaviorRemoveActor(const int nActorID):
        _nActorID(nActorID)
        {}
        
    private:
        int     _nActorID;
    };
    
    ///----------- SCBehaviorRoleActive
    class SCBehaviorRoleActive : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorRoleActive)
        SC_DEFINE_CLASS_PTR(SCBehaviorRoleActive)
        
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorRoleActive,bool)
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorRoleActive,const int,bool)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorRoleActive()
        {}
        
        SCBehaviorRoleActive(const bool bActive):
        _nRoleID(0),
        _bActive(bActive)
        {
        }
        
        SCBehaviorRoleActive(const int nRoleID,const bool bActive):
        _nRoleID(nRoleID),
        _bActive(bActive)
        {
        }
        
    private:
        int         _nRoleID;
        bool        _bActive;
    };
}

#endif // __SPEEDCC__SCBEHAVIORSTAGE_H__
