

#include "SCEntity.h"

namespace SpeedCC
{   
    void SCEntity::setEnable(const bool bEnable)
    {
        if(bEnable!=_bEnable)
        {
            _bEnable = bEnable;
        }
    }
    
    SCComponent::Ptr SCEntity::queryComponentByName(const SCString& strName) const
    {
        for(const auto& it : _componentSet)
        {
            if(it->getName()!=strName)
            {
                return it;
            }
        }
        
        return NULL;
    }
    
    void SCEntity::removeComponentByName(const SCString& strName)
    {
        auto it = std::remove_if(_componentSet.begin(),_componentSet.end(),[strName](const SCComponent::Ptr& ptr)
                                 {
                                     return (ptr->getName()==strName);
                                 });
        
        _componentSet.erase(_componentSet.end(), it);
    }
    
    bool SCEntity::hasComponentByName(const SCString& strName)
    {
        for(const auto& it : _componentSet)
        {
            if(it->getName()==strName)
            {
                return true;
            }
        }
        
        return false;
    }
}

