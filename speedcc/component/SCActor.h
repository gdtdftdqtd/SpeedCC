//
//  SCPerformer.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCACTOR_H__
#define __SPEEDCC__SCACTOR_H__

#include "SCPerformObject.h"
#include "SCMessage.h"

namespace SpeedCC
{
    class SCStrategy;
    class SCRole;
    
    class SCActor : public SCPropertyHolder
    {
        friend class SCRole;
    public:
        enum {kDefaultID = 1};
    public:
        SC_AVOID_CLASS_COPY(SCActor)
        SC_DEFINE_CLASS_PTR(SCActor)
        
        SC_DEFINE_CREATE_FUNC_1(SCActor,const int)
        
        bool applyStrategy(SCStrategy* pStrategy);
        void removeFromRole();
        
        inline SCRole* getRole() {return _pOwnerRole;}
        
        virtual void update(SCMessage::Ptr ptrMsg);
        
    protected:
        SCActor(const int nID);
        
        void setRole(SCRole* pRole) {_pOwnerRole = pRole; }
        
    private:
        SCStrategy*             _pCurStrategy;
        SCRole*                 _pOwnerRole;
    };
    
}

#endif // __SPEEDCC__SCACTOR_H__
