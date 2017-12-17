//
//  SCNumberT.hpp
//  libspeedcc
//
//  Created by Kevin on 13/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCNUMBERT_H__
#define __SPEEDCC__SCNUMBERT_H__

#include "SCMacroDef.h"

namespace SpeedCC
{
#define SC_DEFINE_NUMBER_OPERATOR(_opr_) \
    template<typename T2>\
    T2 operator _opr_ (const T2 num) {\
        return this->_number _opr_ num;\
    }
    
#define SC_DEFINE_NUMBER_CONSTRUCTOR(_type_) \
    SCNumberT(const _type_ num):\
    _number(0),\
    _nIDCounter(0),\
    _funGetString(NULL){\
        this->_number = (T)(num);\
    }
    
    
#define SC_DEFINE_NUMBER_GLOBAL1(_opr_,_ret_type_) \
    template<typename T> \
    _ret_type_ operator _opr_ (const SCNumberT<T>& num1,const SCNumberT<T>& num2) {\
        return num1.getNumber() _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const int num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned int num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const char num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned char num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const short num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned short num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const long num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const unsigned long num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const float num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const double num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber()();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const INT64 num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }\
    template<typename T> \
    _ret_type_ operator _opr_ (const bool num1,const SCNumberT<T>& num2) {\
        return num1 _opr_ num2.getNumber();\
    }
 
#define SC_DEFINE_NUMBER_GLOBAL2(_opr1_,_opr2_) \
    template<typename T2>\
    T2 operator _opr1_ (T2& num1,const SCNumberT<T2>& num) {\
        T2 ret = num1 _opr2_ num.getNumber();\
        num1 = ret;\
        return ret;\
    }
    
#define SC_DEFINE_NUMBER_OPERATOR2(_opr1_,_opr2_) \
    template<typename T2>\
    SCNumberT& operator _opr1_ (const T2 num) {\
        const T oldNum = _number;\
        const T2 ret = _number _opr2_ num;\
        const bool bSame = (_number == ret);\
        if(bSame){\
            return *this;\
        }\
        if(!this->firePreUpdateFun(num,oldNum)){\
            return *this;\
        }\
        *this = ret;\
        this->firePostUpdateFun(num,oldNum);\
        return *this;\
    }
    
    template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type>
    class SCNumberT
    {
    public:
        typedef T  NumberType;
        SCNumberT():
        _number(0),
        _nIDCounter(0),
        _funGetString(NULL)
        {}
        
        SCNumberT(const SCNumberT& num):
        _number(num._number),
        _nIDCounter(0),
        _funGetString(NULL)
        {
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
        SCNumberT& operator=(const SCNumberT<T2>& num)
        {
            const T oldNum = _number;
            bool bDiff = (oldNum!=(T)num._number);
            
            if(!bDiff) {return *this;}
            
            if(bDiff)
            {
                this->firePreUpdateFun(num,oldNum);
            }
            
            _number = (T)num._number;
            
            if(bDiff)
            {
                this->firePostUpdateFun(num,oldNum);
            }
            
            return *this;
        }
        
        template<typename T2>
        SCNumberT& operator=(const T2 num)
        {
            const T oldNum = _number;
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            if(bDiff)
            {
                this->firePreUpdateFun(num,oldNum);
            }
            
            _number = num;
            
            if(bDiff)
            {
                this->firePostUpdateFun(num,oldNum);
            }
            
            return *this;
        }
        
        // prefix ++ (++a)
        SCNumberT& operator++()
        {
            const T oldNum = _number;
            const T num = _number + 1;
            this->firePreUpdateFun(num,oldNum);
            _number += 1;
            this->firePostUpdateFun(num,oldNum);
            return *this;
        }
        
        SCNumberT operator++(T)  // postfix ++ (a++)
        {
            SCNumberT result(*this);
            ++(*this);
            return result;
        }
        
        // prefix -- (--a)
        SCNumberT& operator--()
        {
            const T oldNum = _number;
            const T num = _number - 1;
            this->firePreUpdateFun(num,oldNum);
            _number -= 1;
            this->firePostUpdateFun(num,oldNum);
            return *this;
        }
        
        SCNumberT operator--(T)  // postfix -- (a--)
        {
            SCNumberT result(*this);
            --(*this);
            return result;
        }
        
        int addPreUpdateFun(const std::function<void(SCNumberT* pNum,T newNumber,T oldNumber)>& fun)
        {
            ++_nIDCounter;
            _preUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        int addPosUpdateFun(const std::function<void(SCNumberT* pNum,T newNumber,T oldNumber)>& fun)
        {
            ++_nIDCounter;
            _postUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        void removeUpdateFun(const int nID,bool bPost)
        {
            if(bPost)
            {
                _postUpdateFunMap.erase(nID);
            }
            else
            {
                _preUpdateFunMap.erase(nID);
            }
        }
        
        void firePreUpdateFun(const T newNumber,const T oldNumber)
        {
            for(const auto& it : _preUpdateFunMap)
            {
                it.second(this,newNumber,oldNumber);
            }
        }
        
        void firePostUpdateFun(const T newNumber,const T oldNumber)
        {
            for(const auto& it : _postUpdateFunMap)
            {
                it.second(this,newNumber,oldNumber);
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
        
    private:
        T                   _number;
        int                 _nIDCounter;
        std::map<int,std::function<void(SCNumberT* pNum,const T newNumber,const T oldNumber)> >    _preUpdateFunMap;
        std::map<int,std::function<void(SCNumberT* pNum,const T newNumber,const T oldNumber)> >    _postUpdateFunMap;
        std::function<SCString(const T num)>      _funGetString;
    };
    
    
    template<>
    class SCNumberT<bool>
    {
    public:
        SCNumberT():
        _number(false),
        _nIDCounter(0)
        {
        }
        
        SCNumberT(const bool num):
        _number(num),
        _nIDCounter(0)
        {
        }
        
        SCNumberT(const SCNumberT& num):
        _number(num._number),
        _nIDCounter(0)
        {
        }
        
        inline operator bool() const {return _number;}
        inline bool operator==(const bool num) { return _number==num; }
        inline bool operator!=(const bool num) { return _number!=num; }
        
        SCNumberT& operator=(const bool num)
        {
            const bool oldNum = _number;
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            if(bDiff)
            {
                this->firePreUpdateFun(num,oldNum);
            }
            
            _number = num;

            if(bDiff)
            {
                this->firePostUpdateFun(num,oldNum);
            }
            
            return *this;
        }
        
        
        int addPreUpdateFun(const std::function<void(bool newNumber,bool oldNumber)>& fun)
        {
            ++_nIDCounter;
            _preUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        int addPosUpdateFun(const std::function<void(bool newNumber,bool oldNumber)>& fun)
        {
            ++_nIDCounter;
            _postUpdateFunMap[_nIDCounter] = fun;
            return _nIDCounter;
        }
        
        void removeUpdateFun(const int nID,bool bPost)
        {
            if(bPost)
            {
                _postUpdateFunMap.erase(nID);
            }
            else
            {
                _preUpdateFunMap.erase(nID);
            }
        }
        
        void firePreUpdateFun(const bool newNumber,const bool oldNumber)
        {
            for(const auto& it : _preUpdateFunMap)
            {
                it.second(newNumber,oldNumber);
            }
        }
        
        void firePostUpdateFun(const bool newNumber,const bool oldNumber)
        {
            for(const auto& it : _postUpdateFunMap)
            {
                it.second(newNumber,oldNumber);
            }
        }

        
        inline bool getNumber() const {return _number;}
        
    private:
        bool                   _number;
        int                 _nIDCounter;
        std::map<int,std::function<void(const bool newNumber,const bool oldNumber)> >    _preUpdateFunMap;
        std::map<int,std::function<void(const bool newNumber,const bool oldNumber)> >    _postUpdateFunMap;
    };
    
    SC_DEFINE_NUMBER_GLOBAL1(+,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(-,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(*,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(/,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(%,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(^,SCNumberT<T>)
    SC_DEFINE_NUMBER_GLOBAL1(&,SCNumberT<T>)
    
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
    

    typedef SCNumberT<short>                        SCShort;
    typedef SCNumberT<unsigned short>               SCUnsignedShort;
    typedef SCNumberT<char>                         SCChar;
    typedef SCNumberT<unsigned char>                SCByte;
    typedef SCNumberT<int>                          SCInt;
    typedef SCNumberT<unsigned int>                 SCUnsignedInt;
    typedef SCNumberT<long>                         SCLong;
    typedef SCNumberT<unsigned long>                SCUnsignedLong;
    typedef SCNumberT<INT64>                        SCInt64;
    typedef SCNumberT<float>                        SCFloat;
    typedef SCNumberT<double>                       SCDouble;
    typedef SCNumberT<bool>                         SCBool;
}

#endif // __SPEEDCC__SCNUMBERT_H__
