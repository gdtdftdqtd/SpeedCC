

#ifndef __SPEEDCC__SCCOMPONENT_H__
#define __SPEEDCC__SCCOMPONENT_H__

#include "../base/SCObjPtrT.h"
#include "../base/SCString.h"

namespace SpeedCC
{
    class SCComponent
    {
    protected:
        SC_AVOID_CLASS_COPY(SCComponent);
        SCComponent():
        _bCastInherit(false)
        {}
        
    public:
        SC_DEFINE_CLASS_PTR(SCComponent);
        
#ifdef SPEEDCC_TEST_MODE
        static Ptr create(bool bInherit=false)
        {
            Ptr ret;
            ret.createInstanceWithCon([](void* pData)
                              {
                                  new(pData)SCComponent();
                              });
            
            ret->setCastInherit(bInherit);
            return ret;
        }
#endif
        
        template<typename T>
        bool addComponent(const SCObjPtrT<T>& cmpPtr)
        {
            SC_RETURN_IF(cmpPtr.isNull() || cmpPtr==this,false);
            
            _childCmpList.push_back(cmpPtr);
            return true;
        }
        
        template<typename T>
        void removeComponent(const SCObjPtrT<T>& cmpPtr)
        {
            SC_RETURN_IF_V(cmpPtr.isNull() || cmpPtr==this);
            
            _childCmpList.remove(cmpPtr);
        }
        
        template<typename T>
        void removeComponent(void)
        {
            auto it1 = std::remove_if(_childCmpList.begin(),_childCmpList.end(),
                                      [](const Ptr& cmp) -> bool
                                      {
                                          return (cmp.cast<T>()!=NULL);
                                      });
            
            _childCmpList.erase(it1,_childCmpList.end());
        }
        
        template<typename T>
        void removeComponent(const SCString& strName)
        {
            auto it1 = std::remove_if(_childCmpList.begin(),_childCmpList.end(),
                                      [strName](const Ptr& cmp) -> bool
                                      {
                                          return (cmp.cast<T>()!=NULL && cmp->getName()==strName);
                                      });
            
            _childCmpList.erase(it1,_childCmpList.end());
        }
        
        template<typename T>
        SCObjPtrT<T> getComponent(void)
        {
            for(const auto& cmp : _childCmpList)
            {
                if(cmp.cast<T>()!=NULL)
                {
                    return cmp;
                }
            }
            
            SCObjPtrT<T> ret;
            
            if(_bCastInherit)
            {
                ret = castInheritCompnonent<T>();
            }
            
            return ret;
        }
        
        template<typename T>
        SCObjPtrT<T> getComponent(const SCString& strName)
        {
            for(const auto& cmp : _childCmpList)
            {
                if(cmp.cast<T>()!=NULL && cmp->getName()==strName)
                {
                    return cmp;
                }
            }
            
            SCObjPtrT<T> ret;
            
            if(_bCastInherit && strName.isEmpty())
            {
                ret = castInheritCompnonent<T>();
            }
            
            return ret;
        }
        
        template<typename T>
        std::vector<SCObjPtrT<T> > getComponents()
        {
            std::vector<SCObjPtrT<T> > retVtr;
            for(const auto& cmp : _childCmpList)
            {
                if(cmp.cast<T>()!=NULL)
                {
                    retVtr.push_back(cmp);
                }
            }
            
            if(_bCastInherit)
            {
                auto cmp = castInheritCompnonent<T>();
                if(cmp!=NULL)
                {
                    retVtr.push_back(cmp);
                }
            }
            
            return retVtr;
        }
        
        template<typename T>
        bool hasComponent() const
        {
            for(const auto& cmp : _childCmpList)
            {
                if(cmp.cast<T>()!=NULL)
                {
                    return true;
                }
            }
            
            return false;
        }
        
        inline SCString getName() const { return _strName; }
        void setName(SCString strName) {_strName = strName;}
        
    private:
        template<typename T>
        SCObjPtrT<T> castInheritCompnonent()
        {
            SCObjPtrT<T> ret;
            
            if(dynamic_cast<T*>(this)!=NULL)
            {
                ret._pData = this;
                ret.increaseRef();
            }
            
            return ret;
        }
        
        void setCastInherit(const bool bCast)
        {
            _bCastInherit = bCast;
        }
        
    protected:
        std::list<SCObjPtrT<SCComponent> > _childCmpList;
        SCString    _strName;
        bool        _bCastInherit;
    };
}

#endif // __SPEEDCC__SCCOMPONENT_H__
