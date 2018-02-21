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


#ifndef __SPEEDCC__SCTEMPLATEUTILS_H__
#define __SPEEDCC__SCTEMPLATEUTILS_H__

#include <functional>
#include "SCTemplateDef.h"
#include "SCMacroDef.h"
#include "SCMemAllocator.h"

namespace SpeedCC
{
    template<typename T,bool isClass=(std::is_class<T>::value || SCIsEmptyClassT<T>::value || SCIsNullClassT<T>::value) >
    struct SCDataTypeLifeCycleT
    {
        static void construct(void* p) {new(p)T();}
        
        template<typename A1>
        static void construct(void* p,A1 arg1) {new(p)T(arg1);}
        
        template<typename A1,typename A2>
        static void construct(void* p,A1 arg1,A2 arg2) {new(p)T(arg1,arg2);}
        
        template<typename A1,typename A2,typename A3>
        static void construct(void* p,A1 arg1,A2 arg2,A3 arg3) {new(p)T(arg1,arg2,arg3);}
        
        static int destroy(void* p) {((T*)p)->~T(); return sizeof(T);}
    };
    
    template<typename T>
    struct SCDataTypeLifeCycleT<T,false>
    {
        static void construct(void* p){}
        static int destroy(void* p){return 0;}
    };
    
    
    template<int n>
    struct SCBindFuncUtilsT
    {
        template<typename T1, typename T2>
        static int makeFunc(T1 t1, T2 t2)
        {
            return 0;
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<0>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2);
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<1>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2,std::placeholders::_1);
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<2>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2,std::placeholders::_1,std::placeholders::_2);
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<3>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3);
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<4>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2,
                             std::placeholders::_1,
                             std::placeholders::_2,
                             std::placeholders::_3,
                             std::placeholders::_4);
        }
    };
    
    template<>
    struct SCBindFuncUtilsT<5>
    {
        template<typename T1, typename T2, typename ...Ts>
        static std::function<T1(Ts...)> makeFunc(T1(T2::*pfunc)(Ts ...),T2* t2)
        {
            return std::bind(pfunc,t2,
                             std::placeholders::_1,
                             std::placeholders::_2,
                             std::placeholders::_3,
                             std::placeholders::_4,
                             std::placeholders::_5);
        }
    };
    
}



#endif // __SPEEDCC__SCTEMPLATEUTILS_H__
