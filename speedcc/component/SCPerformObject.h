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
#include "../base/SCDictionary.h"

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
        SCPerformObject(const int nID);
        
        virtual void onActiveChanged(const bool bNewActive){}
        
    private:
        int         _nID;
        bool        _bActive;
    };
    
    class SCBehavior : public SCPerformObject
    {
    protected:
        SCBehavior()
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehavior)
        SC_DEFINE_CLASS_PTR(SCBehavior)
        
        virtual ~SCBehavior() {}
        virtual void execute(const SCDictionary& par=SCDictionary()) = 0;
    };
    
    class SCPropertyHolder : public SCPerformObject
    {
    public:
        template<typename T>
        void addProperty(const int nID,const T& property)
        {
            SCObjPtrT<T> cmpPtr;
            cmpPtr.createInstance();
            *cmpPtr = property;
            
            _id2PropertyMap[nID] = SCValue::create(cmpPtr);
        }
        
        template<typename T>
        void addProperty(const int nID)
        {
            SCObjPtrT<T> cmpPtr;
            cmpPtr.createInstance();
            *cmpPtr = T();
            
            _id2PropertyMap[nID] = SCValue::create(cmpPtr);
        }
        
        template<typename T>
        SCObjPtrT<T> getProperty(const int nID)
        {
            auto it = _id2PropertyMap.find(nID);
            SC_RETURN_IF(it==_id2PropertyMap.end(),NULL);
            SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(),NULL);
            return (*it).second.getObject<SCObjPtrT<T>>();
        }
        
        bool hasProperty(const int nID) const;
        void removeProperty(const int nID);
        
    protected:
        SCPropertyHolder()
        {}
        
        SCPropertyHolder(const int nID):
        SCPerformObject(nID)
        {}
        
    private:
        std::map<int,SCValue>   _id2PropertyMap;
    };
}

#endif /* SCPerformObject_hpp */
