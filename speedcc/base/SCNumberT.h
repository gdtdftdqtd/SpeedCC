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
        return this->getNumber() _opr_ num;\
    }
    
#define SC_DEFINE_NUMBER_CONSTRUCTOR(_type_) \
    SCNumberT(const _type_ num) {\
        this->createInstance();\
        this->getNumber() = (T)(num);\
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
        return num1 _opr_ num2.getNumber();\
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
        T2 ret = num1 _opr2_ num;\
        num1 = ret;\
        return ret;\
    }
    
#define SC_DEFINE_NUMBER_OPERATOR2(_opr1_,_opr2_) \
    template<typename T2>\
    SCNumberT& operator _opr1_ (const T2 num) {\
        const T oldNum = this->getNumber();\
        const T2 ret = this->getNumber() _opr2_ num;\
        const bool bSame = (this->getNumber() == ret);\
        if(bSame){\
            return *this;\
        }\
        if(!this->getStub()->firePreUpdateFun(num,oldNum)){\
            return *this;\
        }\
        this->clone4Write();\
        *this = ret;\
        this->getStub()->firePostUpdateFun(num,oldNum);\
        return *this;\
    }
    
    template<typename T>
    struct SCNumberStub
    {
        SCNumberStub():
        number(0),
        nIDCounter(0)
        {}
        
        T                   number;
        int                 nIDCounter;
        std::map<int,std::function<bool(const T newNumber,const T oldNumber)> >    preUpdateFunMap;
        std::map<int,std::function<void(const T newNumber,const T oldNumber)> >    postUpdateFunMap;
        
        int addPreUpdateFun(const std::function<bool(T newNumber,T oldNumber)>& fun)
        {
            ++nIDCounter;
            preUpdateFunMap[nIDCounter] = fun;
            return nIDCounter;
        }
        
        int addPosUpdateFun(const std::function<void(T newNumber,T oldNumber)>& fun)
        {
            ++nIDCounter;
            postUpdateFunMap[nIDCounter] = fun;
            return nIDCounter;
        }
        
        void removeUpdateFun(const int nID,bool bPost)
        {
            if(bPost)
            {
                postUpdateFunMap.erase(nID);
            }
            else
            {
                preUpdateFunMap.erase(nID);
            }
        }
        
        bool firePreUpdateFun(const T newNumber,const T oldNumber)
        {
            bool bRet = true;
            for(const auto& it : preUpdateFunMap)
            {
                if(!it.second(newNumber,oldNumber))
                {
                    bRet = false;
                }
            }
            
            return bRet;
        }
        
        void firePostUpdateFun(const T newNumber,const T oldNumber)
        {
            for(const auto& it : postUpdateFunMap)
            {
                it.second(newNumber,oldNumber);
            }
        }
    };
    
    template<typename T,typename = typename std::enable_if<std::is_arithmetic<T>::value,T>::type>
    class SCNumberT : public SCObjRefT<SCNumberStub<T>,int>
    {
    public:
        SCNumberT()
        {
            this->createInstance();
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
        
        inline operator int() const {return (int)this->getNumber();}
        inline operator unsigned int() const {return (unsigned int)this->getNumber();}
        inline operator long() const {return (long)this->getNumber();}
        inline operator unsigned long() const {return (unsigned long)this->getNumber();}
        inline operator char() const {return (char)this->getNumber();}
        inline operator unsigned char() const {return (unsigned char)this->getNumber();}
        inline operator INT64() const {return (INT64)this->getNumber();}
        inline operator float() const {return (float)this->getNumber();}
        inline operator double() const {return (double)this->getNumber();}
        
        inline bool operator<(const T num) { return this->getNumber()<num; }
        inline bool operator<=(const T num) { return this->getNumber()<=num; }
        inline bool operator>(const T num) { return this->getNumber()>num; }
        inline bool operator>=(const T num) { return this->getNumber()>=num; }
        inline bool operator==(const T num) { return this->getNumber()==num; }
        inline bool operator!=(const T num) { return this->getNumber()!=num; }
        
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
        SCNumberT& operator=(const T2 num)
        {
            const T oldNum = this->getNumber();
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            if(bDiff)
            {
                if(!this->getStub()->firePreUpdateFun(num,oldNum))
                {
                    return *this;
                }
            }
            
            this->getNumber() = num;
            
            if(bDiff)
            {
                this->getStub()->firePostUpdateFun(num,oldNum);
            }
            
            return *this;
        }
        
        // prefix ++ (++a)
        SCNumberT& operator++(){
            this->clone4Write();
            this->getNumber() += 1;
            return *this;
        }
        
        SCNumberT operator++(T)  // postfix ++ (a++)
        {
            SCNumberT result(*this);
            ++(*this);
            return result;
        }
        
        // prefix -- (--a)
        SCNumberT& operator--(){
            this->clone4Write();
            this->getNumber() -= 1;
            return *this;
        }
        
        SCNumberT operator--(T)  // postfix -- (a--)
        {
            SCNumberT result(*this);
            --(*this);
            return result;
        }
        
        inline T getNumber() const {return this->getStub()->number;}
        
        int addPreUpdateFun(const std::function<bool(T newNumber,T oldNumber)>& fun)
        {
            this->getStub()->addPreUpdateFun(fun);
        }
        
        int addPosUpdateFun(const std::function<void(T newNumber,T oldNumber)>& fun)
        {
            this->getStub()->addPosUpdateFun(fun);
        }
        
        void removeUpdateFun(const int nID,bool bPost)
        {
            this->getStub()->removeUpdateFun(nID,bPost);
        }
        
    private:
        inline T& getNumber() { return this->getStub()->number; }
    };
    
    template<>
    class SCNumberT<bool> : public SCObjRefT<SCNumberStub<bool>,int>
    {
    public:
        SCNumberT()
        {
            this->createInstance();
        }
        
        SCNumberT(const bool num)
        {
            this->createInstance();
            this->getNumber() = (num);
        }
        
        inline operator bool() const {return this->getNumber();}
        inline bool operator==(const bool num) { return this->getNumber()==num; }
        inline bool operator!=(const bool num) { return this->getNumber()!=num; }
        
        SCNumberT& operator=(const bool num)
        {
            const bool oldNum = this->getNumber();
            bool bDiff = (oldNum!=num);
            
            if(!bDiff) {return *this;}
            
            if(bDiff)
            {
                if(!this->getStub()->firePreUpdateFun(num,oldNum))
                {
                    return *this;
                }
            }
            
            this->getNumber() = num;

            if(bDiff)
            {
                this->getStub()->firePostUpdateFun(num,oldNum);
            }
            
            return *this;
        }
        
        inline bool getNumber() const {return this->getStub()->number;}
        
    private:
        inline bool& getNumber() { return this->getStub()->number; }
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
