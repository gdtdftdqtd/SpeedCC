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
#include "SCActor.h"
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
        
        bool addActor(SCActor::Ptr ptrActor);
        void removeActor(const int nID);
        bool hasActor(const int nID) const;
        SCActor::Ptr getActor(const int nID);
        
        void forEach(const std::function<bool(const SCActor::Ptr& ptrActor)>& func) const;
        void forEach(const std::function<bool(SCActor::Ptr& ptrActor)>& func);
        
        void addStrategy(SCStrategy::Ptr ptrStrategy,const bool bInit=false);
        SCStrategy::Ptr getStrategy(const int nID) const;
        bool hasStrategy(const int nID) const;
        
        inline SCStage* getStage() const { return _pOwnerStage;}
        virtual void update(SCMessage::Ptr ptrMsg);
        
        void increaseMsgFilter(const int nMsgID);
        void increaseCmdFilter(const SCString& strCmd);
        void decreaseMsgFilter(const int nMsgID);
        void decreaseCmdFilter(const SCString& strCmd);
        
        inline bool getMsgFilterEnabled() const {return _bFilterMsg;}
        inline void setMsgFilterEnabled(const bool bEnable) {_bFilterMsg = bEnable;}
        
    protected:
        SCRole(const int nID,SCStage* pStage);
        
    private:
        bool filterMsg(SCMessage::Ptr ptrMsg);
        void updateVariationActor();
        bool isActorInRemovedList(const int nID) const;
        
    private:
        bool                                    _bUpdating;
        int                                     _nInitStrategyID;
        std::list<SCActor::Ptr>                 _actorList;
        std::map<int,SCStrategy::Ptr>           _id2StrategyMap;
        SCStage*                                _pOwnerStage;
        bool                                    _bFilterMsg;
        
        std::map<int,int>                       _msgID2FilterCounterMap;
        std::map<SCString,int>                  _cmd2FilterCounterMap;
        
        std::list<int>                          _removeActorList;
        std::list<SCActor::Ptr>                 _addActorList;
    };
}

#endif // __SPEEDCC__SCROLE_H__
