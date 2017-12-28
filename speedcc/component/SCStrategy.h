//
//  SCStrategy.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCBehavior.h"

namespace SpeedCC
{
    class SCPerformer;
    
    class SCStrategy : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategy)
        SC_DEFINE_CLASS_PTR(SCStrategy)
        
        virtual void update();
    protected:
        SCStrategy();
        
    private:
        SCStrategy*         _pParentStrategy;
        SCBehavior::Ptr     _startBehaviorPtr;
        SCBehavior::Ptr     _stopBehaviorPtr;
    };
    
    
    class SCStrategyDefault : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyDefault)
        SC_DEFINE_CLASS_PTR(SCStrategyDefault)
        
    protected:
        SCStrategyDefault();
    };
}

#endif // __SPEEDCC__SCSTRATEGY_H__
