//
//  SCPerformer.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCPERFORMER_H__
#define __SPEEDCC__SCPERFORMER_H__

#include "SCPerformObject.h"
#include "SCMessage.h"

namespace SpeedCC
{
    class SCStrategy;
    class SCRole;
    
    class SCPerformer : public SCPropertyHolder
    {
        friend class SCRole;
        
    public:
        SC_AVOID_CLASS_COPY(SCPerformer)
        SC_DEFINE_CLASS_PTR(SCPerformer)
        
        SC_DEFINE_CREATE_FUNC_0(SCPerformer)
        
        bool applyStrategy(SCStrategy* pStrategy);
        void removeFromRole();
        
        inline SCRole* getRole() {return _pOwnerRole;}
        
        virtual void update(SCMessage::Ptr mi);
        
    protected:
        SCPerformer();
        
        void setRole(SCRole* pRole) {_pOwnerRole = pRole; }
        
    private:
        SCStrategy*             _pCurStrategy;
        SCRole*                 _pOwnerRole;
    };
    
}

#endif // __SPEEDCC__SCPERFORMER_H__
