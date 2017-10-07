

#ifndef __SPEEDCC__SCComponent_H__
#define __SPEEDCC__SCComponent_H__

#include "../base/SCObjPtrT.h"
#include "../base/SCString.h"

namespace SPEEDCC
{
    class SCComponent
    {
    public:
        template<typename T>
        void addComponent(const SCObjPtrT<T>& cmpPtr)
        {
            SC_RETURN_IF_V(cmpPtr.isNULL());
            
            _childCmpList.push_back(cmpPtr);
        }
        
        template<typename T>
        SCObjPtrT<T> getComponent();
        
        template<typename T>
        std::vector<SCObjPtr<T> > getComponents();
        
        template<typename T>
        bool hasComponent();
        
    protected:
        std::list<SCObjPtrT<SCComponent> > _childCmpList;
        SCString    _strName;
    };
}

#endif // __SPEEDCC__SCComponent_H__
