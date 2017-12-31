//
//  SCRole.hpp
//  libspeedcc
//
//  Created by Kevin on 28/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCROLE_H__
#define __SPEEDCC__SCROLE_H__

#include "SCPerformObject.h"
#include "SCPerformer.h"
#include "SCStrategy.h"

namespace SpeedCC
{
    class SCStage;
    
    class SCRole : public SCComponentHolder
    {   
    public:
        SC_AVOID_CLASS_COPY(SCRole)
        SC_DEFINE_CLASS_PTR(SCRole)
        
        SC_DEFINE_CREATE_FUNC2(SCRole, const SCString&,SCStage*);
        
        int addPerformer(SCPerformer::Ptr performerPtr);
        bool removePerformer(const int nID);
        
        void forEach(const std::function<bool(const SCPerformer::Ptr& performerPtr)>& func) const;
        void forEach(const std::function<bool(SCPerformer::Ptr& performerPtr)>& func);
        
        void addStrategy(SCStrategy::Ptr strategyPtr);
        SCStrategy::Ptr getStrategy(const SCString& strName) const;
        void setInitStrategy(SCStrategy::Ptr strategyPtr);
        
        virtual void update(SCMessageInfo& mi);
//        virtual void visit(SCPerformer::Ptr performerPtr);
        
    protected:
        SCRole(const SCString& strName,SCStage* pStage);
        
    private:
        SCStrategy::Ptr                         _initStrategyPtr;
        int                                     _nIDCounter;
        std::map<int,SCPerformer::Ptr>          _id2PerformerPtrMap;
        std::map<SCString,SCStrategy::Ptr>      _name2StrategyMap;
        SCStage*                                _pOwnerStage;
    };
}

#endif // __SPEEDCC__SCROLE_H__
