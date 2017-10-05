

#ifndef __SC__SCValue_H__
#define __SC__SCValue_H__

#include "SCObjRefT.h"

namespace SPEEDCC
{
    class SCDateTime;
    class SCDataBlock;
    class SCString;
    
    struct SCValueStub
    {
        union
        {
            void*       pObject;
            long long   llValue;
            int         nValue;
            float       fValue;
            bool        bValue;
            long        lValue;
            double      dValue;
            void*       pValue;
        }data;
        int (*pfunDestroyFunctor_t)(void*);
        
        SCValueStub():
        pfunDestroyFunctor_t(NULL)
        {
            ::memset(&data,0,sizeof(data));
        }
        
        ~SCValueStub()
        {
            if(pfunDestroyFunctor_t!=NULL && data.pObject!=NULL)
            {
                int nSize = pfunDestroyFunctor_t(data.pObject);
                SCMemAllocator::deallocate(data.pObject, nSize);
            }
        }
    };
    
    class SCValue : public SCObjRefT<SCValueStub,int>
    {
    public:
        enum EType
        {
            UNKNOWN_TYPE = 0,
            INT_TYPE,
            LONG_TYPE,
            LONGLONG_TYPE,
            BOOL_TYPE,
            FLOAT_TYPE,
            DOUBLE_TYPE,
            POINTER_TYPE,
            STRING_TYPE,
            DATETIME_TYPE,
            DATABLOCK_TYPE,
            ARRAY_TYPE,
            VALUE_TYPE,
            OBJECT_TYPE
        };
        
        SCValue();
        SCValue(const int nValue);
        SCValue(const bool bValue);
        SCValue(const float fValue);
        SCValue(const double dValue);
        SCValue(void* const pValue);
        SCValue(const SCString& strValue);
        SCValue(const char* pszValue);
        SCValue(SCDateTime& dateTime);
        SCValue(const SCDataBlock& dataBlock);
        SCValue(const std::vector<SCValue>& valueVtr);
        
        virtual ~SCValue();
        
        inline EType getType() const {return (EType)*this->getCookie();}
        
        bool getInt(int& nValue) const;
        bool getLong(long& lValue) const;
        bool getBool(bool& bValue) const;
        bool getFloat(float& fValue) const;
        bool getDouble(double& dValue) const;
        bool getPointer(void*& ppValue) const;
        bool getLongLong(long long& llValue) const;
        bool getString(SCString& strValue) const;
        bool getDataBlock(SCDataBlock& db) const;
        bool getDateTime(SCDateTime& dateTime) const;
        bool getArray(std::vector<SCValue>& valueVtr) const;
        bool getValue(SCValue& value);
        
        void setInt(const int& nValue);
        void setLong(const long& lValue);
        void setBool(const bool& bValue);
        void setFloat(const float& fValue);
        void setDouble(const double& dValue);
        void setPointer(void* const pValue);
        void setLongLong(long long& llValue);
        void setString(const SCString& strValue);
        void setString(const char* pszValue);
        void setDataBlock(const SCDataBlock& db);
        void setDateTime(const SCDateTime& dateTime);
        void setArray(const std::vector<SCValue>& valueVtr);
        void setValue(const SCValue& value);
        
        template<typename ObjectT>
        bool isValidObject() const
        {
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return false;
            }
            
            const SCValueStub& stub = *(this->getStub());
            return (stub.pfunDestroyFunctor_t==SCDataTypeLifeCycle<ObjectT>::destroy);
        }
        
        template<typename ObjectT>
        bool getObject(ObjectT& value) const
        {
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return false;
            }
            
            const SCValueStub& stub = *(this->getStub());
            
            if(stub.data.pObject==NULL || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycle<ObjectT>::destroy)
            {
                return false;
            }
            
            value = *((ObjectT*)(stub.data.pObject));
            return true;
        }
        
        template<typename ObjectT>
        bool setObject(const ObjectT& value)
        {
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return false;
            }
            
            SCValueStub& stub = *(this->getStub());
            
            if(stub.data.pObject==NULL || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycle<ObjectT>::destroy)
            {
                return false;
            }
            
            *((ObjectT*)(stub.data.pObject)) = value;
            return true;
        }
        
        template<typename ObjectT>
        static SCValue create(const ObjectT& value)
        {
            SCValue ret;
            auto type = (SCIsSameTypeT<ObjectT, SCString>::value ? STRING_TYPE :
                         (SCIsSameTypeT<ObjectT, SCDataBlock>::value ? DATABLOCK_TYPE :
                          (SCIsSameTypeT<ObjectT, SCDateTime>::value ? DATETIME_TYPE :
                           (SCIsSameTypeT<ObjectT, std::vector<SCValue>>::value) ? ARRAY_TYPE :
                           (SCIsSameTypeT<ObjectT, SCValue>::value) ? VALUE_TYPE : OBJECT_TYPE)));
            
            ret.getCookieDesc()->cookie = type;
            SCValueStub& stub = *(ret.getStub());
            
            void* pBuf = SCMemAllocator::allocate(sizeof(ObjectT));
            ObjectT* pMyClass = new(pBuf)ObjectT();
            *pMyClass = value;
            stub.data.pObject = pMyClass;
            stub.pfunDestroyFunctor_t = SCDataTypeLifeCycle<ObjectT>::destroy;
            
            return ret;
        }
        
    private:
        void check4Write();
        
    };
}

#endif // __SC__SCValue_H__
