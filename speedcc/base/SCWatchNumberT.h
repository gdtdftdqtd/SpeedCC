//
//  SCWatchNumberT.hpp
//  libspeedcc
//
//  Created by Kevin on 13/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCWatchNumberT_H__
#define __SPEEDCC__SCWatchNumberT_H__

#include "SCMacroDef.h"

namespace SpeedCC
{
#define SC_DEFINE_NUMBER_OPERATOR(_opr_) \
    template<typename T2>\
    T2 operator _opr_ (const T2 num) {\
        return this->_number _opr_ num;\
    }
    
#define SC_DEFINE_NUMBER_CONSTRUCTOR(_type_) \
    SCWatchNumberT(const _type_ num):\
    _number(0),\
    _nIDCounter(0),\
    _funGetString(NULL){\
        this->_number = (T)(num);\
    }
    
    
#define SC_DEFINE_NUMBER_GLOBAL1(_opr_,_ret_type_) \
    template<typename T> \
    _ret_type_ operator _opr_ (const SCWatchNumberT<T>& num1,const SCWatchNumberT<T>& num2) {\
        return num1.getNumber() _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const int num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned int num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const char num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned char num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const short num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned short num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const long num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned long num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const float num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const double num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber()();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const INT64 num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const bool num1,const SCWatchNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }
 
#define SC_DEFINE_NUMBER_GLOBAL2(_opr1_,_opr2_) \
    template<typename T2>\
    T2 operator _opr1_ (T2& num1,const SCWatchNumberT<T2>& num) {\
        T2 ret = num1 _opr2_ num.getNumber();\
        num1 = ret;\
        return ret;\
    }
    
#define SC_DEFINE_NUMBER_OPERATOR2(_opr1_,_opr2_) \
    template<typename T2>\
    SCWatchNumberT& operator _opr1_ (const T2 num) {\
        const T oldNum = _number;\
        const T2 ret = _number _opr2_ num;\
        const bool bSame = (_number == ret);\
        if(bSame){\
            return *this;\
        }\
        *this = ret;\
        this->firePostUpdateFun(num,oldNum);\
        return *this;\
    }
    
    template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type>
    class SCWatchNumberT : public SCObject
    {
    public:
        typedef T  NumberType;
        
        SC_DEFINE_CLASS_PTR(SCWatchNumberT<T>)
        
        SCWatchNumberT(const SCWatchNumberT& num):
        _number(num._number),
        _nIDCounter(0),
        _funGetString(NULL)
        {
        }
        
        static Ptr create()
        {
            Ptr ret;
            ret.createInstanceWithCon([](void* pData)
                                      {
                                          new(pData)SCWatchNumberT();
                                      });
            return ret;
        }
        
        static Ptr create(const T num)
        {
            Ptr ret;
            ret.createInstanceWithCon([num](void* pData)
                                      {
                                          new(pData)SCWatchNumberT(num);
                                      });
            return ret;
        }
        
        SC_DEFINE_NUMBER_CONSTRUCTOR(int)
        SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned int)
        SC_DEFINE_NUMBER_CONSTRUCTOR(char)
        SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned char)
        SC_DEFINE_NUMBER_CONSTRUCTOR(short)
        SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned short)
        SC_DEFINE_NUMBER_CONSTRUCTOR(long)
        SC_DEFINE_NUMBER_CONSTRUCTOR(unsigned long)
        SC_DEFINE_NUMBER_CONSTRUCTOR(INT64)
        SC_DEFINE_NUMBER_CONSTRUCTOR(float)
        SC_DEFINE_NUMBER_CONSTRUCTOR(double)
        
        inline operator int() const {return (int)_number;}
        inline operator unsigned int() const {return (unsigned int)_number;}
        inline operator long() const {return (long)_number;}
        inline operator unsigned long() const {return (unsigned long)_number;}
        inline operator char() const {return (char)_number;}
        inline operator unsigned char() const {return (unsigned char)_number;}
        inline operator INT64() const {return (INT64)_number;}
        inline operator float() const {return (float)_number;}
        inline operator double() const {return (double)_number;}
        
        inline bool operator<(const T num) { return _number<num; }
        inline bool operator<=(const T num) { return _number<=num; }
        inline bool operator>(const T num) { return _number>num; }
        inline bool operator>=(const T num) { return _number>=num; }
        inline bool operator==(const T num) { return _number==num; }
        inline bool operator!=(const T num) { return _number!=num; }
        
        SC_DEFINE_NUMBER_OPERATOR(+)
        SC_DEFINE_NUMBER_OPERATOR(-)
        SC_DEFINE_NUMBER_OPERATOR(*)
        SC_DEFINE_NUMBER_OPERATOR(/)
        SC_DEFINE_NUMBER_OPERATOR(%)
        SC_DEFINE_NUMBER_OPERATOR(^)
        SC_DEFINE_NUMBER_OPERATOR(&)
        
        SC_DEFINE_NUMBER_OPERATOR2(+=,+)
        SC_DEFINE_NUMBER_OPERATOR2(-=,-)
        SC_DEFINE_NUMBER_OPERATOR2(*=,*)
        SC_DEFINE_NUMBER_OPERATOR2(/=,/)
        SC_DEFINE_NUMBER_OPERATOR2(%=,%)
        SC_DEFINE_NUMBER_OPERATOR2(^=,^)
        SC_DEFINE_NUMBER_OPERATOR2(&=,&)
        
        SC_DEFINE_NUMBER_OPERATOR2(<<=,<<)
        SC_DEFINE_NUMBER_OPERATOR2(>>=,>>)
        
        template<typename T2>
        SCWatchNumberT& operator=(const SCWatchNumberT<T2>& num)
        {
            const T oldNum = _number;
            bool bDiff = (oldNum!=(T)num._number);
            
            if(!bDiff) {return *this;}
            
            _number = (T)num._number;
            this->firePostUpdateFun(num,oldNum);
            
            return *this;
        }
        
        template<typename T2>
        SCWatchNumberT& operator=(const T2 num)
        {
            const T oldNum = _number;
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            _number = num;
            this->firePostUpdateFun(num,oldNum);
            
            return *this;
        }
        
        // prefix ++ (++a)
        SCWatchNumberT& operator++()
        {
            const T oldNum = _number;
            const T num = _number + 1;
            _number += 1;
            this->firePostUpdateFun(num,oldNum);
            return *this;
        }
        
        SCWatchNumberT operator++(T)  // postfix ++ (a++)
        {
            SCWatchNumberT result(*this);
            ++(*this);
            return result;
        }
        
        // prefix -- (--a)
        SCWatchNumberT& operator--()
        {
            const T oldNum = _number;
            const T num = _number - 1;
            _number -= 1;
            this->firePostUpdateFun(num,oldNum);
            return *this;
        }
        
        SCWatchNumberT operator--(T)  // postfix -- (a--)
        {
            SCWatchNumberT result(*this);
            --(*this);
            return result;
        }
        
        int addPosUpdateFun(const std::function<void(SCWatchNumberT* pNum,T newNumber,T oldNumber)>& fun)
        {
            ++_nIDCounter;
            _postUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        void removeUpdateFun(const int nID)
        {
            if(_postUpdateFunMap.find(nID)!=_postUpdateFunMap.end())
            {
                _postUpdateFunMap.erase(nID);
            }
        }
        
        void setGetStringFun(const std::function<SCString(const T num)>& fun)
        {
            _funGetString = fun;
        }
        
        SCString getString()
        {
            if(_funGetString)
            {
                return _funGetString(_number);
            }
            
            return SCString(_number);
        }

        inline T getNumber() const {return _number;}
        
    protected:
        SCWatchNumberT():
        _number(0),
        _nIDCounter(0),
        _funGetString(NULL)
        {}
        
        void firePostUpdateFun(const T newNumber,const T oldNumber)
        {
            for(const auto& it : _postUpdateFunMap)
            {
                it.second(this->makeObjPtr<SCWatchNumberT>(),newNumber,oldNumber);
            }
        }
        
    private:
        T                   _number;
        int                 _nIDCounter;
        std::map<int,std::function<void(Ptr numPtr,
                                        const T newNumber,
                                        const T oldNumber)> >    _postUpdateFunMap;
        std::function<SCString(const T num)>      _funGetString;
    };
    
    
    template<>
    class SCWatchNumberT<bool> : public SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCWatchNumberT<bool>)
        
        SCWatchNumberT(const SCWatchNumberT& num):
        _number(num._number),
        _nIDCounter(0)
        {
        }
        
        static Ptr create()
        {
            Ptr ret;
            ret.createInstanceWithCon([](void* pData)
                                      {
                                          new(pData)SCWatchNumberT();
                                      });
            return ret;
        }
        
        static Ptr create(const bool num)
        {
            Ptr ret;
            ret.createInstanceWithCon([num](void* pData)
                                      {
                                          new(pData)SCWatchNumberT(num);
                                      });
            return ret;
        }
        
        inline operator bool() const {return _number;}
        inline bool operator==(const bool num) { return _number==num; }
        inline bool operator!=(const bool num) { return _number!=num; }
        
        SCWatchNumberT& operator=(const bool num)
        {
            const bool oldNum = _number;
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            _number = num;
            this->firePostUpdateFun(num,oldNum);
            
            return *this;
        }
        
        int addPosUpdateFun(const std::function<void(Ptr numPtr,bool newNumber,bool oldNumber)>& fun)
        {
            ++_nIDCounter;
            _postUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        void removeUpdateFun(const int nID)
        {
            if(_postUpdateFunMap.find(nID)!=_postUpdateFunMap.end())
            {
                _postUpdateFunMap.erase(nID);
            }
        }

        
        inline bool getNumber() const {return _number;}
        
    protected:
        SCWatchNumberT():
        _number(false),
        _nIDCounter(0)
        {
        }
        
        SCWatchNumberT(const bool num):
        _number(num),
        _nIDCounter(0)
        {
        }
        
        void firePostUpdateFun(const bool newNumber,const bool oldNumber)
        {
            for(const auto& it : _postUpdateFunMap)
            {
                it.second(this->makeObjPtr<SCWatchNumberT<bool> >(), newNumber,oldNumber);
            }
        }
        
    private:
        bool                   _number;
        int                 _nIDCounter;
        std::map<int,std::function<void(Ptr numPtr,
                                        const bool newNumber,
                                        const bool oldNumber)> >    _postUpdateFunMap;
    };
    
    SC_DEFINE_NUMBER_GLOBAL1(+,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(-,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(*,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(/,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(%,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(^,SCWatchNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(&,SCWatchNumberT<T>)
    
    SC_DEFINE_NUMBER_GLOBAL1(>,bool)
    SC_DEFINE_NUMBER_GLOBAL1(>=,bool)
    SC_DEFINE_NUMBER_GLOBAL1(<,bool)
    SC_DEFINE_NUMBER_GLOBAL1(<=,bool)
    SC_DEFINE_NUMBER_GLOBAL1(==,bool)
    SC_DEFINE_NUMBER_GLOBAL1(!=,bool)

    SC_DEFINE_NUMBER_GLOBAL2(+=,+)
    SC_DEFINE_NUMBER_GLOBAL2(-=,-)
    SC_DEFINE_NUMBER_GLOBAL2(*=,*)
    SC_DEFINE_NUMBER_GLOBAL2(/=,/)
    SC_DEFINE_NUMBER_GLOBAL2(%=,%)
    SC_DEFINE_NUMBER_GLOBAL2(^=,^)
    SC_DEFINE_NUMBER_GLOBAL2(&=,&)
    
    SC_DEFINE_NUMBER_GLOBAL2(<<=,<<)
    SC_DEFINE_NUMBER_GLOBAL2(>>=,>>)
    

    typedef SCWatchNumberT<short>                        SCWatchShort;
    typedef SCWatchNumberT<unsigned short>               SCWatchUnsignedShort;
    typedef SCWatchNumberT<char>                         SCWatchChar;
    typedef SCWatchNumberT<unsigned char>                SCWatchByte;
    typedef SCWatchNumberT<int>                          SCWatchInt;
    typedef SCWatchNumberT<unsigned int>                 SCWatchUnsignedInt;
    typedef SCWatchNumberT<long>                         SCWatchLong;
    typedef SCWatchNumberT<unsigned long>                SCWatchUnsignedLong;
    typedef SCWatchNumberT<INT64>                        SCWatchInt64;
    typedef SCWatchNumberT<float>                        SCWatchFloat;
    typedef SCWatchNumberT<double>                       SCWatchDouble;
    typedef SCWatchNumberT<bool>                         SCWatchBool;
}

#endif // __SPEEDCC__SCWatchNumberT_H__
