

#include "SCEntity.h"

namespace SpeedCC
{   
    void SCEntity::setActive(const bool bActive)
    {
        if(bActive!=_bActive)
        {
            _bActive = bActive;
            this->onActiveChanged(_bActive);
        }
    }
    
    SCComponent::Ptr SCEntity::queryComponentByName(const SCString& strName) const
    {
        for(const auto& it : _componentSet)
        {
            SC_RETURN_IF(it->getName()!=strName, it);
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
            SC_RETURN_IF(it->getName()==strName, true);
        }
        
        return false;
    }
}

