//
//  SCRole.hpp
//  libspeedcc
//
//  Created by Kevin on 28/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCROLE_H__
#define __SPEEDCC__SCROLE_H__

#include "SCPerformer.h"
#include "SCStrategy.h"

namespace SpeedCC
{
    class SCRole : public SCEntity
    {
    public:
        SC_AVOID_CLASS_COPY(SCRole)
        SC_DEFINE_CLASS_PTR(SCRole)
        
        int addPerformer(const SCPerformer::Ptr performerPtr);
        void removePerformer(const int nID);
        
        void forEach(const std::function<bool(const SCPerformer::Ptr& performerPtr)>& func) const;
        void forEach(const std::function<bool(SCPerformer::Ptr& performerPtr)>& func);
        
        virtual void visit(SCPerformer::Ptr performerPtr);
        
    private:
        std::list<SCPerformer::Ptr>             _performDataList;
        std::map<SCString,SCStrategy::Ptr>      _name2StrategyMap;
        SCStage*                                _pOwnerStage;
    };
}

#endif // __SPEEDCC__SCROLE_H__
