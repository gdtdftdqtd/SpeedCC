//
//  SCPerformObject.hpp
//  libspeedcc
//
//  Created by Kevin on 31/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCPERFORMOBJECT_H__
#define __SPEEDCC__SCPERFORMOBJECT_H__

#include "../base/SCObject.h"
#include "../base/SCValue.h"

namespace SpeedCC
{
    class SCPerformObject : public SCObject
    {
    public:
        virtual ~SCPerformObject();
        
        inline int getID() const {return _nID;}
        inline void setID(const int nID) { _nID = nID;}
        
        inline bool getActive() const {return _bActive;}
        void setActive(const bool _bActive);
        
    protected:
        SCPerformObject();
        virtual void onActiveChanged(const bool bNewActive){}
        
    private:
        int         _nID;
        bool        _bActive;
    };
    
    class SCComponentHolder : public SCPerformObject
    {
    public:
        template<typename T>
        void addComponent(const int nID,const T& component)
        {
            SCObjPtrT<T> cmpPtr;
            cmpPtr.createInstance();
            *cmpPtr = component;
            
            _id2ComponentMap[nID] = SCValue::create(cmpPtr);
        }
        
        template<typename T>
        SCObjPtrT<T> getComponent(const int nID)
        {
            auto it = _id2ComponentMap.find(nID);
            SC_RETURN_IF(it==_id2ComponentMap.end(),NULL);
            SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(),NULL);
            return (*it).second.getObject<SCObjPtrT<T>>();
        }
        
        bool hasComponent(const int nID) const;
        void removeComponent(const int nID);
        
    private:
        std::map<int,SCValue>   _id2ComponentMap;
    };
}

#endif /* SCPerformObject_hpp */
