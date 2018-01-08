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
    
    class SCRole : public SCPropertyHolder
    {   
    public:
        SC_AVOID_CLASS_COPY(SCRole)
        SC_DEFINE_CLASS_PTR(SCRole)
        
        SC_DEFINE_CREATE_FUNC_2(SCRole, const int,SCStage*);
        
        bool addPerformer(SCPerformer::Ptr performerPtr);
        void removePerformer(const int nID);
        bool hasPerformer(const int nID) const;
        SCPerformer::Ptr getPerformer(const int nID);
        
        void forEach(const std::function<bool(const SCPerformer::Ptr& performerPtr)>& func) const;
        void forEach(const std::function<bool(SCPerformer::Ptr& performerPtr)>& func);
        
        void addStrategy(SCStrategy::Ptr strategyPtr,const bool bInit=false);
        SCStrategy::Ptr getStrategy(const int nID) const;
        bool hasStrategy(const int nID) const;
        
        inline SCStage* getStage() const { return _pOwnerStage;}
        virtual void update(SCMessage::Ptr mi);
        
    protected:
        SCRole(const int nID,SCStage* pStage);
        
    private:
        int                                     _nInitStrategyID;
        std::list<SCPerformer::Ptr>             _performerList;
        std::map<int,SCStrategy::Ptr>           _id2StrategyMap;
        SCStage*                                _pOwnerStage;
    };
}

#endif // __SPEEDCC__SCROLE_H__
