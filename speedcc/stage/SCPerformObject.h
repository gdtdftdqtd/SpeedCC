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

#include <typeindex>

namespace SpeedCC
{
    ///------------ SCPerformObject
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
    
    ///---------- SCBehavior
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
    
    
    ///------------ SCPropertyHolder
    class SCPropertyHolder : public SCPerformObject
    {
    public:
        template<typename T>
        void addProperty(const T& property)
        {
            SCObjPtrT<T> ptrCmd;
            ptrCmd.createInstance();
            *ptrCmd = property;
            
            _id2PropertyMap[std::type_index(typeid(T))] = SCValue::create(ptrCmd);
        }
        
        template<typename T1,typename T2,typename ...Ts>
        void addProperty(const T1& arg1,const T2& arg2,Ts... args)
        {
            this->addProperty<T1>(arg1);
            this->addProperty<T2,Ts...>(arg2,args...);
        }
        
        template<typename T>
        void addProperty()
        {
            SCObjPtrT<T> ptrCmd;
            ptrCmd.createInstance();
            *ptrCmd = T();
            
            _id2PropertyMap[std::type_index(typeid(T))] = SCValue::create(ptrCmd);
        }
        
        template<typename T1,typename T2,typename ...Ts>
        void addProperty()
        {
            this->addProperty<T1>();
            this->addProperty<T2,Ts...>();
        }
        
        template<typename T>
        SCObjPtrT<T> getProperty()
        {
            auto it = _id2PropertyMap.find(std::type_index(typeid(T)));
            SC_RETURN_IF(it==_id2PropertyMap.end(),NULL);
            SC_RETURN_IF(!(*it).second.isValidObject<SCObjPtrT<T>>(),NULL);
            return (*it).second.getObject<SCObjPtrT<T>>();
        }
        
        template<typename T>
        bool hasProperty() const
        {
            return (_id2PropertyMap.find(std::type_index(typeid(T)))!=_id2PropertyMap.end());
        }
        
        template<typename T>
        void removeProperty()
        {
            _id2PropertyMap.erase(std::type_index(typeid(T)));
        }
        
    protected:
        SCPropertyHolder()
        {}
        
        SCPropertyHolder(const int nID):
        SCPerformObject(nID)
        {}
        
    private:
        std::map<std::type_index,SCValue>   _id2PropertyMap;
    };
}

#endif /* SCPerformObject_hpp */