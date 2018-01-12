//
//  SCPerformer.cpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCActor.h"
#include "SCRole.h"
#include "SCStage.h"

namespace SpeedCC
{
    SCActor::SCActor(const int nID):
    _pCurStrategy(NULL),
    _pOwnerRole(NULL)
    {
        this->setID(nID);
    }
    
    bool SCActor::applyStrategy(SCStrategy* pStrategy)
    {
        SC_RETURN_IF(_pOwnerRole==NULL,false);
        SC_RETURN_IF(!_pOwnerRole->getActive(),false);
        SC_RETURN_IF(!_pOwnerRole->getStage()->getActive(),false);
        
        
        if(_pCurStrategy!=NULL)
        {
            _pCurStrategy->exit(this);
        }
        
        _pCurStrategy = pStrategy;
        
        if(_pCurStrategy!=NULL)
        {
            _pCurStrategy->enter(this);
        }
        
        return true;
    }
    
    void SCActor::removeFromRole()
    {
        SC_RETURN_IF_V(_pOwnerRole==NULL);
        _pOwnerRole->removeActor(this->getID());
    }
    
    void SCActor::update(SCMessage::Ptr ptrMsg)
    {
        SC_RETURN_IF_V(_pCurStrategy==NULL);
        SC_RETURN_IF_V(!this->getActive());
        _pCurStrategy->update(this,ptrMsg);
    }
}


