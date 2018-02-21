/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#ifndef __SPEEDCC__SCVALUE_H__
#define __SPEEDCC__SCVALUE_H__


#include "SCObjPtrT.h"
#include "SCString.h"

namespace SpeedCC
{
    class SCDateTime;
    class SCDataBlock;
    class SCString;
    
    struct SCValueStub
    {
        union
        {
            void*           pObject;
            INT64           llValue;
            char            cValue;
            unsigned char   byValue;
            int             nValue;
            unsigned int    uValue;
            float           fValue;
            bool            bValue;
            long            lValue;
            double          dValue;
            void*           pValue;
        }data;
        int (*pfunDestroyFunctor_t)(void*);
        
        SCValueStub():
        pfunDestroyFunctor_t(nullptr)
        {
            ::memset(&data,0,sizeof(data));
        }
        
        ~SCValueStub()
        {
            if(pfunDestroyFunctor_t!=nullptr && data.pObject!=nullptr)
            {
                int nSize = pfunDestroyFunctor_t(data.pObject);
                SCMemAllocator::deallocate(data.pObject, nSize);
            }
        }
    };
    
    class SCValue :
    public SCObjRefT<SCValueStub,int>,
    public SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCValue)
        enum EType
        {
            UNKNOWN_TYPE = 0,
            BYTE_TYPE,
            CHAR_TYPE,
            INT_TYPE,
            UINT_TYPE,
            LONG_TYPE,
            INT64_TYPE,
            BOOL_TYPE,
            FLOAT_TYPE,
            DOUBLE_TYPE,
            POINTER_TYPE,
            STRING_TYPE,
            DATETIME_TYPE,
            DATABLOCK_TYPE,
            ARRAY_TYPE,
            OBJECT_TYPE
        };
        
        SCValue();
        SCValue(const char cValue);
        SCValue(const unsigned char byValue);
        SCValue(const unsigned int nValue);
        SCValue(const int nValue);
        SCValue(const bool bValue);
        SCValue(const float fValue);
        SCValue(const double dValue);
        SCValue(const long lValue);
        SCValue(const INT64 llValue);
        SCValue(void* const pValue);
        SCValue(const SCString& strValue);
        SCValue(const char* pszValue);
        SCValue(SCDateTime& dateTime);
        SCValue(const SCDataBlock& dataBlock);
        SCValue(const std::vector<SCValue>& valueVtr);
        template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value,ObjectT>::type>
        SCValue(const ObjectT& obj)
        {
            auto result = SCValue::create(obj);
            _pObjData = result._pObjData;
            this->increaseRef();
        }
        
        virtual ~SCValue();
        
        bool isNumberType() const;
        inline EType getType() const {return (EType)*this->getCookie();}
        inline bool isUnknown() const {return (getType()==UNKNOWN_TYPE);}
        
        char getChar(bool* pResult=nullptr,const bool bExactMatch=false) const;
        unsigned char getByte(bool* pResult=nullptr,const bool bExactMatch=false) const;
        unsigned int getUnsignedInt(bool* pResult=nullptr,const bool bExactMatch=false) const;
        int getInt(bool* pResult=nullptr,const bool bExactMatch=false) const;
        long getLong(bool* pResult=nullptr,const bool bExactMatch=false) const;
        bool getBool(bool* pResult=nullptr,const bool bExactMatch=false) const;
        float getFloat(bool* pResult=nullptr,const bool bExactMatch=false) const;
        double getDouble(bool* pResult=nullptr,const bool bExactMatch=false) const;
        void* getPointer(bool* pResult=nullptr,const bool bExactMatch=false) const;
        INT64 getInt64(bool* pResult=nullptr,const bool bExactMatch=false) const;
        SCString getString(bool* pResult=nullptr,const bool bExactMatch=false) const;
        SCDataBlock getDataBlock(bool* pResult=nullptr,const bool bExactMatch=false) const;
        SCDateTime getDateTime(bool* pResult=nullptr,const bool bExactMatch=false) const;
        std::vector<SCValue> getArray(bool* pResult=nullptr,const bool bExactMatch=false) const;
        
        void setChar(const char cValue);
        void setByte(const unsigned char byValue);
        void setUnsignedInt(const unsigned int uValue);
        void setInt(const int nValue);
        void setLong(const long lValue);
        void setBool(const bool bValue);
        void setFloat(const float fValue);
        void setDouble(const double dValue);
        void setPointer(void* const pValue);
        void setInt64(INT64 llValue);
        void setString(const SCString& strValue);
        void setString(const char* pszValue);
        void setDataBlock(const SCDataBlock& db);
        void setDateTime(const SCDateTime& dateTime);
        void setArray(const std::vector<SCValue>& valueVcr);
        
        SCValue& operator=(const unsigned char byValue);
        SCValue& operator=(const int nValue);
        SCValue& operator=(const unsigned int uValue);
        SCValue& operator=(const long lValue);
        SCValue& operator=(const bool bValue);
        SCValue& operator=(const float fValue);
        SCValue& operator=(const double dValue);
        SCValue& operator=(void* const pValue);
        SCValue& operator=(const INT64 llValue);
        SCValue& operator=(const SCString& strValue);
        SCValue& operator=(const char* pszValue);
        SCValue& operator=(const SCDataBlock& db);
        SCValue& operator=(const SCDateTime& dateTime);
        SCValue& operator=(const std::vector<SCValue>& valueVcr);
        
        template<typename ObjectT>
        bool isValidObject() const
        {
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return false;
            }
            
            const SCValueStub& stub = *(this->getStub());
            return (stub.pfunDestroyFunctor_t==SCDataTypeLifeCycleT<ObjectT>::destroy);
        }
        
        template<typename ObjectT>
        ObjectT getObject(bool* pResult=nullptr) const
        {
            if(pResult!=nullptr)
            {
                *pResult = false;
            }
            
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return ObjectT();
            }
            
            const SCValueStub& stub = *(this->getStub());
            
            if(stub.data.pObject==nullptr || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycleT<ObjectT>::destroy)
            {
                return ObjectT();
            }
            
            if(pResult!=nullptr)
            {
                *pResult = true;
            }
            return *((ObjectT*)(stub.data.pObject));
        }
        
        template<typename ObjectT>
        ObjectT* getRefObject(bool* pResult=nullptr)
        {
            if(pResult!=nullptr)
            {
                *pResult = false;
            }
            
            if(this->getCookieDesc()->cookie!=OBJECT_TYPE)
            {
                return nullptr;
            }
            
            const SCValueStub& stub = *(this->getStub());
            
            if(stub.data.pObject==nullptr || stub.pfunDestroyFunctor_t!=SCDataTypeLifeCycleT<ObjectT>::destroy)
            {
                return nullptr;
            }
            
            if(pResult!=nullptr)
            {
                *pResult = true;
            }
            return (ObjectT*)(stub.data.pObject);
        }
        
        template<typename ObjectT>
        void setObject(const ObjectT& value)
        {
            *this = SCValue::create(value);
        }
        
        static SCValue create(const SCValue& value)
        {
            return value;
        }
        
        template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type >
        static SCValue create(const T value)
        {
            return SCValue(value);
        }
        
        static SCValue create(void* const value)
        {
            return SCValue(value);
        }
        
        template<typename ObjectT,typename = typename std::enable_if<std::is_class<ObjectT>::value,ObjectT>::type>
        static SCValue create(const ObjectT& value)
        {
            SCValue ret;
            auto type = (std::is_same<ObjectT, SCString>::value ? STRING_TYPE :
                         (std::is_same<ObjectT, SCDataBlock>::value ? DATABLOCK_TYPE :
                          (std::is_same<ObjectT, SCDateTime>::value ? DATETIME_TYPE :
                           (std::is_same<ObjectT, std::vector<SCValue>>::value) ? ARRAY_TYPE : OBJECT_TYPE)));
            
            ret.getCookieDesc()->cookie = type;
            SCValueStub& stub = *(ret.getStub());
            
            void* pBuf = SCMemAllocator::allocate(sizeof(ObjectT));
            ObjectT* pMyClass = new(pBuf)ObjectT(value);
//            *pMyClass = value;
            stub.data.pObject = pMyClass;
            stub.pfunDestroyFunctor_t = SCDataTypeLifeCycleT<ObjectT>::destroy;
            
            return ret;
        }
        
    private:
        void check4Write();
    };
}

#endif // __SPEEDCC__SCVALUE_H__
