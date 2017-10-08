//


#ifndef __SC__TEMPLATEUTILS_H__
#define __SC__TEMPLATEUTILS_H__

#include "SCTemplateDef.h"
#include "SCMacroDef.h"
#include "SCMemAllocator.h"

namespace SpeedCC
{
    template<typename T,bool isClass=(std::is_class<T>::value || SCIsEmptyClassT<T>::value || SCIsNullClassT<T>::value) >
    struct SCDataTypeLifeCycle
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
    struct SCDataTypeLifeCycle<T,false>
    {
        static void construct(void* p){}
        static int destroy(void* p){return 0;}
    };
    
}



#endif // __SC__TEMPLATEUTILS_H__
