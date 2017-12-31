//
//  SCPerformer.cpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCPerformer.h"
#include "SCStrategy.h"
#include "SCRole.h"

namespace SpeedCC
{
    SCPerformer::SCPerformer():
    _pCurStrategy(NULL),
    _pOwnerRole(NULL)
    {
    }
    
    void SCPerformer::setStrategy(SCStrategy* pStrategy)
    {
        if(_pCurStrategy!=NULL)
        {
            _pCurStrategy->exit(this);
        }
        
        _pCurStrategy = pStrategy;
        
        if(_pCurStrategy!=NULL)
        {
            _pCurStrategy->enter(this);
        }
    }
    
    void SCPerformer::removeFromRole()
    {
        SC_RETURN_IF_V(_pOwnerRole==NULL);
        _pOwnerRole->removePerformer(this->getID());
    }
    
    void SCPerformer::update(SCMessageInfo& mi)
    {
        SC_RETURN_IF_V(_pCurStrategy==NULL);
        SC_RETURN_IF_V(!this->getActive());
        _pCurStrategy->update(this,mi);
    }
}


