

#ifndef __SPEEDCC__SCENTITY_H__
#define __SPEEDCC__SCENTITY_H__

#include "SCComponent.h"
#include "../base/SCObjPtrT.h"
#include "../base/SCString.h"

namespace SpeedCC
{
    class SCEntity
    {   
    protected:
        SC_AVOID_CLASS_COPY(SCEntity);
        
        SCEntity():
        _bEnable(true)
        {}
        
        SCEntity(const SCString& strName):
        _strName(strName),
        _bEnable(true)
        {}
        
    public:
        SC_DEFINE_CLASS_PTR(SCEntity);
        
        template<typename T>
        bool addComponent(T ptrCmp)
        {
            SC_RETURN_IF(ptrCmp.isNull(), true);
            _componentSet.push_back(ptrCmp);
            return true;
        }
        
        template<typename T>
        SCComponent::Ptr queryComponent() const
        {
            for(const auto& it : _componentSet)
            {
                if(it.cast<T>()!=NULL)
                {
                    return it;
                }
            }
            
            return NULL;
        }
        
        template<typename T>
        void removeComponent()
        {
            auto it = std::remove_if(_componentSet.begin(),_componentSet.end(),[](const SCComponent::Ptr& ptr)
                                     {
                                         return (ptr.cast<T>()!=NULL);
                                     });
            
            _componentSet.erase(_componentSet.end(), it);
        }
        
        template<typename T>
        bool hasComponent()
        {
            for(const auto& it : _componentSet)
            {
                if(it.cast<T>()!=NULL)
                {
                    return true;
                }
            }
            
            return false;
        }
        
        
        SCComponent::Ptr queryComponentByName(const SCString& strName) const;
        void removeComponentByName(const SCString& strName);
        bool hasComponentByName(const SCString& strName);
        
        inline bool getEnable() const {return _bEnable;}
        void setEnable(const bool bEnable);
        inline SCString getName() const { return _strName; }
        void setName(SCString strName) {_strName = strName;}
        
    protected:
        std::list<SCComponent::Ptr>          _componentSet;
        
    private:
        bool        _bEnable;
        SCString    _strName;
    };
}

#endif // __SPEEDCC__SCENTITY_H__
